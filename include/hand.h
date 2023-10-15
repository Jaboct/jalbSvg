#pragma once

#include <jalbXml/jalbXml_02.h>
#include <jalb/jalbStr.h>

#include <jalb/jalbSb.h>
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
	path_moveTo_abs = 0,
	path_moveTo_rel,

	path_lineTo_abs,
	path_lineTo_rel,

	path_lineTo_vert_abs,
	path_lineTo_vert_rel,

	path_lineTo_hor_abs,
	path_lineTo_hor_rel,

	path_cubicBez_abs,
	path_cubicBez_rel,

	path_cubicBez_s_abs,
	path_cubicBez_s_rel,

	path_quadBez_abs,
	path_quadBez_rel,

	path_quadBez_t_abs,
	path_quadBez_t_rel,

	path_ellipArc_abs,
	path_ellipArc_rel,

	path_pathEnd_abs,
	path_pathEnd_rel,
};

enum {
	lineTo_vert = 1,
	lineTo_hor,
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

void pathUni_set_type ( struct pathUni *uni, int type );

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


/** Errand Manager */

void hand_errand_00 ( );

void add_errand ( struct g *g, float *XY, char *name, char *desc );

void save_global_xml ( char *dir );
void save_global_svg ( char *dir );



















