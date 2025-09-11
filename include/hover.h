#pragma once


/** Includes */

#include <jalb/jalbArrayList.h>
#include <jalb/jama.h>

/** Forward Declaring */

struct jPath;
struct jVert;
struct jText;
struct jRect;
struct jCirc;

struct cursor_ele;


/** Functions */

/// cursor glboals

void init_jvg_cursor ( );

// isnt used at all.
int click_drill ( ArrayList *eleList, int *XY, int type );

/// hover cursor

void onHoverCheck ( int *XY );
int onHoverType ( int *XY );
int onHoverType_eleList ( int *XY, ArrayList *eleList );

int isOnPath ( struct jPath *path, int *XY );

// return the index of the vert that this cursor is on.
int isOnVert ( struct jPath *path, int *screenXY );
int isOnVert_world ( struct jPath *path, float *worldXY );

int isOnLine ( struct jVert *v0, struct jVert *v1, int *XY );
int isOnText ( struct jText *text, int *XY );
int isOnRect ( struct jRect *rect, int *XY );
int isOnCirc ( struct jCirc *circ, int *XY );

//float pointLineDist ( float *p, float *v0, float *v1 );


/** Util */

// return 1 if the arraylist has the int i, 0 otherwise
int al_hasInt ( ArrayList *al, int i );
// return -1 if the arraylist does not have the int i, otherwise it returns its index.
int al_getIndex_int ( ArrayList *al, int i );

// al is of type (cursor_ele*)
int eleList_getIndex ( ArrayList *al, int i );

void say_cursor_ele ( struct cursor_ele *cursorEle );
void say_cursorList_new ( );

