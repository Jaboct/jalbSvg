#include "api.h"

/** Includes */

#include "jGroup.h"

#include "jPath.h"
#include "path.h"

#include "jText.h"

#include "jHand.h"

#include "api_jvg.h"


/** Variables */

struct jvg_api jvg_api_void = {
	.initJvgEle = &initJvgEle,
	.addJvgEle = addJvgEle,
	.initPath = (void *(*) ( ))&initPathEle,
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
	.textBox_set_text = textBox_set_text,
	.textBox_set_XYWH = textBox_set_XYWH,

	.initTextBox = 	(void *(*) ( ))initTextEle,

	.saveToDir = saveToDir,
};

/** Functions */

void *get_jvg_api ( ) {
	printf ( "get_jvg_api ( )\n" );
	printf ( "&jvg_api_void: %p\n", &jvg_api_void );

	return &jvg_api_void;
}

void *initJvgEle ( ) {
	printf ( "initJvgEle ( )\n" );

	struct jvg *jvg = jvgInit ( );

	printf ( "jvg: %p\n", jvg );

	return jvg;
}

void addJvgEle ( void *jvg, void *ele ) {
	printf ( "addJvgEle ( )\n" );
	printf ( "jvg: %p\n", jvg );

	struct jvg *j = jvg;
	arrayListAddEndPointer ( j->eles, ele );

	printf ( "addJvgEle ( ) OVER\n" );
}

/// Path

void *initPathEle ( ) {
	struct jNakedUnion *uni = jNakedUnionInit ( );
	jNakedUnionTypeChange0 ( uni, jNaked_Path );
	return uni;
}

void *initPathVert ( void *path, float *loc ) {
	struct jVert *vert = jVertInit ( );
	vert->XY[0] = loc[0];
	vert->XY[1] = loc[1];

	struct jNakedUnion *uni = path;
	struct jPath *p = uni->path;
	arrayListAddEndPointer ( p->verts, vert );

	return vert;
}

void *initPathLine ( void *path, int v0, int v1 ) {
	struct jLine *line = jLineInit ( );
	line->v0 = v0;
	line->v1 = v1;

	line->type = path_LineTo;

	struct jNakedUnion *uni = path;
	struct jPath *p = uni->path;
	arrayListAddEndPointer ( p->lines, line );

	return line;
}

/// Text Box

void *initTextEle ( ) {
	printf ( "initTextEle ( )\n" );

	struct jNakedUnion *uni = jNakedUnionInit ( );
	jNakedUnionTypeChange0 ( uni, jNaked_Text );
	return uni;
}

void textBox_set_XYWH ( void *textBox, float *XYWH ) {
	printf ( "textBox_set_XYWH ( )\n" );

	struct jNakedUnion *uni = textBox;
	struct jText *text = uni->text;
	text->XYWH[0] = XYWH[0];
	text->XYWH[1] = XYWH[1];
	text->XYWH[2] = XYWH[2];
	text->XYWH[3] = XYWH[3];

}

void textBox_set_text ( void *textBox, char *str ) {
	printf ( "textBox_set_text ( )\n" );
	printf ( "str: %s\n", str );

	struct jNakedUnion *uni = textBox;
	struct jText *text = uni->text;
	fillStringBuilder ( str, text->sb );

	printf ( "textBox_set_text ( ) OVER\n" );
}

/// Other

void saveToDir ( void *jvg, char *dir ) {
	printf ( "saveToDir ( )\n" );

	struct jvg *j = jvg;

	jalbJvg_save ( j, dir );
}



