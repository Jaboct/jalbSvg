#include "xmlFunctGrouper.h"



int num_structStruct = 15;


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


struct xmlFuncts *xmlFuncts_arr[] = {
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
