#pragma once


/** Includes */

#include <jalb/jalbArrayList.h>


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


/// hover cursor

void onHoverCheck ( int *XY );
int onHoverType ( int *XY );
int onHoverType_eleList ( int *XY, ArrayList *eleList );

int isOnVert ( struct jPath *path, int *XY );
int isOnLine ( struct jVert *v0, struct jVert *v1, int *XY );
int isOnText ( struct jText *text, int *XY );
int isOnRect ( struct jRect *rect, int *XY );
int isOnCirc ( struct jCirc *circ, int *XY );

//float pointLineDist ( float *p, float *v0, float *v1 );


void say_cursor_ele ( struct cursor_ele *cursorEle );



