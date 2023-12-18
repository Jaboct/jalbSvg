#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <jalb/jalbSay.h>

/** Functions */

void point_to_loc ( float *p0, float *pSet, float *viewLoc, float viewScale );

void loc_to_point ( float *p0, float *pSet, float *viewLoc, float viewScale );
