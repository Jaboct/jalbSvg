#include "canvas_util.h"

/** Functions */

//extern float glob_viewScale;
//extern float glob_viewLoc[];


// convert a world loc to a screen loc. (world_to_screen)
void point_to_loc ( float *p0, float *pSet, float *viewLoc, float viewScale ) {
/*
	printf ( "point_to_loc ( )\n" );
	sayFloatArray ( "viewLoc", viewLoc, 2 );
	printf ( "viewScale: %f\n", viewScale );
	sayFloatArray ( "p0", p0, 2 );
*/

//	pSet[0] = p0[0] * glob_viewScale - glob_viewLoc[0];
//	pSet[1] = p0[1] * glob_viewScale - glob_viewLoc[1];

//	pSet[0] = p0[0];
//	pSet[1] = p0[1];


	pSet[0] = ( p0[0] - viewLoc[0] ) / viewScale;
	pSet[1] = ( p0[1] - viewLoc[1] ) / viewScale;


//	sayFloatArray ( "pSet", pSet, 2 );
}

void world_to_screen ( float *pWorld, float *pScreen, float *viewLoc, float viewScale ) {
	point_to_loc ( pWorld, pScreen, viewLoc, viewScale );
}


// convert a screen loc to a world loc.
void loc_to_point ( float *p0, float *pSet, float *viewLoc, float viewScale ) {
//	sayFloatArray ( "p0", p0, 2 );
//	printf ( "viewScale: %f\n", viewScale );

	pSet[0] = p0[0] * viewScale + viewLoc[0];
	pSet[1] = p0[1] * viewScale + viewLoc[1];
}

void screen_to_world ( float *pScreen, float *pWorld, float *viewLoc, float viewScale ) {
	loc_to_point ( pScreen, pWorld, viewLoc, viewScale );
}

void loc_to_pointI ( int *p0, float *pSet, float *viewLoc, float viewScale ) {
	pSet[0] = p0[0] * viewScale + viewLoc[0];
	pSet[1] = p0[1] * viewScale + viewLoc[1];
}

void screen_to_world_i ( int *pScreen, float *pWorld, float *viewLoc, float viewScale ) {
	loc_to_pointI ( pScreen, pWorld, viewLoc, viewScale );
}


// generally for clicking.

int pointInside ( float *p, float *XYWH ) {
	if ( p[0] >= XYWH[0] &&
	     p[0] <= XYWH[0] + XYWH[2] ) {
		if ( p[1] >= XYWH[1] &&
		     p[1] <= XYWH[1] + XYWH[3] ) {
			return 1;
		}
	}
	return 0;
}

int pointInsideI ( int *p, float *XYWH ) {
	if ( p[0] >= XYWH[0] &&
	     p[0] <= XYWH[0] + XYWH[2] ) {
		if ( p[1] >= XYWH[1] &&
		     p[1] <= XYWH[1] + XYWH[3] ) {
			return 1;
		}
	}
	return 0;
}














