
/** Macros */

#define handleCursor_start \
	printf ( "handleCursor_start ( )\n" ); \
	printf ( "cursor_depth: %d\n", cursor_depth ); \
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
	printf ( "handleCursor ( )\n" ); \
	printf ( "cursor_depth: %d\n", cursor_depth ); \
	struct cursorMem *mem = arrayListGetPointer ( cursorList, cursor_depth ); \
	mem->selI = i;



// cursorRecur + cursorDecur?
#define cursorDown \
	cursor_depth += 1;

#define cursorUp \
	cursor_depth -= 1;





