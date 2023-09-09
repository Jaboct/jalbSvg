#include "hand.h"




/** Functions */


extern int num_structStruct_jalbSvg;
extern struct xmlFuncts *xmlFuncts_arr_jalbSvg[];


extern int len_backbone_arr_jalbSvg;
extern struct backbone_structStruct *backbone_arr_jalbSvg[];

extern int svg_attributes[];
extern struct backbone_structStruct svg;

void hand_test ( ) {
	printf ( "hand_test ( )\n" );

	char *dir = "/home/jadoo/workspace/jHigh/jalbSvg/res/test_00.xml";
	struct svg *svgEle = loadXmlFile_03 ( dir, xmlFuncts_arr_jalbSvg, num_structStruct_jalbSvg );

	say_svg ( svgEle );

	char *dirSave = "/home/jadoo/workspace/jHigh/jalbSvg/res/test_save_00.xml";

	fwriteXml_backbone ( dirSave, &svg, svgEle,
		svg_attributes, backbone_arr_jalbSvg, len_backbone_arr_jalbSvg );

	printf ( "hand_test ( ) OVER\n" );
}

/*
int svgNameToIndex ( char *body, void *data, void *ret, char **strPtr ) {

	struct svg *var = data;
	if ( strcmp ( body, "width" ) == 0 ) {
		return 0;
	} else if ( strcmp ( body, "height" ) == 0 ) {
		return 1;
	} else if ( strcmp ( body, "eles" ) == 0 ) {
		void **ptrPtr = (void**)ret;
		*ptrPtr = var->eles;
		return jxnAlPtr;

	} else if ( strcmp ( body, "g" ) == 0 ) {
		struct nakedUnion *naked = nakedUnionInit ( );
		arrayListAddEndPointer ( var->eles, naked );
		nakedUnionTypeChange0 ( naked, G );

//		nakedUnionTypeChange0 ( var, 0 );
		*strPtr = "g";
		void **retPtr = ret;
//		*retPtr = &var->g;
		*retPtr = &naked->g;
		return jxnPtr;
	}
	return -1;
}
*/

void say_svg ( struct svg *svg ) {
	printf ( "say_svg ( )\n" );
	printf ( "svg: %p\n", svg );
	if ( !svg ) {
		return;
	}

	printf ( "svg->eles.len: %d\n", arrayListGetLength ( svg->eles ) );

	printf ( "say_svg ( ) OVER\n" );
}










