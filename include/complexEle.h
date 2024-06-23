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

struct complexDec {
	char name[256];
	ArrayList *subVars;	// (struct subVar*)
};
struct complexEle {
	char name[256];
	ArrayList *subVars;	// (void*)
};


/** Post Includes */


/** Functions */

/** complexDec */
struct complexDec *complexDecInit ( );
void complexDecFill ( struct complexDec *var );
void *complexDecInitMask ( );
void complexDecClose ( struct complexDec *var );
void complexDecBodyToVal ( void *varPass, int nameI, char *body );
int complexDecNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName );

/** complexEle */
struct complexEle *complexEleInit ( );
void complexEleFill ( struct complexEle *var );
void *complexEleInitMask ( );
void complexEleClose ( struct complexEle *var );
void complexEleBodyToVal ( void *varPass, int nameI, char *body );
int complexEleNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName );

/** Other Functs */
