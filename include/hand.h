#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <jalbXml/jalbXml_02.h>
#include <jalb/jalbStr.h>

#include <jalb/jalbSb.h>
#include <jalb/jalbScreenshot.h>

#include "svg.h"
#include "path.h"
#include "parse.h"

#include "mod_ext.h"

#include "recursiveCursor.h"


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



struct cursorIconInfo {
	char *dir;
	int hotXY[2];
};



/** Functions */

void load_global_svg ( char *dir );


/** Post Init */

void pathPostInit ( void *data );
void path_style_handle ( struct path *path, char *name, char *value );

void text_postInit ( struct text *text );


/** Say */

void say_svg ( struct svg *svg );

void sayEleList ( ArrayList *eles );
void say_svgText ( struct text *text );

void sayPath ( struct path *path );
void say_pathUni_type ( int i );
void sayPathUni ( struct pathUni *uni );

int isBlankSpace ( char c );


/** to paste **/

/** Saving */

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

/** Pre Save */

void svg_preSave ( struct svg *svg );
void preSave_nakedList ( ArrayList *eles );

void preSave_nakedUnion ( struct nakedUnion *uni );
void preSave_g ( struct g *g );
void preSave_path ( struct path *path );
void preSave_text ( struct text *text );
void preSave_tspan ( struct tspan *tspan );
void preSave_rect ( struct rect *rect );

void compile_path_style ( struct path *path );

/** should be auto generated for the naked structs */

int nakedStru_nameToIndex ( char *body, ArrayList *eles, void *ret, char **strPtr );


/** Cursor Stuff */

void changeCursor ( );
void set_cursor_iconI ( int i );
void set_cursor_icon ( struct cursorIconInfo *icon );


/** Toggle */

void toggle_renderMode ( );
void set_renderMode ( int i );


/// Layout Keywords

void jSvg_preInit ( ArrayList *keyList, ArrayList *modList );

// This is from jalbText.
void jKeyCtrl ( char *line, void *data );














