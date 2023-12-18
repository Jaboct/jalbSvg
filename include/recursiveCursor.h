
/** Macros */

#define handleCursor_start \
	printf ( "handleCursor_start ( )\n" ); \
	printf ( "depth: %d\n", depth ); \
	int oldLen = arrayListGetLength ( selList ); \
	while ( oldLen > depth ) { \
		arrayListRemove ( selList, oldLen - 1 ); \
		oldLen -= 1; \
	} \
	while ( oldLen < depth + 1 ) { \
		struct cursorMem *mem = malloc ( sizeof ( *mem ) ); \
		arrayListAddEndPointer ( selList, mem ); \
		oldLen += 1; \
	} \
	struct cursorMem *mem = arrayListGetPointer ( selList, depth ); \
	mem->selI = i;

#define handleCursor \
	printf ( "handleCursor ( )\n" ); \
	printf ( "depth: %d\n", depth ); \
	struct cursorMem *mem = arrayListGetPointer ( selList, depth ); \
	mem->selI = i;


