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



void shapes_preInit ( );




/** Structs */

struct rect {
	char style[256];
	char id[256];
	float x;
	float y;
	float width;
	float height;
	char fill[256];
	char stroke[256];
	char stroke_width[256];
	char stroke_opacity[256];
};
struct circle {
	char style[256];
	char id[256];
	float cx;
	float cy;
	float r;
};
struct ellipse {
	char style[256];
	char id[256];
	float cx;
	float cy;
	float rx;
	float ry;
};


/** Post Includes */


/** Functions */

/** rect */
struct rect *rectInit ( );
void rectFill ( struct rect *var );
void *rectInitMask ( );
void rectClose ( struct rect *var );
void rectBodyToVal ( void *varPass, int nameI, char *body );
int rectNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName );

/** circle */
struct circle *circleInit ( );
void circleFill ( struct circle *var );
void *circleInitMask ( );
void circleClose ( struct circle *var );
void circleBodyToVal ( void *varPass, int nameI, char *body );
int circleNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName );

/** ellipse */
struct ellipse *ellipseInit ( );
void ellipseFill ( struct ellipse *var );
void *ellipseInitMask ( );
void ellipseClose ( struct ellipse *var );
void ellipseBodyToVal ( void *varPass, int nameI, char *body );
int ellipseNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName );

/** Other Functs */
