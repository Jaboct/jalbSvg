#include "xmlFunctGrouper_jalbJvg.h"



int num_structStruct_jalbJvg = 18;


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
};


void *get_num_structStruct ( ) {
	return &num_structStruct_jalbJvg;
}
void *get_xmlFuncts_arr ( ) {
	return xmlFuncts_arr_jalbJvg;
}
extern struct backbone_structStruct *backbone_arr_jalbJvg[];
void *get_backbone_arr ( ) {
	return backbone_arr_jalbJvg;
}
int num_projectVars_jalbJvg = 1;

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
	&proj_global_jEles,
};

void *get_num_projectVars ( ) {
	return &num_projectVars_jalbJvg;
}

void *get_projectVars_list ( ) {
	return projectVar_arr_jalbJvg;
}
