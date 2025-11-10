#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <jalb/jalbArrayList.h>
#include <jalbApi/api_uiGen.h>


/** Foward Declaring */

struct cursorMem;
struct jNakedUnion;
struct jPath;
struct jText;
struct jRect;
struct jCirc;

struct cursor_path;
struct cursor_union;

struct jvg;



struct cursor_ele;

// cursor_circ->type: 1 is center, 2 is edge.
enum jCirc_cursorTypes {
	circ_center = 1,
	circ_right,
};


enum jText_cursorType {
	text_move = 1,
	text_botRight = 5,
};


/** Functions */

int jalbJvg_keyDown ( SDL_Event *e, int *clickXYpass, int *eleWH, struct jvg *jvgEle,
		float *viewLoc, float viewScale );

int keydown_cursor_ele ( SDL_Event *e, struct jNakedUnion *uni, struct cursor_ele *cursor );
int keydown_text ( SDL_Event *e, struct jText *text );

int jalbJvg_mDown ( SDL_Event *e, int *clickXYpass, int *eleWH, struct jvg *jvg,
		float *viewLoc, float viewScale );
int jalbJvg_mMotion ( SDL_Event *e, int *clickXYpass, int *eleWH, struct jvg *jvgEle,
		float *viewLoc, float viewScale );



int jNakedList_mEvent_start ( SDL_Event *e, int *clickXYpass, int *eleWH, ArrayList *eles,
		float *viewLoc, float viewScale );
int jNakedList_mEvent ( SDL_Event *e, int *clickXYpass, int *eleWH, ArrayList *eles,
		float *viewLoc, float viewScale );


void set_cursorList_text ( );
void set_cursorList_complex ( );


int jText_mEvent ( SDL_Event *e, int *clickXYpass, int *eleWH, struct jText *text,
		float *viewLoc, float viewScale );

int jRect_mEvent ( SDL_Event *e, int *clickXYpass, int *eleWH, struct jRect *rect,
		float *viewLoc, float viewScale );
int jRect_mPos ( int *clickXYpass, struct jRect *rect,
		float *viewLoc, float viewScale );

int jCirc_mEvent ( SDL_Event *e, int *clickXYpass, int *eleWH, struct jCirc *circ,
		float *viewLoc, float viewScale );


// return 1 if its in the center, 2 if its on the side.
// eleWH isnt necessary rn.
int jCirc_click ( int *clickXYpass, int *eleWH, struct jCirc *circ,
		float *viewLoc, float viewScale );

/// Specific Pens

int cursorPen_click ( ArrayList *eles, float *worldXY );
void cursorText_click ( ArrayList *eles, float *worldXY );

/// Other

// see if only 1 vertex is selected.
// if so, return that path?
struct jPath *onlyVertSelected ( struct cursor_ele *cursor, ArrayList *eleList, int *vertI );

// already know only 1 vert is selected.
void update_cursor_path ( struct cursor_ele *cursor, int newI );





void drag_cursor_new ( SDL_Event *e, ArrayList *cursorList, ArrayList *eleList );
void drag_cursor_path ( struct jNakedUnion *ele, struct cursor_path *cuPath, float *dXY );

int keySpecialChar ( SDL_Event *e, ArrayList *sb );


/** Cursor Ext */

int toggle_cursorEle ( ArrayList *cursorList, struct cursor_ele *temp );
int toggle_cursorEle_child ( struct cursor_ele *ele, struct cursor_ele *temp );


/// TODO, not used anymore since i changed how jvg cursor works


int jIterateToSelected ( ArrayList *eleList, struct jNakedUnion **parent, struct jNakedUnion **ele,
		int *vertI, int *controlI, struct cursorMem **lastCursor );


/** Cursor Utilities */

/*
// why is this a funct and not a string array?
char *cursor_union_type_to_str ( struct cursor_union *uni );

void say_jvg_cursor ( );
void say_cursor_ele ( struct cursor_ele *ele );
void say_cursor_union ( struct cursor_union *uni );
*/













