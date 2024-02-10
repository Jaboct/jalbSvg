#pragma once

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <stdio.h>
#include <stdlib.h>

#include <jalb/jalbArrayList.h>

#include "jGroup.h"
#include "jPath.h"
#include "svg.h"
#include "path.h"

#include "jEvent.h"
#include "event_sb.h"

#include "jRender.h"


/** Functions */

//LayLibDynamic:
//jalbJvg	jalbJvg	jalbJvg_init	jalbJvg_renderDyn	tic	jalbJvg_mEvent	jalbJvg_mEvent	jalbJvg_close



void *jalbJvg_init ( );

void jalbJvg_render ( int *screenDims, GLuint *glBuffers, int *XYWH, void *data );
int jalbJvg_event ( SDL_Event *e, int *clickXY, int *eleWH, void *data );

void jalbJvg_renderDyn ( int *screenDims, GLuint *glBuffers, int *XYWHpass, void *data,
		float *viewLoc, float viewScale );
int jalbJvg_mEvent ( SDL_Event *e, int *clickXYpass, int *eleWH, void *data,
		float *viewLoc, float viewScale );

void jalbJvg_close ( void *data );



/** Other */

void hand_doStuff ( );
void hand_doStuff2 ( char *dir );
void convert_list ( ArrayList *uniList );

struct jPath *path_to_jPath ( struct path *path );

void say_jPath ( struct jPath *path );


/** Save and Load */

void jHand_save ( );
void jalbJvg_save ( char *dir );

void jHand_load ( );
void jalbJvg_load ( char *dir );

/** Debug */

void toggle_debugPrint_jvg_render ( );

void add_special ( ArrayList *sb, int index );




