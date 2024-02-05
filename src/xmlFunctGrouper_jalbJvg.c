#include "xmlFunctGrouper_jalbJvg.h"



int num_structStruct_jalbJvg = 10;


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
int num_projectVars_jalbJvg = 0;
struct backbone_projectVar *projectVar_arr_jalbJvg[] = {
};

void *get_num_projectVars ( ) {
	return &num_projectVars_jalbJvg;
}

void *get_projectVars_list ( ) {
	return projectVar_arr_jalbJvg;
}
