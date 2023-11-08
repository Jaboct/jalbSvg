#include "event.h"

/** Varaibles */

// editing vars
extern int selected;
extern ArrayList *selList;
extern int depth;

extern int renderMode;
extern int pointW;

// debug vars
extern int svg_debugPrint_event;

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

			depth += 1;
			int ret = nakedList_mEvent ( e, clickXYpass, eleWH, g->eles,
				viewLoc, viewScale );
			depth -= 1;
			if ( ret == 1 ) {
				handleCursor;
				return ret;
			}

		} else if ( uni->type == Path ) {
			struct path *path = uni->path;
			depth += 1;
			int ret = path_mEvent ( e, clickXYpass, eleWH, path,
				viewLoc, viewScale );
			depth -= 1;
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

	int i;
	int len;

	i = 0;
	len = arrayListGetLength ( path->eles );
	while ( i < len ) {
		struct pathUni *uni = arrayListGetPointer ( path->eles, i );

		float XY[2];
		get_pathUni_XY ( uni, XY );

		point_to_loc ( XY, XY );

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

		i += 1;
	}

	if ( svg_debugPrint_event ) {
		printf ( "path_mEvent ( ) OVER\n" );
	}

	return 0;
}











