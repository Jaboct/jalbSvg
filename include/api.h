#pragma once

#include <jalb/jalbArrayList.h>
#include <jalb/jalbSb.h>

#include "jPath.h"
#include "path.h"

#include "jText.h"

#include "api_jvg.h"

/** Functions */

void *get_jvg_api ( );
void *initJvgEle ( );
void addJvgEle ( void *jvg, void *ele );

void *initPathVert ( void *path, float *loc );
void *initPathLine ( void *path, int v0, int v1 );

void textBox_set_XYWH ( void *textBox, float *XYWH );
void textBox_set_text ( void *textBox, char *str );




