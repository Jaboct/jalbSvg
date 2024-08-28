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
	char name[256];
	ArrayList *complexDecList;	// (struct complexDec*)
	ArrayList *globalVars;	// (struct subVar*)
	ArrayList *globalScripts;	// (struct complexScript*)
};
struct complexModData {
	ArrayList *globalData;	// (struct jLiveData*)
};


/** Post Includes */

#include "complexEle.h"
#include "complexScript.h"


/** Functions */

/** complexMod */
struct complexMod *complexModInit ( );
void complexModFill ( struct complexMod *var );
void *complexModInitMask ( );
void complexModClose ( struct complexMod *var );
void complexModBodyToVal ( void *varPass, int nameI, char *body );
int complexModNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName );

/** complexModData */
struct complexModData *complexModDataInit ( );
void complexModDataFill ( struct complexModData *var );
void *complexModDataInitMask ( );
void complexModDataClose ( struct complexModData *var );
void complexModDataBodyToVal ( void *varPass, int nameI, char *body );
int complexModDataNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName );

/** Other Functs */
