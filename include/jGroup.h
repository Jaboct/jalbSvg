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



#include "jPath.h"
#include "jText.h"
#include "jShapes.h"

void jGroup_preInit ( );




/** Structs */

struct jGroup {
	ArrayList *eles;	// (struct jNakedUnion*)
};
struct jNakedUnion {
	int type;
	union  {
		struct jGroup *g;
		struct jPath *path;
		struct jText *text;
		struct jRect *rect;
		struct jCirc *circ;
		struct jEllipse *ellipse;
		struct complexEle *complex;
	};
};
enum jNakedUnionEnum {
	jNaked_G = 0,
	jNaked_Path,
	jNaked_Text,
	jNaked_Rect,
	jNaked_Circ,
	jNaked_Ellipse,	// 5
	jNaked_Complex,
};
struct jvg {
	ArrayList *eles;	// (struct jNakedUnion*)
	ArrayList *moduleList;	// (struct complexMod*)
	ArrayList *moduleDataList;	// (struct complexModData*)
};


/** Post Includes */

#include "complexMod.h"


/** Functions */

/** jGroup */
struct jGroup *jGroupInit ( );
void jGroupFill ( struct jGroup *var );
void *jGroupInitMask ( );
void jGroupClose ( struct jGroup *var );
void jGroupBodyToVal ( void *varPass, int nameI, char *body );
int jGroupNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName );

/** jNakedUnion */
struct jNakedUnion *jNakedUnionInit ( );
void jNakedUnionFill ( struct jNakedUnion *var );
void jNakedUnionTypeChange0 ( struct jNakedUnion *var, int type );
void *jNakedUnionInitMask ( );
void jNakedUnionClose ( struct jNakedUnion *var );
void jNakedUnionBodyToVal ( void *varPass, int nameI, char *body );
int jNakedUnionNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName );

/** jvg */
struct jvg *jvgInit ( );
void jvgFill ( struct jvg *var );
void *jvgInitMask ( );
void jvgClose ( struct jvg *var );
void jvgBodyToVal ( void *varPass, int nameI, char *body );
int jvgNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName );

/** Other Functs */
