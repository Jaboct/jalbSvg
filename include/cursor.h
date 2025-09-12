#pragma once

/** AUTO GENERATED CODE */

#include <stdio.h>
#include <stdlib.h>

#include <jalb/jalbArrayList.h>
#include <jalb/jalbSay.h>

#include <jalb/jfile.h>
#include <jalb/jalb_addCanvas.h>
#include <jalbDraw/drawCutString.h>

#include <jalbXml/jalbXml_02.h>



void cursor_preInit ( );




/** Structs */

struct cursor_ele {
	int index;
	// this should just be the union?
	struct cursor_union *payload;
};

struct cursor_union {
	int type;
	union  {
		struct cursor_path *path;
		struct cursor_group *group;
		struct cursor_circ *circ;
		struct cursor_text *text;
		struct cursor_rect *rect;
	};
};

enum cursor_unionEnum {
	cu_Path = 0,
	cu_Group,
	cu_Circ,
	cu_Text,
	cu_Rect,
};
struct cursor_path {
	int itself;
	ArrayList *verts;	// (int)
};

struct cursor_group {
	int this;
	ArrayList *eles;	// (struct cursor_ele*)
};

struct cursor_circ {
	int type;
};

struct cursor_text {
	int vertI;
};

struct cursor_rect {
	int type;
};



/** Post Includes */


/** Functions */

/** cursor_ele */
struct cursor_ele *cursor_eleInit ( );
void cursor_eleFill ( struct cursor_ele *var );
void *cursor_eleInitMask ( );
void cursor_eleClose ( struct cursor_ele *var );
void cursor_eleBodyToVal ( void *varPass, int nameI, char *body );
int cursor_eleNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName );

/** cursor_union */
struct cursor_union *cursor_unionInit ( );
void cursor_unionFill ( struct cursor_union *var );
void cursor_unionTypeChange0 ( struct cursor_union *var, int type );
void *cursor_unionInitMask ( );
void cursor_unionClose ( struct cursor_union *var );
void cursor_unionBodyToVal ( void *varPass, int nameI, char *body );
int cursor_unionNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName );

/** cursor_path */
struct cursor_path *cursor_pathInit ( );
void cursor_pathFill ( struct cursor_path *var );
void *cursor_pathInitMask ( );
void cursor_pathClose ( struct cursor_path *var );
void cursor_pathBodyToVal ( void *varPass, int nameI, char *body );
int cursor_pathNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName );

/** cursor_group */
struct cursor_group *cursor_groupInit ( );
void cursor_groupFill ( struct cursor_group *var );
void *cursor_groupInitMask ( );
void cursor_groupClose ( struct cursor_group *var );
void cursor_groupBodyToVal ( void *varPass, int nameI, char *body );
int cursor_groupNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName );

/** cursor_circ */
struct cursor_circ *cursor_circInit ( );
void cursor_circFill ( struct cursor_circ *var );
void *cursor_circInitMask ( );
void cursor_circClose ( struct cursor_circ *var );
void cursor_circBodyToVal ( void *varPass, int nameI, char *body );
int cursor_circNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName );

/** cursor_text */
struct cursor_text *cursor_textInit ( );
void cursor_textFill ( struct cursor_text *var );
void *cursor_textInitMask ( );
void cursor_textClose ( struct cursor_text *var );
void cursor_textBodyToVal ( void *varPass, int nameI, char *body );
int cursor_textNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName );

/** cursor_rect */
struct cursor_rect *cursor_rectInit ( );
void cursor_rectFill ( struct cursor_rect *var );
void *cursor_rectInitMask ( );
void cursor_rectClose ( struct cursor_rect *var );
void cursor_rectBodyToVal ( void *varPass, int nameI, char *body );
int cursor_rectNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName );

/** Other Functs */
