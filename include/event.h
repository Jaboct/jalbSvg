#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <jalb/jama.h>
#include <jalb/jalbSb.h>

//#include <jalb/jalb_cursor.h>	// this requires me to convert it from a struct to an int, todo.

/** Forward Declaring */

struct svg;
struct path;
struct pathUni;
struct cursorMem;
struct nakedUnion;


/** Functions */

int svg_event ( SDL_Event *e, int *clickXYpass, int *eleWH, struct svg *svg,
		float *viewLoc, float viewScale );

void addText ( struct svg *svg, int *clickXY,
		float *viewLoc, float viewScale );

int nakedList_mEvent ( SDL_Event *e, int *clickXYpass, int *eleWH, ArrayList *eles,
		float *viewLoc, float viewScale );

int path_mEvent ( SDL_Event *e, int *clickXYpass, int *eleWH, struct path *path,
		float *viewLoc, float viewScale );


// iterate to the object that cursor is selecting.
/* return enum cursorType
 * object:
 *  the object itself, and its parent.
 * vert:
 *  the object and the vert index
 * control:
 *  the object, vert index, and control index.
 */
int iterateToSelected ( struct svg *svg, struct nakedUnion **parent, struct nakedUnion **ele,
		int *vertI, int *controlI, struct cursorMem **lastCursor );
int shiftClick ( struct svg *svg, float *worldXY );

void move_pUni ( struct pathUni *pUni,  struct pathUni *pUniNext, float dx, float dy );









