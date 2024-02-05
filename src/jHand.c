#include "jHand.h"


/** Variables */

extern char altKeys[];

extern float colorWhite[];
extern float colorBlack[];

extern struct draw2dStruct *draw2dApi;

extern struct jalbFont *fonts[];
extern int numFonts;


extern ArrayList *cursorList;
extern int cursor_depth;

extern int cursorType;



// text cursor info.
int cStart[3];
int cEnd[3];


struct jvg *glob_jvg = NULL;
ArrayList *global_jEles = NULL; // (struct jNakedUnion*)
struct jNakedUnion *tempEle = NULL;


int debugPrint_jvg_render = 1;

int tabW = 8;
int ctrlMemLast = -1;


extern int selected;
extern int mouseHeld;
extern int thisSel; // used during rendering to figure if the ele being rendered is currently selected.

char saveDir[256] = "";


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

void jalbJvg_renderDyn ( int *screenDims, GLuint *glBuffers, int *XYWHpass, void *data,
		float *viewLoc, float viewScale ) {
	if ( debugPrint_jvg_render ) {
		printf ( "jalbJvg_renderDyn ( )\n" );
	}

	if ( !glob_jvg ) {
		glob_jvg = jvgInit ( );
		global_jEles = glob_jvg->eles;
	}
	if ( !global_jEles ) {
		global_jEles = initArrayList ( 10, sizeof ( struct jNakedUnion* ), 10 );
	}
	if ( !cursorList ) {
		cursorList = initArrayList ( 10, sizeof ( struct cursorMem*), 10 );
	}

	viewScale = 1.0 / viewScale;

	thisSel = selected;
	cursor_depth = 0;
	jNakedList_render ( screenDims, glBuffers, XYWHpass, glob_jvg->eles,
		viewLoc, viewScale );

	if ( tempEle ) {
		jNaked_render ( screenDims, glBuffers, XYWHpass, tempEle,
			viewLoc, viewScale );
	}

	// at the top render the save dir
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

	// draw a white line
	XYWH[1] += XYWH[3] - 1;
	XYWH[3] = 1;
	draw2dApi->fillRect ( XYWH, colorWhite, screenDims, glBuffers );


	if ( debugPrint_jvg_render ) {
		printf ( "jalbJvg_renderDyn ( ) OVER\n" );
	}
}

int jalbJvg_mEvent ( SDL_Event *e, int *clickXYpass, int *eleWH, void *data,
		float *viewLoc, float viewScale ) {
	printf ( "jalbJvg_mEvent ( )\n" );

	viewScale = 1.0 / viewScale;

	ArrayList *eles = glob_jvg->eles;

	if ( e->type == SDL_KEYDOWN ) {

		if ( e->key.keysym.sym == SDLK_ESCAPE ) {

			if ( tempEle ) {
				jNakedUnionClose ( tempEle );
				tempEle = NULL;
				mouseHeld = 0;
			}

			set_cursor_iconI ( c_reg );
			return 1;
		}

		struct jNakedUnion *parent;
		struct jNakedUnion *ele;
		int vertI = -1;
		int controlI = -1;
		struct cursorMem *lastCursor;

		int selType = jIterateToSelected ( global_jEles, &parent, &ele, &vertI, &controlI, &lastCursor );
		if ( selType == cs_text &&
		     selected ) {
			ArrayList *sb = ele->text->sb;
			struct undoRedo *undoMem = NULL;
			struct textSearch *search = NULL;
			int searching = 0;

			int textWrap = 0;
			int maxCols = 200;
//			int maxCols = task->maxWH[0] / glyphW;

			ArrayList *glob_ctrlKeys = NULL;

			int ret = sbKey ( e->key.keysym.sym, sb, undoMem, cStart, cEnd,
				&searching, search, altKeys,
				glob_ctrlKeys, NULL, textWrap, maxCols );
			printf ( "SB KEY RET: %d\n", ret );
			if ( ret ) {
				return 1;
			}
			printSb ( ele->text->sb );
		}
	} else if ( e->type == SDL_MOUSEBUTTONDOWN ) {
		mouseHeld = 1;

		if ( cursorType == c_pen ) {
			// create a new path.

			float worldXY[2];
			loc_to_pointI ( clickXYpass, worldXY, viewLoc, viewScale );

			struct jNakedUnion *ele = jNakedUnionInit ( );
			arrayListAddEndPointer ( eles, ele );
			jNakedUnionTypeChange0 ( ele, jNaked_Path );
			struct jPath *path = ele->path;
			struct jVert *vert = jVertInit ( );
			arrayListAddEndPointer ( path->verts, vert );
			vert->XY[0] = worldXY[0];
			vert->XY[1] = worldXY[1];

			set_cursor_iconI ( c_reg );

			return 1;

		} else if ( cursorType == c_circ ) {
			if ( tempEle ) {
				printf ( "TEMP ELE ERROR\n" );
			}
			tempEle = jNakedUnionInit ( );
			jNakedUnionTypeChange0 ( tempEle, jNaked_Circ );
			struct jCirc *circ = tempEle->circ;

			float worldXY[2];
			loc_to_pointI ( clickXYpass, worldXY, viewLoc, viewScale );

			circ->XY[0] = worldXY[0];
			circ->XY[1] = worldXY[1];
			circ->radius = 10;

			set_cursor_iconI ( c_reg );

			return 1;
		}

		selected = 0;

		int ret = jNakedList_mEvent ( e, clickXYpass, eleWH, eles,
			viewLoc, viewScale );
		if ( ret ) {
			sayCursor;
			return 1;
		}



		if ( cursorType == c_text ) {
			// create a new jText

			int defaultWH[2] = { 300, 300 };

			float fClickXY[2] = { clickXYpass[0], clickXYpass[1] };
			float worldXY[2];
			loc_to_point ( fClickXY, worldXY, viewLoc, viewScale );

//			struct jText *text = jTextInit ( );
			struct jNakedUnion *naked = jNakedUnionInit ( );
			arrayListAddEndPointer ( global_jEles, naked );
			jNakedUnionTypeChange0 ( naked, jNaked_Text );
			struct jText *text = naked->text;
			text->XYWH[0] = worldXY[0];
			text->XYWH[1] = worldXY[1];
			text->XYWH[2] = defaultWH[0];
			text->XYWH[3] = defaultWH[1];

			{
				cursor_depth = 1;
				int i = 0;	// irrelevent, just needs to be 1 deeper than the text box.
				handleCursor_start;
			}
			printf ( "set second part\n" );
			{
				cursor_depth = 0;
				int i = arrayListGetLength ( global_jEles ) - 1;
				handleCursor;
			}

			cStart[0] = 0;
			cEnd[1] = 0;

			sayCursor;

			set_cursor_iconI ( c_reg );

			return 1;
		}

	} else if ( e->type == SDL_MOUSEBUTTONUP ) {
		mouseHeld = 0;

		if ( tempEle ) {
			printf ( "BUTTON UP ADD TEMP ELE\n" );
			arrayListAddEndPointer ( eles, tempEle );
			tempEle = NULL;
		}

	} else if ( e->type == SDL_MOUSEMOTION ) {
//		printf ( "selected: %d\n", selected );
//		printf ( "mouseHeld: %d\n", mouseHeld );

		float dx = e->motion.xrel * viewScale;
		float dy = e->motion.yrel * viewScale;

		if ( tempEle ) {
//			printf ( "tempEle->type: %d\n", tempEle->type );
			if ( tempEle->type == jNaked_Circ ) {
				struct jCirc *circ = tempEle->circ;
				circ->radius += dx;
			}
			return 1;
		}


		if ( !selected ||
		     !mouseHeld ) {
			return 0;
		}

		struct jNakedUnion *parent;
		struct jNakedUnion *ele;
		int vertI = -1;
		int controlI = -1;
		struct cursorMem *lastCursor = NULL;

		int selType = jIterateToSelected ( global_jEles, &parent, &ele, &vertI, &controlI, &lastCursor );

		printf ( "selType: %d\n", selType );
		printf ( "ele: %p\n", ele );
		printf ( "vertI: %d\n", vertI );
		printf ( "controlI: %d\n", controlI );
		printf ( "lastCursor: %p\n", lastCursor );
		if ( lastCursor ) {
			printf ( "lastCursor->selI: %d\n", lastCursor->selI );
		}

		if ( selType == cs_vert ) {
//			struct jVert *vert = arrayListGetPointer ( ele->path->verts, vertI );
//			vert->XY[0] += dx;
//			vert->XY[1] += dy;

			move_jPathVert ( ele->path, vertI, dx, dy );

		} else if ( selType == cs_control ) {
			struct jLine *line = arrayListGetPointer ( ele->path->lines, vertI );

			if ( controlI == 0 ) {
				line->c0[0] += dx;
				line->c0[1] += dy;
			} else if ( controlI == 1 ) {
				line->c1[0] += dx;
				line->c1[1] += dy;
			}

		} else if ( selType == cs_text ) {
			struct jText *text = ele->text;

			if ( vertI == 0 ) {
				// TODO get rid of this, 0 should only mean editing text.
				text->XYWH[0] += dx;
				text->XYWH[1] += dy;
			} else if ( vertI == 1 ) {
				text->XYWH[0] += dx;
				text->XYWH[1] += dy;
			} else if ( vertI == 5 ) {
				// TODO, have a minimum size.

				text->XYWH[2] += dx;
				text->XYWH[3] += dy;
			}
		}
	}

	printf ( "jalbJvg_mEvent ( ) OVER\n" );

	return 0;
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
extern struct backbone_structStruct jvg;

extern int num_structStruct_jalbJvg;
extern struct xmlFuncts *xmlFuncts_arr_jalbJvg[];


void jHand_save ( ) {
	printf ( "jHand_save ( )\n" );

	if ( saveDir[0] != '\0' ) {
		jalbJvg_save ( saveDir );
	} else {
		char *dir = "/home/jadoo/workspace/jHigh/jalbSvg/res/jvg/test_00.xml";
		jalbJvg_save ( dir );
	}

	printf ( "jHand_save ( ) OVER\n" );
}

void jalbJvg_save ( char *dir ) {
	printf ( "jalbJvg_save ( )\n" );
	printf ( "dir: %s\n", dir );

	fwriteXml_backbone ( dir, &jvg, glob_jvg,
		jvg_attributes, backbone_arr_jalbJvg, len_backbone_arr_jalbJvg );

	printf ( "jalbJvg_save ( ) OVER\n" );
}

void jHand_load ( ) {
	printf ( "jHand_load ( )\n" );

	char *dir = "/home/jadoo/workspace/jHigh/jalbSvg/res/jvg/test_00.xml";

	jalbJvg_load ( dir );
}

void jalbJvg_load ( char *dir ) {
	struct jvg *jvgEle = loadXmlFile_03 ( dir, xmlFuncts_arr_jalbJvg, num_structStruct_jalbJvg );
	printf ( "jvgEle: %p\n", jvgEle );
//	printf ( "jvgEle->eles.len: %d\n", arrayListGetLength ( jvgEle->eles ) );

	if ( jvgEle ) {
		glob_jvg = jvgEle;

		global_jEles = glob_jvg->eles;
	}

	strcpy ( saveDir, dir );

	printf ( "jHand_load ( ) OVER\n" );
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
