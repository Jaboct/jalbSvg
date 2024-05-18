#include "api.h"


/** Variables */

struct jvg_api jvg_api_void = {
	.initJvgEle = &initJvgEle,
	.addJvgEle = addJvgEle,
	.initPath = (void *(*) ( ))&jPathInit,
	.initPathVert = initPathVert,
	.initPathLine = initPathLine,
//	.initPathLine = (void *(*) ( ))&jLineInit,
//	.getPathVert = 
/*	void *(*initPathVert) ( );
	void *(*initPathLine) ( );
	void *(*getPathVert) ( );
	void *(*setPathLineVert) ( void *line, int vertIndex, void *vert );
	void *(*initTextBox) ( );
*/
	.initTextBox = 	(void *(*) ( ))jTextInit,
};

/** Functions */

void *get_jvg_api ( ) {
	return &jvg_api_void;
}

void *initJvgEle ( ) {
	// rn this is just an arraylist, should i stick it in its own struct eventually?

	ArrayList *jEles = initArrayList ( 10, sizeof ( struct jNakedUnion* ), 10 );
	return jEles;
}

void addJvgEle ( void *jvg, void *ele ) {
	arrayListAddEndPointer ( jvg, ele );
}

/// Path

void *initPathVert ( void *path, float *loc ) {
	struct jVert *vert = jVertInit ( );
	vert->XY[0] = loc[0];
	vert->XY[1] = loc[1];

	struct jPath *p = path;
	arrayListAddEndPointer ( p->verts, vert );

	return vert;
}

void *initPathLine ( void *path, int v0, int v1 ) {
	struct jLine *line = jLineInit ( );
	line->v0 = v0;
	line->v1 = v1;

	line->type = path_LineTo;

	struct jPath *p = path;
	arrayListAddEndPointer ( p->lines, line );

	return line;
}

/// Text Box

void textBox_set_XYWH ( void *textBox, float *XYWH ) {
	struct jText *text = textBox;
	text->XYWH[0] = XYWH[0];
	text->XYWH[1] = XYWH[1];
	text->XYWH[2] = XYWH[2];
	text->XYWH[3] = XYWH[3];

}

void textBox_set_text ( void *textBox, char *str ) {
	struct jText *text = textBox;
	fillStringBuilder ( str, text->sb );
}





