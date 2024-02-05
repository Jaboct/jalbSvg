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



void jShapes_preInit ( );




/** Structs */

struct jRect {
	float XYWH[4];
};
struct jCirc {
	float XY[2];
	float radius;
};
struct jEllipse {
	float XY[2];
	float cx;
	float cy;
	float rx;
	float ry;
};


/** Post Includes */


/** Functions */

/** jRect */
struct jRect *jRectInit ( );
void jRectFill ( struct jRect *var );
void *jRectInitMask ( );
void jRectClose ( struct jRect *var );
void jRectBodyToVal ( void *varPass, int nameI, char *body );
int jRectNameToIndex ( char *body, void *data, void *ret, char **strPtr );

/** jCirc */
struct jCirc *jCircInit ( );
void jCircFill ( struct jCirc *var );
void *jCircInitMask ( );
void jCircClose ( struct jCirc *var );
void jCircBodyToVal ( void *varPass, int nameI, char *body );
int jCircNameToIndex ( char *body, void *data, void *ret, char **strPtr );

/** jEllipse */
struct jEllipse *jEllipseInit ( );
void jEllipseFill ( struct jEllipse *var );
void *jEllipseInitMask ( );
void jEllipseClose ( struct jEllipse *var );
void jEllipseBodyToVal ( void *varPass, int nameI, char *body );
int jEllipseNameToIndex ( char *body, void *data, void *ret, char **strPtr );

/** Other Functs */
