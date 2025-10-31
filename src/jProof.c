#include "jProof.h"


/** Variables */

char *outputLog = "/home/jadoo/workspace/jHigh/jalbSvg/res/jvg_proof/outputLog.txt";
char *diffTemp = "/home/jadoo/workspace/jHigh/jalbSvg/res/jvg_proof/diffTemp.txt";

int num_jvg_tests = 1;
struct jvg_proof_test jvg_tests[1] = {
	{
		.name = "test_00",
		.knownDir = "/home/jadoo/workspace/jHigh/jalbSvg/res/jvg_proof/expected/test_00.xml",
		.madeDir = "/home/jadoo/workspace/jHigh/jalbSvg/res/jvg_proof/created/test_00.xml",
	}
};


/** Functions */

void jProof_test_all ( ) {

//	hand_save_stru_all ( );

	FILE *fp = jfopenAT ( outputLog );
	printf ( "log fp: %p\n", fp );

	char time[256];
	timeToString ( time );

	jalbFwrite ( fp, "\n" );
	jalbFwrite ( fp, "(%s)\n", time );

	int i = 0;
	int len = num_jvg_tests;
	while ( i < len ) {
		struct jvg_proof_test *t = &jvg_tests[i];
		int ret = hand_diff ( t->knownDir, t->madeDir );
		if ( ret == 0 ) {
			jalbFwrite ( fp, "good\t%s\n", t->name );
		} else {
			jalbFwrite ( fp, "bad\t%s\n", t->name );
		}


		i += 1;
	}

	fclose ( fp );
}

int hand_diff ( char *fknow, char *ftest ) {
	printf ( "hand_diff ( )\n" );
	printf ( "fknow: %s\n", fknow );
	printf ( "ftest: %s\n", ftest );

	char console[2024];
	sprintf ( console, "diff %s %s >%s", fknow, ftest, diffTemp );

	printf ( "console: %s\n", console );
	system ( console );

	FILE *fp = jfopenRT ( diffTemp );
	printf ( "diffTemp fp: %p\n", fp );

	int fileLines = fcountLines ( fp );
	fclose ( fp );

	if ( fileLines == 0 ) {
//		jalbFwrite ( fp, "the file is good\n" );

		return 0;
	} else {
//		jalbFwrite ( fp, "the file is bad\n" );

		return 1;
	}

	printf ( "hand_diff ( ) OVER\n" );
}


/// Complex

#include "jGroup.h"
#include "jHand.h"

extern struct jvg *glob_jvg;
extern char saveDir[];

void complex_test_03 ( ) {
	printf ( "complex_test_03 ( )\n" );


	// spawn new jvg ele, make a complexMod, make a complexDec, define it as jalbCalc,
	// spawn a complexEle, then compare the render and save file.
	// todo, add event, and add proofs for the uiGen eles.

	char *fullDir = "/home/jadeb/workspace/jHigh/jalbSvg/res/jvgTest/test_03.xml";
	strcpy ( saveDir, fullDir );

	glob_jvg = jvgInit ( );
	struct jvg *jvg = glob_jvg;

	spawn_new_complexDec ( );

	struct complexMod *mod = arrayListGetPointer ( jvg->moduleList, 0 );
	struct complexDec *dec = arrayListGetPointer ( mod->complexDecList, 0 );

	strcpy ( mod->name, "jalbCalc" );
	strcpy ( dec->modName, "jalbCalc" );

	strcpy ( dec->renderFunct_name, "rendEquation_render_dynamic" );
	strcpy ( dec->eventFunct_name, "rendEquation_event_dynamic" );


	// add complexEle
	struct jNakedUnion *uni = jNakedUnionInit ( );
	jNakedUnionTypeChange0 ( uni, jNaked_Complex );
	uni->complex->XYWH[0] = 637;
	uni->complex->XYWH[1] = 418;
	uni->complex->XYWH[2] = 400;
	uni->complex->XYWH[3] = 100;

	arrayListAddEndPointer ( jvg->eles, uni );



	complexDecPostInit ( dec );



	jHand_save ( );

	printf ( "complex_test_03 ( ) OVER\n" );
}





























