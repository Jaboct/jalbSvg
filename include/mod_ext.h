#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <jalb/jama.h>

#include "svg.h"


/** Functions */

void *jalbSvg_init ( );
void jalbSvg_render ( int *screenDims, GLuint *glBuffers, int *XYWH, void *data );
int jalbSvg_event ( SDL_Event *e, int *clickXY, int *eleWH, void *data );
void jalbSvg_close ( void *data );




// i need the dynamic canvas info.

void svg_render ( int *screenDims, GLuint *glBuffers, int *XYWH, struct svg *svg );
void eles_render ( int *screenDims, GLuint *glBuffers, int *XYWH, ArrayList *eles );
void path_render ( int *screenDims, GLuint *glBuffers, int *XYWH, struct path *path );

void cubicBez_render ( int *screenDims, GLuint *glBuffers, float *p0, float *p1, float *c0, float *c1 );


void segScale ( float *p0, float *p1, float *pSet, float scale, int len );




























