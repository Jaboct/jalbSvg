#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <GL/glew.h>


#include <jalb/undoRedo.h>
#include <jalb/jalbText_util.h>
#include <jalb/jalbStr.h>
#include <jalb/jalbSb.h>
#include <jalb/jalb_altKeys.h>

#include <jalbDraw/jalbFont.h>


//#include "task.h"


/** coppied from jalbText */

int sbKey ( SDL_Keycode key, ArrayList *sb, struct undoRedo *undoMem, int *cursorStartMem, int *cursorEndMem,
	    int *searching, struct textSearch *search, char *altKeys,
	    ArrayList *ctrlKeys, struct scrollMem *sm, int wrap, int maxCols );

// is this just a generic arraylist function?
void arrayListIterateBackList ( ArrayList *al, int startIndex, int ( *funct ) ( char *, ArrayList * ), ArrayList **retPart, int *retIndex,
		ArrayList *param );
void arrayListIterateList ( ArrayList *al, int startIndex, int ( *funct ) ( char *, ArrayList * ), ArrayList **retPart, int *retIndex,
		ArrayList *param );
// So i want this to be accessable by
int isCtrlCharChange ( char *cPtr, ArrayList *charList );

// I guess i just want alPartIndex, then i can add partI on my own.
int arrayListPartToAbs ( ArrayList *al, ArrayList *part, int partI );























