#include "cursorIcon.h"



/** Variables */



int cursorInputMode = 0;	// enum cursorInputTypes;
int cursorRenderMode = 0;	// enum cursorRenderTypes;



/** Functions */




// cur_num
// the more positive hotXY is, the farther the even is down and to the right.
struct cursorIconInfo cursorIcons[6] = {
	{
		.dir = "/home/jadeb/workspace/jHigh/jalbSvg/res/cursor/cursor_32.png",
		.hotXY = { 10, 4 },
	},
	{
		.dir = "/home/jadeb/workspace/jHigh/jalbSvg/res/cursor/cursor_text_32.png",
		.hotXY = { 10, 10 },
	},
	{
		.dir = "/home/jadeb/workspace/jHigh/jalbSvg/res/cursor/pen_32.png",
		.hotXY = { 4, 4 },
	},
	{
		.dir = "/home/jadeb/workspace/jHigh/jalbSvg/res/cursor/rect.png",
		.hotXY = { 10, 10 },
	},
	{
		.dir = "/home/jadeb/workspace/jHigh/jalbSvg/res/cursor/arc_32.png",
		.hotXY = { 10, 10 },
	},
	{
		.dir = "/home/jadeb/workspace/jHigh/jalbSvg/res/cursor/select-mouseover.png",
		.hotXY = { 0, 0 },
	},
};

/*
void changeCursor ( ) {
	char *filename = "/home/jadeb/workspace/jHigh/jalbSvg/res/cursor/xterm_32.png";
	int hotX = 10;
	int hotY = 10;

	cursorInputMode += 1;
	cursorInputMode %= 2;


	if ( cursorRenderMode == 0 ) {
//		filename = "/home/jadeb/workspace/jHigh/jalbSvg/res/cursor/xterm_32.png";
		filename = "/home/jadeb/workspace/jHigh/jalbSvg/res/cursor/cursor_text_32.png";
		hotX = 10;
		hotY = 10;
	} else {
//		filename = "/home/jadeb/workspace/jHigh/jalbSvg/res/cursor/cursor_48.png";
		filename = "/home/jadeb/workspace/jHigh/jalbSvg/res/cursor/cursor_32.png";
		hotX = 10;
		hotY = 4;
	}


	SDL_Surface *surface = IMG_Load ( filename );

	if ( !surface ) {
		const char *error = SDL_GetError ( );
		printf ( "error: %s\n", error );
		return;
	}

	SDL_Cursor *cursor = SDL_CreateColorCursor ( surface, hotX, hotY );
	SDL_SetCursor ( cursor );
}
*/


// pass an index from (enum cursorInputTypes (mod_ext.h)).
void set_cursorInputMode ( int i ) {
	printf ( "set_cursorInputMode ( )\n" );
	printf ( "i: %d\n", i );
	printf ( "old mode: %d\n", cursorInputMode );

	cursorInputMode = i;

	int newIcon = 0;

	// now convert input mode to render icon.
	if ( cursorInputMode == ci_reg ) {
		newIcon = cr_reg;
	} else if ( cursorInputMode == ci_text ) {
		newIcon = cr_text;
	} else if ( cursorInputMode == ci_pen ) {
		newIcon = cr_pen;
	} else if ( cursorInputMode == ci_rect ) {
		newIcon = cr_rect;
	} else if ( cursorInputMode == ci_circ ) {
		newIcon = cr_circ;
	} else if ( cursorInputMode == ci_complex ) {
		// TODO
		newIcon = cr_circ;
	}

	set_cursor_iconI ( newIcon );
}

// sets the icon and the cursorRenderMode.
void set_cursor_iconI ( int i ) {
//	printf ( "set_cursor_iconI ( )\n" );

	// if they are already the same, then done make a change.
	if ( cursorRenderMode != i ) {

		cursorRenderMode = i;
		if ( i < cr_num ) {
			set_cursor_icon ( &cursorIcons[i] );
		}
	} else {
//		printf ( "dont change cursor\n" );
	}
}

void set_cursor_icon ( struct cursorIconInfo *icon ) {
	SDL_Surface *surface = IMG_Load ( icon->dir );

	if ( !surface ) {
		const char *error = SDL_GetError ( );
		printf ( "error: %s\n", error );
		return;
	}

	SDL_Cursor *cursor = SDL_CreateColorCursor ( surface, icon->hotXY[0], icon->hotXY[1] );
	SDL_SetCursor ( cursor );
}


