#include "jEvent.h"


/** Variables */

extern char altKeys[];

extern struct jalbFont *fonts[];
extern int numFonts;


extern ArrayList *cursorList;
extern int cursor_depth;


extern int renderMode;


extern int vertWidth;
extern int controlPointR;

extern int selected;

int debugPrint_jvg_event = 0;


extern int cStart[];
extern int cEnd[];


extern int tabW;

/** Functions */

int jIterateToSelected ( ArrayList *eleList, struct jNakedUnion **parent, struct jNakedUnion **ele,
		int *vertI, int *controlI, struct cursorMem **lastCursor ) {
//	printf ( "iterateToSelected ( )\n" );

	int i = 0;
	int len = arrayListGetLength ( cursorList );
//	printf ( "cursorList.len: %d\n", len );

	struct jNakedUnion *uni = NULL;
//	ArrayList *nextList = svg->eles;
	ArrayList *nextList = eleList;
	struct cursorMem *mem = NULL;

	while ( i < len - 1) {
		mem = arrayListGetPointer ( cursorList, i );
//		printf ( "mem->selI: %d\n", mem->selI );

		uni = arrayListGetPointer ( nextList, mem->selI );
//		printf ( "[%d], uni->type: %d\n", i, uni->type );
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
//	printf ( "exited while: %d\n", i );
/*
	*parent = uni;

	i += 1;
	mem = arrayListGetPointer ( cursorList, i );
//	printf ( "mem->selI: %d\n", mem->selI );
	uni = arrayListGetPointer ( nextList, mem->selI );
	*ele = uni;
*/

	*ele = uni;
//	printf ( "set ele\n" );
	if ( i == len - 1 ) {	// == len, cuz i do i += 1 directly above
		// that means an object is selected.
		return cs_object;

	} else if ( i == len - 2 ) {
		// that means a vert is selected.
		// OR im editing text in a text box.

		if ( uni->type == jNaked_Path ) {
			i += 1;
			mem = arrayListGetPointer ( cursorList, i );
			*vertI = mem->selI;

			*lastCursor = mem;

			return cs_vert;
		} else if ( uni->type == jNaked_Text ) {
			i += 1;
			mem = arrayListGetPointer ( cursorList, i );

			*vertI = mem->selI;

			*lastCursor = mem;

//			printf ( "SELECTED TEXT\n" );

			return cs_text;
		}

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

	return -1;
}


int jNakedList_mEvent ( SDL_Event *e, int *clickXYpass, int *eleWH, ArrayList *eles,
		float *viewLoc, float viewScale ) {
	if ( debugPrint_jvg_event ) {
		printf ( "jNakedList_mEvent ( )\n" );
	}

	if ( renderMode != renderM_edit ) {
		return 0;
	}

	if ( e->button.button == SDL_BUTTON_MIDDLE ) {
		// treat it like im just moving the camera around.
		return 0;
	}

	if ( altKeys[akShift] ||
	     altKeys[akCtrl] ) {
		// if i currently have a vert seleted, the add to it the place i clicked.
		// but if i clicked on a different vert, the draw a line between them.

		struct jNakedUnion *parent;
		struct jNakedUnion *ele;
		int vertI = -1;
		int controlI = -1;
		struct cursorMem *lastCursor;

		int selType = jIterateToSelected ( eles, &parent, &ele,
			&vertI, &controlI, &lastCursor );
		printf ( "vertI: %d\n", vertI );
		if ( selType == cs_vert ) {
			// see if im clicking on another vert.
			// then make sure there is not currently a line between this vert and that.
			// if not, then create only a new line.

			// if im not clicking on another vert, then add a new vert, and a new line.

			struct jPath *path = ele->path;

			if ( altKeys[akShift] ) {
				add_line ( path, vertI, path_LineTo, clickXYpass,
					viewLoc, viewScale );
			} else if ( altKeys[akCtrl] ) {
				add_line ( path, vertI, path_CubicBez, clickXYpass,
					viewLoc, viewScale );
			}

			return 1;
		}
	}

	int i;
	int len;

	i = 0;
	len = arrayListGetLength ( eles );
	while ( i < len ) {
		struct jNakedUnion *uni = arrayListGetPointer ( eles, i );

		if ( uni->type == jNaked_G ) {
//			printf ( "TODO\n" );
			struct jGroup *g = uni->g;

			cursorDown;
			int ret = jNakedList_mEvent ( e, clickXYpass, eleWH, g->eles,
				viewLoc, viewScale );
			cursorUp;
			if ( ret == 1 ) {
				handleCursor;
				return ret;
			}

		} else if ( uni->type == jNaked_Path ) {
			struct jPath *path = uni->path;
			cursorDown;
			int ret = jPath_mEvent ( e, clickXYpass, eleWH, path,
				viewLoc, viewScale );
			cursorUp;
			if ( ret == 1 ) {
//				selI = i;
				handleCursor;
				return ret;
			}
		} else if ( uni->type == jNaked_Text ) {
			struct jText *text = uni->text;
			cursorDown;
			int ret = jText_mEvent ( e, clickXYpass, eleWH, text,
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

void add_line ( struct jPath *path, int vertI, int lineType, int *clickXYpass,
		float *viewLoc, float viewScale ) {
//	printf ( "add_line ( )\n" );
//	printf ( "lineType: %d\n", lineType );

	float worldXY[2];
	loc_to_pointI ( clickXYpass, worldXY, viewLoc, viewScale );
	struct jVert *v = jVertInit ( );
	v->XY[0] = worldXY[0];
	v->XY[1] = worldXY[1];
	int numVerts = arrayListGetLength ( path->verts );
	arrayListAddEndPointer ( path->verts, v );
	struct jLine *l = jLineInit ( );
	l->v0 = vertI;
	l->v1 = numVerts;

	if ( lineType == path_LineTo ) {
		l->type = path_LineTo;
	} else if ( lineType == path_CubicBez ) {
		l->type = path_CubicBez;
		// calc the vector, and put the control point.
		float vect[2];
		struct jVert *v0 = arrayListGetPointer ( path->verts, vertI );
		vectSub ( v0->XY, worldXY, vect, 2 );
		l->c0[0] = v0->XY[0] - (vect[0] / 10.0);
		l->c0[1] = v0->XY[1] - (vect[1] / 10.0);

		l->c1[0] = worldXY[0] + (vect[0] / 10.0);
		l->c1[1] = worldXY[1] + (vect[1] / 10.0);
	} else {
		printf ( "add_line ( ) ERROR\n" );
	}

	arrayListAddEndPointer ( path->lines, l );

	// set the cursor to here?
}

// return 1 if i select this ele
int jPath_mEvent ( SDL_Event *e, int *clickXYpass, int *eleWH, struct jPath *path,
		float *viewLoc, float viewScale ) {
	if ( debugPrint_jvg_event ) {
		printf ( "jPath_mEvent ( )\n" );
		sayIntArray ( "clickXYpass", clickXYpass, 2 );
	}

	// only check this path if it, or one of its sub eles is being edited.

	int i;
	int len;

	i = 0;
	len = arrayListGetLength ( path->verts );
	while ( i < len ) {
		struct jVert *vert = arrayListGetPointer ( path->verts, i );

		float screenXY[2];

		point_to_loc ( vert->XY, screenXY, viewLoc,  viewScale );

//		sayFloatArray ( "screenXY", screenXY, 2 );

		if ( clickXYpass[0] >= screenXY[0] - (vertWidth / 2.0) &&
		     clickXYpass[0] <= screenXY[0] + (vertWidth / 2.0) ) {
			if ( clickXYpass[1] >= screenXY[1] - (vertWidth / 2.0) &&
			     clickXYpass[1] <= screenXY[1] + (vertWidth / 2.0) ) {
				printf ( "CLICK ON VERT\n" );

				selected = 1;

				handleCursor_start;

				return 1;
			}
		}

		i += 1;
	}


	i = 0;
	len = arrayListGetLength ( path->lines );
	while ( i < len ) {
		struct jLine *line = arrayListGetPointer ( path->lines, i );

		if ( line->type == path_CubicBez ) {
			// check both control points.

			float cXY[2];
			point_to_loc ( line->c0, cXY, viewLoc,  viewScale );
			cXY[0] -= clickXYpass[0];
			cXY[1] -= clickXYpass[1];
			float delta = vectNorm ( cXY, 2 );
			if ( delta < controlPointR ) {
				printf ( "CLICK ON CONTROL\n");
				{
					selected = 1;
					cursorDown;
					int i = 0;
					handleCursor_start;
					cursorUp;
				}
				handleCursor;

				return 1;
			}

			point_to_loc ( line->c1, cXY, viewLoc,  viewScale );
			cXY[0] -= clickXYpass[0];
			cXY[1] -= clickXYpass[1];
			delta = vectNorm ( cXY, 2 );
			if ( delta < controlPointR ) {
				printf ( "CLICK ON CONTROL\n");
				{
					selected = 1;
					cursorDown;
					int i = 1;
					handleCursor_start;
					cursorUp;
				}
				handleCursor;

				return 1;
			}
		} else if ( line->type == path_QuadBez ) {
			// check 1 control point.

			float cXY[2];
			point_to_loc ( line->c0, cXY, viewLoc,  viewScale );
			cXY[0] -= clickXYpass[0];
			cXY[1] -= clickXYpass[1];
			float delta = vectNorm ( cXY, 2 );
			if ( delta < controlPointR ) {
				printf ( "CLICK ON CONTROL\n");
				{
					selected = 1;
					cursorDown;
					int i = 0;
					handleCursor_start;
					cursorUp;
				}
				handleCursor;

				return 1;
			}

		}

		i += 1;
	}
/*
		float XY[2];
		get_pathUni_XY ( uni, XY );

		point_to_loc_glob ( XY, XY );

		sayFloatArray ( "XY", XY, 2 );

		if ( clickXYpass[0] >= XY[0] &&
		     clickXYpass[0] <= XY[0] + vertWidth ) {
			if ( clickXYpass[1] >= XY[1] &&
			     clickXYpass[1] <= XY[1] + vertWidth ) {
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
*/

	if ( debugPrint_jvg_event ) {
		printf ( "path_mEvent ( ) OVER\n" );
	}

	return 0;
}


void move_jPathVert ( struct jPath *path, int vertI, float dx, float dy ) {
	printf ( "move_jPathUni ( )\n" );

	struct jVert *vert = arrayListGetPointer ( path->verts, vertI );

	vert->XY[0] += dx;
	vert->XY[1] += dy;

	// iterate all the lines, if they use this vert, move the control point.
	int i;
	int len;

	i = 0;
	len = arrayListGetLength ( path->lines );
	while ( i < len ) {
		struct jLine *line = arrayListGetPointer ( path->lines, i );

		if ( line->type == path_CubicBez ) {
			if ( line->v0 == vertI ) {
				line->c0[0] += dx;
				line->c0[1] += dy;
			}
			if ( line->v1 == vertI ) {
				line->c1[0] += dx;
				line->c1[1] += dy;
			}
		}

		i += 1;
	}

}

int jText_mEvent ( SDL_Event *e, int *clickXYpass, int *eleWH, struct jText *text,
		float *viewLoc, float viewScale ) {
//	printf ( "jText_mEvent ( )\n" );

	float screenXYWH[4];
	point_to_loc ( text->XYWH, screenXYWH, viewLoc, viewScale );

	screenXYWH[2] = text->XYWH[2] / viewScale;
	screenXYWH[3] = text->XYWH[3] / viewScale;

//	sayIntArray ( "clickXYpass", clickXYpass, 2 );
//	sayFloatArray ( "screenXYWH", screenXYWH, 4 );

	if ( pointInsideI ( clickXYpass, screenXYWH ) ) {
/*
	if ( clickXYpass[0] >= screenXYWH[0] &&
	     clickXYpass[0] < screenXYWH[0] + screenXYWH[2] ) {
		if ( clickXYpass[1] >= screenXYWH[1] &&
		     clickXYpass[1] < screenXYWH[1] + screenXYWH[3] ) {
*/

//			printf ( "CLICKED IN TEXT\n" );

			if ( altKeys[akCtrl] ) {
				// i want to edit the box itself, not the text inside.

				// TODO this up and down is a shitty work around. fix it.
				int i = 0;

				cursorUp;
				handleCursor_start;
				cursorDown;
				return 1;
			}

			// i doesnt matter, aslong as its 1 deeper than the text ele itself so i know im editing the internal text, not moving the ele around
			int i = 0;
			handleCursor_start;

			selected = 1;
			cStart[0] = 0;
			cEnd[0] = 0;

			float glyphWH[2] = {
				fonts[0]->atlasInfo.glyphW / viewScale,
				fonts[0]->atlasInfo.glyphH / viewScale
			};
//			sayFloatArray ( "glyphWH", glyphWH, 2 );

			int charXY[2];
			charXY[0] = (clickXYpass[0] - screenXYWH[0]) / glyphWH[0] + 0.5;
			charXY[1] = (clickXYpass[1] - screenXYWH[1]) / glyphWH[1];

//			sayIntArray ( "charXY", charXY, 2 );

			
			int maxCols = text->XYWH[2] / fonts[0]->atlasInfo.glyphW;
			int textWrap = 1;

//			printf ( "maxCols: %d\n", maxCols );

// set_debugPrint_jalbSb ( 1 );
			int overClickLines = -1;
			// determines the index of the click (this should also handle return the cursorXY...)
			int ret = newSbClickToIndex_wrap ( charXY, text->sb, maxCols, tabW, &overClickLines );

// set_debugPrint_jalbSb ( 0 );

//			printf ( "ret: %d\n", ret );

			cStart[0] = ret;
			cEnd[0] = ret;

			// takes the index and returnes the clickXY
			newSbIndexToCoords ( cStart[0], &cStart[1], text->sb, textWrap, maxCols, tabW );

			return 1;
		}
//	}

	// so if its 1 deeper with a value of 0 then im editing the text.
	// 0 = editing text, 1 = moving it around.
	// 2 im editing top left corner? 3 top right.
	// 4 bot left, 5 bot right.
	// see if i click on the bottom right, so adjust the size.
	int boxWidth = 10 / viewScale;
	float boxXYWH[4] = {
		screenXYWH[0] + screenXYWH[2],
		screenXYWH[1] + screenXYWH[3],
		boxWidth,
		boxWidth,
	};
	if ( pointInsideI ( clickXYpass, boxXYWH ) ){
		printf ( "ADJUST CORNER\n" );
		printf ( "cursor_depth: %d\n", cursor_depth );

		int i = 5;

//		cursorDown;
		handleCursor_start;
//		cursorUp;

		selected = 1;

		return 1;
	}

	return 0;
}
















