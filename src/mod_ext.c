#include "mod_ext.h"

/** Variables */

/// modCore externs 

extern char altKeys[];

extern struct draw2dStruct *draw2dApi;
extern struct jalbFont *fonts[];

extern float colorWhite[];
extern float colorBlack[];
extern float colorOrange[];
extern float colorGray[];


/// locals

struct svg *global_svg = NULL;

float *viewLoc_ptr;
float glob_viewLoc[2] = { 0.0, 0.0 };
float glob_viewScale = 1.0;;

int glob_screenDims[2];


void (*setViewScale) (float s) = NULL;


int svg_debugPrint_render = 0;
int svg_debugPrint_render_text = 0;

int svg_debugPrint_event = 0;


int renderMode = renderM_edit;

int pointW = 10;

GLuint *glob_glBuffers = NULL;


/// proofs

extern int doingTests;
extern int testStage;

/** Functions */

void *jalbSvg_init ( ) {
	return NULL;
}

void jalbSvg_render ( int *screenDims, GLuint *glBuffers, int *XYWH, void *data ) {
	printf ( "\n" );
	printf ( "jalbSvg_render ( )\n" );

	if ( global_svg ) {
		svg_render ( screenDims, glBuffers, XYWH, global_svg );
	}
}

void jalbSvg_renderDyn ( int *screenDims, GLuint *glBuffers, int *XYWHpass, void *data,
		float *viewLoc, float viewScale ) {
	if ( svg_debugPrint_render ) {
		printf ( "\n" );

		printf ( "jalbSvg_renderDyn ( )\n" );
	}

	glob_glBuffers = glBuffers;

/*
	viewLoc[0] = 10;
	if ( setViewScale ) {
//		setViewScale ( 4.0 );
		setViewScale ( 0.5 );
	} else {
		printf ( "!setViewScale ( ) error\n" );
	}
*/

	if ( svg_debugPrint_render ) {
		sayFloatArray ( "viewLoc", viewLoc, 2 );
		printf ( "viewScale: %f\n", viewScale );
	}

	glob_screenDims[0] = screenDims[0];
	glob_screenDims[1] = screenDims[1];

	viewLoc_ptr = viewLoc;
	glob_viewLoc[0] = viewLoc[0];
	glob_viewLoc[1] = viewLoc[1];
	glob_viewScale = 1.0 / viewScale;

	if ( global_svg ) {
		svg_render ( screenDims, glBuffers, XYWHpass, global_svg );
	}

//	handle_render_proof ( );

	if ( doingTests ) {
		run_allTests ( testStage );
		testStage += 1;
	}


	if ( svg_debugPrint_render ) {
		printf ( "jalbSvg_renderDyn ( ) OVER\n" );
	}
}

int jalbSvg_event ( SDL_Event *e, int *clickXY, int *eleWH, void *data ) {
	return 1;
}

// this has recursion so needs an arraylist.
int selected = 0;
int mouseHeld = 0;

ArrayList *cursorList = NULL;
int cursor_depth = 0;

int jalbSvg_mEvent ( SDL_Event *e, int *clickXYpass, int *eleWH, void *data,
		float *viewLoc, float viewScale ) {
	if ( svg_debugPrint_event ) {
		printf ( "jalbSvg_mEvent ( )\n" );
	}

	if ( !cursorList ) {
		cursorList = initArrayList ( 10, sizeof ( void* ), 10 );
	}

	if ( !global_svg ) {
//		svg_event ( screenDims, glBuffers, XYWHpass, global_svg );
		return 0;
	}
	struct svg *svg = global_svg;


	if ( e->type == SDL_MOUSEMOTION ) {
		if ( selected &&
		     mouseHeld ) {

			struct nakedUnion *parent = NULL;
			struct nakedUnion *ele = NULL;
			int vertI = -1;
			int controlI = -1;
			struct cursorMem *lastCursor = NULL;
			int selType = iterateToSelected ( svg, &parent, &ele, &vertI, &controlI, &lastCursor );
			if ( selType == c_vert ) {
				struct pathUni *pUni = arrayListGetPointer ( ele->path->eles, vertI );
				struct pathUni *pUniNext = NULL;
				int numEles = arrayListGetLength ( ele->path->eles );
//				printf ( "numEles: %d\n", numEles );
//				printf ( "vertI: %d\n", vertI );
				if ( numEles > vertI + 1 ) {
					pUniNext = arrayListGetPointer ( ele->path->eles, vertI + 1 );
				}

				float dx = e->motion.xrel / viewScale;
				float dy = e->motion.yrel / viewScale;
				move_pUni ( pUni, pUniNext, dx, dy );

				return 1;

			} else if ( selType == c_control ) {
				struct pathUni *pUni = arrayListGetPointer ( ele->path->eles, vertI );

				float dx = e->motion.xrel / viewScale;
				float dy = e->motion.yrel / viewScale;
				if ( pUni->type == path_CubicBez ) {
					if ( controlI == 0 ) {
						pUni->cubicBez->c0[0] += dx;
						pUni->cubicBez->c0[1] += dy;
					} else if ( controlI == 1 ) {
						pUni->cubicBez->c1[0] += dx;
						pUni->cubicBez->c1[1] += dy;
					}
				}
				return 1;
			}
		}

		return 0;
	}

	if ( e->type == SDL_MOUSEBUTTONUP ) {
		mouseHeld = 0;
	}

	if ( e->type == SDL_MOUSEBUTTONDOWN ) {
		mouseHeld = 1;

		int ret = nakedList_mEvent ( e, clickXYpass, eleWH, svg->eles,
			viewLoc, viewScale );
		if ( ret ) {
			printf ( "finish set cursor\n" );
			printf ( "cursorList.len: %d\n", arrayListGetLength ( cursorList ) );

			int i = 0;
			int len = arrayListGetLength ( cursorList );
			while ( i < len ) {
				struct cursorMem *mem = arrayListGetPointer ( cursorList, i );
				printf ( "%d, ", mem->selI );
				i += 1;
			}
			printf ( "\n" );

			return 1;
		} else {
			// i didnt click on an existing ele.
			if ( altKeys[akShift] ) {
				float cXY[2] = { clickXYpass[0], clickXYpass[1] };
				float worldXY[2];
				loc_to_point_glob ( cXY, worldXY );
				int ret = shiftClick ( svg, worldXY );
				if ( ret ) {
					return 1;
				}
			}
		}

		// it didnt return already, so i didnt click on anything.
		selected = 0;
	}

	if ( svg_debugPrint_event ) {
		printf ( "jalbSvg_mEvent ( ) OVER\n" );
	}

	return 0;
}

void jalbSvg_close ( void *data ) {

}

// iterate to the object that cursor is selecting.
/* return enum cursorType
 * object:
 *  the object itself, and its parent.
 * vert:
 *  the object and, vert index, the cursorMem so i can update it to the newly created ele.
 * control:
 *  the object, vert index, and control index.
 */
int iterateToSelected ( struct svg *svg, struct nakedUnion **parent, struct nakedUnion **ele, int *vertI, int *controlI, struct cursorMem **lastCursor ) {
	printf ( "iterateToSelected ( )\n" );

	int i = 0;
	int len = arrayListGetLength ( cursorList );
	printf ( "cursorList.len: %d\n", len );

	struct nakedUnion *uni = NULL;
	ArrayList *nextList = svg->eles;
	struct cursorMem *mem = NULL;

	while ( i < len - 1) {
		mem = arrayListGetPointer ( cursorList, i );
		printf ( "mem->selI: %d\n", mem->selI );

		uni = arrayListGetPointer ( nextList, mem->selI );
		printf ( "[%d], uni->type: %d\n", i, uni->type );
		if ( uni->type == G ) {
			nextList = uni->g->eles;
			*parent = uni;
		} else {
			// this should sometimes happen.
			// at i = len-1 for object. (wont happen cuz while (len-1)
			// at i = len-2 for vert.
			// at i = len-3 for control.
			break;
		}
		i += 1;
	}
	printf ( "exited while: %d\n", i );
/*
	*parent = uni;

	i += 1;
	mem = arrayListGetPointer ( cursorList, i );
//	printf ( "mem->selI: %d\n", mem->selI );
	uni = arrayListGetPointer ( nextList, mem->selI );
	*ele = uni;
*/

	*ele = uni;
	printf ( "set ele\n" );
	if ( i == len - 1 ) {	// == len, cuz i do i += 1 directly above
		// that means an object is selected.
		return c_object;

	} else if ( i == len - 2 ) {
		// that means a vert is selected.
		i += 1;
		mem = arrayListGetPointer ( cursorList, i );
		*vertI = mem->selI;

		*lastCursor = mem;

		return c_vert;

	} else if ( i == len - 3 ) {
		// that means a control is selected.

		i += 1;
		mem = arrayListGetPointer ( cursorList, i );
		*vertI = mem->selI;

		i += 1;
		mem = arrayListGetPointer ( cursorList, i );
		*controlI = mem->selI;

		return c_control;
	} else {
		return -1;
	}
}



int shiftClick ( struct svg *svg, float *worldXY ) {
	printf ( "shiftClick ( )\n" );
	sayFloatArray ( "worldXY", worldXY, 2 );
	printf ( "selected: %d\n", selected );

	if ( selected ) {
		// figure the type of ele i am selecting.

		struct nakedUnion *parent = NULL;
		struct nakedUnion *ele = NULL;
		int vertI = -1;
		int controlI = -1;
		struct cursorMem *lastCursor = NULL;
		int selType = iterateToSelected ( svg, &parent, &ele, &vertI, &controlI, &lastCursor );
		printf ( "selType: %d\n", selType );

		if ( selType == c_object ) {
		} else if ( selType == c_vert ) {
			ArrayList *eles = NULL;
			if ( ele->type == Path ) {
				eles = ele->path->eles;
			} else {
				printf ( "ERROR\n" );
				return 0;
			}
			int numEles = arrayListGetLength ( eles );
			if ( vertI == 0 ) {
				// add to the start.
				struct pathUni *start = arrayListGetPointer ( eles, 0 );
				if ( start->type == path_MoveTo ) {
					// change moveTo to the click location.
					// and insert a lineTo at the old moveTo position.

					struct moveTo *moveTo = start->moveTo;

					struct pathUni *uni = pathUniInit ( );
					printf ( "uni: %p\n", uni );
					pathUniTypeChange0 ( uni, path_LineTo );

					printf ( "uni->type: %d\n", uni->type );

					struct lineTo *line = uni->lineTo;
					printf ( "line: %p\n", line );
					line->rel = 0;
					line->XY[0] = moveTo->XY[0];
					line->XY[1] = moveTo->XY[1];

					arrayListAddPointerI ( eles, uni, 1 );

					moveTo->XY[0] = worldXY[0];
					moveTo->XY[1] = worldXY[1];
				}

				printf ( "over\n" );
			} else if ( vertI == numEles - 1 ) {
				// add to the end.

				struct pathUni *uni = pathUniInit ( );
				printf ( "uni: %p\n", uni );
				pathUniTypeChange0 ( uni, path_LineTo );

				printf ( "uni->type: %d\n", uni->type );

				struct lineTo *line = uni->lineTo;
				printf ( "line: %p\n", line );
				line->rel = 0;
				line->XY[0] = worldXY[0];
				line->XY[1] = worldXY[1];

				arrayListAddEndPointer ( eles, uni );

				// change the cursor so its select this now.
				lastCursor->selI += 1;
			}
			return 1;
		} else if ( selType == c_control ) {
		}
	} else {
		// this means create a new path object?
	}
	return 0;
}


void move_pUni ( struct pathUni *pUni,  struct pathUni *pUniNext, float dx, float dy ) {
//	if ( svg_debugPrint_event ) {
		printf ( "move_pUni ( )\n" );
		printf ( "pUni->type: %d\n", pUni->type );
//	}

	if ( pUni->type == path_MoveTo ) {
		struct moveTo *ele = pUni->moveTo;
		ele->XY[0] += dx;
		ele->XY[1] += dy;

		if ( pUniNext ) {
			if ( pUniNext->type == path_CubicBez ) {
				pUniNext->cubicBez->c0[0] += dx;
				pUniNext->cubicBez->c0[1] += dy;
			}
		}
	} else if ( pUni->type == path_LineTo ) {
		struct lineTo *ele = pUni->lineTo;
		ele->XY[0] += dx;
		ele->XY[1] += dy;
	} else if ( pUni->type == path_CubicBez ) {
		struct cubicBez *ele = pUni->cubicBez;
		ele->XY[0] += dx;
		ele->XY[1] += dy;

//		ele->c0[0] += dx;
//		ele->c0[1] += dy;

		ele->c1[0] += dx;
		ele->c1[1] += dy;

		if ( pUniNext ) {
			if ( pUniNext->type == path_CubicBez ) {
				pUniNext->cubicBez->c0[0] += dx;
				pUniNext->cubicBez->c0[1] += dy;
			}
		}
	} else if ( pUni->type == path_QuadBez ) {
		struct quadBez *ele = pUni->quadBez;
		ele->XY[0] += dx;
		ele->XY[1] += dy;
	} else if ( pUni->type == path_EllipArc ) {
		struct ellipArc *ele = pUni->ellipArc;
		ele->XY[0] += dx;
		ele->XY[1] += dy;
	} else if ( pUni->type == path_PathEnd ) {
	}

//	if ( svg_debugPrint_event ) {
		printf ( "move_pUni ( ) OVER\n" );
//	}
}


/** Util */

// this only works if they are not relative?
// otherwise i need to keep track of the XY of prev ele.
void get_pathUni_XY ( struct pathUni *pUni, float *XY ) {
	if ( pUni->type == path_MoveTo ) {
		struct moveTo *ele = pUni->moveTo;
		XY[0] = ele->XY[0];
		XY[1] = ele->XY[1];

	} else if ( pUni->type == path_LineTo ) {
		struct lineTo *ele = pUni->lineTo;
		XY[0] = ele->XY[0];
		XY[1] = ele->XY[1];

	} else if ( pUni->type == path_CubicBez ) {
		struct cubicBez *ele = pUni->cubicBez;
		XY[0] = ele->XY[0];
		XY[1] = ele->XY[1];

	} else if ( pUni->type == path_QuadBez ) {
		struct quadBez *ele = pUni->quadBez;
		XY[0] = ele->XY[0];
		XY[1] = ele->XY[1];

	} else if ( pUni->type == path_EllipArc ) {
		struct ellipArc *ele = pUni->ellipArc;
		XY[0] = ele->XY[0];
		XY[1] = ele->XY[1];

	} else if ( pUni->type == path_PathEnd ) {
	}
}

void point_to_loc_glob ( float *p0, float *pSet ) {
	point_to_loc ( p0, pSet, glob_viewLoc, glob_viewScale );
}

void loc_to_point_glob ( float *p0, float *pSet ) {
	loc_to_point ( p0, pSet, glob_viewLoc, glob_viewScale );
}


/** Api Setter */

void set_set_viewScale ( void *f ) {
	setViewScale = f;
}


/** Debug */

void set_svg_debugPrint_render ( int i ) {
	printf ( "set_svg_debugPrint_render ( )\n" );
	printf ( "i: %d\n", i );

	svg_debugPrint_render = i;

	printf ( "set_svg_debugPrint_render ( ) OVER\n" );
}

void toggle_svg_debugPrint_render ( ) {
	printf ( "toggle_svg_debugPrint_render ( )\n" );

	if ( svg_debugPrint_render ) {
		svg_debugPrint_render = 0;
	} else {
		svg_debugPrint_render = 1;
	}

	printf ( "svg_debugPrint_render: %d\n", svg_debugPrint_render );

	printf ( "toggle_svg_debugPrint_render ( ) OVER\n" );
}

void toggle_svg_debugPrint_event ( ) {
	printf ( "toggle_svg_debugPrint_event ( )\n" );

	if ( svg_debugPrint_event ) {
		svg_debugPrint_event = 0;
	} else {
		svg_debugPrint_event = 1;
	}

	printf ( "svg_debugPrint_event: %d\n", svg_debugPrint_event );

	printf ( "toggle_svg_debugPrint_event ( ) OVER\n" );
}






