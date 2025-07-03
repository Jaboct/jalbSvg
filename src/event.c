#include "event.h"

/** Varaibles */

extern char altKeys[];

extern struct jalbFont *fonts[];


// editing vars
extern int selected;
extern int mouseHeld;

extern ArrayList *cursorList;
extern int cursor_depth;

extern int renderMode;
extern int cursorInputMode;

extern int pointW;

// debug vars
extern int svg_debugPrint_event;


#define DEBUGPRINT_JALB_CURSOR 0

int controlPointR = 4;




/** Functions */


int svg_event ( SDL_Event *e, int *clickXYpass, int *eleWH, struct svg *svg,
		float *viewLoc, float viewScale ) {

	cursor_depth = 0;

	if ( e->type == SDL_MOUSEMOTION ) {
		if ( selected &&
		     mouseHeld ) {

			struct nakedUnion *parent = NULL;
			struct nakedUnion *ele = NULL;
			int vertI = -1;
			int controlI = -1;
			struct cursorMem *lastCursor = NULL;
			int selType = iterateToSelected ( svg, &parent, &ele, &vertI, &controlI, &lastCursor );
			if ( selType == cs_vert ) {
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

			} else if ( selType == cs_control ) {
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

			sayCursor;
/*
			printf ( "cursorList.len: %d\n", arrayListGetLength ( cursorList ) );

			int i = 0;
			int len = arrayListGetLength ( cursorList );
			while ( i < len ) {
				struct cursorMem *mem = arrayListGetPointer ( cursorList, i );
				printf ( "%d, ", mem->selI );
				i += 1;
			}
			printf ( "\n" );
*/

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
			} else {
				// if im in text mode, add a new text box.
				if ( renderMode == renderM_editAll ) {
					if ( cursorInputMode == ci_text ) {
						addText ( svg, clickXYpass,
							viewLoc, viewScale );
					}
				}
			}
		}

		// it didnt return already, so i didnt click on anything.
		selected = 0;
	}

	return 0;
}

void addText ( struct svg *svg, int *clickXY,
		float *viewLoc, float viewScale ) {
	printf ( "addText ( )\n" );

	float fClickXY[2] = { clickXY[0], clickXY[1] };
	float worldXY[2];
	loc_to_point ( fClickXY, worldXY, viewLoc, viewScale );

	sayFloatArray ( "worldXY", worldXY, 2 );

	// rn just drill to the first group.
	ArrayList *eles = svg->eles;
	if ( arrayListGetLength ( eles ) > 0 ) {
		struct nakedUnion *naked = arrayListGetPointer ( eles, 0 );
		if ( naked->type == G ) {
			eles = naked->g->eles;
		} else {
			printf ( "add text ERROR\n" );
			return;
		}
	}

	int numEles = arrayListGetLength ( eles );

	// add it to eles.
	struct nakedUnion *naked = nakedUnionInit ( );
	arrayListAddEndPointer ( eles, naked );

	nakedUnionTypeChange0 ( naked, Text );
	struct text *text = naked->text;
	text->x = worldXY[0];
	text->y = worldXY[1];

	// TODO, this should come from my default.
//	text->fontSize = fonts[0]->atlasInfo.glyphH;

	struct tspan *span = tspanInit ( );
	arrayListAddEndPointer ( text->spanList, span );
	strcpy ( span->body, "new span" );
	span->fontSize = fonts[0]->atlasInfo.glyphH;

	span->x = worldXY[0];
	span->y = worldXY[1];

	tspanPostInit ( span );

	// set cursor
	{
		// set cursor to this text index.
		cursor_depth = 1;
		int i = numEles;
		handleCursor_start;
	}
	{
		// set cursor to group 0
		cursor_depth -= 1;
		int i = 0;
		handleCursor;
	}
}


int nakedList_mEvent ( SDL_Event *e, int *clickXYpass, int *eleWH, ArrayList *eles,
		float *viewLoc, float viewScale ) {

	if ( renderMode != renderM_editAll ) {
		return 0;
	}

	int i;
	int len;

	i = 0;
	len = arrayListGetLength ( eles );
	while ( i < len ) {
		struct nakedUnion *uni = arrayListGetPointer ( eles, i );

		if ( uni->type == G ) {
//			printf ( "TODO\n" );
			struct g *g = uni->g;

			cursorDown;
			int ret = nakedList_mEvent ( e, clickXYpass, eleWH, g->eles,
				viewLoc, viewScale );
			cursorUp;
			if ( ret == 1 ) {
				handleCursor;
				return ret;
			}

		} else if ( uni->type == Path ) {
			struct path *path = uni->path;
			cursorDown;
			int ret = path_mEvent ( e, clickXYpass, eleWH, path,
				viewLoc, viewScale );
			cursorUp;
			if ( ret == 1 ) {
//				selI = i;
				handleCursor;
				return ret;
			}
		}

		i += 1;
	}
	return 0;
}

// return 1 if i select this ele
int path_mEvent ( SDL_Event *e, int *clickXYpass, int *eleWH, struct path *path,
		float *viewLoc, float viewScale ) {
	if ( svg_debugPrint_event ) {
		printf ( "path_mEvent ( )\n" );
		sayIntArray ( "clickXYpass", clickXYpass, 2 );
	}

	// only check this path if it, or one of its sub eles is being edited.

	int i;
	int len;

	i = 0;
	len = arrayListGetLength ( path->eles );
	while ( i < len ) {
		struct pathUni *uni = arrayListGetPointer ( path->eles, i );

		float XY[2];
		get_pathUni_XY ( uni, XY );

		point_to_loc_glob ( XY, XY );

		sayFloatArray ( "XY", XY, 2 );

		if ( clickXYpass[0] >= XY[0] &&
		     clickXYpass[0] <= XY[0] + pointW ) {
			if ( clickXYpass[1] >= XY[1] &&
			     clickXYpass[1] <= XY[1] + pointW ) {
				selected = 1;
//				selP = i;

				printf ( "SELECTED ELE\n" );
				handleCursor_start;

				return 1;
			}
		}

		printf ( "uni->type: %d\n", uni->type );

		// eventually only check this in a few situations.
		if ( uni->type == path_CubicBez ) {
			printf ( "CHECK CONTROL\n" );

			// check the control points.
			float cXY[2];
			cXY[0] = uni->cubicBez->c0[0];
			cXY[1] = uni->cubicBez->c0[1];
			point_to_loc_glob ( cXY, cXY );
			cXY[0] -= clickXYpass[0];
			cXY[1] -= clickXYpass[1];

			sayFloatArray ( "cXY", cXY, 2 );

			float delta = vectNorm ( cXY, 2 );
			if ( delta < controlPointR ) {
				selected = 1;
				{
					cursorDown;
					int i = 0;
					handleCursor_start;
					cursorUp;
				}

				handleCursor;

				return 1;
			}

			// check c1
			cXY[0] = uni->cubicBez->c1[0];
			cXY[1] = uni->cubicBez->c1[1];
			point_to_loc_glob ( cXY, cXY );
			cXY[0] -= clickXYpass[0];
			cXY[1] -= clickXYpass[1];

			sayFloatArray ( "cXY", cXY, 2 );

			delta = vectNorm ( cXY, 2 );
			if ( delta < controlPointR ) {
				selected = 1;
				{
					cursorDown;
					int i = 1;
					handleCursor_start;
					cursorUp;
				}

				handleCursor;

				return 1;
			}
		}

		i += 1;
	}

	if ( svg_debugPrint_event ) {
		printf ( "path_mEvent ( ) OVER\n" );
	}

	return 0;
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
int iterateToSelected ( struct svg *svg, struct nakedUnion **parent, struct nakedUnion **ele,
		int *vertI, int *controlI, struct cursorMem **lastCursor ) {
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
		return cs_object;

	} else if ( i == len - 2 ) {
		// that means a vert is selected.
		i += 1;
		mem = arrayListGetPointer ( cursorList, i );
		*vertI = mem->selI;

		*lastCursor = mem;

		return cs_vert;

	} else if ( i == len - 3 ) {
		// that means a control is selected.

		i += 1;
		mem = arrayListGetPointer ( cursorList, i );
		*vertI = mem->selI;

		i += 1;
		mem = arrayListGetPointer ( cursorList, i );
		*controlI = mem->selI;

		return cs_control;
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

		if ( selType == cs_object ) {
		} else if ( selType == cs_vert ) {
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
		} else if ( selType == cs_control ) {
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











