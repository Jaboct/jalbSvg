#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <jalb/jalbSay.h>

/** Functions */

// convert a world loc to a screen loc.
void point_to_loc ( float *p0, float *pSet, float *viewLoc, float viewScale );

// convert a screen loc to a world loc.
void loc_to_point ( float *p0, float *pSet, float *viewLoc, float viewScale );
void loc_to_pointI ( int *p0, float *pSet, float *viewLoc, float viewScale );


int pointInside ( float *p, float *XYWH );
int pointInsideI ( int *p, float *XYWH );
