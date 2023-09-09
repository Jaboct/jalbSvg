#include "xmlFunctGrouper.h"



int num_structStruct = 4;


extern struct xmlFuncts svgXml;
extern struct xmlFuncts nakedUnionXml;
extern struct xmlFuncts gXml;
extern struct xmlFuncts pathXml;


struct xmlFuncts *xmlFuncts_arr[] = {
	&svgXml,
	&nakedUnionXml,
	&gXml,
	&pathXml,
};


void *get_num_structStruct ( ) {
	return &num_structStruct;
}
void *get_xmlFuncts_arr ( ) {
	return xmlFuncts_arr;
}
extern struct backbone_structStruct *backbone_arr[];
void *get_backbone_arr ( ) {
	return backbone_arr;
}
int num_projectVars = 0;
struct backbone_projectVar *projectVar_arr[] = {
};

void *get_num_projectVars ( ) {
	return &num_projectVars;
}

void *get_projectVars_list ( ) {
	return projectVar_arr;
}
