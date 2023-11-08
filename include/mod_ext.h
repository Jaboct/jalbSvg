#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <jalb/jama.h>
#include <jalb/jalbSb.h>

#include "svg.h"

#include "proof.h"


/** Structs */


enum renderMode_e {
	renderM_normal = 0,
	renderM_edit,
	renderM_num,
};


/*
struct slimText {
	ArrayList *sb;	// (char)
	int cursorStartMem[3];
	int cursorEndMem[3];
//	struct undoRedo undoMem;
//	struct textSearch *search;
};
*/

struct cursorMem {
	int selI;
	int selP;
};

/** Macros */

#define handleCursor_start \
	printf ( "handleCursor_start ( )\n" ); \
	printf ( "depth: %d\n", depth ); \
	int oldLen = arrayListGetLength ( selList ); \
	while ( oldLen > depth ) { \
		arrayListRemove ( selList, oldLen - 1 ); \
		oldLen -= 1; \
	} \
	while ( oldLen < depth + 1 ) { \
		struct cursorMem *mem = malloc ( sizeof ( *mem ) ); \
		arrayListAddEndPointer ( selList, mem ); \
		oldLen += 1; \
	} \
	struct cursorMem *mem = arrayListGetPointer ( selList, depth ); \
	mem->selI = i;

#define handleCursor \
	printf ( "handleCursor ( )\n" ); \
	printf ( "depth: %d\n", depth ); \
	struct cursorMem *mem = arrayListGetPointer ( selList, depth ); \
	mem->selI = i;




/** Functions */

void *jalbSvg_init ( );

void jalbSvg_render ( int *screenDims, GLuint *glBuffers, int *XYWH, void *data );
int jalbSvg_event ( SDL_Event *e, int *clickXY, int *eleWH, void *data );

void jalbSvg_renderDyn ( int *screenDims, GLuint *glBuffers, int *XYWHpass, void *data,
		float *viewLoc, float viewScale );
int jalbSvg_mEvent ( SDL_Event *e, int *clickXYpass, int *eleWH, void *data,
		float *viewLoc, float viewScale );

void jalbSvg_close ( void *data );


// other stuff

int nakedList_mEvent ( SDL_Event *e, int *clickXYpass, int *eleWH, ArrayList *eles,
		float *viewLoc, float viewScale );
void move_pUni ( struct pathUni *pUni, float dx, float dy );
int path_mEvent ( SDL_Event *e, int *clickXYpass, int *eleWH, struct path *path,
		float *viewLoc, float viewScale );


// i need the dynamic canvas info.


void svg_render ( int *screenDims, GLuint *glBuffers, int *XYWH, struct svg *svg );
void eles_render ( int *screenDims, GLuint *glBuffers, int *XYWH, ArrayList *eles );
void path_render ( int *screenDims, GLuint *glBuffers, int *XYWH, struct path *path );

void seg_render ( int *screenDims, GLuint *glBuffers, float *p0, float *p1 );
void cubicBez_render ( int *screenDims, GLuint *glBuffers, float *p0, float *p1, float *c0, float *c1 );

void segScale ( float *p0, float *p1, float *pSet, float scale, int len );

void textRender ( int *screenDims, GLuint *glBuffers, int *XYWH, struct text *text );
void spanRender ( int *screenDims, GLuint *glBuffers, int *XYWHpass, float *glyphWH, float *fXYWH, ArrayList *sb );

void rectRender ( int *screenDims, GLuint *glBuffers, int *XYWH, struct rect *rect );
void circleRender ( int *screenDims, GLuint *glBuffers, int *XYWH, struct circle *circle );
void ellipseRender ( int *screenDims, GLuint *glBuffers, int *XYWH, struct ellipse *ellipse );


/** Util */

void get_pathUni_XY ( struct pathUni *pUni, float *XY );
void point_to_loc ( float *p0, float *pSet );


/** Api Setter */

void set_set_viewScale ( void *f );














