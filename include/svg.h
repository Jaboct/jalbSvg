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



void svg_preInit ( );


/** Structs */

struct svg {
	char width[256];
	char height[256];
	ArrayList *eles;	// (struct svg*)
};


/** Post Includes */


/** Functions */

/** svg */
struct svg *svgInit ( );
void svgFill ( struct svg *var );
void *svgInitMask ( );
void svgClose ( struct svg *var );
void svgBodyToVal ( void *varPass, int nameI, char *body );
int svgNameToIndex ( char *body, void *data, void *ret, char **strPtr );

/** Other Functs */
