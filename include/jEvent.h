#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <jalb/jalbArrayList.h>

#include "hand.h"
#include "jGroup.h"


/** Functions */

int jIterateToSelected ( ArrayList *eleList, struct jNakedUnion **parent, struct jNakedUnion **ele,
		int *vertI, int *controlI, struct cursorMem **lastCursor );


int jNakedList_mEvent ( SDL_Event *e, int *clickXYpass, int *eleWH, ArrayList *eles,
		float *viewLoc, float viewScale );

void add_line ( struct jPath *path, int vertI, int lineType, int *clickXYpass,
		float *viewLoc, float viewScale );
int jPath_mEvent ( SDL_Event *e, int *clickXYpass, int *eleWH, struct jPath *path,
		float *viewLoc, float viewScale );

void move_jPathVert ( struct jPath *path, int vertI, float dx, float dy );


int jText_mEvent ( SDL_Event *e, int *clickXYpass, int *eleWH, struct jText *text,
		float *viewLoc, float viewScale );






