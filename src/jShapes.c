#include "jShapes.h"

/** AUTO GENERATED CODE */

extern char altKeys[];

extern float colorWhite[];
extern float colorGray[];
extern float colorDGray[];
extern float colorDGray1[];
extern float colorDGray2[];
extern float colorBlack[];
extern float colorGold[];




void jShapes_preInit ( ) {
}


extern int jRectEditId;
extern int jCircEditId;
extern int jEllipseEditId;
extern int debugPrint_projectName_init;


/** Variables */

extern struct draw2dStruct *draw2dApi;
extern struct draw3dStruct *draw3dApi;
extern struct jalbFont *fonts[];

//extern void (*addCanvas)(int id, void *data, int *xywh);
extern addCanvasF *addCanvas;

extern struct backbone_structStruct backboneStru_jRect;
extern struct backbone_structStruct backboneStru_jCirc;
extern struct backbone_structStruct backboneStru_jEllipse;

/** Functions */

/** jRect */

struct jRect *jRectInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "jRectInit ( )\n" );
	}
	struct jRect *var = malloc ( sizeof ( struct jRect ) );
	jRectFill ( var );
	return var;
}
void jRectFill ( struct jRect *var ) {
	var->XYWH[0] = 0.0;
	var->XYWH[1] = 0.0;
	var->XYWH[2] = 0.0;
	var->XYWH[3] = 0.0;

}

void *jRectInitMask ( ) {
	void *ret = jRectInit ( );
	return ret;

}
void jRectClose ( struct jRect *var ) {
	free ( var );

}
int jRect_attrib_arr[] = {
	0,
};
void jRectBodyToVal ( void *varPass, int nameI, char *body ) {

	struct jRect *var = varPass;

	if ( nameI == 0 ) {
		consumeStdArr ( body, 1, 1, var->XYWH, 4 );
	}
}

int jRectNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

	if ( strcmp ( body, "XYWH" ) == 0 ) {
		return 0;
	}
	return -1;
}

struct xmlFuncts jRectXml = {
	"jRect",
	jRectInitMask,
	jRectNameToIndex,
	jRectBodyToVal,
};

void jRect_print ( struct jRect *stru ) {
	printf ( "jRect_print ( )\n" );
}
/** jCirc */

struct jCirc *jCircInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "jCircInit ( )\n" );
	}
	struct jCirc *var = malloc ( sizeof ( struct jCirc ) );
	jCircFill ( var );
	return var;
}
void jCircFill ( struct jCirc *var ) {
	var->XY[0] = 0.0;
	var->XY[1] = 0.0;

	var->radius = 0.0;
}

void *jCircInitMask ( ) {
	void *ret = jCircInit ( );
	return ret;

}
void jCircClose ( struct jCirc *var ) {
	free ( var );

}
int jCirc_attrib_arr[] = {
	0,
	0,
};
void jCircBodyToVal ( void *varPass, int nameI, char *body ) {

	struct jCirc *var = varPass;

	if ( nameI == 0 ) {
		consumeStdArr ( body, 1, 1, var->XY, 2 );
	} else if ( nameI == 1 ) {
		var->radius = atof ( body );
	}
}

int jCircNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

	if ( strcmp ( body, "XY" ) == 0 ) {
		return 0;
	} else if ( strcmp ( body, "radius" ) == 0 ) {
		return 1;
	}
	return -1;
}

struct xmlFuncts jCircXml = {
	"jCirc",
	jCircInitMask,
	jCircNameToIndex,
	jCircBodyToVal,
};

void jCirc_print ( struct jCirc *stru ) {
	printf ( "jCirc_print ( )\n" );
}
/** jEllipse */

struct jEllipse *jEllipseInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "jEllipseInit ( )\n" );
	}
	struct jEllipse *var = malloc ( sizeof ( struct jEllipse ) );
	jEllipseFill ( var );
	return var;
}
void jEllipseFill ( struct jEllipse *var ) {
	var->XY[0] = 0.0;
	var->XY[1] = 0.0;

	var->cx = 0.0;
	var->cy = 0.0;
	var->rx = 0.0;
	var->ry = 0.0;
}

void *jEllipseInitMask ( ) {
	void *ret = jEllipseInit ( );
	return ret;

}
void jEllipseClose ( struct jEllipse *var ) {
	free ( var );

}
int jEllipse_attrib_arr[] = {
	0,
	0,
	0,
	0,
	0,
};
void jEllipseBodyToVal ( void *varPass, int nameI, char *body ) {

	struct jEllipse *var = varPass;

	if ( nameI == 0 ) {
		consumeStdArr ( body, 1, 1, var->XY, 2 );
	} else if ( nameI == 1 ) {
		var->cx = atof ( body );
	} else if ( nameI == 2 ) {
		var->cy = atof ( body );
	} else if ( nameI == 3 ) {
		var->rx = atof ( body );
	} else if ( nameI == 4 ) {
		var->ry = atof ( body );
	}
}

int jEllipseNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

	if ( strcmp ( body, "XY" ) == 0 ) {
		return 0;
	} else if ( strcmp ( body, "cx" ) == 0 ) {
		return 1;
	} else if ( strcmp ( body, "cy" ) == 0 ) {
		return 2;
	} else if ( strcmp ( body, "rx" ) == 0 ) {
		return 3;
	} else if ( strcmp ( body, "ry" ) == 0 ) {
		return 4;
	}
	return -1;
}

struct xmlFuncts jEllipseXml = {
	"jEllipse",
	jEllipseInitMask,
	jEllipseNameToIndex,
	jEllipseBodyToVal,
};

void jEllipse_print ( struct jEllipse *stru ) {
	printf ( "jEllipse_print ( )\n" );
}
/** Other Functs */
