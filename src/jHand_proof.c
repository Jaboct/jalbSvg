#include "jHand_proof.h"


void *(*f_subVar_init) ( ) = NULL;
void (*f_subVar_setName) ( void *data, char *name ) = NULL;


extern int len_backbone_arr_jalbJvg;
extern struct backbone_structStruct *backbone_arr_jalbJvg[];

extern int len_backbone_arr_consumeMod;
extern struct backbone_structStruct *backbone_arr_consumeMod[];

extern int num_structStruct_jalbJvg;
extern struct xmlFuncts *xmlFuncts_arr_jalbJvg[];

extern int num_structStruct_consumeMod;
extern struct xmlFuncts *xmlFuncts_arr_consumeMod[];


int jvg_backbone_wrangled = 0;

/** Functions */

void jvg_backbone_wrangle ( ) {
	printf ( "jvg_backbone_wrangle ( )\n" );

	// first send backbones the xml lib.
	if ( !jvg_backbone_wrangled ) {
		wrangleBackbone ( "jalbJvg", len_backbone_arr_jalbJvg, backbone_arr_jalbJvg );
		wrangleBackbone ( "jHigh", len_backbone_arr_consumeMod, backbone_arr_consumeMod );

		wrangleXmlFuncts ( "jalbJvg", num_structStruct_jalbJvg, xmlFuncts_arr_jalbJvg );
		wrangleXmlFuncts ( "jHigh", num_structStruct_consumeMod, xmlFuncts_arr_consumeMod );

		jvg_backbone_wrangled = 1;
	}
}

void hand_complex_save ( ) {
	printf ( "hand_complex_save ( )\n" );

	jvg_backbone_wrangle ( );

	if ( !f_subVar_init ) {
		printf ( "ERROR, !f_subVar_init\n" );
		return;
	}
	if ( !f_subVar_setName ) {
		printf ( "ERROR, !f_subVar_setName\n" );
		return;
	}


	struct complexMod *mod = complexModInit ( );


printf ( "a\n" );
	struct jvg *jvg = jvgInit ( );
	struct complexDec *dec = complexDecInit ( );
	arrayListAddEndPointer ( mod->complexDecList, dec );

printf ( "b\n" );
	void *subVar = f_subVar_init ( );
printf ( "c\n" );
	arrayListAddEndPointer ( dec->subVars, subVar );
printf ( "d\n" );
	f_subVar_setName ( subVar, "firstSubVar" );

	char *dir = "/home/jadoo/workspace/jHigh/jalbSvg/res/jvgTest/test_00.xml";
	jalbJvg_save ( jvg, dir );

	printf ( "hand_complex_save ( ) OVER\n" );
}

void hand_complex_load ( ) {
	printf ( "hand_complex_load ( )\n" );

	jvg_backbone_wrangle ( );

	char *dir = "/home/jadoo/workspace/jHigh/jalbSvg/res/jvgTest/test_00.xml";
	struct jvg *jvg = jalbJvg_load ( dir );


//	printf ( "jvg->complexDecList.len: %d\n", arrayListGetLength ( mod->complexDecList ) );

	char *dir1 = "/home/jadoo/workspace/jHigh/jalbSvg/res/jvgTest/test_01.xml";
	jalbJvg_save ( jvg, dir1 );

//	exit ( 12 );

	printf ( "hand_complex_load ( ) OVER\n" );
}

/** subVar Setters */

void set_subVar_init ( void *data ) {
	f_subVar_init = data;
}

void set_subVar_setName ( void *data ) {
	f_subVar_setName = data;
}


















