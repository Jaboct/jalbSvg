#pragma once


#include <stdio.h>
#include <stdlib.h>

#include <jalb/jfile.h>
#include <jalb/jalbUtilities.h>
#include <jalb/jalbSay.h>

#include "hand.h"


/** Structs */

struct autoTest {
	char *testName;

	char *xmlDir;
	char *imgDir;

	int XYWH[4];

	float viewLoc[2];
	float viewScale;

//	void *data;
//	void *(*dataInitFunct)();
	// maybe call this, event funct? welll it can do mroe than just uiGen events.
	// it shouldnt be (void *uiGen), should be (struct uiGen *uiGen). why dont i do this?
	// cuz its in a different mod.
//	void (*dataSetFunct)(void *uiGen, void *data);
};


/** Functions */

void start_allTests ( );
void run_allTests ( );

int render_autoTest ( struct autoTest *render_auto );
int render_autoTest_end ( struct autoTest *render_auto );

// takes the pixels from window according to part_XYWH, the compares them to the ppm from ppmName
// return 1 if they are the same, 0 otherwise.
//int compare_ppm ( char *ppmName, SDL_Window *window, int part_XYWH[4] );
int compare_ppm ( char *ppmName, int part_XYWH[4] );
