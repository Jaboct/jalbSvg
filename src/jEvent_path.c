#include "jEvent_path.h"


/** Includes */

#include "canvas_util.h"

#include "jPath.h"
#include "path.h"

#include "jHand.h"

#include "cursor.h"

#include "jEvent.h"

#include "recursiveCursor.h"	// TODO, remove once cursor is done.


/** Variables */

extern char altKeys[];

extern int debugPrint_jvg_event;


extern struct cursor_ele *temp_clickMem;
extern struct cursor_ele *temp_clickMem_parent;
extern struct cursor_ele *glob_cursor_ele;

extern int heldType;	// enum heldTypes; (jHand.h)

// TODO, remove once cursor is done.
extern int selected;
extern int cursor_depth;

extern int vertWidth;
extern int controlPointR;

extern int pointDist;


/** Functions */

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
	printf ( "\n" );
	printf ( "jPath_mEvent ( )\n" );

	if ( debugPrint_jvg_event ) {
		printf ( "jPath_mEvent ( )\n" );
		sayIntArray ( "clickXYpass", clickXYpass, 2 );
	}

	// only check this path if it, or one of its sub eles is being edited.

	// first check the verts
	// then the control poitns of the lines
	// then see if im close enough to a line to drag the object around.

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

				path_vert_click ( i );

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

	// ok, i didnt click on a control point, now see if im trying to drag a line.

	i = 0;
	len = arrayListGetLength ( path->lines );
	while ( i < len ) {
		struct jLine *line = arrayListGetPointer ( path->lines, i );

		struct jVert *v0 = arrayListGetPointer ( path->verts, line->v0 );
		struct jVert *v1 = arrayListGetPointer ( path->verts, line->v1 );

		float fXY[2] = { clickXYpass[0], clickXYpass[1] };
		loc_to_point ( fXY, fXY, viewLoc, viewScale );
		float dist = pointSegDist ( fXY, v0->XY, v1->XY );

//		printf ( "line dist: %f\n", dist );

		if ( dist < pointDist ) {
			// im not effecting this line.

			cursorUp;
			// i dont want this specific line to be selected rn.
			handleCursor_start;
			cursorDown;

//			printf ( "CLICK ON LINE\n" );
			selected = 1;

			return 1;
		}

		i += 1;
	}



/*
	// what is this stuff?
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

// used when clicking to see if i click on a vert, and set the cursor appropriatly.
int path_vert_click ( int i ) {
	printf ( "path_vert_click ( )\n" );

	cursor_unionTypeChange0 ( temp_clickMem->payload, cu_Path );
	struct cursor_path *cuPath = temp_clickMem->payload->path;

	int *tempNext = arrayListGetNext ( cuPath->verts );
	*tempNext = i;

	ArrayList *cursorList = glob_cursor_ele->payload->group->eles;

	int ret = toggle_cursorEle ( cursorList, temp_clickMem_parent );
	printf ( "toggle_cursorEle ret: %d\n", ret );
	printf ( "cursorList.len: %d\n", arrayListGetLength ( cursorList ) );

	if ( altKeys[akShift] ) {
		// see if there is a cursor with this address already.

		// if so, see if this vert is already selected.
		// if so, remove it.
		// if not, add it, might need to turn off ->itself

		// if not, add this address.

		if ( !ret ) {
			heldType = ht_eleMove;
			arrayListAddEndPointer ( cursorList, temp_clickMem_parent );
		} else {
			// TODO free temp_clickMen_parent
			if ( ret == 2 ) {
				// idk
			} else {
				heldType = ht_eleMove;
			}
		}
		return 1;
	} else {
		// current cursor is already wiped, so simply add this.
		heldType = ht_eleMove;
		arrayListAddEndPointer ( cursorList, temp_clickMem_parent );

		return 1;
	}
}

int path_control_click ( int i ) {
	// since you are not allowed to select multiple control points
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

