#pragma once

/** Structs */

// idk if i want naked unions returned or the type themslves?
// i could return the type themselves, then when i add it to the list it gets wrapped in a naked union.
// but then when adding it need to tell it what type it is, lets just return the union.

struct jvg_api {
	void *(*initJvgEle) ( );
	void (*addJvgEle) ( void *jvg, void *ele );

	void *(*initPath) ( );	// returns a naked union
	void *(*initPathVert) ( void *path, float *loc );
	void *(*initPathLine) ( void *path, int v0, int v1 );

//	void *(*getPathVert) ( );
//	void *(*setPathLineVert) ( void *line, int vertIndex, void *vert );

	void *(*initTextBox) ( );

	void (*textBox_set_XYWH) ( void *textBox, float *XYWH );
	void (*textBox_set_text) ( void *textBox, char *str );

	void (*saveToDir) ( void *jvg, char *dir );
};








