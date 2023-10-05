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

void jalbSvg_renderDyn ( int *screenDims, GLuint *glBuffers, int *XYWHpass, void *data,
		float *viewLoc, float viewScale );
int jalbSvg_mEvent ( SDL_Event *e, int *clickXYpass, int *eleWH, void *data,
		float *viewLoc, float viewScale );

void jalbSvg_close ( void *data );




// i need the dynamic canvas info.

void point_to_loc ( float *p0, float *pSet );

void svg_render ( int *screenDims, GLuint *glBuffers, int *XYWH, struct svg *svg );
void eles_render ( int *screenDims, GLuint *glBuffers, int *XYWH, ArrayList *eles );
void path_render ( int *screenDims, GLuint *glBuffers, int *XYWH, struct path *path );

void seg_render ( int *screenDims, GLuint *glBuffers, float *p0, float *p1 );
void cubicBez_render ( int *screenDims, GLuint *glBuffers, float *p0, float *p1, float *c0, float *c1 );


void segScale ( float *p0, float *p1, float *pSet, float scale, int len );

/** Screenshot */
void set_window ( void *window );
void screenshot_02 ( char *dir );
void window_screenshot_bmp ( char *dir );


int screenShot( char *dir );





















