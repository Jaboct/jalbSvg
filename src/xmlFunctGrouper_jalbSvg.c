#include "xmlFunctGrouper_jalbSvg.h"


#include "mod.h"
#include "svg.h"
#include "path.h"
#include "text.h"
#include "shapes.h"

int xmlFuncts_arr_len_jalbSvg = 15;


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


void *get_xmlFuncts_arr_len ( ) {
	return &xmlFuncts_arr_len_jalbSvg;
}
void *get_xmlFuncts_arr ( ) {
	return xmlFuncts_arr_jalbSvg;
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
