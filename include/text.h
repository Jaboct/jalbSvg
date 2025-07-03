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



void text_preInit ( );




/** Structs */

struct text {
	char space[256];
	char style[256];
	float x;
	float y;
	ArrayList *spanList;	// (struct tspan*)
};
struct tspan {
	char role[256];
	char id[256];
	char style[256];
	float x;
	float y;
	char body[256];
	float fontSize;
	ArrayList *stringBuilder;	// (char)
};


/** Post Includes */

#include "hand.h"

/** Functions */

/** text */
struct text *textInit ( );
void textFill ( struct text *var );
void *textInitMask ( );
void textClose ( struct text *var );
void textBodyToVal ( void *varPass, int nameI, char *body );
int textNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName );

/** tspan */
struct tspan *tspanInit ( );
void tspanFill ( struct tspan *var );
void *tspanInitMask ( );
void tspanClose ( struct tspan *var );
void tspanBodyToVal ( void *varPass, int nameI, char *body );
int tspanNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName );

/** Other Functs */
