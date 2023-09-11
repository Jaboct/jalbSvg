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
	ArrayList *eles;	// (struct nakedUnion*)
};
struct nakedUnion {
	int type;
	union  {
		struct g *g;
		struct path *path;
	};
};
enum nakedUnionEnum {
	G = 0,
	Path,
};
struct g {
	char id[256];
	ArrayList *eles;	// (struct nakedUnion*)
};
struct path {
	char style[256];
	char d[256];
	char id[256];
};


/** Post Includes */

#include "hand.h"


/** Functions */

/** svg */
struct svg *svgInit ( );
void svgFill ( struct svg *var );
void *svgInitMask ( );
void svgClose ( struct svg *var );
void svgBodyToVal ( void *varPass, int nameI, char *body );
int svgNameToIndex ( char *body, void *data, void *ret, char **strPtr );

/** nakedUnion */
struct nakedUnion *nakedUnionInit ( );
void nakedUnionFill ( struct nakedUnion *var );
void nakedUnionTypeChange0 ( struct nakedUnion *var, int type );
void *nakedUnionInitMask ( );
void nakedUnionClose ( struct nakedUnion *var );
void nakedUnionBodyToVal ( void *varPass, int nameI, char *body );
int nakedUnionNameToIndex ( char *body, void *data, void *ret, char **strPtr );

/** g */
struct g *gInit ( );
void gFill ( struct g *var );
void *gInitMask ( );
void gClose ( struct g *var );
void gBodyToVal ( void *varPass, int nameI, char *body );
int gNameToIndex ( char *body, void *data, void *ret, char **strPtr );

/** path */
struct path *pathInit ( );
void pathFill ( struct path *var );
void *pathInitMask ( );
void pathClose ( struct path *var );
void pathBodyToVal ( void *varPass, int nameI, char *body );
int pathNameToIndex ( char *body, void *data, void *ret, char **strPtr );

/** Other Functs */
