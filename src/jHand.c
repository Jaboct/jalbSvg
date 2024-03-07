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

extern int cursorInputMode;



// text cursor info.
int cStart[3];
int cEnd[3];


struct jvg *glob_jvg = NULL;
ArrayList *global_jEles = NULL; // (struct jNakedUnion*)
struct jNakedUnion *tempEle = NULL;


int debugPrint_jvg_render = 0;
extern int debugPrint_jvg_event;
extern int svg_debugPrint_render_text;

int tabW = 8;
int ctrlMemLast = -1;


extern int selected;
extern int mouseHeld;
extern int thisSel; // used during rendering to figure if the ele being rendered is currently selected.

extern int renderMode;


int vert_subMode = 0;


char saveDir[256] = "";

// for text box ctrl jumping.
extern ArrayList *glob_ctrlKeys;


extern float glob_viewScale;
extern float glob_viewLoc[];



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
		svg_debugPrint_render_text = 1;
	}


	if ( !glob_ctrlKeys ) {
//		char *line = " \n\t.,/\\<>{}[]():;\"\'|_-+=~`!@#$%^&*?";
		char *line = " \\n\\t.,/\\\\<>{}[]():;\\\"\\\'|_-+=~`!@#$%^&*?";
		jKeyCtrl ( line, NULL );
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

	glob_viewLoc[0] = viewLoc[0];
	glob_viewLoc[1] = viewLoc[1];

	glob_viewScale = viewScale;

	thisSel = selected;
	cursor_depth = 0;
	jNakedList_render ( screenDims, glBuffers, XYWHpass, glob_jvg->eles,
		viewLoc, viewScale );

	if ( tempEle ) {
		jNaked_render ( screenDims, glBuffers, XYWHpass, tempEle,
			viewLoc, viewScale );
	}

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
/*
	if ( debugPrint_jvg_event ) {
		printf ( "jalbJvg_mEvent ( )\n" );
	}
*/

	if ( !glob_jvg ) {
		glob_jvg = jvgInit ( );
		global_jEles = glob_jvg->eles;
	}

	viewScale = 1.0 / viewScale;

	ArrayList *eles = glob_jvg->eles;

	if ( e->type == SDL_KEYDOWN ) {

		if ( e->key.keysym.sym == SDLK_ESCAPE ) {
			if ( tempEle ) {
				jNakedUnionClose ( tempEle );
				tempEle = NULL;
				mouseHeld = 0;
			}

			set_cursorInputMode ( ci_reg );
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
//			printf ( "editing text\n" );

			struct jText *text = ele->text;
			ArrayList *sb = text->sb;
			struct undoRedo *undoMem = NULL;
			struct textSearch *search = NULL;
			int searching = 0;

			int textWrap = 1;
			int maxCols = text->XYWH[2] / fonts[0]->atlasInfo.glyphW;

//			printf ( "maxCols: %d\n", maxCols );

			if ( altKeys[akCtrl] ) {
				if ( e->key.keysym.sym == SDLK_h ) {		// Math characters
					add_special ( sb, spec_therefore );
					return 1;
				} else if ( e->key.keysym.sym == SDLK_7 ) {
					add_special ( sb, spec_and );
					return 1;
				} else if ( e->key.keysym.sym == SDLK_BACKSLASH ) {
					add_special ( sb, spec_or );
					return 1;
				} else if ( e->key.keysym.sym == SDLK_m ) {
					add_special ( sb, spec_micro );
					return 1;
				} else if ( e->key.keysym.sym == SDLK_j ) {
					add_special ( sb, spec_emptySet );
					return 1;

				} else if ( e->key.keysym.sym == SDLK_k ) {	// Greek Letters
					add_special ( sb, spec_alphaL );
					return 1;
				} else if ( e->key.keysym.sym == SDLK_b ) {
					add_special ( sb, spec_betaL );
					return 1;
				} else if ( e->key.keysym.sym == SDLK_d ) {
					if ( altKeys[akShift] ) {
						add_special ( sb, spec_deltaU );
					} else {
						add_special ( sb, spec_deltaL );
					}
					return 1;
				} else if ( e->key.keysym.sym == SDLK_y ) {
					add_special ( sb, spec_thetaL );
					return 1;
				} else if ( e->key.keysym.sym == SDLK_u ) {
					add_special ( sb, spec_lambdaL );
					return 1;
				} else if ( e->key.keysym.sym == SDLK_p ) {
					add_special ( sb, spec_pi );
					return 1;
				} else if ( e->key.keysym.sym == SDLK_i ) {
					add_special ( sb, spec_rhoL );
					return 1;
				} else if ( e->key.keysym.sym == SDLK_o ) {
					add_special ( sb, spec_omegaL );
					return 1;
				}
			}


			int ret = sbKey ( e->key.keysym.sym, sb, undoMem, cStart, cEnd,
				&searching, search, altKeys,
				glob_ctrlKeys, NULL, textWrap, maxCols );
//			printf ( "SB KEY RET: %d\n", ret );

			if ( ret ) {
				return 1;
			}
//			printSb ( sb );
		}
	} else if ( e->type == SDL_MOUSEBUTTONDOWN ) {
		if ( renderMode != renderM_editAll &&
		     renderMode != renderM_edit ) {
			return 0;
		}
		mouseHeld = 1;

		if ( cursorInputMode == ci_pen ) {
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

			set_cursorInputMode ( ci_reg );

			return 1;

		} else if ( cursorInputMode == ci_circ ) {
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

			set_cursorInputMode ( ci_reg );

			return 1;
		}

		selected = 0;

		int ret = jNakedList_mEvent ( e, clickXYpass, eleWH, eles,
			viewLoc, viewScale );

//		printf ( "naked list return: %d\n", ret );
		if ( ret ) {
			sayCursor;
			return 1;
		}


		if ( cursorInputMode == ci_text ) {
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

			selected = 1;

			cStart[0] = 0;
			cEnd[0] = 0;
			cStart[1] = 0;
			cStart[2] = 0;
			cEnd[1] = 0;
			cEnd[2] = 0;

//			sayCursor;

			set_cursorInputMode ( ci_reg );

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
		float dXY[2] = { dx, dy };

		if ( tempEle ) {
//			printf ( "tempEle->type: %d\n", tempEle->type );
			if ( tempEle->type == jNaked_Circ ) {
				struct jCirc *circ = tempEle->circ;
				circ->radius += dx;
			}
			return 1;
		}


		if ( renderMode == renderM_editAll ||
		     renderMode == renderM_edit ) {
			onHoverCheck ( clickXYpass );
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
/*
		printf ( "selType: %d\n", selType );
		printf ( "parent: %p\n", parent );
		printf ( "ele: %p\n", ele );
		printf ( "vertI: %d\n", vertI );
		printf ( "controlI: %d\n", controlI );
		printf ( "lastCursor: %p\n", lastCursor );
		if ( lastCursor ) {
			printf ( "lastCursor->selI: %d\n", lastCursor->selI );
		}
*/

		if ( selType == cs_object ) {
			if ( ele->type == jNaked_Path ) {
				// drag the entire path around.
				dragJPath ( ele->path, dXY );
			}
		} else if ( selType == cs_vert ) {
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
		} else {
			printf ( "unhandled selType: %d\n", selType );
		}
	}

/*
	if ( debugPrint_jvg_event ) {
		printf ( "jalbJvg_mEvent ( ) OVER\n" );
	}
*/

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


/** hover cursor */

void onHoverCheck ( int *XY ) {
//	printf ( "onHoverCheck ( )\n" );
//	sayIntArray ( "XY", XY, 2 );

	if ( cursorInputMode == ci_reg ) {
		// see if my cursor is on a vert.

		if ( onHoverType ( XY ) ) {
			// TODO cr_move
			set_cursor_iconI ( cr_move );
		} else {
			set_cursor_iconI ( cr_reg );
		}
	}
}

int onHoverType ( int *XY ) {
	int i = 0;
	int len = arrayListGetLength ( glob_jvg->eles );
	while ( i < len ) {
		struct jNakedUnion *uni = arrayListGetPointer ( glob_jvg->eles, i );

		if ( uni->type == jNaked_Path ) {
			struct jPath *path = uni->path;

			if ( isOnVert ( path, XY ) ) {
				return 1;
			}
		}

		i += 1;
	}

	return 0;
}

int pointDist = 4.0;

int isOnVert ( struct jPath *path, int *XY ) {
//	printf ( "isOnVert ( )\n" );
//	sayIntArray ( "XY", XY, 2 );

	int boxW = 10;

	float viewScale = glob_viewScale;
	float *viewLoc = glob_viewLoc;

//	printf ( "viewScale: %f\n", viewScale );
//	sayFloatArray ( "viewLoc", viewLoc, 2 );

	int i;
	int len;
/*
	i = 0;
	len = arrayListGetLength ( path->verts );
	while ( i < len ) {
		struct jVert *v = arrayListGetPointer ( path->verts, i );

		float cXY[2];
		point_to_loc ( v->XY, cXY, viewLoc,  viewScale );

		sayFloatArray ( "cXY", cXY, 2 );

		cXY[0] -= XY[0];
		cXY[1] -= XY[1];

		// this is a circular check, not rect
		float d = vectNorm ( cXY, 2 );

		if ( d < boxW ) {
			return 1;
		}

		i += 1;
	}
*/

	// ok now check if its on a line aswell.
	i = 0;
	len = arrayListGetLength ( path->lines );
	while ( i < len ) {
		struct jLine *l = arrayListGetPointer ( path->lines, i );

		struct jVert *v0 = arrayListGetPointer ( path->verts, l->v0 );
		struct jVert *v1 = arrayListGetPointer ( path->verts, l->v1 );

		float fXY[2] = { XY[0], XY[1] };
		loc_to_point ( fXY, fXY, viewLoc, viewScale );
		float dist = pointLineDist ( fXY, v0->XY, v1->XY );

		if ( dist < pointDist ) {
			return 1;
		}

		i += 1;
	}


	return 0;
}

int isOnLine ( struct jVert *v0, struct jVert *v1, int *XY ) {
	// TODO, rn this treats everything like a straight line, ignores curves.

	

	return 0;
}


/** Dragging */

void dragJPath ( struct jPath *path, float *dXY ) {
	// move all the verts.
	// maybe one day ill want to just move some internal offset.

	int i;
	int len;

	i = 0;
	len = arrayListGetLength ( path->verts );
	while ( i < len ) {
		struct jVert *vert = arrayListGetPointer ( path->verts, i );

		vert->XY[0] += dXY[0];
		vert->XY[1] += dXY[1];

		i += 1;
	}
}






