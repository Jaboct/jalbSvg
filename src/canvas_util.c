#include "canvas_util.h"

/** Functions */

//extern float glob_viewScale;
//extern float glob_viewLoc[];

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



void loc_to_point ( float *p0, float *pSet, float *viewLoc, float viewScale ) {
//	sayFloatArray ( "p0", p0, 2 );
//	printf ( "viewScale: %f\n", viewScale );

	pSet[0] = p0[0] * viewScale + viewLoc[0];
	pSet[1] = p0[1] * viewScale + viewLoc[1];
}



