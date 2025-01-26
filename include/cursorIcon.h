#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


/// enum

// for inputting data via the cursor.
enum cursorInputTypes {
	ci_reg = 0,
	ci_text,
	ci_pen,
	ci_rect,
	ci_circ,
	ci_complex,
	ci_num,
};

enum cursorRenderTypes {
	cr_reg = 0,
	cr_text,
	cr_pen,
	cr_rect,
	cr_circ,
	cr_move,
	cr_num,
};

// for whatever my cursor is currently selecting.
enum cursorSelect {
	cs_object = 0,
	cs_vert,
	cs_control,
	cs_text,
	cs_rect,
	cs_circ,
	cs_complex,
};


/** Structs */

struct cursorIconInfo {
	char *dir;
	int hotXY[2];
//	SDL_Surface *surface;
};



/** Functions */


//void changeCursor ( );

void set_cursorInputMode ( int i );
void set_cursor_iconI ( int i );
void set_cursor_icon ( struct cursorIconInfo *icon );








