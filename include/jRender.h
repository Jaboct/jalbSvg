#pragma once


#include <stdio.h>
#include <stdlib.h>

#include <jalb/jalbArrayList.h>

#include "jGroup.h"
#include "jPath.h"
#include "jText.h"

#include "path.h"	// for enums
#include "mod_ext.h"	// for enums
#include "render.h"

/** Structs */

enum vert_subModes {
	vSubM_move = 0,
	vSubM_rotate,
	vSubM_verts,
};


/** Functions */

void jNakedList_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass, ArrayList *eles,
		float *viewLoc, float viewScale );

void jNaked_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass, struct jNakedUnion *uni,
		float *viewLoc, float viewScale );

void jPath_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass, struct jPath *path,
		float *viewLoc, float viewScale );
void jVerts_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass, ArrayList *verts,
		float *viewLoc, float viewScale );
void controlPoints_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass, struct jPath *path,
		float *viewLoc, float viewScale );

void verts_CAD_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass, ArrayList *verts,
		float *viewLoc, float viewScale );
void lines_CAD_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass, struct jPath *path,
		float *viewLoc, float viewScale );

// text

void jText_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass, struct jText *text,
		float *viewLoc, float viewScale );

void jRectRender ( int *screenDims, GLuint *glBuffers, int *XYWHpass, struct jRect *rect,
		float *viewLoc, float viewScale );
void jCircRender ( int *screenDims, GLuint *glBuffers, int *XYWHpass, struct jCirc *circ,
		float *viewLoc, float viewScale );

void complexEleRender ( int *screenDims, GLuint *glBuffers, int *XYWHpass, struct complexEle *complex,
		float *viewLoc, float viewScale );

void grid_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass, float *gridWH,
		float *viewLoc, float viewScale );
void grid_render_cursor ( int *screenDims, GLuint *glBuffers, int *XYWHpass, float *gridWH,
		float *viewLoc, float viewScale, int *cursorScreenXY );

// always rounds up
float roundUp ( float val, float roundTo );
// round up or down, depending on what closer.
float roundClose ( float val, float roundTo );

/** Util */

void path_lrtb ( struct jPath *path, float *lrtb );


