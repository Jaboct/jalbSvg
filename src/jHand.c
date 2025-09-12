#include "jHand.h"


/** Includes */

#include "jGroup.h"
#include "jPath.h"
#include "svg.h"
#include "path.h"

#include "jEvent.h"
#include "jEvent_path.h"
#include "event_sb.h"

#include "jRender.h"

#include "complexEle_ext.h"

#include "hover.h"

#include "cursor.h"


/** Variables */

extern char altKeys[];

extern float colorWhite[];
extern float colorBlack[];

extern struct draw2dStruct *draw2dApi;

extern struct jalbFont *fonts[];
extern int numFonts;

// uiGen
struct uiGen_api *uiGen_api = NULL;


// cursor
extern ArrayList *cursorList;
extern int cursor_depth;

extern int cursorInputMode;

// text cursor info.
int cStart[3];
int cEnd[3];


//struct jvg *glob_jvg = NULL;
extern struct jvg *glob_jvg;
//ArrayList *global_jEles = NULL; // (struct jNakedUnion*)
extern ArrayList *global_jEles; // (struct jNakedUnion*)
struct jNakedUnion *tempEle = NULL;

char saveDir[256] = "";

extern float glob_viewScale;
extern float glob_viewLoc[];


extern int renderCAD;
extern int gridRender;
extern int gridSnap;
extern float gridWH[];

// debug
int debugPrint_jvg_render = 0;
extern int debugPrint_jvg_event;

extern int debugPrint_jvg_complex_render;

extern int svg_debugPrint_render_text;



int tabW = 8;
int ctrlMemLast = -1;


// more cursor
extern int selected;
extern int mouseHeld;
int heldType = 0;
float heldStart[2];	// what is this
//float cursorWorldLoc[2] = { 0, 0 };
extern int thisSel; // used during rendering to figure if the ele, or a subEle, being rendered is currently selected.

// this is relative to the elements top left position, not to the entire window.
int cursorScreenXY[2];

// new cursor stuff
extern struct cursor_ele *glob_cursor_ele;
extern struct cursor_ele *temp_actualMem;
// cursor hover
extern int isHover;
extern struct cursor_ele *hoverMem;
extern struct cursor_ele *temp_hoverMem;

extern struct cursor_ele *temp_clickMem_parent;
extern struct cursor_ele *temp_clickMem;



extern int renderMode;

int vert_subMode = 0;


// for text box ctrl jumping.
extern ArrayList *glob_ctrlKeys;


// this aint right
char *workspaceDir_jalbJvg = "/home/jadeb/workspace/jHigh/jalbSvg/";



/** Functions */

void *jalbJvg_init ( ) {
	return NULL;
}

void jalbJvg_render ( int *screenDims, GLuint *glBuffers, int *XYWH, void *data ) {
	printf ( "jalbJvg_render ( )\n" );
	if ( !global_jEles ) {
		global_jEles = initArrayList ( 10, sizeof ( struct jNakedUnion* ), 10 );
	}
}

int jalbJvg_event ( SDL_Event *e, int *clickXY, int *eleWH, void *data ) {
	return 0;
}

int render_todo_done = 0;
int screenDim_mem[2];

void jalbJvg_renderDyn ( int *screenDims, GLuint *glBuffers, int *XYWHpass, void *data,
		float *viewLoc, float viewScale ) {
	if ( debugPrint_jvg_render ) {
		printf ( "jalbJvg_renderDyn ( )\n" );
		svg_debugPrint_render_text = 1;
	}


	if ( !glob_ctrlKeys ) {
		// TODO, this should be imported, i think its in Layout.
//		char *line = " \n\t.,/\\<>{}[]():;\"\'|_-+=~`!@#$%^&*?";
		char *line = " \\n\\t.,/\\\\<>{}[]():;\\\"\\\'|_-+=~`!@#$%^&*?";
		jKeyCtrl ( line, NULL );
	}

	if ( !render_todo_done ) {
		screenDim_mem[0] = screenDims[0];
		screenDim_mem[1] = screenDims[1];
		firstRender_todo ( );
		render_todo_done = 1;
	}

	if ( !glob_jvg ) {
		glob_jvg = jvgInit ( );
		global_jEles = glob_jvg->eles;
	}
	if ( !global_jEles ) {
		global_jEles = initArrayList ( 10, sizeof ( struct jNakedUnion* ), 10 );
	}
	if ( !cursorList ) {
		cursorList = initArrayList ( 10, sizeof ( struct cursorMem* ), 10 );
	}

	viewScale = 1.0 / viewScale;

	glob_viewLoc[0] = viewLoc[0];
	glob_viewLoc[1] = viewLoc[1];

	glob_viewScale = viewScale;

//	sayIntArray ( "XYWHpass", XYWHpass, 4 );

	if ( gridRender ) {
		// draw grid lines
		grid_render ( screenDims, glBuffers, XYWHpass, gridWH,
			viewLoc, viewScale );
	}
	if ( gridSnap ) {
		// draw an x at the grid position closest to the cursor.
		grid_render_cursor ( screenDims, glBuffers, XYWHpass, gridWH,
			viewLoc, viewScale, cursorScreenXY );
	}


	if ( !glob_cursor_ele ) {
		init_jvg_cursor ( );
	}
	temp_actualMem = glob_cursor_ele;

	if ( isHover ) {
		temp_hoverMem = hoverMem;
	} else {
		temp_hoverMem = NULL;
	}


	thisSel = selected;
	cursor_depth = 0;


	thisSel = 0;
	jNakedList_render ( screenDims, glBuffers, XYWHpass, glob_jvg->eles,
		viewLoc, viewScale );

	if ( tempEle ) {
		jNaked_render ( screenDims, glBuffers, XYWHpass, tempEle,
			viewLoc, viewScale );
	}

/** TODO im  not sure what this is.
	// if the cursor is held, render the box represnting the selction area.
	if ( mouseHeld &&
	     heldType == ht_highlight ) {
		// get the cursor loc.
		int XYWH[4];

		float screenXY[2];
		point_to_loc ( heldStart, screenXY, viewLoc, viewScale );
		screenXY[0] += XYWHpass[0];
		screenXY[1] += XYWHpass[1];

		XYWH[0] = screenXY[0];
		XYWH[1] = screenXY[1];

		point_to_loc ( cursorWorldLoc, screenXY, viewLoc, viewScale );
		screenXY[0] += XYWHpass[0];
		screenXY[1] += XYWHpass[1];

		XYWH[2] = screenXY[0] - XYWH[0];
		XYWH[3] = screenXY[1] - XYWH[1];

		draw2dApi->drawRect ( XYWH, colorWhite, screenDims, glBuffers );
	}
*/

	/// at the top render the save dir
	int XYWH[4] = {
		XYWHpass[0],
		XYWHpass[1],
		XYWHpass[2],
		fonts[0]->atlasInfo.glyphH + 4,
	};
	draw2dApi->fillRect ( XYWH, colorBlack, screenDims, glBuffers );

	// draw save dir
	draw2dApi->drawCharPre ( fonts[0], colorWhite );
	draw2dApi->drawString ( screenDims, glBuffers, XYWH, fonts[0], saveDir );

	// on the right side, draw the current viewMode.
	char *editStr = "";
	if ( renderMode == renderM_view ) {
		editStr = "view";
	} else if ( renderMode == renderM_editAll ) {
		editStr = "edit all";
	} else if ( renderMode == renderM_edit ) {
		editStr = "edit one";
	}
	XYWH[0] += XYWH[2] - fonts[0]->atlasInfo.glyphW * strlen ( editStr );
	draw2dApi->drawCharPre ( fonts[0], colorWhite );
	draw2dApi->drawString ( screenDims, glBuffers, XYWH, fonts[0], editStr );

	// draw a white line
	XYWH[0] = XYWHpass[0];
	XYWH[1] += XYWH[3] - 1;
	XYWH[3] = 1;
	draw2dApi->fillRect ( XYWH, colorWhite, screenDims, glBuffers );


	if ( debugPrint_jvg_render ) {
		printf ( "jalbJvg_renderDyn ( ) OVER\n" );
	}
}

int jalbJvg_mEvent ( SDL_Event *e, int *clickXYpass, int *eleWH, void *data,
		float *viewLoc, float viewScale ) {

	if ( debugPrint_jvg_event ) {
		printf ( "jalbJvg_mEvent ( )\n" );
		printf ( "selected: %d\n", selected );
		sayIntArray ( "clickXYpass", clickXYpass, 2 );
	}

	int ret = 0;

	if ( !glob_jvg ) {
		glob_jvg = jvgInit ( );
		global_jEles = glob_jvg->eles;
	}

	// clickXYpass is relative to the element, not to the screen.
	cursorScreenXY[0] = clickXYpass[0];
	cursorScreenXY[1] = clickXYpass[1];

	viewScale = 1.0 / viewScale;

	struct jvg *jvgEle = glob_jvg;
	ArrayList *eles = jvgEle->eles;

	if ( gridSnap ) {
		float screenXY[2] = {
			clickXYpass[0],
			clickXYpass[1],
		};
		float worldXY[2];
		screen_to_world ( screenXY, worldXY, viewLoc, viewScale );
		// round to nearest

		worldXY[0] = roundClose ( worldXY[0], gridWH[0] );
		worldXY[1] = roundClose ( worldXY[1], gridWH[1] );

		world_to_screen ( worldXY, screenXY, viewLoc, viewScale );
		clickXYpass[0] = screenXY[0];
		clickXYpass[1] = screenXY[1];
	}


	if ( e->type == SDL_KEYDOWN ) {
		ret = jalbJvg_keyDown ( e, clickXYpass, eleWH, jvgEle,
			viewLoc, viewScale );

	} else if ( e->type == SDL_MOUSEBUTTONDOWN ) {
		if ( renderMode != renderM_editAll &&
		     renderMode != renderM_edit ) {
			return 0;
		}

		ret = jalbJvg_mDown ( e, clickXYpass, eleWH, jvgEle,
			viewLoc, viewScale );

	} else if ( e->type == SDL_MOUSEBUTTONUP ) {
		mouseHeld = 0;

		// if left mouse button is down, then held is still true.
		int XY[2];
		Uint32 state = SDL_GetMouseState ( &XY[0], &XY[1] );
		if ( ( state & SDL_BUTTON_LMASK ) != 0 ) {
			mouseHeld = 1;
		} else {
			heldType = ht_none;
		}

		if ( tempEle ) {
			printf ( "BUTTON UP ADD TEMP ELE\n" );
			arrayListAddEndPointer ( eles, tempEle );
			tempEle = NULL;
		}

	} else if ( e->type == SDL_MOUSEMOTION ) {
//		printf ( "selected: %d\n", selected );
//		printf ( "mouseHeld: %d\n", mouseHeld );


		ret = jalbJvg_mMotion ( e, clickXYpass, eleWH, jvgEle,
			viewLoc, viewScale );

	}

	functEnd:;

	if ( debugPrint_jvg_event ) {
		printf ( "jalbJvg_mEvent ( ) OVER\n" );
	}


	return ret;
}



void jalbJvg_close ( void *data ) {
}


/** Other */

void hand_doStuff ( ) {
	printf ( "hand_doStuff ( )\n" );

	printf ( "global_jEles: %p\n", global_jEles );

	// load a svg from a dir, then go into ele[0], which is a group.
	// iterate it, look for every path.
	// convert them all into jPath, and add them to my global_jEles.
	// then render the globalJEles.

	// first lets just init a path by hand.

	struct jNakedUnion *jNake = jNakedUnionInit ( );
	arrayListAddEndPointer ( global_jEles, jNake );

	jNakedUnionTypeChange0 ( jNake, jNaked_Path );
	printf ( "jNake: %p\n", jNake );
	printf ( "jNake->type: %d\n", jNake->type );
	struct jPath *path = jNake->path;

	struct jVert *vert = jVertInit ( );
	arrayListAddEndPointer ( path->verts, vert );
	vert->XY[0] = 0;
	vert->XY[1] = 0;

	vert = jVertInit ( );
	arrayListAddEndPointer ( path->verts, vert );
	vert->XY[0] = 100;
	vert->XY[1] = 0;

	struct jLine *line = jLineInit ( );
	arrayListAddEndPointer ( path->lines, line );
	line->type = path_LineTo;
	line->v0 = 0;
	line->v1 = 1;

	printf ( "hand_doStuff ( )\n" );
}


extern int num_structStruct_jalbSvg;
extern struct xmlFuncts *xmlFuncts_arr_jalbSvg[];

void hand_doStuff2 ( char *dir ) {
	struct svg *svgEle = loadXmlFile_03 ( dir, xmlFuncts_arr_jalbSvg, num_structStruct_jalbSvg );

	convert_list ( svgEle->eles );
/*
	struct nakedUnion *uni = arrayListGetPointer ( svgEle->eles, 0 );
	printf ( "uni->type: %d\n", uni->type );
	if ( uni->type == G ) {
		struct g *g = uni->g;
		convert_list ( g->eles );
	}
*/
}

void convert_list ( ArrayList *uniList ) {
	printf ( "convert_list ( )\n" );
	printf ( "uniList: %p\n", uniList );

	int i;
	int len;

	i = 0;
	len = arrayListGetLength ( uniList );

	printf ( "uniList.len: %d\n", len );

	while ( i < len ) {
		struct nakedUnion *uni = arrayListGetPointer ( uniList, i );
		printf ( "[%d]: %d\n", i, uni->type );

		if ( uni->type == G ) {
			struct g *g = uni->g;

			convert_list ( g->eles );
		} else if ( uni->type == Path ) {
			struct path *path = uni->path;

			struct jNakedUnion *jNake = jNakedUnionInit ( );
			arrayListAddEndPointer ( global_jEles, jNake );

			jNakedUnionTypeChange0 ( jNake, jNaked_Path );
			struct jPath *jPath = path_to_jPath ( path );
			jNake->path = jPath;
		}
		i += 1;
	}
}

struct jPath *path_to_jPath ( struct path *path ) {
	struct jPath *jPath = jPathInit ( );

	// i can simply convert each ele into a vert and a line.
	// maybe after that do a 

	int numEles = arrayListGetLength ( path->eles );

	int i;

	i = 0;
	while ( i < numEles ) {
		struct pathUni *uni = arrayListGetPointer ( path->eles, i );

		if ( uni->type == path_MoveTo ) {
			// its just a vert
			struct moveTo *moveTo = uni->moveTo;

			struct jVert *vert = jVertInit ( );
			arrayListAddEndPointer ( jPath->verts, vert );
			vert->XY[0] = moveTo->XY[0];
			vert->XY[1] = moveTo->XY[1];
		} else {
			// its a vert and a line.

			struct jVert *vert = jVertInit ( );
			struct jLine *line = jLineInit ( );

			if ( uni->type == path_LineTo ) {
				struct lineTo *lineTo = uni->lineTo;

				vert->XY[0] = lineTo->XY[0];
				vert->XY[1] = lineTo->XY[1];

				line->type = path_LineTo;

			} else if ( uni->type == path_CubicBez ) {
				struct cubicBez *cubic = uni->cubicBez;

				vert->XY[0] = cubic->XY[0];
				vert->XY[1] = cubic->XY[1];

				line->type = path_CubicBez;

				line->c0[0] = cubic->c0[0];
				line->c0[1] = cubic->c0[1];

				line->c1[0] = cubic->c1[0];
				line->c1[1] = cubic->c1[1];
			} else if ( uni->type == path_QuadBez ) {
				struct quadBez *quad = uni->quadBez;

				vert->XY[0] = quad->XY[0];
				vert->XY[1] = quad->XY[1];

				line->type = path_QuadBez;
				line->c0[0] = quad->control[0];
				line->c0[1] = quad->control[1];
			} else {
				printf ( "ERROR UNHANDLED TYPE\n" );
				i += 1;
				continue;
			}

			line->v0 = i - 1;
			line->v1 = i;

			arrayListAddEndPointer ( jPath->verts, vert );
			arrayListAddEndPointer ( jPath->lines, line );
		}

		i += 1;
	}

//	printf ( "verts.len: %d\n", arrayListGetLength ( jPath->verts ) );
//	printf ( "lines.len: %d\n", arrayListGetLength ( jPath->lines ) );

	say_jPath ( jPath );

	return jPath;
}

void say_jPath ( struct jPath *path ) {
	printf ( "say_jPath ( )\n" );
//	printf ( "path: %p\n", path );

	int numVerts = arrayListGetLength ( path->verts );
	int numLines = arrayListGetLength ( path->lines );

	printf ( "verts.len: %d\n", numVerts );
	printf ( "lines.len: %d\n", numLines );

	int i;

	printf ( "verts:\n" );
	i = 0;
	while ( i < numVerts ) {
		struct jVert *v = arrayListGetPointer ( path->verts, i );
		sayFloatArray ( "", v->XY, 2 );

		i += 1;
	}

	printf ( "lines:\n" );
	i = 0;
	while ( i < numLines ) {
		struct jLine *l = arrayListGetPointer ( path->lines, i );
		printf ( "{ %d, %d }\n", l->v0, l->v1 );

		i += 1;
	}
}

/** Save and Load */


extern int len_backbone_arr_jalbJvg;
extern struct backbone_structStruct *backbone_arr_jalbJvg[];

extern int jvg_attributes[];
extern struct backbone_structStruct backboneStru_jvg;

extern int num_structStruct_jalbJvg;
extern struct xmlFuncts *xmlFuncts_arr_jalbJvg[];


void jHand_save ( ) {
	printf ( "jHand_save ( )\n" );

	if ( saveDir[0] != '\0' ) {
		jalbJvg_glob_save ( saveDir );
	} else {
		char *dir = "/home/jadeb/workspace/jHigh/jalbSvg/res/jvg/test_00.xml";
		jalbJvg_glob_save ( dir );
	}

	printf ( "jHand_save ( ) OVER\n" );
}

void jalbJvg_glob_save ( char *dir ) {
	printf ( "jalbJvg_save ( )\n" );
	printf ( "dir: %s\n", dir );

	jalbJvg_save ( glob_jvg, dir );

	printf ( "jalbJvg_save ( ) OVER\n" );
}

void jalbJvg_save ( struct jvg *jvgEle, char *dir ) {
	printf ( "jalbJvg_save ( )\n" );
	printf ( "jvgEle: %p\n", jvgEle );

	jvgPreSave ( jvgEle );
	fwriteXml_backbone ( dir, &backboneStru_jvg, jvgEle,
		jvg_attributes, backbone_arr_jalbJvg, len_backbone_arr_jalbJvg );
}

void jHand_load ( ) {
	printf ( "jHand_load ( )\n" );

	char *dir = "/home/jadeb/workspace/jHigh/jalbSvg/res/jvg/test_00.xml";

	jalbJvg_load ( dir );
}

void jalbJvg_load_global ( char *dir ) {
	struct jvg *jvgEle = jalbJvg_load ( dir );
	printf ( "jvgEle: %p\n", jvgEle );
//	printf ( "jvgEle->eles.len: %d\n", arrayListGetLength ( jvgEle->eles ) );

	if ( jvgEle ) {
		glob_jvg = jvgEle;

		global_jEles = glob_jvg->eles;
	}

	strcpy ( saveDir, dir );
}

void *jalbJvg_load ( char *dir ) {
	printf ( "jalbJvg_load ( )\n" );

	struct jvg *jvgEle = loadXmlFile_03 ( dir, xmlFuncts_arr_jalbJvg, num_structStruct_jalbJvg );

	printf ( "jalbJvg_load ( ) OVER\n" );

	return jvgEle;
}

void *get_jalbJvg_load ( ) {
	printf ( "get_jalbJvg_load ( )\n" );

	return jalbJvg_load;
}


/** Debug */

void toggle_debugPrint_jvg_render ( ) {
	printf ( "toggle_debugPrint_jvg_render ( )\n" );

	if ( debugPrint_jvg_render ) {
		debugPrint_jvg_render = 0;
	} else {
		debugPrint_jvg_render = 1;
	}
}

void set_debugPrint_jvg_render ( int i ) {
	printf ( "set_debugPrint_jvg_render ( )\n" );
	printf ( "i: %d\n", i );

	debugPrint_jvg_render = i;
	debugPrint_jvg_complex_render = i;

	printf ( "set_debugPrint_jvg_render ( ) OVER\n" );
}

extern int debugPrint_jvg_event;

void set_debugPrint_jvg_event ( int i ) {
	printf ( "set_debugPrint_jvg_event ( )\n" );
	printf ( "i: %d\n", i );

	debugPrint_jvg_event = i;

	printf ( "set_debugPrint_jvg_event ( ) OVER\n" );
}

/** Other stuff */


void UTF_stuff ( ) {
	printf ( "UTF_stuff ( )\n" );

	// https://lists.freedesktop.org/archives/fontconfig/2013-September/004915.html

	int val = 0x2202;
	printf ( "val x: %x\n", val );
	printf ( "val d: %d\n", val );

	/// first astersik

	int row = val / 0xff;
	printf ( "row x: %x\n", row );

	// ampersand to get remainder.
	// could do val % 250 or val % 0x100 instead.
	int remain = val & 0xff;
	printf ( "remain x: %x\n", remain );
	printf ( "remain d: %d\n", remain );

	int map = 0x46260044;
//	char mapStr[8] = "46260044";
	/// second asterisk
	// could do remain & 0x20 instead???
	int remain2 = remain % 32;
	printf ( "remain2 x: %x\n", remain2 );
	printf ( "remain2 d: %d\n", remain2 );

	// third asterisk
	int remain3 = remain2 / 0xf;
	printf ( "remain3 x: %x\n", remain3 );
	printf ( "remain3 d: %d\n", remain3 );

	// its 0 so its the least sig digit of the block.
	int sigDig = map & 0xf;
	printf ( "sigDig x: %x\n", sigDig );
	printf ( "sigDig d: %d\n", sigDig );

	// if it was 1, then what do i do?
	int remain4 = remain2 % 0xf;
	printf ( "remain4 x: %x\n", remain4 );
	printf ( "remain4 d: %d\n", remain4 );

	exit ( 12 );
}

// relies on the global cStart[]
void add_special ( ArrayList *sb, int index ) {
	char *str = NULL;

	if ( index == spec_therefore ) {	// Math Characters
		// therefore
		char str1[] = { 0xE2, 0x88, 0xB4, 00 };
		str = str1;
	} else if ( index == spec_and ) {
		// and
		char str1[] = { 0xE2, 0x88, 0xA7, 00 };
		str = str1;
	} else if ( index == spec_or ) {
		// or
		char str1[] = { 0xE2, 0x88, 0xA8, 00 };
		str = str1;
	} else if ( index == spec_micro ) {
		char str1[] = { 0xC2, 0xB5, 00 };
		str = str1;
	} else if ( index == spec_emptySet ) {
		char str1[] = { 0xE2, 0x88, 0x85, 00 };
		str = str1;

	} else if ( index == spec_integral ) {
		// omega (lower)
		char str1[] = { 0xE2, 0x88, 0xAB, 0x00 };
		str = str1;

	} else if ( index == spec_alphaL ) {	// Greek characters
		char str1[] = { 0xCE, 0xB1, 00 };
		str = str1;
	} else if ( index == spec_betaL ) {
		char str1[] = { 0xCE, 0xB2, 00 };
		str = str1;
	} else if ( index == spec_deltaU ) {
		char str1[] = { 0xCE, 0x94, 00 };
		str = str1;
	} else if ( index == spec_deltaL ) {
		char str1[] = { 0xCE, 0xB4, 00 };
		str = str1;
	} else if ( index == spec_thetaL ) {
		char str1[] = { 0xCE, 0xB8, 00 };
		str = str1;
	} else if ( index == spec_lambdaL ) {
		char str1[] = { 0xCE, 0xBB, 00 };
		str = str1;
	} else if ( index == spec_pi ) {
		char str1[] = { 0xCF, 0x80, 00 };
		str = str1;
	} else if ( index == spec_rhoL ) {
		char str1[] = { 0xCF, 0x81, 00 };
		str = str1;
	} else if ( index == spec_omegaU ) {
		// omega (lower)
		char str1[] = { 0xCE, 0xA9, 0x00 };
		str = str1;
	} else if ( index == spec_omegaL ) {
		// omega (lower)
		char str1[] = { 0xCF, 0x89, 0x00 };
		str = str1;
	}

	if ( !str ) {
		return;
	}

//	char str[] = { 'a', 'b', 'c' };
/*
	if ( cursorStartMem[0] != -1 ) {
			// ctrl is not pressed, and its a regular ascii character.

			if ( altKeys[akShift] ) {
				key = shiftKeys ( key );
			}

			highlightRemove ( sb, cursorStartMem, cursorEndMem, undoMem );

			if ( undoMem ) {
				undoCheck ( undoMem, key, 0, sb, cursorStartMem );
			}

			arrayListAdd ( sb, cursorStartMem[0], &key );
			cursorStartMem[0] += 1;
			cursorEndMem[0] = cursorStartMem[0];

//			sbIndexToCoords ( cursorStartMem[0], &cursorStartMem[1], sb, eleWH );
			newSbIndexToCoords ( cursorStartMem[0], &cursorStartMem[1], sb, wrap, maxCols, tabW );
		}
*/

	int spot = cStart[0];

	int len = strlen ( str );
	int i;
	i = 0;
	while ( i < len ) {
		arrayListAdd ( sb, spot, &str[i] );

		spot += 1;

		i += 1;
	}

	cStart[0] += len;
	cStart[1] += 1;

	cEnd[0] = cStart[0];
}



/** Spread sheet stuff */

void make_spread_sheet ( ) {
	printf ( "make_spread_sheet ( )\n" );

//	int i = 2;

//	makeColumn ( 1, 0 );
//	makeColumn ( 3, 0 );

//	int numVars = 9;
//	unsigned char arr[2] = { 0, 0 };

	int numVars = 3;
	unsigned char arr[1] = { 0 };
	int numChars = (numVars - 1) / 8 + 1;

	int numRows = pow ( 2, numVars );
/*
	int i = 0;
	int len = numRows;
//	int len = 2;
	while ( i < len ) {
		makeRow ( arr, numVars );
		printf ( "\n" );

		iterateCharArr ( arr, numChars );
//		sayUCharArray_hex ( "arr", arr, numChars );

		i += 1;
	}
*/

	printf ( "p\t" );
	printf ( "q\t" );
	printf ( "r\t" );
	printf ( "~r\t" );
	printf ( "q V ~r\t" );
	printf ( "p ^ r\t" );
	printf ( "p -> q V ~r\t" );
	printf ( "q -> p ^ r\t" );
	printf ( "p -> r\t" );
	printf ( "\n" );

	int i;
	int len;

	// sometimes for looking in the console i want extra tabs.
	// if its going to a spreadsheet i dont want that.

	// hand make shit table
	i = 0;
	len = numRows;
	while ( i < len ) {
		// print column of vars.

		makeRow ( arr, numVars );
		printf ( "\t" );

		int p = !getCol ( arr, numVars - 0 );
		int q = !getCol ( arr, numVars - 1 );
		int r = !getCol ( arr, numVars - 2 );

//		printf ( "r: %d", r );

		// next column
		printVal ( !r );

		printVal ( q || !r );

		printVal ( p && r );

		// this is ifThen ( col0, col4 )
		printVal ( ifThen ( p, (q || !r) ) );
//		printf ( "\t" );

		printVal ( ifThen ( q, (p && r) ) );
//		printf ( "\t" );

		printVal ( ifThen ( p, r ) );


		iterateCharArr ( arr, numChars );

		printf ( "\n" );

		i += 1;
	}

	printf ( "make_spread_sheet ( ) OVER\n" );
//	exit ( 12 );
}

int ifThen ( int a, int b ) {
	if ( a ) {
		return b;
	} else {
		return 1;
	}
}

void printVal ( int i ) {
	if ( i ) {
		printf ( "T\t" );
	} else {
		printf ( "F\t" );
	}
}

int getCol ( unsigned char *arr, int i ) {
//	printf ( "getCol ( )\n" );
//	printf ( "i: %d\n", i );
	i -= 1;

//	int numChars = (numVars - 1) / 8 + 1;
	int c = i / 8;
	int b = i % 8;

	unsigned char copy = arr[c];
	copy = copy << (7 - b);

	if ( copy & 0x80 ) {
		// the highest bit is 1.
		return 1;
	} else {
		return 0;
	}
}

void comb ( int i, int n ) {
	printf ( "T\n" );
	printf ( "F\n" );
}


void makeColumn ( int numVars, int thisColumn ) {
	int numRows = pow ( 2, numVars );
	int numSwaps = pow ( 2, thisColumn + 1 );

	int range = 0;	// even range = true, odd range = false;

	int rowsPerSwap = numRows / numSwaps;

	int i = 0;
//	int len = numRows;
	while ( i < numSwaps ) {
		int j = 0;
		while ( j < rowsPerSwap ) {
			if ( range % 2 == 0 ) {
				printf ( "T\n" );
			} else {
				printf ( "F\n" );
			}
			j += 1;
		}
		range += 1;
		i += 1;
	}
}



void makeRowI ( int value, int numVars ) {
	// i need to understand sizeof more, its not necessarily 8 
//	int bitsPerInt = 8 * sizeof ( int );
}

int debugPrint_makeRow = 0;

// the arr should only be big enough to fit numVars, if its larger i need to change this function.
void makeRow ( unsigned char *arr, int numVars ) {
	if ( debugPrint_makeRow ) {
		printf ( "makeRow ( )\n" );
		printf ( "numVars: %d\n", numVars );
	}


	// instead of using 8 use CHAR_BIT? idk what a weird thing to care about.
	int numChars = (numVars - 1) / 8 + 1;

	if ( debugPrint_makeRow ) {
		printf ( "numChars: %d\n", numChars );
		sayUCharArray_hex ( "arr", arr, numChars );
	}


//	int c = numChars - 1;	// start by accessing the last char?
	int c = 0;
	// iterate char by char;

	int b = (numVars - 1) % 8;
	// iterate the char over, to the highest relevent bit of the last char.
	unsigned char copy = arr[c];
/*
	for ( int i = 7; i < b; i -= 1 ) {
		copy << 1
	}
*/
	if ( debugPrint_makeRow ) {
		printf ( "c: %d\n", c );
		printf ( "b: %d\n", b );
		printf ( "copy: %x\n", copy );
	}

	copy = copy << (7 - b);

//	printf ( "copy: %x\n", copy );

//	while ( c >= 0 ) {
	while ( c < numChars ) {
//		printf ( "copy: %x\n", copy );
		while ( b >= 0 ) {
			if ( copy & 0x80 ) {
				// the highest bit is 1.
				printf ( "F" );
			} else {
				printf ( "T" );
			}

			copy = copy << 1;

			if ( b > 0 ) {
				printf ( "\t" );
			}

			b -= 1;
		}

//		if ( c > 0 ) {
		if ( c + 1 < numChars ) {
			copy = arr[c + 1];
			printf ( "\t" );
		}

//		c -= 1;
		c += 1;
		b = 7;
	}
}

/*
// unit test for iterateCharArray
//	int numChars = 2;
//	unsigned char arr[2] = { 0, 0 };
	int numChars = 3;
	unsigned char arr[3] = { 0, 0xFF, 0xF0 };

	int i = 0;
	while ( i < 300 ) {
		printf ( "[%d] ", i );
		sayUCharArray_hex ( "arr", arr, numChars );

		iterateCharArr ( arr, numChars );

		i += 1;
	}
*/

// this seems to work well.
void iterateCharArr ( unsigned char *arr, int numChars ) {
	int i = 0;
	int len = numChars;
	while ( i < len ) {
		if ( arr[numChars - i - 1] == 0xFF ) {
			// it will overflow to the next char.
			if ( i == len - 1 ) {
				// it has reached max.
				printf ( "Reached max\n" );
			}

			// iterate this and the next.
			arr[numChars - i - 1] = 0;
		} else {
			// this bit isnt overflowing, so i am done.
			arr[numChars - i - 1] += 1;
			return;
		}
		i += 1;
	}
}

// does -= 1;
// this doesnt really work as simply... cuz the last char might not represnt 8 bits or 256 values.
// i might want to only utilize a single bit of it.

void decreaseCharArr ( unsigned char *arr, int numChars ) {
	int i = 0;
	int len = numChars;
	while ( i < len ) {
		if ( arr[numChars - i - 1] == 0xFF ) {
			// it will overflow to the next char.
			if ( i == len - 1 ) {
				// it has reached max.
				printf ( "Reached max\n" );
			}

			// iterate this and the next.
			arr[numChars - i - 1] = 0;
		} else {
			// this bit isnt overflowing, so i am done.
			arr[numChars - i - 1] += 1;
			return;
		}
		i += 1;
	}
}



/** Dragging */

void dragJPath ( struct jPath *path, float *dXY ) {
	// move all the verts.
	// maybe one day ill want to just move some internal offset.

	int i;
	int len;

	// move verts
	i = 0;
	len = arrayListGetLength ( path->verts );
	while ( i < len ) {
		struct jVert *vert = arrayListGetPointer ( path->verts, i );

		vert->XY[0] += dXY[0];
		vert->XY[1] += dXY[1];

		i += 1;
	}

	// move control points aswell.
	i = 0;
	len = arrayListGetLength ( path->lines );
	while ( i < len ) {
		struct jLine *line = arrayListGetPointer ( path->lines, i );

		if ( line->type == path_CubicBez ) {
			line->c0[0] += dXY[0];
			line->c0[1] += dXY[1];

			line->c1[0] += dXY[0];
			line->c1[1] += dXY[1];
		} else if ( line->type == path_QuadBez ) {
			line->c0[0] += dXY[0];
			line->c0[1] += dXY[1];
		}



		i += 1;
	}
}


/// util stuff

char *jType_to_str ( struct jNakedUnion *uni ) {
//	printf ( "jType_to_str ( )\n" );
//	printf ( "uni: %p\n", uni );

	switch ( uni->type ) {
		case jNaked_G:
			return "Group";
		case jNaked_Path:
			return "Path";
		case jNaked_Text:
			return "Text";
		case jNaked_Rect:
			return "Rect";
		case jNaked_Circ:
			return "Circ";
		case jNaked_Ellipse:
			return "Ellipse";
		case jNaked_Complex:
			return "Complex Ele";
		default:
			return "Type out of Range";
	}


	return "Type out of Range";
}


/// spawning uiGen eles

void jType_spawnEditUi ( struct jNakedUnion *uni ) {
	printf ( "jType_spawnEditUi ( )\n" );

	char *dir = NULL;
	void *data = NULL;

	switch ( uni->type ) {
		case jNaked_G:
			break;
		case jNaked_Path:
			dir = "/home/jadeb/workspace/jHigh/jalbSvg/res/uiGen_hand/jPath.xml";
			data = uni->path;

			break;
		case jNaked_Text:
			dir = "/home/jadeb/workspace/jHigh/jalbSvg/res/uiGen_hand/jText.xml";
			data = uni->text;

			break;
		case jNaked_Rect:

			break;
		case jNaked_Circ:

			break;
		case jNaked_Ellipse:

			break;
		case jNaked_Complex:
			dir = "/home/jadeb/workspace/jHigh/jalbSvg/res/uiGen_hand/complexEle.xml";
			data = uni->text;

			break;
		default:
			break;
	}

	if ( dir ) {
		uiGen_api->load_and_set_norm ( dir, data );
	}
}

void open_jVert_edit ( struct jVert *vert ) {
	printf ( "open_jVert_edit ( )\n" );
	printf ( "vert: %p\n", vert );
	sayFloatArray ( "vert->XY", vert->XY, 2 );

	printf ( "open_jVert_edit ( ) OVER\n" );

//	exit ( 12 );
}

void open_jLine_edit ( struct jLine *line ) {
	printf ( "open_jLine_edit ( )\n" );
	printf ( "line: %p\n", line );

	printf ( "line->v0: %d\n", line->v0 );
	printf ( "line->v1: %d\n", line->v1 );

//	char *workspaceDir_jalbJvg = "/home/jadeb/workspace/jHigh/jalbSvg/";
	char *fileDir = "res/uiGen_hand/jLine.xml";

	char fullDir[1024];
	sprintf ( fullDir, "%s%s", workspaceDir_jalbJvg, fileDir );

	if ( uiGen_api ) {
		uiGen_api->load_and_set_norm ( fullDir, line );
	}

	printf ( "open_jLine_edit ( ) OVER\n" );
}

/// uiGen

void set_uiGen_api ( void *data ) {
	printf ( "set_uiGen_api ( ) (consume)\n" );

	uiGen_api = data;

	printf ( "uiGen_api: %p\n", uiGen_api );
	printf ( "uiGen_api->uiGen_init: %p\n", uiGen_api->uiGen_init );
}


extern void (*setViewScale) (float s);

void set_jvg_viewScale ( float f ) {
	if ( !setViewScale ) {
		printf ( "ERROR !setViewScale\n" );
		return;
	}
	setViewScale ( f );
}


/// Xml

extern int num_structStruct_consumeMod;
extern struct xmlFuncts *xmlFuncts_arr_consumeMod[];

int xmlPrepaired = 0;

void prepairComplex_xml ( ) {
	if ( xmlPrepaired ) {
		return;
	}
	xmlPrepaired = 1;

	wrangleXmlFuncts ( "jalbJvg", num_structStruct_jalbJvg, xmlFuncts_arr_jalbJvg );
	wrangleXmlFuncts ( "jHigh", num_structStruct_consumeMod, xmlFuncts_arr_consumeMod );
}



/** Toolbar */

#include <jalbApi/api_toolbar.h>

struct api_toolbar *api_toolbar = NULL;

void set_api_toolbar ( void *data ) {
	printf ( "set_api_toolbar ( )\n" );
	printf ( "data: %p\n", data );

	api_toolbar = data;

	printf ( "set_api_toolbar ( ) OVER\n" );
}

void jvg_pass_toolbar ( ) {
	printf ( "jvg_pass_toolbar ( )\n" );

	if ( !api_toolbar ) {
		printf ( "ERROR, !api_toolbar, return\n" );
		return;
	}

	// what dropdowns do i want?
	void *topEle = NULL;
	void *dropEle = NULL;
	void *f = NULL;

	// jvg regular
	topEle = api_toolbar->spawn_toolbarEle ( "jvg", rt_drop, NULL, NULL );
	api_toolbar->add_toolbarEle ( topEle );

	f = load_jvg_dirList;
	dropEle = api_toolbar->spawn_toolbarEle ( "load", rt_funct, NULL, f );
	api_toolbar->add_drop_toolbarEle ( topEle, dropEle );

	f = jHand_save;
	dropEle = api_toolbar->spawn_toolbarEle ( "save", rt_funct, NULL, f );
	api_toolbar->add_drop_toolbarEle ( topEle, dropEle );

	// open a uiGen showing glob_jvg project info.
	f = spawn_projectInfo;
	dropEle = api_toolbar->spawn_toolbarEle ( "projectInfo", rt_funct, NULL, f );
	api_toolbar->add_drop_toolbarEle ( topEle, dropEle );

	api_toolbar->crunch_drop ( topEle );


	// jvg tools
	topEle = api_toolbar->spawn_toolbarEle ( "jvg tools", rt_drop, NULL, NULL );
	api_toolbar->add_toolbarEle ( topEle );

	f = set_cursor_pen;
	dropEle = api_toolbar->spawn_toolbarEle ( "pen", rt_funct, NULL, f );
	api_toolbar->add_drop_toolbarEle ( topEle, dropEle );
	f = set_cursor_text;
	dropEle = api_toolbar->spawn_toolbarEle ( "text", rt_funct, NULL, f );
	api_toolbar->add_drop_toolbarEle ( topEle, dropEle );
	f = set_cursor_circ;
	dropEle = api_toolbar->spawn_toolbarEle ( "circ", rt_funct, NULL, f );
	api_toolbar->add_drop_toolbarEle ( topEle, dropEle );
	f = set_cursor_complex;
	dropEle = api_toolbar->spawn_toolbarEle ( "complex", rt_funct, NULL, f );
	api_toolbar->add_drop_toolbarEle ( topEle, dropEle );

	api_toolbar->crunch_drop ( topEle );


	// jvg complex
	topEle = api_toolbar->spawn_toolbarEle ( "jvg complex", rt_drop, NULL, NULL );
	api_toolbar->add_toolbarEle ( topEle );

	f = spawn_new_complexDec;
	dropEle = api_toolbar->spawn_toolbarEle ( "new complexDec", rt_funct, NULL, f );
	api_toolbar->add_drop_toolbarEle ( topEle, dropEle );

	api_toolbar->crunch_drop ( topEle );

	f = jvg_toggle_CAD;
	topEle = api_toolbar->spawn_toolbarEle ( "CAD", rt_funct, NULL, f );
	api_toolbar->add_toolbarEle ( topEle );

	f = jvg_toggle_grid;
	topEle = api_toolbar->spawn_toolbarEle ( "grid", rt_funct, NULL, f );
	api_toolbar->add_toolbarEle ( topEle );



	// User Interface
	topEle = api_toolbar->spawn_toolbarEle ( "User Interface", rt_drop, NULL, NULL );
	api_toolbar->add_toolbarEle ( topEle );

	f = uiGen_open_eleList;
	dropEle = api_toolbar->spawn_toolbarEle ( "Ele List", rt_funct, NULL, f );
	api_toolbar->add_drop_toolbarEle ( topEle, dropEle );
	f = open_left_toolbar;
	dropEle = api_toolbar->spawn_toolbarEle ( "Tool Bar", rt_funct, NULL, f );
	api_toolbar->add_drop_toolbarEle ( topEle, dropEle );


	api_toolbar->crunch_drop ( topEle );

	printf ( "jvg_pass_toolbar ( ) OVER\n" );
}

void spawn_new_complexDec ( ) {
	printf ( "spawn_new_complexDec ( )\n" );
	// add to the last mod.

	int numMods = arrayListGetLength ( glob_jvg->moduleList );
	struct complexMod *mod = NULL;
	if ( numMods == 0 ) {
		// spawn a new mod
		mod = complexModInit ( );
		arrayListAddEndPointer ( glob_jvg->moduleList, mod );

	} else {
		mod = arrayListGetPointer ( glob_jvg->moduleList, numMods-1 );
	}

	struct complexDec *dec = complexDecInit ( );
	arrayListAddEndPointer ( mod->complexDecList, dec );

	printf ( "spawn_new_complexDec ( ) OVER\n" );
}

void spawn_projectInfo ( ) {
	printf ( "spawn_projectInfo ( )\n" );

	printf ( "spawn_projectInfo ( ) OVER\n" );
}


void (*jalbDir_loadPane)(char *) = NULL;
void set_jalbDir_loadPane ( void *data ) {
	printf ( "set_jalbDir_loadPane ( )\n" );
	printf ( "data: %p\n", data );

	jalbDir_loadPane = data;

	printf ( "set_jalbDir_loadPane ( ) OVER\n" );
}

void load_jvg_dirList ( ) {
	printf ( "load_jvg_dirList ( )\n" );

	if ( !jalbDir_loadPane ) {
		printf ( "ERROR, !jalbDir_loadPane, return\n" );
		return;
	}

	char *dir = "/home/jadeb/workspace/jHigh/jalbSvg/res/jvg/";
	jalbDir_loadPane ( dir );

	printf ( "load_jvg_dirList ( ) OVER\n" );
}

void jvg_toggle_CAD ( ) {
	printf ( "jvg_toggle_CAD ( )\n" );

	if ( renderCAD ) {
		renderCAD = 0;
	} else {
		renderCAD = 1;
	}

	printf ( "jvg_toggle_CAD ( ) OVER\n" );
}

void jvg_toggle_grid ( ) {
	if ( gridRender ) {
		gridRender = 0;
		gridSnap = 0;
	} else {
		gridRender = 1;
		gridSnap = 1;
	}
}

void jvg_toggle_gridRender ( ) {
	printf ( "jvg_toggle_gridRender ( )\n" );

	if ( gridRender ) {
		gridRender = 0;
	} else {
		gridRender = 1;
	}

	printf ( "jvg_toggle_gridRender ( ) OVER\n" );
}

// should snap ever be enabled when render isnt?
void jvg_set_gridSnap ( int i ) {
	printf ( "jvg_set_gridSnap ( )\n" );

	gridSnap = i;
}

void jvg_toggle_gridSnap ( ) {
	printf ( "jvg_toggle_gridSnap ( )\n" );

	if ( gridSnap ) {
		gridSnap = 0;
	} else {
		gridSnap = 1;
	}

	printf ( "jvg_toggle_gridSnap ( ) OVER\n" );
}

/// tools

void set_cursor_pen ( ) {
	set_cursorInputMode ( ci_pen );
}

void set_cursor_text ( ) {
	set_cursorInputMode ( ci_text );
}

void set_cursor_circ ( ) {
	set_cursorInputMode ( ci_circ );
}

void set_cursor_complex ( ) {
	set_cursorInputMode ( ci_complex );
}



/** Loading examples for uiGen_liveDev */

struct jvg *load_jvg_example_eleList ( ) {
	printf ( "load_jvg_example_eleList ( )\n" );

	struct jvg *jvg = jvgInit ( );
	struct jNakedUnion *uni = jNakedUnionInit ( );
	jNakedUnionTypeChange0 ( uni, jNaked_G );
	arrayListAddEndPointer ( jvg->eles, uni );

	uni = jNakedUnionInit ( );
	jNakedUnionTypeChange0 ( uni, jNaked_Path );
	arrayListAddEndPointer ( jvg->eles, uni );

	uni = jNakedUnionInit ( );
	jNakedUnionTypeChange0 ( uni, jNaked_Text );
	arrayListAddEndPointer ( jvg->eles, uni );

	uni = jNakedUnionInit ( );
	jNakedUnionTypeChange0 ( uni, jNaked_Rect );
	arrayListAddEndPointer ( jvg->eles, uni );

	uni = jNakedUnionInit ( );
	jNakedUnionTypeChange0 ( uni, jNaked_Circ );
	arrayListAddEndPointer ( jvg->eles, uni );

	uni = jNakedUnionInit ( );
	jNakedUnionTypeChange0 ( uni, jNaked_Ellipse );
	arrayListAddEndPointer ( jvg->eles, uni );

	uni = jNakedUnionInit ( );
	jNakedUnionTypeChange0 ( uni, jNaked_Complex );
	arrayListAddEndPointer ( jvg->eles, uni );

	glob_jvg = jvg;

	printf ( "load_jvg_example_eleList ( ) OVER\n" );

	return jvg;
}

struct jPath *load_jvg_example_jPath ( ) {
	printf ( "load_jvg_example_jPath ( )\n" );

	struct jPath *path = jPathInit ( );

	struct jVert *vert = jVertInit ( );
	arrayListAddEndPointer ( path->verts, vert );
	vert->XY[0] = 1.0;
	vert->XY[1] = -1.0;

	vert = jVertInit ( );
	arrayListAddEndPointer ( path->verts, vert );
	vert->XY[0] = 2.0;
	vert->XY[1] = -2.0;

	struct jLine *line = jLineInit ( );
	arrayListAddEndPointer ( path->lines, line );
	line->v0 = 0;
	line->v1 = 1;

	printf ( "load_jvg_example_jPath ( ) OVER\n" );

	return path;
}

struct jVert *load_jvg_example_jVert ( ) {
	printf ( "load_jvg_example_jVert ( )\n" );

	struct jVert *vert = jVertInit ( );
	vert->XY[0] = 1.0;
	vert->XY[1] = -1.0;

	printf ( "load_jvg_example_jvert ( ) OVER\n" );

	return vert;
}

struct jLine *load_jvg_example_jLine ( ) {
	printf ( "load_jvg_example_jLine ( )\n" );

	struct jLine *line = jLineInit ( );
	line->v0 = 0;
	line->v1 = 0;

	printf ( "load_jvg_example_jLine ( ) OVER\n" );

	return line;
}



/** UiGen spawning */

char *jvg_projectDir = "/home/jadeb/workspace/jHigh/jalbSvg";

void open_left_toolbar ( ) {
	printf ( "open_left_toolbar ( )\n" );

//	char *fullDir = "/home/jadeb/workspace/jHigh/jalbSvg/res/uiGen_hand/eleSpawner.xml";

	char *dir = "res/uiGen_hand/eleSpawner.xml";
	char fullDir[256];
	sprintf ( fullDir, "%s/%s", jvg_projectDir, dir );


	void *data = NULL;
	int type = 1; // no red bar.

	int XYWH[4] = { 0, 54, 100, 400 };
	void *uiGen = uiGen_api->load_and_set_XYWH ( fullDir, data, XYWH, type );

	printf ( "uiGen: %p\n", uiGen );

	printf ( "open_left_toolbar ( ) OVER\n" );
}

void uiGen_open_eleList ( ) {
	printf ( "uiGen_open_eleList ( )\n" );

	char *dir = "res/uiGen_hand/eleList.xml";

	char fullDir[256];
	sprintf ( fullDir, "%s/%s", jvg_projectDir, dir );

	void *data = glob_jvg;
	int type = 0; // red bar.

	// open it on the right side of the screen.
	int XYWH[4] = { screenDim_mem[0] - 400, 74, 400, 400 };
	uiGen_api->load_and_set_XYWH ( fullDir, data, XYWH, type );

	printf ( "uiGen_open_eleList ( ) OVER\n" );
}

void uiGen_open_jNaked ( struct jNakedUnion *jNaked ) {
	printf ( "uiGen_open_jNaked ( )\n" );

	printf ( "projectDir: %s\n", jvg_projectDir );

	printf ( "jNaked: %p\n", jNaked );
	printf ( "jNaked->type: %d\n", jNaked->type );

//	char *dir = "/home/jadeb/workspace/jHigh/jalbSvg/res/uiGen_hand/";
	char *midDir = "res/uiGen_hand";

	int type = 0; // red bar.

	if ( jNaked->type == jNaked_G ) {
	} else if ( jNaked->type == jNaked_Path ) {
		char *name = "jPath.xml";
		char fullDir[1024];
//		sprintf ( fullDir, "%s%s", dir, name );
		sprintf ( fullDir, "%s/%s/%s", jvg_projectDir, midDir, name );

		void *data = jNaked->path;

		int XYWH[4] = { 40, 40, 400, 400 };
		uiGen_api->load_and_set_XYWH ( fullDir, data, XYWH, type );

	} else if ( jNaked->type == jNaked_Text ) {
		char *name = "jText.xml";
		char fullDir[1024];
		sprintf ( fullDir, "%s/%s/%s", jvg_projectDir, midDir, name );

		void *data = jNaked->text;

		int XYWH[4] = { 40, 40, 400, 400 };
		uiGen_api->load_and_set_XYWH ( fullDir, data, XYWH, type );

	} else if ( jNaked->type == jNaked_Rect ) {
	} else if ( jNaked->type == jNaked_Circ ) {
	} else if ( jNaked->type == jNaked_Ellipse ) {
	} else if ( jNaked->type == jNaked_Complex ) {
	}

	printf ( "uiGen_open_jNaked ( ) OVER\n" );
}


/// uiGen left toolbar stuff

float retColor[4] = { 0.0 };
float *toolBar_icon_color ( int i ) {
//	printf ( "toolBar_icon_color ( )\n" );
//	printf ( "i: %d\n", i );

	if ( cursorInputMode == i ) {
		retColor[0] = 0.8;
		retColor[1] = 0.6;
		retColor[2] = 0.0;
		retColor[3] = 1.0;
	} else {
		retColor[0] = 0.4;
		retColor[1] = 0.4;
		retColor[2] = 0.4;
		retColor[3] = 1.0;
	}

	return retColor;
}


/** Specific Loading Examples */

void load_CAD_00 ( ) {
	char *dir = "../jalbSvg/res/jvg/CAD/test_00.xml";

	jalbJvg_load_global ( dir );

	jvg_toggle_grid ( );	// enable grid
	jvg_set_gridSnap ( 0 );	// dissable gridSnap

	// user interface
//	open_left_toolbar ( );
//	uiGen_open_eleList ( );
}

void firstRender_todo ( ) {
	open_left_toolbar ( );
	uiGen_open_eleList ( );
}




























