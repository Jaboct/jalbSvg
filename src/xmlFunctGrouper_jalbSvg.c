#include "xmlFunctGrouper_jalbSvg.h"



int num_structStruct_jalbSvg = 4;


extern struct xmlFuncts svgXml;
extern struct xmlFuncts nakedUnionXml;
extern struct xmlFuncts gXml;
extern struct xmlFuncts pathXml;


struct xmlFuncts *xmlFuncts_arr_jalbSvg[] = {
	&svgXml,
	&nakedUnionXml,
	&gXml,
	&pathXml,
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
int num_projectVars_jalbSvg = 0;
struct backbone_projectVar *projectVar_arr_jalbSvg[] = {
};

void *get_num_projectVars ( ) {
	return &num_projectVars_jalbSvg;
}

void *get_projectVars_list ( ) {
	return projectVar_arr_jalbSvg;
}
