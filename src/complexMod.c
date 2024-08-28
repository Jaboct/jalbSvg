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
	var->name[0] = '\0';
	var->complexDecList = initArrayList ( 10, sizeof ( struct complexDec* ), 10 );
	var->globalVars = initArrayList ( 10, sizeof ( struct subVar* ), 10 );
	var->globalScripts = initArrayList ( 10, sizeof ( struct complexScript* ), 10 );
}

void *complexModInitMask ( ) {
	void *ret = complexModInit ( );
	return ret;

}
void complexModClose ( struct complexMod *var ) {
	if ( var->complexDecList ) {
		freeArrayListPointerFunction ( var->complexDecList, (void (*)(void*))complexDecClose );
	}
	if ( var->globalVars ) {
		// TODO subVar from out of mod, import close (modNick: jHigh, subVarName: subVar).
	}
	if ( var->globalScripts ) {
		freeArrayListPointerFunction ( var->globalScripts, (void (*)(void*))complexScriptClose );
	}
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
		strcpy ( var->name, body );
	} else if ( nameI == 1 ) {
	} else if ( nameI == 2 ) {
	} else if ( nameI == 3 ) {
	}
}

int complexModNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

	struct complexMod *var = data;
	if ( strcmp ( body, "name" ) == 0 ) {
		return 0;
	} else if ( strcmp ( body, "complexDecList" ) == 0 ) {
		void **ptrPtr = (void**)ret;
		*ptrPtr = var->complexDecList;
		return jxnAlPtr;
	} else if ( strcmp ( body, "globalVars" ) == 0 ) {
		*modName = "jHigh";
		void **ptrPtr = (void**)ret;
		*ptrPtr = var->globalVars;
		return jxnAlPtr;
	} else if ( strcmp ( body, "globalScripts" ) == 0 ) {
		void **ptrPtr = (void**)ret;
		*ptrPtr = var->globalScripts;
		return jxnAlPtr;
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
