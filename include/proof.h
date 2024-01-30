#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <SOIL/SOIL.h>

#include <jalbXml/jalbXml_02.h>

#include <jalb/jalbScreenshot.h>

#include "hand.h"
#include "parse.h"

/** Functions */

void hand_test ( );
void hand_test_load ( );
void hand_test_01 ( );



/** line 1 */

void line_1_test ( );

/// Other

void extra_test ( );


void proof_parseD ( );



/** Render Proof */

void set_onTest ( int i );

void handle_render_proof ( );

void render_proof_00 ( int stage );
void render_proof_01 ( int stage );


void test_viewLoc_00 ( );
void test_viewLoc_01 ( );
void test_viewScale_00 ( );



void screenshot_ppm_xywh ( char *dir, int *XYWHpass );

