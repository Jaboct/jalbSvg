#pragma once

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <stdio.h>
#include <stdlib.h>

#include <jalb/jalbArrayList.h>

#include <jalbXml/jalbXml_02_read.h>
#include <jalbXml/jalbXml_02_write.h>
#include <jalbXml/backbone_wrangler.h>


/** Foward Declaring */

struct jvg;
struct path;
struct jNakedUnion;

struct jPath;
struct jVert;
struct jText;
struct jRect;
struct jCirc;

struct jLine;

struct cursor_path;

struct complexMod;
struct complexDec;


/** Structs */

// special keys for adding unicode chars
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


enum heldTypes {	// u can have highlight and camera move at the same time.
	ht_none = 0,
	ht_cameraMove,
	ht_eleMove,
	ht_highlight,
};



/** Functions */

//LayLibDynamic:
//jalbJvg	jalbJvg	jalbJvg_init	jalbJvg_renderDyn	tic	jalbJvg_mEvent	jalbJvg_mEvent	jalbJvg_close



void *jalbJvg_init ( );
void make_glob_jvg ( );

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
void jalbJvg_glob_save ( char *dir );
void jalbJvg_save ( struct jvg *jvgEle, char *dir );

void jHand_load ( );
void jalbJvg_load_global ( char *dir );
void *jalbJvg_load ( char *dir );


/** Debug */

void toggle_debugPrint_jvg_render ( );
void set_debugPrint_jvg_render ( int i );
void set_debugPrint_jvg_complex_render ( int i );

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


/** Dragging */

void dragJPath ( struct jPath *path, float *dXY );


/// util stuff

char *jType_to_str ( struct jNakedUnion *uni );


/// Xml

void prepairComplex_xml ( );



// partiall toolbar stuff

void set_api_toolbar ( void *data );
void jvg_pass_toolbar ( );

struct complexMod *spawnAndOpen_new_complexDec ( );
struct complexMod *spawn_new_complexDec ( );
void spawn_projectInfo ( );


/// jalbDir

void set_jalbDir_loadPane ( void *data );
void load_jvg_dirList ( );


/// Toggles

void jvg_toggle_CAD ( );

void jvg_toggle_grid ( );
void jvg_toggle_gridRender ( );
// should snap ever be enabled when render isnt?
void jvg_set_gridSnap ( int i );
void jvg_toggle_gridSnap ( );


/// tools

void set_cursor_pen ( );
void set_cursor_text ( );
void set_cursor_circ ( );
void set_cursor_complex ( );





/** Specific Loading Examples */

void load_CAD_00 ( );
void firstRender_todo ( );


/** Getters */

void *get_glob_jvg ( );









