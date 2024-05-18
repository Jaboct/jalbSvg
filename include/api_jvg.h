#pragma once

/** Structs */

struct jvg_api {
	void *(*initJvgEle) ( );
	void (*addJvgEle) ( void *jvg, void *ele );

	void *(*initPath) ( );
	void *(*initPathVert) ( void *path, float *loc );
	void *(*initPathLine) ( void *path, int v0, int v1 );

//	void *(*getPathVert) ( );
//	void *(*setPathLineVert) ( void *line, int vertIndex, void *vert );

	void *(*initTextBox) ( );

	void (*textBox_set_XYWH) ( void *textBox, float *XYWH );
	void (*textBox_set_text) ( void *textBox, char *str );
};








