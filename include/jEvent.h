#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <jalb/jalbArrayList.h>
#include <jalbApi/api_uiGen.h>


/** Foward Declaring */

struct cursorMem;
struct jNakedUnion;
struct jPath;
struct jText;
struct jRect;
struct jCirc;


/// temp

struct cursor_ele;
int toggle_cursorEle ( ArrayList *cursorList, struct cursor_ele *temp );
int toggle_cursorEle_child ( struct cursor_ele *ele, struct cursor_ele *temp );


/** Functions */

int jIterateToSelected ( ArrayList *eleList, struct jNakedUnion **parent, struct jNakedUnion **ele,
		int *vertI, int *controlI, struct cursorMem **lastCursor );

int jNakedList_mEvent_start ( SDL_Event *e, int *clickXYpass, int *eleWH, ArrayList *eles,
		float *viewLoc, float viewScale );
int jNakedList_mEvent ( SDL_Event *e, int *clickXYpass, int *eleWH, ArrayList *eles,
		float *viewLoc, float viewScale );

int jText_mEvent ( SDL_Event *e, int *clickXYpass, int *eleWH, struct jText *text,
		float *viewLoc, float viewScale );

int jRect_mEvent ( SDL_Event *e, int *clickXYpass, int *eleWH, struct jRect *rect,
		float *viewLoc, float viewScale );
int jRect_mPos ( int *clickXYpass, struct jRect *rect,
		float *viewLoc, float viewScale );

int jCirc_mEvent ( SDL_Event *e, int *clickXYpass, int *eleWH, struct jCirc *circ,
		float *viewLoc, float viewScale );





