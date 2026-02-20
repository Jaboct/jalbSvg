#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <jalb/jama.h>
#include <jalb/jalbSb.h>


/** Forward Declaring */

struct pathUni;


/** Structs */


enum renderMode_e {
	renderM_view = 0,
	renderM_edit,
	renderM_editAll,
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



/** Util */

void get_pathUni_XY ( struct pathUni *pUni, float *XY );
void point_to_loc_glob ( float *p0, float *pSet );
void loc_to_point_glob ( float *p0, float *pSet );


/** event util */

int thisEdit ( int thisSel );


/** Api Setter */

void set_set_viewScale ( void *f );














