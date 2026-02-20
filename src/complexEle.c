#include "complexEle.h"

/** AUTO GENERATED CODE */

/** Includes */


#include "complexEle_ext.h"


/** Variables */


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
extern int jLiveDataEditId;
extern int complexRefEditId;
extern int complexListEditId;
extern int debugPrint_projectName_init;


/** Variables */

extern struct draw2dStruct *draw2dApi;
extern struct draw3dStruct *draw3dApi;
extern struct jalbFont *fonts[];

//extern void (*addCanvas)(int id, void *data, int *xywh);
extern addCanvasF *addCanvas;

extern struct backbone_structStruct backboneStru_complexDec;
extern struct backbone_structStruct backboneStru_complexEle;
extern struct backbone_structStruct backboneStru_jLiveData;
extern struct backbone_structStruct backboneStru_complexRef;
extern struct backbone_structStruct backboneStru_complexList;

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
	var->renderParams = initArrayList ( 10, sizeof ( int ), 10 );
	var->eventFunct_name[0] = '\0';
	var->eventFunct = NULL;
	var->eventParams = initArrayList ( 10, sizeof ( int ), 10 );
}

void *complexDecInitMask ( ) {
	void *ret = complexDecInit ( );
	return ret;

}
void complexDecClose ( struct complexDec *var ) {
	if ( var->subVars ) {
		// TODO subVar from out of mod, import close (modNick: jHigh, subVarName: subVar).
	}
	if ( var->renderParams ) {
		freeArrayList ( var->renderParams );
	}
	if ( var->eventParams ) {
		freeArrayList ( var->eventParams );
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
	0,
	0,
};
void complexDecBodyToVal ( void *varPass, int nameI, char *body ) {

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
		consumeStdAl ( body, 0, 1, var->renderParams );
	} else if ( nameI == 6 ) {
		strcpy ( var->eventFunct_name, body );
	} else if ( nameI == 7 ) {
		// wont get called?
	} else if ( nameI == 8 ) {
		consumeStdAl ( body, 0, 1, var->eventParams );
	}
}

int complexDecNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

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
		return 4;
	} else if ( strcmp ( body, "renderParams" ) == 0 ) {
		return 5;
	} else if ( strcmp ( body, "eventFunct_name" ) == 0 ) {
		return 6;
	} else if ( strcmp ( body, "eventFunct" ) == 0 ) {
		return 7;
	} else if ( strcmp ( body, "eventParams" ) == 0 ) {
		return 8;
	}
	return -1;
}

struct xmlFuncts complexDecXml = {
	.typeName = "complexDec",
	.init = complexDecInitMask,
	.nameToIndex = complexDecNameToIndex,
	.bodyToVal = complexDecBodyToVal,
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

	var->decModI = 0;
	var->decType = 0;
	var->liveSubVars = initArrayList ( 10, sizeof ( struct jLiveData* ), 10 );
}

void *complexEleInitMask ( ) {
	void *ret = complexEleInit ( );
	return ret;

}
void complexEleClose ( struct complexEle *var ) {
	if ( var->liveSubVars ) {
		freeArrayListPointerFunction ( var->liveSubVars, (void (*)(void*))jLiveDataClose );
	}
	free ( var );

}
int complexEle_attrib_arr[] = {
	0,
	0,
	0,
	0,
};
void complexEleBodyToVal ( void *varPass, int nameI, char *body ) {

	struct complexEle *var = varPass;

	if ( nameI == 0 ) {
		consumeStdArr ( body, 1, 1, var->XYWH, 4 );
	} else if ( nameI == 1 ) {
		var->decModI = atoi ( body );
	} else if ( nameI == 2 ) {
		var->decType = atoi ( body );
	} else if ( nameI == 3 ) {
	}
}

int complexEleNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

	struct complexEle *var = data;
	if ( strcmp ( body, "XYWH" ) == 0 ) {
		return 0;
	} else if ( strcmp ( body, "decModI" ) == 0 ) {
		return 1;
	} else if ( strcmp ( body, "decType" ) == 0 ) {
		return 2;
	} else if ( strcmp ( body, "liveSubVars" ) == 0 ) {
		void **ptrPtr = (void**)ret;
		*ptrPtr = var->liveSubVars;
		return jxnAlPtr;
	}
	return -1;
}

struct xmlFuncts complexEleXml = {
	.typeName = "complexEle",
	.init = complexEleInitMask,
	.nameToIndex = complexEleNameToIndex,
	.bodyToVal = complexEleBodyToVal,
};

void complexEle_print ( struct complexEle *stru ) {
	printf ( "complexEle_print ( )\n" );
}
/** jLiveData */

struct jLiveData *jLiveDataInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "jLiveDataInit ( )\n" );
	}
	struct jLiveData *var = malloc ( sizeof ( struct jLiveData ) );
	jLiveDataFill ( var );
	return var;
}
void jLiveDataFill ( struct jLiveData *var ) {
	var->type = -1;
//	jLiveDataTypeChange0 ( var, 0 );
}
void jLiveDataTypeChange0 ( struct jLiveData *var, int type ) {
	if ( var->type == type ) {
		return;
	}
	if ( var->type == 0 ) {
	} else if ( var->type == 1 ) {
	} else if ( var->type == 2 ) {
	} else if ( var->type == 3 ) {
	}
	if ( type == 0 ) {
		var->i = 0;
	} else if ( type == 1 ) {
		var->f = 0.0;
	} else if ( type == 2 ) {
		var->v = NULL;
	} else if ( type == 3 ) {
		var->complexRef = complexRefInit ( );
	}
	var->type = type;
}


void *jLiveDataInitMask ( ) {
	void *ret = jLiveDataInit ( );
	return ret;

}
void jLiveDataClose ( struct jLiveData *var ) {
	if ( var->type == 0 ) {
	} else if ( var->type == 1 ) {
	} else if ( var->type == 2 ) {
	} else if ( var->type == 3 ) {
		if ( var->complexRef ) {
			complexRefClose ( var->complexRef );
		}
	}
	free ( var );

}
int jLiveData_attrib_arr[] = {
	0,
};
void jLiveDataBodyToVal ( void *varPass, int nameI, char *body ) {

	struct jLiveData *var = varPass;

	if ( nameI == 0 ) {
		if ( var->type == 0 ) {
			var->i = atoi ( body );
		} else if ( var->type == 1 ) {
			var->f = atof ( body );
		} else if ( var->type == 2 ) {
			// wont get called?
		} else if ( var->type == 3 ) {
			// wont get called?
		}
	}
}

int jLiveDataNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

	struct jLiveData *var = data;
	if ( strcmp ( body, "i" ) == 0 ) {
		jLiveDataTypeChange0 ( var, 0 );
		return 0;
	} else if ( strcmp ( body, "f" ) == 0 ) {
		jLiveDataTypeChange0 ( var, 1 );
		return 0;
	} else if ( strcmp ( body, "v" ) == 0 ) {
		jLiveDataTypeChange0 ( var, 2 );
		return 0;
	} else if ( strcmp ( body, "complexRef" ) == 0 ) {
		jLiveDataTypeChange0 ( var, 3 );
		*strPtr = "complexRef";
		void **retPtr = ret;
		*retPtr = &var->complexRef;
		return jxnPtr;
	}
	return -1;
}

struct xmlFuncts jLiveDataXml = {
	.typeName = "jLiveData",
	.init = jLiveDataInitMask,
	.nameToIndex = jLiveDataNameToIndex,
	.bodyToVal = jLiveDataBodyToVal,
	.typeChange = (void (*) (void*, int))jLiveDataTypeChange0,
};

void jLiveData_print ( struct jLiveData *stru ) {
	printf ( "jLiveData_print ( )\n" );
}
/** complexRef */

struct complexRef *complexRefInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "complexRefInit ( )\n" );
	}
	struct complexRef *var = malloc ( sizeof ( struct complexRef ) );
	complexRefFill ( var );
	return var;
}
void complexRefFill ( struct complexRef *var ) {
	var->eleI = 0;
	var->complexPtr = complexEleInit ( );
}

void *complexRefInitMask ( ) {
	void *ret = complexRefInit ( );
	return ret;

}
void complexRefClose ( struct complexRef *var ) {
	free ( var );

}
int complexRef_attrib_arr[] = {
	0,
	0,
};
void complexRefBodyToVal ( void *varPass, int nameI, char *body ) {

	struct complexRef *var = varPass;

	if ( nameI == 0 ) {
		var->eleI = atoi ( body );
	} else if ( nameI == 1 ) {
		// wont get called?
	}
}

int complexRefNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

	struct complexRef *var = data;
	if ( strcmp ( body, "eleI" ) == 0 ) {
		return 0;
	} else if ( strcmp ( body, "complexPtr" ) == 0 ) {
		*strPtr = "complexEle";
		void **retPtr = ret;
		*retPtr = &var->complexPtr;
		return jxnPtr;
	}
	return -1;
}

struct xmlFuncts complexRefXml = {
	.typeName = "complexRef",
	.init = complexRefInitMask,
	.nameToIndex = complexRefNameToIndex,
	.bodyToVal = complexRefBodyToVal,
};

void complexRef_print ( struct complexRef *stru ) {
	printf ( "complexRef_print ( )\n" );
}
/** complexList */

struct complexList *complexListInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "complexListInit ( )\n" );
	}
	struct complexList *var = malloc ( sizeof ( struct complexList ) );
	complexListFill ( var );
	return var;
}
void complexListFill ( struct complexList *var ) {
	var->XYWH[0] = 0;
	var->XYWH[1] = 0;
	var->XYWH[2] = 0;
	var->XYWH[3] = 0;

	var->eleList = initArrayList ( 10, sizeof ( struct complexEle* ), 10 );
}

void *complexListInitMask ( ) {
	void *ret = complexListInit ( );
	return ret;

}
void complexListClose ( struct complexList *var ) {
	if ( var->eleList ) {
		freeArrayListPointerFunction ( var->eleList, (void (*)(void*))complexEleClose );
	}
	free ( var );

}
int complexList_attrib_arr[] = {
	0,
	0,
};
void complexListBodyToVal ( void *varPass, int nameI, char *body ) {

	struct complexList *var = varPass;

	if ( nameI == 0 ) {
		consumeStdArr ( body, 0, 1, var->XYWH, 4 );
	} else if ( nameI == 1 ) {
	}
}

int complexListNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

	struct complexList *var = data;
	if ( strcmp ( body, "XYWH" ) == 0 ) {
		return 0;
	} else if ( strcmp ( body, "eleList" ) == 0 ) {
		void **ptrPtr = (void**)ret;
		*ptrPtr = var->eleList;
		return jxnAlPtr;
	}
	return -1;
}

struct xmlFuncts complexListXml = {
	.typeName = "complexList",
	.init = complexListInitMask,
	.nameToIndex = complexListNameToIndex,
	.bodyToVal = complexListBodyToVal,
};

void complexList_print ( struct complexList *stru ) {
	printf ( "complexList_print ( )\n" );
}
/** Other Functs */
