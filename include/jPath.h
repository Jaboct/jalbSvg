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



void jPath_preInit ( );




/** Structs */

struct jPath {
	ArrayList *verts;	// (struct jVert*)
	ArrayList *lines;	// (struct jLine*)
};
struct jVert {
	float XY[2];
};
struct jLine {
	int type;
	int v0;
	int v1;
	float c0[2];
	float c1[2];
};


/** Post Includes */


/** Functions */

/** jPath */
struct jPath *jPathInit ( );
void jPathFill ( struct jPath *var );
void *jPathInitMask ( );
void jPathClose ( struct jPath *var );
void jPathBodyToVal ( void *varPass, int nameI, char *body );
int jPathNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName );

/** jVert */
struct jVert *jVertInit ( );
void jVertFill ( struct jVert *var );
void *jVertInitMask ( );
void jVertClose ( struct jVert *var );
void jVertBodyToVal ( void *varPass, int nameI, char *body );
int jVertNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName );

/** jLine */
struct jLine *jLineInit ( );
void jLineFill ( struct jLine *var );
void *jLineInitMask ( );
void jLineClose ( struct jLine *var );
void jLineBodyToVal ( void *varPass, int nameI, char *body );
int jLineNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName );

/** Other Functs */
