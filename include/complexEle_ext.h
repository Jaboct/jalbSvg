#pragma once

#include <jalb/jalbArrayList.h>
#include <jalb/soMacros>
#include <jalb/jalbUtilities.h>

#include "api/structStruct.h"

#include "canvas_util.h"

#include "jGroup.h"
#include "complexEle.h"

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



/** Event */

int complexEle_mEvent ( SDL_Event *e, int *clickXYpass, int *eleWH, struct complexEle *complex,
		float *viewLoc, float viewScale );





