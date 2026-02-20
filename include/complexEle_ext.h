#pragma once

#include <jalb/jalbArrayList.h>
#include <jalb/soMacros>
#include <jalb/jalbUtilities.h>

#include <jalbXml/backbone_wrangler.h>


/** Foward Declaring */

struct jvg;
struct complexDec;
struct complexEle;
struct complexList;


/** Struct */

struct modWrap {
	char nick[256];
	char realName[256];	// for grabbing auto generated functions.
	void *handle;
};




/** Functions */

void hand_complex_00 ( );
void hand_complex_01 ( );


/** Multi Mod Backbone */

void hand_grab_mod ( char *modNick, char *jvgNick, char *realName );
void recieveMod ( char *nick, void *handle, char *realName );

// its modName not modNick, because it grabs the function.
void grabBackbone ( char *jvgNick, char *modName, void *handle );
struct modWrap *modWrap_fromNick ( char *nick );


/// Setter

void set_modCore_modGetter ( void *mod );


/// Other

void complexDecPostInit ( struct complexDec *dec );



void complexEle_initType ( struct complexEle *ele, int type );


/** Render */

void complexEleRender_sub ( int *screenDims, GLuint *glBuffers, int *XYWHpass, struct complexEle *complex, struct complexDec *dec,
		float *viewLoc, float viewScale );

/** Event */

int complexEle_mEvent ( SDL_Event *e, int *clickXYpass, int *eleWH, struct complexEle *complex,
		float *viewLoc, float viewScale );
int complexEle_kEvent ( SDL_Event *e, int *clickXYpass, int *eleWH, struct complexEle *ele,
		float *viewLoc, float viewScale );

int hand_ee_event ( SDL_Event *e, int *clickXYpass, int *eleWH, struct complexEle *ele );



// for complexRef linking
void jvgPostInit ( struct jvg *jvg );

// converts complexRef ptr to eleI
void jvgPreSave ( struct jvg *jvg );

void complexEle_ref_link ( struct jvg *jvg, struct complexEle *ele );

void complexEle_index_link ( struct jvg *jvg, struct complexEle *ele );
int complexEle_toIndex ( struct jvg *jvg, struct complexEle *ele );


/** Temp Hand Electrical Engineering Functions */

extern struct draw2dStruct *draw2dApi;

void hand_voltageSource_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass,
		float *viewLoc, float viewScale,
		int *voltage, struct complexEle *linkTo, struct complexEle *linkFrom );
void hand_resistor_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass,
		float *viewLoc, float viewScale,
		int *resistance, struct complexEle *linkTo, struct complexEle *linkFrom );

// i need further node info.
void complexEleNodePosition ( float *viewLoc, float viewScale,
		struct complexEle *complexEle, int type, float *fillXY );



/// Complex List

void complexList_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass, struct complexList *ele,
		float *viewLoc, float viewScale );

/// TEMP

void spawn_complexEle ( );















