#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <jalb/jalbSay.h>

/** Functions */

// convert a world loc to a screen loc.
// world_to_screen
void point_to_loc ( float *p0, float *pSet, float *viewLoc, float viewScale );
void world_to_screen ( float *pWorld, float *pScreen, float *viewLoc, float viewScale );

// convert a screen loc to a world loc.
// screen_to_world
void loc_to_point ( float *p0, float *pSet, float *viewLoc, float viewScale );
void screen_to_world ( float *pScreen, float *pWorld, float *viewLoc, float viewScale );

void loc_to_pointI ( int *p0, float *pSet, float *viewLoc, float viewScale );
void screen_to_world_i ( int *pScreen, float *pWorld, float *viewLoc, float viewScale );


int pointInside ( float *p, float *XYWH );
int pointInsideI ( int *p, float *XYWH );



