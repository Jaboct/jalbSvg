#pragma once


/** Includes */

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <jalb/jama.h>


/** Foward Declaring */

struct jPath;


/** Functions */

void add_line ( struct jPath *path, int vertI, int lineType, int *clickXYpass,
		float *viewLoc, float viewScale );
int jPath_mEvent ( SDL_Event *e, int *clickXYpass, int *eleWH, struct jPath *path,
		float *viewLoc, float viewScale );

void move_jPathVert ( struct jPath *path, int vertI, float dx, float dy );

int path_vert_click ( int i );


