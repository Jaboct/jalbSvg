#include "complexMod.h"

/** AUTO GENERATED CODE */

extern char altKeys[];

extern float colorWhite[];
extern float colorGray[];
extern float colorDGray[];
extern float colorDGray1[];
extern float colorDGray2[];
extern float colorBlack[];
extern float colorGold[];




void complexMod_preInit ( ) {
}


extern int complexModEditId;
extern int debugPrint_projectName_init;


extern struct draw2dStruct *draw2dApi;
extern struct draw3dStruct *draw3dApi;
extern struct jalbFont *fonts[];

//extern void (*addCanvas)(int id, void *data, int *xywh);
extern addCanvasF *addCanvas;

extern struct backbone_structStruct complexMod;

/** Functions */

/** complexMod */

struct complexMod *complexModInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "complexModInit ( )\n" );
	}
	struct complexMod *var = malloc ( sizeof ( struct complexMod ) );
	complexModFill ( var );
	return var;
}
void complexModFill ( struct complexMod *var ) {
	var->complexDecList = initArrayList ( 0, sizeof ( out of range (type: -1) (typeIndex: -1)* ), 0 );
	var->globalVars = initArrayList ( 0, sizeof ( out of range (type: -1) (typeIndex: -1)* ), 0 );
	var->globalScripts = initArrayList ( 0, sizeof ( out of range (type: -1) (typeIndex: -1)* ), 0 );
	var->globalScripts = initArrayList ( 0, sizeof ( out of range (type: -1) (typeIndex: -1)* ), 0 );
}

void *complexModInitMask ( ) {
	void *ret = complexModInit ( );
	return ret;

}
void complexModClose ( struct complexMod *var ) {
	free ( var );

}
int complexMod_attrib_arr[] = {
	0,
	0,
	0,
	0,
};
void complexModBodyToVal ( void *varPass, int nameI, char *body ) {

	struct complexMod *var = varPass;

	if ( nameI == 0 ) {
	} else if ( nameI == 1 ) {
	} else if ( nameI == 2 ) {
	} else if ( nameI == 3 ) {
		// wont get called?
	}
}

int complexModNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

	struct complexMod *var = data;
	if ( strcmp ( body, "complexDecList" ) == 0 ) {
		void **ptrPtr = (void**)ret;
		*ptrPtr = var->complexDecList;
		return jxnAlPtr;
	} else if ( strcmp ( body, "globalVars" ) == 0 ) {
		void **ptrPtr = (void**)ret;
		*ptrPtr = var->globalVars;
		return jxnAlPtr;
	} else if ( strcmp ( body, "globalScripts" ) == 0 ) {
		void **ptrPtr = (void**)ret;
		*ptrPtr = var->globalScripts;
		return jxnAlPtr;
	} else if ( strcmp ( body, "" ) == 0 ) {
		return 3;
	}
	return -1;
}

struct xmlFuncts complexModXml = {
	"complexMod",
	complexModInitMask,
	complexModNameToIndex,
	complexModBodyToVal,
};

void complexMod_print ( struct complexMod *stru ) {
	printf ( "complexMod_print ( )\n" );
}
/** Other Functs */
