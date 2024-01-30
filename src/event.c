#include "event.h"

/** Varaibles */

// editing vars
extern int selected;
extern ArrayList *cursorList;
extern int cursor_depth;

extern int renderMode;
extern int pointW;

// debug vars
extern int svg_debugPrint_event;


#define DEBUGPRINT_JALB_CURSOR 0

int controlPointR = 4;


/** Functions */

int nakedList_mEvent ( SDL_Event *e, int *clickXYpass, int *eleWH, ArrayList *eles,
		float *viewLoc, float viewScale ) {

	if ( renderMode != renderM_edit ) {
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











