
// TODO, unite with <jalb/jalb_cursor.h>

#include "mod_ext.h"

/** Macros */

#define handleCursor_start \
/*	printf ( "handleCursor_start ( )\n" ); */ \
/*	printf ( "cursor_depth: %d\n", cursor_depth ); */ \
	int oldLen = arrayListGetLength ( cursorList ); \
	while ( oldLen > cursor_depth ) { \
		arrayListRemove ( cursorList, oldLen - 1 ); \
		oldLen -= 1; \
	} \
	while ( oldLen < cursor_depth + 1 ) { \
		struct cursorMem *mem = malloc ( sizeof ( *mem ) ); \
		arrayListAddEndPointer ( cursorList, mem ); \
		oldLen += 1; \
	} \
	struct cursorMem *mem = arrayListGetPointer ( cursorList, cursor_depth ); \
	mem->selI = i;

#define handleCursor \
/*	printf ( "handleCursor ( )\n" ); */ \
/*	printf ( "cursor_depth: %d\n", cursor_depth ); */ \
	struct cursorMem *mem = arrayListGetPointer ( cursorList, cursor_depth ); \
	mem->selI = i;



// cursorRecur + cursorDecur?
#define cursorDown \
	cursor_depth += 1;

#define cursorUp \
	cursor_depth -= 1;



// This should just be a function, but i cant stick a function in a header.
// the extra squig brackets is for scope of i and len.
#define sayCursor { \
	int i = 0; \
	int len = arrayListGetLength ( cursorList ); \
	printf ( "sayCursor[%d] { ", len ); \
	while ( i < len ) { \
		struct cursorMem *mem = arrayListGetPointer ( cursorList, i ); \
		printf ( "%d", mem->selI ); \
		if ( i < len - 1 ) { \
			printf ( "," ); \
		} \
		printf ( " " ); \
		i += 1; \
	} \
	printf ( "}\n" ); \
}

/* before this do
	int parentSel = thisSel;
	thisSel = 0; // put this inside the loop
	cursorDown; // only necessary if im going deeper.
 * then do the macro, and the render of the ele
 * and after it do
	cursorUp;
	thisSel = parentSel;;
 */
/*
	printf ( "isThisSel ( )\n" ); \
	printf ( "i: %d\n", i ); \
*/
#define isThisSel \
	if ( selected && \
	     parentSel ) { \
		int cursorLen = arrayListGetLength ( cursorList ); \
		if ( cursorLen > cursor_depth ) { \
			struct cursorMem *mem = arrayListGetPointer ( cursorList, cursor_depth ); \
			if ( mem->selI == i ) { \
				thisSel = 1; \
			} \
		} \
	}


#define isThisIt \
	int cursorLen = arrayListGetLength ( cursorList ); \
	if ( thisSel && \
	     cursor_depth == cursorLen - 1 ) { \
		thisSel = 1; \
	} else {\
		thisSel = 0; \
	}


// make, isNextSel ( int index )
// which gets the next sees if it equals index, and then if cursor_depth == cursorLen - 2, maybe.
// instead do
// i = index
// cursorDown
// isThisSel
// i think.




