#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <jalb/jama.h>
#include <jalb/jalbSb.h>

#include <jalbDraw/jalb_draw2d_api.h>


#include "canvas_util.h"


/** Functions */

void seg_render ( int *screenDims, GLuint *glBuffers, float *p0, float *p1, float lineW,
		float *viewLoc, float viewScale );
void cubicBez_render ( int *screenDims, GLuint *glBuffers, float *p0, float *p1, float *c0, float *c1,
		float *viewLoc, float viewScale );
void quadBez_render ( int *screenDims, GLuint *glBuffers, float *p0, float *p1, float *c0,
		float *viewLoc, float viewScale );
void ellipseArc_render ( int *screenDims, GLuint *glBuffers, float *p0, float *p1, float *c0, float *c1,
		float *viewLoc, float viewScale );

void segScale ( float *p0, float *p1, float *pSet, float scale, int len );

//void textRender ( int *screenDims, GLuint *glBuffers, int *XYWH, struct text *text );
//void spanRender ( int *screenDims, GLuint *glBuffers, int *XYWHpass, float *glyphWH, float *fXYWH, ArrayList *sb,
//		float *viewLoc, float viewScale );
int spanRender ( int *screenDims, GLuint *glBuffers, int *XYWHpass, float *glyphWH, float *fXYWH, ArrayList *sb,
		int selected, int *cursorStartMem, int *cursorEndMem,
		float *viewLoc, float viewScale );

void rectRender ( int *screenDims, GLuint *glBuffers, int *XYWH, float *rXYWH,
		float *viewLoc, float viewScale );

void circleRender ( int *screenDims, GLuint *glBuffers, int *XYWH, float *XY, float r,
		float *viewLoc, float viewScale );
void ellipseRender ( int *screenDims, GLuint *glBuffers, int *XYWH, float *XY, float rx, float ry,
		float *viewLoc, float viewScale );




























