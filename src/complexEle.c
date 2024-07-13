#include "complexEle.h"

/** AUTO GENERATED CODE */

extern char altKeys[];

extern float colorWhite[];
extern float colorGray[];
extern float colorDGray[];
extern float colorDGray1[];
extern float colorDGray2[];
extern float colorBlack[];
extern float colorGold[];




void complexEle_preInit ( ) {
}


extern int complexDecEditId;
extern int complexEleEditId;
extern int debugPrint_projectName_init;


extern struct draw2dStruct *draw2dApi;
extern struct draw3dStruct *draw3dApi;
extern struct jalbFont *fonts[];

//extern void (*addCanvas)(int id, void *data, int *xywh);
extern addCanvasF *addCanvas;

extern struct backbone_structStruct complexDec;
extern struct backbone_structStruct complexEle;

/** Functions */

/** complexDec */

struct complexDec *complexDecInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "complexDecInit ( )\n" );
	}
	struct complexDec *var = malloc ( sizeof ( struct complexDec ) );
	complexDecFill ( var );
	return var;
}
void complexDecFill ( struct complexDec *var ) {
	var->name[0] = '\0';
	var->subVars = initArrayList ( 10, sizeof ( struct subVar* ), 10 );
	var->modName[0] = '\0';
	var->renderFunct_name[0] = '\0';
	var->renderFunct = NULL;
	var->eventFunct_name[0] = '\0';
	var->eventFunct = NULL;
}

void *complexDecInitMask ( ) {
	void *ret = complexDecInit ( );
	return ret;

}
void complexDecClose ( struct complexDec *var ) {
	if ( var->subVars ) {
		// TODO subVar from out of mod, import close (modNick: jHigh, subVarName: subVar).
	}
	free ( var );

}
int complexDec_attrib_arr[] = {
	0,
	0,
	0,
	0,
	0,
	0,
	0,
};
void complexDecBodyToVal ( void *varPass, int nameI, char *body ) {
	printf ( "complexDecBodyToVal ( )\n" );
	printf ( "nameI: %d\n", nameI );
	printf ( "body: %s\n", body );

	struct complexDec *var = varPass;

	if ( nameI == 0 ) {
		strcpy ( var->name, body );
	} else if ( nameI == 1 ) {
	} else if ( nameI == 2 ) {
		strcpy ( var->modName, body );
	} else if ( nameI == 3 ) {
		strcpy ( var->renderFunct_name, body );
	} else if ( nameI == 4 ) {
		// wont get called?
	} else if ( nameI == 5 ) {
		strcpy ( var->eventFunct_name, body );
	} else if ( nameI == 6 ) {
		// wont get called?
	}
}

int complexDecNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {
	printf ( "complexDecNameToIndex ( )\n" );
	printf ( "body: %s\n", body );

	struct complexDec *var = data;
	if ( strcmp ( body, "name" ) == 0 ) {
		return 0;
	} else if ( strcmp ( body, "subVars" ) == 0 ) {
		*modName = "jHigh";
		void **ptrPtr = (void**)ret;
		*ptrPtr = var->subVars;
		return jxnAlPtr;
	} else if ( strcmp ( body, "modName" ) == 0 ) {
		return 2;
	} else if ( strcmp ( body, "renderFunct_name" ) == 0 ) {
		return 3;
	} else if ( strcmp ( body, "renderFunct" ) == 0 ) {
		void **retPtr = ret;
		*retPtr = &var->renderFunct;
		*strPtr = (char*)(offsetof ( struct complexDec, renderFunct_typeName ) - offsetof ( struct complexDec, renderFunct ));
		return jxnPtrAmbig;
	} else if ( strcmp ( body, "eventFunct_name" ) == 0 ) {
		return 5;
	} else if ( strcmp ( body, "eventFunct" ) == 0 ) {
		return 6;
	}
	return -1;
}

struct xmlFuncts complexDecXml = {
	"complexDec",
	complexDecInitMask,
	complexDecNameToIndex,
	complexDecBodyToVal,
	.postInit = (void(*)(void*))complexDecPostInit,
};

void complexDec_print ( struct complexDec *stru ) {
	printf ( "complexDec_print ( )\n" );
}
/** complexEle */

struct complexEle *complexEleInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "complexEleInit ( )\n" );
	}
	struct complexEle *var = malloc ( sizeof ( struct complexEle ) );
	complexEleFill ( var );
	return var;
}
void complexEleFill ( struct complexEle *var ) {
	var->XYWH[0] = 0.0;
	var->XYWH[1] = 0.0;
	var->XYWH[2] = 0.0;
	var->XYWH[3] = 0.0;

	var->decType = 0;
	var->liveSubVars = initArrayList ( 10, sizeof ( void* ), 10 );
}

void *complexEleInitMask ( ) {
	void *ret = complexEleInit ( );
	return ret;

}
void complexEleClose ( struct complexEle *var ) {
	if ( var->liveSubVars ) {
		freeArrayListPointer ( var->liveSubVars );
	}
	free ( var );

}
int complexEle_attrib_arr[] = {
	0,
	0,
	0,
};
void complexEleBodyToVal ( void *varPass, int nameI, char *body ) {

	struct complexEle *var = varPass;

	if ( nameI == 0 ) {
		consumeStdArr ( body, 1, 1, var->XYWH, 4 );
	} else if ( nameI == 1 ) {
		var->decType = atoi ( body );
	} else if ( nameI == 2 ) {
	}
}

int complexEleNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

//	struct complexEle *var = data;
	if ( strcmp ( body, "XYWH" ) == 0 ) {
		return 0;
	} else if ( strcmp ( body, "decType" ) == 0 ) {
		return 1;
	} else if ( strcmp ( body, "liveSubVars" ) == 0 ) {
		return 2;
	}
	return -1;
}

struct xmlFuncts complexEleXml = {
	"complexEle",
	complexEleInitMask,
	complexEleNameToIndex,
	complexEleBodyToVal,
};

void complexEle_print ( struct complexEle *stru ) {
	printf ( "complexEle_print ( )\n" );
}
/** Other Functs */
