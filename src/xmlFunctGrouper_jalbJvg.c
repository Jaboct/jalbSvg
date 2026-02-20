#include "xmlFunctGrouper_jalbJvg.h"


/** Includes */

#include "jMod.h"
#include "jPath.h"
#include "jText.h"
#include "jGroup.h"
#include "jShapes.h"
#include "complexEle.h"
#include "complexMod.h"
#include "complexScript.h"
//#include "CAD_history.h"
#include "cursor.h"


/** Variables */

int xmlFuncts_arr_len_jalbJvg = 27;


extern struct xmlFuncts jPathXml;
extern struct xmlFuncts jVertXml;
extern struct xmlFuncts jLineXml;
extern struct xmlFuncts jTextXml;
extern struct xmlFuncts jGroupXml;
extern struct xmlFuncts jNakedUnionXml;
extern struct xmlFuncts jvgXml;
extern struct xmlFuncts jRectXml;
extern struct xmlFuncts jCircXml;
extern struct xmlFuncts jEllipseXml;
extern struct xmlFuncts complexDecXml;
extern struct xmlFuncts complexEleXml;
extern struct xmlFuncts jLiveDataXml;
extern struct xmlFuncts complexModXml;
extern struct xmlFuncts complexScriptXml;
extern struct xmlFuncts cScriptEleXml;
extern struct xmlFuncts complexModDataXml;
extern struct xmlFuncts complexRefXml;
//extern struct xmlFuncts CAD_historyXml;
extern struct xmlFuncts cursor_eleXml;
extern struct xmlFuncts cursor_unionXml;
extern struct xmlFuncts cursor_pathXml;
extern struct xmlFuncts cursor_groupXml;
extern struct xmlFuncts cursor_circXml;
extern struct xmlFuncts cursor_textXml;
extern struct xmlFuncts cursor_rectXml;
extern struct xmlFuncts complexListXml;


struct xmlFuncts *xmlFuncts_arr_jalbJvg[] = {
	&jPathXml,
	&jVertXml,
	&jLineXml,
	&jTextXml,
	&jGroupXml,
	&jNakedUnionXml,
	&jvgXml,
	&jRectXml,
	&jCircXml,
	&jEllipseXml,
	&complexDecXml,
	&complexEleXml,
	&jLiveDataXml,
	&complexModXml,
	&complexScriptXml,
	&cScriptEleXml,
	&complexModDataXml,
	&complexRefXml,
//	&CAD_historyXml,
	NULL,
	&cursor_eleXml,
	&cursor_unionXml,
	&cursor_pathXml,
	&cursor_groupXml,
	&cursor_circXml,
	&cursor_textXml,
	&cursor_rectXml,
	&complexListXml,
};


void *get_xmlFuncts_arr_len ( ) {
	return &xmlFuncts_arr_len_jalbJvg;
}
void *get_xmlFuncts_arr ( ) {
	return xmlFuncts_arr_jalbJvg;
}
int num_projectVars_jalbJvg = 2;

extern struct jvg glob_jvg;// (jMod.c)

struct backbone_projectVar proj_glob_jvg = {
	{
		.name = "glob_jvg",
		.type = 1,
		.typeIndex = 6,
		.initType = 0,
		.length = 0,
		.literal = 1,
		.data = {
			.id = 0,
		},
		.saveFlag = 1,
		.naked = 0,
	},
	.data = &glob_jvg,
};


extern ArrayList global_jEles;// (jMod.c)
struct backbone_subAl global_jEles_global_jEles_subAl = {
	.overflow = 10,
	.literal = 0,
	.type = 1,
	.typeIndex = 5,
	.length = -1,
	.naked = 0,
};

struct backbone_projectVar proj_global_jEles = {
	{
		.name = "global_jEles",
		.type = 0,
		.typeIndex = 3,
		.initType = 0,
		.length = 0,
		.literal = 1,
		.data = {
			.id = 0,
			.ptr = &global_jEles_global_jEles_subAl,
		},
		.saveFlag = 1,
		.naked = 0,
	},
	.data = &global_jEles,
};

struct backbone_projectVar *projectVar_arr_jalbJvg[] = {
	&proj_glob_jvg,
	&proj_global_jEles,
};

void *get_num_projectVars ( ) {
	return &num_projectVars_jalbJvg;
}

void *get_projectVars_list ( ) {
	return projectVar_arr_jalbJvg;
}
