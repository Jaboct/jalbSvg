#include "complexScript.h"

/** AUTO GENERATED CODE */

extern char altKeys[];

extern float colorWhite[];
extern float colorGray[];
extern float colorDGray[];
extern float colorDGray1[];
extern float colorDGray2[];
extern float colorBlack[];
extern float colorGold[];




void complexScript_preInit ( ) {
}


extern int complexScriptEditId;
extern int cScriptEleEditId;
extern int debugPrint_projectName_init;


/** Variables */

extern struct draw2dStruct *draw2dApi;
extern struct draw3dStruct *draw3dApi;
extern struct jalbFont *fonts[];

//extern void (*addCanvas)(int id, void *data, int *xywh);
extern addCanvasF *addCanvas;

extern struct backbone_structStruct backboneStru_complexScript;
extern struct backbone_structStruct backboneStru_cScriptEle;

/** Functions */

/** complexScript */

struct complexScript *complexScriptInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "complexScriptInit ( )\n" );
	}
	struct complexScript *var = malloc ( sizeof ( struct complexScript ) );
	complexScriptFill ( var );
	return var;
}
void complexScriptFill ( struct complexScript *var ) {
	var->name[0] = '\0';
	var->eleList = initArrayList ( 10, sizeof ( struct cScriptEle* ), 10 );
}

void *complexScriptInitMask ( ) {
	void *ret = complexScriptInit ( );
	return ret;

}
void complexScriptClose ( struct complexScript *var ) {
	if ( var->eleList ) {
		freeArrayListPointerFunction ( var->eleList, (void (*)(void*))cScriptEleClose );
	}
	free ( var );

}
int complexScript_attrib_arr[] = {
	0,
	0,
};
void complexScriptBodyToVal ( void *varPass, int nameI, char *body ) {

	struct complexScript *var = varPass;

	if ( nameI == 0 ) {
		strcpy ( var->name, body );
	} else if ( nameI == 1 ) {
	}
}

int complexScriptNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

	struct complexScript *var = data;
	if ( strcmp ( body, "name" ) == 0 ) {
		return 0;
	} else if ( strcmp ( body, "eleList" ) == 0 ) {
		void **ptrPtr = (void**)ret;
		*ptrPtr = var->eleList;
		return jxnAlPtr;
	}
	return -1;
}

struct xmlFuncts complexScriptXml = {
	"complexScript",
	complexScriptInitMask,
	complexScriptNameToIndex,
	complexScriptBodyToVal,
};

void complexScript_print ( struct complexScript *stru ) {
	printf ( "complexScript_print ( )\n" );
}
/** cScriptEle */

struct cScriptEle *cScriptEleInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "cScriptEleInit ( )\n" );
	}
	struct cScriptEle *var = malloc ( sizeof ( struct cScriptEle ) );
	cScriptEleFill ( var );
	return var;
}
void cScriptEleFill ( struct cScriptEle *var ) {
	var->type = -1;
//	cScriptEleTypeChange0 ( var, 0 );
}
void cScriptEleTypeChange0 ( struct cScriptEle *var, int type ) {
	if ( var->type == type ) {
		return;
	}
	if ( var->type == 0 ) {
	} else if ( var->type == 1 ) {
	}
	if ( type == 0 ) {
				
	} else if ( type == 1 ) {
				
	}
	var->type = type;
}


void *cScriptEleInitMask ( ) {
	void *ret = cScriptEleInit ( );
	return ret;

}
void cScriptEleClose ( struct cScriptEle *var ) {
	if ( var->type == 0 ) {
	} else if ( var->type == 1 ) {
	}
	free ( var );

}
int cScriptEle_attrib_arr[] = {
	0,
};
void cScriptEleBodyToVal ( void *varPass, int nameI, char *body ) {

	struct cScriptEle *var = varPass;

	if ( nameI == 0 ) {
		if ( var->type == 0 ) {
			// wont get called?
		} else if ( var->type == 1 ) {
			// wont get called?
		}
	}
}

int cScriptEleNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

	struct cScriptEle *var = data;
	if ( strcmp ( body, "varDec" ) == 0 ) {
		cScriptEleTypeChange0 ( var, 0 );
		return 0;
	} else if ( strcmp ( body, "operator" ) == 0 ) {
		cScriptEleTypeChange0 ( var, 1 );
		return 0;
	}
	return -1;
}

struct xmlFuncts cScriptEleXml = {
	"cScriptEle",
	cScriptEleInitMask,
	cScriptEleNameToIndex,
	cScriptEleBodyToVal,
	.typeChange = (void (*) (void*, int))cScriptEleTypeChange0,
};

void cScriptEle_print ( struct cScriptEle *stru ) {
	printf ( "cScriptEle_print ( )\n" );
}
/** Other Functs */
