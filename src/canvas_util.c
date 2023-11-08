#include "canvas_util.h"

/** Functions */

extern float glob_viewScale;
extern float glob_viewLoc[];

void point_to_loc ( float *p0, float *pSet ) {

	printf ( "point_to_loc ( )\n" );
	sayFloatArray ( "glob_viewLoc", glob_viewLoc, 2 );
	printf ( "glob_viewScale: %f\n", glob_viewScale );
	sayFloatArray ( "p0", p0, 2 );


//	pSet[0] = p0[0] * glob_viewScale - glob_viewLoc[0];
//	pSet[1] = p0[1] * glob_viewScale - glob_viewLoc[1];

//	pSet[0] = p0[0];
//	pSet[1] = p0[1];


	pSet[0] = ( p0[0] - glob_viewLoc[0] ) / glob_viewScale;
	pSet[1] = ( p0[1] - glob_viewLoc[1] ) / glob_viewScale;


//	sayFloatArray ( "pSet", pSet, 2 );
}


