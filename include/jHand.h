#pragma once

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <stdio.h>
#include <stdlib.h>

#include <jalb/jalbArrayList.h>
#include <jalbApi/api_uiGen.h>

#include "jGroup.h"
#include "jPath.h"
#include "svg.h"
#include "path.h"

#include "jEvent.h"
#include "event_sb.h"

#include "jRender.h"

#include "complexEle_ext.h"


/** Structs */

enum spec_keys {
	spec_therefore = 0,
	spec_and,
	spec_or,
	spec_micro,
	spec_emptySet,
	spec_alphaL,
	spec_betaL,
	spec_deltaU,
	spec_deltaL,
	spec_thetaL,
	spec_lambdaL,
	spec_pi,
	spec_rhoL,
	spec_omegaU,
	spec_omegaL,

	spec_integral,
};


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

int jalbJvg_mDown ( SDL_Event *e, int *clickXYpass, int *eleWH, struct jvg *jvg,
		float *viewLoc, float viewScale );
int jalbJvg_mMotion ( SDL_Event *e, int *clickXYpass, int *eleWH, struct jvg *jvgEle,
		float *viewLoc, float viewScale );
int keySpecialChar ( SDL_Event *e, ArrayList *sb );

void jalbJvg_close ( void *data );



/** Other */

void hand_doStuff ( );
void hand_doStuff2 ( char *dir );
void convert_list ( ArrayList *uniList );

struct jPath *path_to_jPath ( struct path *path );

void say_jPath ( struct jPath *path );


/** Save and Load */

void jHand_save ( );
void jalbJvg_glob_save ( char *dir );
void jalbJvg_save ( struct jvg *jvgEle, char *dir );

void jHand_load ( );
void jalbJvg_load_global ( char *dir );
void *jalbJvg_load ( char *dir );


/** Debug */

void toggle_debugPrint_jvg_render ( );
void set_debugPrint_jvg_render ( int i );

void add_special ( ArrayList *sb, int index );


void make_spread_sheet ( );
int ifThen ( int a, int b );

void printVal ( int i );
int getCol ( unsigned char *arr, int i );

void comb ( int i, int n );
void makeColumn ( int numVars, int thisColumn );

// the arr should only be big enough to fit numVars, if its larger i need to change this function.
void makeRow ( unsigned char *arr, int numVars );

void iterateCharArr ( unsigned char *arr, int numChars );
void decreaseCharArr ( unsigned char *arr, int numChars );


/** hover cursor */

void onHoverCheck ( int *XY );
int onHoverType ( int *XY );
int isOnVert ( struct jPath *path, int *XY );
int isOnLine ( struct jVert *v0, struct jVert *v1, int *XY );
int isOnText ( struct jText *text, int *XY );
int isOnRect ( struct jRect *rect, int *XY );
int isOnCirc ( struct jCirc *circ, int *XY );

float pointLineDist ( float *p, float *v0, float *v1 );


/** Dragging */

void dragJPath ( struct jPath *path, float *dXY );




/// util stuff

char *jType_to_str ( struct jNakedUnion *uni );
void jType_spawnEditUi ( struct jNakedUnion *uni );


/// uiGen

void set_uiGen_api ( void *data );


/// Xml

void prepairComplex_xml ( );



// partiall toolbar stuff

void set_api_toolbar ( void *data );
void jvg_pass_toolbar ( );
void spawn_new_complexDec ( );
void spawn_projectInfo ( );

void set_jalbDir_loadPane ( void *data );
void load_jvg_dirList ( );

void jvg_toggle_CAD ( );

/// tools

void set_cursor_pen ( );
void set_cursor_text ( );
void set_cursor_circ ( );
void set_cursor_complex ( );



/** Loading examples for uiGen_liveDev */

struct jvg *load_jvg_example_eleList ( );









