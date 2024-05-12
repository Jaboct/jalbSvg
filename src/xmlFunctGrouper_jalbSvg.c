#include "xmlFunctGrouper_jalbSvg.h"



int num_structStruct_jalbSvg = 15;


extern struct xmlFuncts svgXml;
extern struct xmlFuncts nakedUnionXml;
extern struct xmlFuncts gXml;
extern struct xmlFuncts pathXml;
extern struct xmlFuncts pathUniXml;
extern struct xmlFuncts moveToXml;
extern struct xmlFuncts lineToXml;
extern struct xmlFuncts cubicBezXml;
extern struct xmlFuncts quadBezXml;
extern struct xmlFuncts ellipArcXml;
extern struct xmlFuncts textXml;
extern struct xmlFuncts tspanXml;
extern struct xmlFuncts rectXml;
extern struct xmlFuncts circleXml;
extern struct xmlFuncts ellipseXml;


struct xmlFuncts *xmlFuncts_arr_jalbSvg[] = {
	&svgXml,
	&nakedUnionXml,
	&gXml,
	&pathXml,
	&pathUniXml,
	&moveToXml,
	&lineToXml,
	&cubicBezXml,
	&quadBezXml,
	&ellipArcXml,
	&textXml,
	&tspanXml,
	&rectXml,
	&circleXml,
	&ellipseXml,
};


void *get_num_structStruct ( ) {
	return &num_structStruct_jalbSvg;
}
void *get_xmlFuncts_arr ( ) {
	return xmlFuncts_arr_jalbSvg;
}
extern struct backbone_structStruct *backbone_arr_jalbSvg[];
void *get_backbone_arr ( ) {
	return backbone_arr_jalbSvg;
}
int num_projectVars_jalbSvg = 1;

extern ArrayList global_jEles;// (jMod.c)
struct backbone_subAl global_jEles_global_jEles_subAl = {
	.overflow = 10,
	.literal = 0,
	.type = 1,
	.typeIndex = 15,
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
			0,
			&global_jEles_global_jEles_subAl,
		},
		.saveFlag = 1,
		.naked = 0,
	},
	.data = &global_jEles,
};

struct backbone_projectVar *projectVar_arr_jalbSvg[] = {
	&proj_global_jEles,
};

void *get_num_projectVars ( ) {
	return &num_projectVars_jalbSvg;
}

void *get_projectVars_list ( ) {
	return projectVar_arr_jalbSvg;
}
