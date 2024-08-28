#pragma once

/** AUTO GENERATED CODE */

#include <stdio.h>
#include <stdlib.h>

#include <jalb/jalbArrayList.h>
#include <jalb/jalbSay.h>

#include <jalb/jfile.h>
#include <jalb/jalb_addCanvas.h>
#include <jalbDraw/drawCutString.h>

#include <jalbXml/jalbXml_02.h>



void complexMod_preInit ( );




/** Structs */

struct complexMod {
	ArrayList *complexDecList;	// (out of range (type: -1) (typeIndex: -1)*)
	ArrayList *globalVars;	// (out of range (type: -1) (typeIndex: -1)*)
	ArrayList *globalScripts;	// (out of range (type: -1) (typeIndex: -1)*)
	[type (0) typeIndex (-1)] *;
};


/** Post Includes */


/** Functions */

/** complexMod */
struct complexMod *complexModInit ( );
void complexModFill ( struct complexMod *var );
void *complexModInitMask ( );
void complexModClose ( struct complexMod *var );
void complexModBodyToVal ( void *varPass, int nameI, char *body );
int complexModNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName );

/** Other Functs */
