#pragma once

#include <jalb/jalbSb.h>


/** Functions */

void *get_jvg_api ( );
void *initJvgEle ( );
void addJvgEle ( void *jvg, void *ele );

// Path

void *initPathEle ( );
void *initPathVert ( void *path, float *loc );
void *initPathLine ( void *path, int v0, int v1 );


/// Text Box

void *initTextEle ( );
void textBox_set_XYWH ( void *textBox, float *XYWH );
void textBox_set_text ( void *textBox, char *str );


/// Other

void saveToDir ( void *jvg, char *dir );



