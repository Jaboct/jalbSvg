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



void complexEle_preInit ( );




/** Structs */

struct complexEle {
};


/** Post Includes */


/** Functions */

/** complexEle */
struct complexEle *complexEleInit ( );
void complexEleFill ( struct complexEle *var );
void *complexEleInitMask ( );
void complexEleClose ( struct complexEle *var );
void complexEleBodyToVal ( void *varPass, int nameI, char *body );
int complexEleNameToIndex ( char *body, void *data, void *ret, char **strPtr );

/** Other Functs */
