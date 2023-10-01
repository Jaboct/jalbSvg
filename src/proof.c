#include "proof.h"


extern struct svg *global_svg;



extern int num_structStruct_jalbSvg;
extern struct xmlFuncts *xmlFuncts_arr_jalbSvg[];


extern int len_backbone_arr_jalbSvg;
extern struct backbone_structStruct *backbone_arr_jalbSvg[];

extern int svg_attributes[];
extern struct backbone_structStruct svg;



/** Functions */

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

//	printf ( "svgEle: %p\n", svgEle );
	say_svg ( svgEle );

	global_svg = svgEle;

	char *dirSave = "/home/jadoo/workspace/jHigh/jalbSvg/res/test_save_01.xml";

	fwriteXml_backbone ( dirSave, &svg, svgEle,
		svg_attributes, backbone_arr_jalbSvg, len_backbone_arr_jalbSvg );

	printf ( "hand_test_load ( ) OVER\n" );
}

void hand_test_01 ( ) {
	printf ( "hand_test_01 ( )\n" );

	char *dirLoad = "/home/jadoo/workspace/jHigh/jalbSvg/res/svgProof/heart.svg";
	char *dirSave = "/home/jadoo/workspace/jHigh/jalbSvg/res/svgProof/heart_save.svg";

	struct svg *svgEle = loadXmlFile_03 ( dirLoad, xmlFuncts_arr_jalbSvg, num_structStruct_jalbSvg );

	expandSvg ( svgEle );

	say_svg ( svgEle );

	prepair_d ( svgEle->eles );

	fwriteXml_backbone ( dirSave, &svg, svgEle,
		svg_attributes, backbone_arr_jalbSvg, len_backbone_arr_jalbSvg );

	printf ( "hand_test_01 ( ) OVER\n" );
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



/// Other

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





void proof_parseD ( ) {
	printf ( "proof_parseD ( )\n" );

	// parses this d string to structs, then prints the structs, then converts it back to string and print that.

/*
	char *str = "M 10,30 \
       A 20,20 0,0,1 50,30 \
       A 20,20 0,0,1 90,30 \
       Q 90,60 50,90 \
       Q 10,60 10,30 z";
*/
	char *str = "M 10.287852,46.635926 41.093974,15.829804";

	ArrayList *eles = initArrayList ( 10, sizeof ( struct pathUni* ), 10 );
	parseD ( str, eles );

	int i;
	int len;

	i = 0;
	len = arrayListGetLength ( eles );

	printf ( "eles.len: %d\n", len );

	while ( i < len ) {
		struct pathUni *uni = arrayListGetPointer ( eles, i );

		sayPathUni ( uni );

		i += 1;
	}

	char d[1024];
	eleListToD ( eles, d );
	printf ( "d: (%s)\n", d );

	printf ( "proof_parseD ( ) OVER\n" );
}









