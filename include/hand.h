#pragma once

#include <jalbXml/jalbXml_02.h>
#include <jalb/jalbStr.h>

#include <jalb/jalbScreenshot.h>

#include "svg.h"
#include "path.h"


/** Structs */

/*
enum pathTypes {
	path_moveTo = 0,
	path_lineTo,
	path_
};
*/

enum {
	path_moveto_rel = 0,
	path_moveto_abs,
};

/** Functions */

void load_global_svg ( char *dir );

void say_svg ( struct svg *svg );

void sayEleList ( ArrayList *eles );
void say_svgText ( struct text *text );



void pathPostInit ( void *data );
void sayPath ( struct path *path );
void sayPathUni ( struct pathUni *uni );

int isBlankSpace ( char c );

void parseD ( char *d, ArrayList *eles );

int charToPathUni ( char c );
int charToPathUni2 ( char c, struct pathUni **uniPass );

int moveTo_dFill ( struct moveTo *moveTo, int i, float val );
int lineTo_dFill ( struct lineTo *lineTo, int i, float val );
int cubicBez_dFill ( struct cubicBez *cubicBez, int i, float val );
int quadBez_dFill ( struct quadBez *quadBez, int i, float val );
int ellipArc_dFill ( struct ellipArc *ellipArc, int i, float val );


void eleListToD ( ArrayList *eleList, char *d );


void save_svg ( char *dir, struct svg *svg );
void prepair_d ( ArrayList *eles );


void expandSvg ( struct svg *svg );
void expandEleList ( ArrayList *eles );


/** Other */

void hand_load ( );

void hand_p ( char *dir );



/** postInit */

void text_postInit ( struct text *text );
void tspan_postInit ( struct tspan *tspan );
void tspan_style_handle ( struct tspan *tspan, char *name, char *value );
void text_style_handle ( struct text *text, char *name, char *value );


