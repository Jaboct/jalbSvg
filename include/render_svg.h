#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <jalb/jama.h>
#include <jalb/jalbSb.h>

#include "svg.h"
#include "render.h"

#include "mod_ext.h"

/** Functions */

void svg_render ( int *screenDims, GLuint *glBuffers, int *XYWH, struct svg *svg );
void eles_render ( int *screenDims, GLuint *glBuffers, int *XYWH, ArrayList *eles );

void path_render ( int *screenDims, GLuint *glBuffers, int *XYWH, struct path *path );

void rectRender_svg ( int *screenDims, GLuint *glBuffers, int *XYWH, struct rect *rect );
void circleRender_svg ( int *screenDims, GLuint *glBuffers, int *XYWH, struct circle *circle );
void ellipseRender_svg ( int *screenDims, GLuint *glBuffers, int *XYWH, struct ellipse *ellipse );

void textRender ( int *screenDims, GLuint *glBuffers, int *XYWH, struct text *text );


