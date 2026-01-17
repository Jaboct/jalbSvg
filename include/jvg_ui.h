#pragma once


/** Includes */

#include <stdio.h>
#include <stdlib.h>

#include <jalbApi/api_uiGen.h>


/** Forward Declaring */

struct jVert;
struct jLine;

struct jNakedUnion;
struct complexMod;
struct complexDec;


/** Functions */

/// uiGen

void set_uiGen_api ( void *data );


/// spawning uiGen eles

void jType_spawnEditUi ( struct jNakedUnion *uni );

void open_jVert_edit ( struct jVert *vert );
void open_jLine_edit ( struct jLine *line );


/// UiGen spawning

void open_left_toolbar ( );
void uiGen_open_eleList ( );
void uiGen_open_jNaked ( struct jNakedUnion *jNaked );

void uiGen_open_complexWrangler ( );
void uiGen_open_complexMod ( struct complexMod *mod );
void uiGen_open_complexDec ( struct complexDec *dec );


float *toolBar_icon_color ( int i );



/// Loading examples for uiGen_liveDev

struct jvg *load_jvg_example_eleList ( );
struct jPath *load_jvg_example_jPath ( );
struct jVert *load_jvg_example_jVert ( );
struct jLine *load_jvg_example_jLine ( );


