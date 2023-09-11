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

void hand_test_load ( ) {
	printf ( "hand_test_load ( )\n" );

	char *dirLoad = "/home/jadoo/workspace/jHigh/jalbSvg/res/test_save_00.xml";
	struct svg *svgEle = loadXmlFile_03 ( dirLoad, xmlFuncts_arr_jalbSvg, num_structStruct_jalbSvg );

	say_svg ( svgEle );

	char *dirSave = "/home/jadoo/workspace/jHigh/jalbSvg/res/test_save_01.xml";

	fwriteXml_backbone ( dirSave, &svg, svgEle,
		svg_attributes, backbone_arr_jalbSvg, len_backbone_arr_jalbSvg );

	printf ( "hand_test_load ( ) OVER\n" );
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



/** line 1 */

void line_1_test ( ) {
	printf ( "line_1_test ( )\n" );

//	char *dir = "/home/jadoo/workspace/jHigh/jalbSvg/res/svgProof/1_line.svg";
	char *dir = "/home/jadoo/workspace/jHigh/jalbSvg/res/svgProof/1_line_trim.svg";

	// this is to test parsing.
	struct svg *svgEle = loadXmlFile_03 ( dir, xmlFuncts_arr_jalbSvg, num_structStruct_jalbSvg );

	int numEles = arrayListGetLength ( svgEle->eles );
	printf ( "numEles: %d\n", numEles );

	sayEleList ( svgEle->eles );
/*
	int i;
	int len;

	i = 0;
	len = numEles;

	while ( i < len ) {
		struct nakedUnion *uni = arrayListGetPointer ( svgEle->eles, i );

		printf ( "uni->type: %d\n", uni->type );

		if ( uni->type == G ) {
			struct g *g = uni->g;
			printf ( "id: %s\n", g->id );
			printf ( "numEles: %d\n", arrayListGetLength ( g->eles ) );
		}

		i += 1;
	}
*/

	// so i need to do postInit.


	printf ( "line_1_test ( ) OVER\n" );
}

void sayEleList ( ArrayList *eles ) {
	int i;
	int len;

	i = 0;
	len = arrayListGetLength ( eles );

	while ( i < len ) {
		struct nakedUnion *uni = arrayListGetPointer ( eles, i );

		printf ( "uni->type: %d\n", uni->type );

		if ( uni->type == G ) {
			struct g *g = uni->g;
			printf ( "id: %s\n", g->id );
			printf ( "numEles: %d\n", arrayListGetLength ( g->eles ) );

			sayEleList ( g->eles );
		} else if ( uni->type == Path ) {
			struct path *path = uni->path;
			printf ( "style: %s\n", path->style );
			printf ( "d: %s\n", path->d );
			printf ( "id: %s\n", path->id );
		}

		i += 1;
	}
}

void extra_test ( ) {
	printf ( "extra_test ( )\n" );

	char *dir = "/home/jadoo/workspace/jHigh/jalbSvg/res/test_save_extra.xml";

	// this is to test parsing.
	struct svg *svgEle = loadXmlFile_03 ( dir, xmlFuncts_arr_jalbSvg, num_structStruct_jalbSvg );

	int numEles = arrayListGetLength ( svgEle->eles );
	printf ( "numEles: %d\n", numEles );

	int i;
	int len;

	i = 0;
	len = numEles;

	while ( i < len ) {
		struct nakedUnion *uni = arrayListGetPointer ( svgEle->eles, i );

		printf ( "uni->type: %d\n", uni->type );

		i += 1;
	}

	printf ( "extra_test ( ) OVER\n" );
}

void pathPostInit ( void *data ) {
	printf ( "pathPostInit ( )\n" );
	struct path *path = data;

	sayPath ( path );

	// ok so i need to parse d.
	// i can do this in the BodyToVal, i dont need to do it here.
	// whatever.
}

void sayPath ( struct path *path ) {
	printf ( "style: %s\n", path->style );
	printf ( "d: %s\n", path->d );
	printf ( "id: %s\n", path->id );
}





