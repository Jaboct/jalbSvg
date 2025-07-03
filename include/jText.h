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



void jText_preInit ( );




/** Structs */

struct jText {
	float XYWH[4];
	ArrayList *sb;	// (char)
	float fontSize;
};


/** Post Includes */


/** Functions */

/** jText */
struct jText *jTextInit ( );
void jTextFill ( struct jText *var );
void *jTextInitMask ( );
void jTextClose ( struct jText *var );
void jTextBodyToVal ( void *varPass, int nameI, char *body );
int jTextNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName );

/** Other Functs */
