#include "jPath.h"

/** AUTO GENERATED CODE */

extern char altKeys[];

extern float colorWhite[];
extern float colorGray[];
extern float colorDGray[];
extern float colorDGray1[];
extern float colorDGray2[];
extern float colorBlack[];
extern float colorGold[];




void jPath_preInit ( ) {
}


extern int jPathEditId;
extern int jVertEditId;
extern int jLineEditId;
extern int debugPrint_projectName_init;


/** Variables */

extern struct draw2dStruct *draw2dApi;
extern struct draw3dStruct *draw3dApi;
extern struct jalbFont *fonts[];

//extern void (*addCanvas)(int id, void *data, int *xywh);
extern addCanvasF *addCanvas;

extern struct backbone_structStruct backboneStru_jPath;
extern struct backbone_structStruct backboneStru_jVert;
extern struct backbone_structStruct backboneStru_jLine;

/** Functions */

/** jPath */

struct jPath *jPathInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "jPathInit ( )\n" );
	}
	struct jPath *var = malloc ( sizeof ( struct jPath ) );
	jPathFill ( var );
	return var;
}
void jPathFill ( struct jPath *var ) {
	var->verts = initArrayList ( 10, sizeof ( struct jVert* ), 10 );
	var->lines = initArrayList ( 10, sizeof ( struct jLine* ), 10 );
}

void *jPathInitMask ( ) {
	void *ret = jPathInit ( );
	return ret;

}
void jPathClose ( struct jPath *var ) {
	if ( var->verts ) {
		freeArrayListPointerFunction ( var->verts, (void (*)(void*))jVertClose );
	}
	if ( var->lines ) {
		freeArrayListPointerFunction ( var->lines, (void (*)(void*))jLineClose );
	}
	free ( var );

}
int jPath_attrib_arr[] = {
	0,
	0,
};
void jPathBodyToVal ( void *varPass, int nameI, char *body ) {

//	struct jPath *var = varPass;

	if ( nameI == 0 ) {
	} else if ( nameI == 1 ) {
	}
}

int jPathNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

	struct jPath *var = data;
	if ( strcmp ( body, "verts" ) == 0 ) {
		void **ptrPtr = (void**)ret;
		*ptrPtr = var->verts;
		return jxnAlPtr;
	} else if ( strcmp ( body, "lines" ) == 0 ) {
		void **ptrPtr = (void**)ret;
		*ptrPtr = var->lines;
		return jxnAlPtr;
	}
	return -1;
}

struct xmlFuncts jPathXml = {
	"jPath",
	jPathInitMask,
	jPathNameToIndex,
	jPathBodyToVal,
};

void jPath_print ( struct jPath *stru ) {
	printf ( "jPath_print ( )\n" );
}
/** jVert */

struct jVert *jVertInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "jVertInit ( )\n" );
	}
	struct jVert *var = malloc ( sizeof ( struct jVert ) );
	jVertFill ( var );
	return var;
}
void jVertFill ( struct jVert *var ) {
	var->XY[0] = 0.0;
	var->XY[1] = 0.0;

}

void *jVertInitMask ( ) {
	void *ret = jVertInit ( );
	return ret;

}
void jVertClose ( struct jVert *var ) {
	free ( var );

}
int jVert_attrib_arr[] = {
	0,
};
void jVertBodyToVal ( void *varPass, int nameI, char *body ) {

	struct jVert *var = varPass;

	if ( nameI == 0 ) {
		consumeStdArr ( body, 1, 1, var->XY, 2 );
	}
}

int jVertNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

	if ( strcmp ( body, "XY" ) == 0 ) {
		return 0;
	}
	return -1;
}

struct xmlFuncts jVertXml = {
	"jVert",
	jVertInitMask,
	jVertNameToIndex,
	jVertBodyToVal,
};

void jVert_print ( struct jVert *stru ) {
	printf ( "jVert_print ( )\n" );
}
/** jLine */

struct jLine *jLineInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "jLineInit ( )\n" );
	}
	struct jLine *var = malloc ( sizeof ( struct jLine ) );
	jLineFill ( var );
	return var;
}
void jLineFill ( struct jLine *var ) {
	var->type = 0;
	var->v0 = 0;
	var->v1 = 0;
	var->c0[0] = 0.0;
	var->c0[1] = 0.0;

	var->c1[0] = 0.0;
	var->c1[1] = 0.0;

	var->markerStart = 0;
	var->markerMid = 0;
	var->markerEnd = 0;
}

void *jLineInitMask ( ) {
	void *ret = jLineInit ( );
	return ret;

}
void jLineClose ( struct jLine *var ) {
	free ( var );

}
int jLine_attrib_arr[] = {
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
};
void jLineBodyToVal ( void *varPass, int nameI, char *body ) {

	struct jLine *var = varPass;

	if ( nameI == 0 ) {
		var->type = atoi ( body );
	} else if ( nameI == 1 ) {
		var->v0 = atoi ( body );
	} else if ( nameI == 2 ) {
		var->v1 = atoi ( body );
	} else if ( nameI == 3 ) {
		consumeStdArr ( body, 1, 1, var->c0, 2 );
	} else if ( nameI == 4 ) {
		consumeStdArr ( body, 1, 1, var->c1, 2 );
	} else if ( nameI == 5 ) {
		var->markerStart = atoi ( body );
	} else if ( nameI == 6 ) {
		var->markerMid = atoi ( body );
	} else if ( nameI == 7 ) {
		var->markerEnd = atoi ( body );
	}
}

int jLineNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

	if ( strcmp ( body, "type" ) == 0 ) {
		return 0;
	} else if ( strcmp ( body, "v0" ) == 0 ) {
		return 1;
	} else if ( strcmp ( body, "v1" ) == 0 ) {
		return 2;
	} else if ( strcmp ( body, "c0" ) == 0 ) {
		return 3;
	} else if ( strcmp ( body, "c1" ) == 0 ) {
		return 4;
	} else if ( strcmp ( body, "markerStart" ) == 0 ) {
		return 5;
	} else if ( strcmp ( body, "markerMid" ) == 0 ) {
		return 6;
	} else if ( strcmp ( body, "markerEnd" ) == 0 ) {
		return 7;
	}
	return -1;
}

struct xmlFuncts jLineXml = {
	"jLine",
	jLineInitMask,
	jLineNameToIndex,
	jLineBodyToVal,
};

void jLine_print ( struct jLine *stru ) {
	printf ( "jLine_print ( )\n" );
}
/** Other Functs */
