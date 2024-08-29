#include "jGroup.h"

/** AUTO GENERATED CODE */

extern char altKeys[];

extern float colorWhite[];
extern float colorGray[];
extern float colorDGray[];
extern float colorDGray1[];
extern float colorDGray2[];
extern float colorBlack[];
extern float colorGold[];




void jGroup_preInit ( ) {
}


extern int jGroupEditId;
extern int jNakedUnionEditId;
extern int jvgEditId;
extern int debugPrint_projectName_init;


extern struct draw2dStruct *draw2dApi;
extern struct draw3dStruct *draw3dApi;
extern struct jalbFont *fonts[];

//extern void (*addCanvas)(int id, void *data, int *xywh);
extern addCanvasF *addCanvas;

extern struct backbone_structStruct jGroup;
extern struct backbone_structStruct jNakedUnion;
extern struct backbone_structStruct jvg;

/** Functions */

/** jGroup */

struct jGroup *jGroupInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "jGroupInit ( )\n" );
	}
	struct jGroup *var = malloc ( sizeof ( struct jGroup ) );
	jGroupFill ( var );
	return var;
}
void jGroupFill ( struct jGroup *var ) {
	var->eles = initArrayList ( 10, sizeof ( struct jNakedUnion* ), 10 );
}

void *jGroupInitMask ( ) {
	void *ret = jGroupInit ( );
	return ret;

}
void jGroupClose ( struct jGroup *var ) {
	if ( var->eles ) {
		freeArrayListPointerFunction ( var->eles, (void (*)(void*))jNakedUnionClose );
	}
	free ( var );

}
int jGroup_attrib_arr[] = {
	0,
};
void jGroupBodyToVal ( void *varPass, int nameI, char *body ) {

//	struct jGroup *var = varPass;

	if ( nameI == 0 ) {
	}
}

int jGroupNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

	struct jGroup *var = data;
	if ( strcmp ( body, "eles" ) == 0 ) {
		void **ptrPtr = (void**)ret;
		*ptrPtr = var->eles;
		return jxnAlPtr;
	}
	return -1;
}

struct xmlFuncts jGroupXml = {
	"jGroup",
	jGroupInitMask,
	jGroupNameToIndex,
	jGroupBodyToVal,
};

void jGroup_print ( struct jGroup *stru ) {
	printf ( "jGroup_print ( )\n" );
}
/** jNakedUnion */

struct jNakedUnion *jNakedUnionInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "jNakedUnionInit ( )\n" );
	}
	struct jNakedUnion *var = malloc ( sizeof ( struct jNakedUnion ) );
	jNakedUnionFill ( var );
	return var;
}
void jNakedUnionFill ( struct jNakedUnion *var ) {
	var->type = -1;
//	jNakedUnionTypeChange0 ( var, 0 );
}
void jNakedUnionTypeChange0 ( struct jNakedUnion *var, int type ) {
	if ( var->type == type ) {
		return;
	}
	if ( var->type == 0 ) {
	} else if ( var->type == 1 ) {
	} else if ( var->type == 2 ) {
	} else if ( var->type == 3 ) {
	} else if ( var->type == 4 ) {
	} else if ( var->type == 5 ) {
	} else if ( var->type == 6 ) {
	}
	if ( type == 0 ) {
		var->g = jGroupInit ( );
	} else if ( type == 1 ) {
		var->path = jPathInit ( );
	} else if ( type == 2 ) {
		var->text = jTextInit ( );
	} else if ( type == 3 ) {
		var->rect = jRectInit ( );
	} else if ( type == 4 ) {
		var->circ = jCircInit ( );
	} else if ( type == 5 ) {
		var->ellipse = jEllipseInit ( );
	} else if ( type == 6 ) {
		var->complex = complexEleInit ( );
	}
	var->type = type;
}


void *jNakedUnionInitMask ( ) {
	void *ret = jNakedUnionInit ( );
	return ret;

}
void jNakedUnionClose ( struct jNakedUnion *var ) {
	if ( var->type == 0 ) {
		if ( var->g ) {
			jGroupClose ( var->g );
		}
	} else if ( var->type == 1 ) {
		if ( var->path ) {
			jPathClose ( var->path );
		}
	} else if ( var->type == 2 ) {
		if ( var->text ) {
			jTextClose ( var->text );
		}
	} else if ( var->type == 3 ) {
		if ( var->rect ) {
			jRectClose ( var->rect );
		}
	} else if ( var->type == 4 ) {
		if ( var->circ ) {
			jCircClose ( var->circ );
		}
	} else if ( var->type == 5 ) {
		if ( var->ellipse ) {
			jEllipseClose ( var->ellipse );
		}
	} else if ( var->type == 6 ) {
		if ( var->complex ) {
			complexEleClose ( var->complex );
		}
	}
	free ( var );

}
int jNakedUnion_attrib_arr[] = {
	0,
};
void jNakedUnionBodyToVal ( void *varPass, int nameI, char *body ) {

	struct jNakedUnion *var = varPass;

	if ( nameI == 0 ) {
		if ( var->type == 0 ) {
			// wont get called?
		} else if ( var->type == 1 ) {
			// wont get called?
		} else if ( var->type == 2 ) {
			// wont get called?
		} else if ( var->type == 3 ) {
			// wont get called?
		} else if ( var->type == 4 ) {
			// wont get called?
		} else if ( var->type == 5 ) {
			// wont get called?
		} else if ( var->type == 6 ) {
			// wont get called?
		}
	}
}

int jNakedUnionNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

	struct jNakedUnion *var = data;
	if ( strcmp ( body, "g" ) == 0 ) {
		jNakedUnionTypeChange0 ( var, 0 );
		*strPtr = "jGroup";
		void **retPtr = ret;
		*retPtr = &var->g;
		return jxnPtr;
	} else if ( strcmp ( body, "path" ) == 0 ) {
		jNakedUnionTypeChange0 ( var, 1 );
		*strPtr = "jPath";
		void **retPtr = ret;
		*retPtr = &var->path;
		return jxnPtr;
	} else if ( strcmp ( body, "text" ) == 0 ) {
		jNakedUnionTypeChange0 ( var, 2 );
		*strPtr = "jText";
		void **retPtr = ret;
		*retPtr = &var->text;
		return jxnPtr;
	} else if ( strcmp ( body, "rect" ) == 0 ) {
		jNakedUnionTypeChange0 ( var, 3 );
		*strPtr = "jRect";
		void **retPtr = ret;
		*retPtr = &var->rect;
		return jxnPtr;
	} else if ( strcmp ( body, "circ" ) == 0 ) {
		jNakedUnionTypeChange0 ( var, 4 );
		*strPtr = "jCirc";
		void **retPtr = ret;
		*retPtr = &var->circ;
		return jxnPtr;
	} else if ( strcmp ( body, "ellipse" ) == 0 ) {
		jNakedUnionTypeChange0 ( var, 5 );
		*strPtr = "jEllipse";
		void **retPtr = ret;
		*retPtr = &var->ellipse;
		return jxnPtr;
	} else if ( strcmp ( body, "complex" ) == 0 ) {
		jNakedUnionTypeChange0 ( var, 6 );
		*strPtr = "complexEle";
		void **retPtr = ret;
		*retPtr = &var->complex;
		return jxnPtr;
	}
	return -1;
}

struct xmlFuncts jNakedUnionXml = {
	"jNakedUnion",
	jNakedUnionInitMask,
	jNakedUnionNameToIndex,
	jNakedUnionBodyToVal,
	.typeChange = (void (*) (void*, int))jNakedUnionTypeChange0,
};

void jNakedUnion_print ( struct jNakedUnion *stru ) {
	printf ( "jNakedUnion_print ( )\n" );
}
/** jvg */

struct jvg *jvgInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "jvgInit ( )\n" );
	}
	struct jvg *var = malloc ( sizeof ( struct jvg ) );
	jvgFill ( var );
	return var;
}
void jvgFill ( struct jvg *var ) {
	var->eles = initArrayList ( 10, sizeof ( struct jNakedUnion* ), 10 );
	var->moduleList = initArrayList ( 10, sizeof ( struct complexMod* ), 10 );
	var->moduleDataList = initArrayList ( 10, sizeof ( struct complexModData* ), 10 );
}

void *jvgInitMask ( ) {
	void *ret = jvgInit ( );
	return ret;

}
void jvgClose ( struct jvg *var ) {
	if ( var->eles ) {
		freeArrayListPointerFunction ( var->eles, (void (*)(void*))jNakedUnionClose );
	}
	if ( var->moduleList ) {
		freeArrayListPointerFunction ( var->moduleList, (void (*)(void*))complexModClose );
	}
	if ( var->moduleDataList ) {
		freeArrayListPointerFunction ( var->moduleDataList, (void (*)(void*))complexModDataClose );
	}
	free ( var );

}
int jvg_attrib_arr[] = {
	0,
	0,
	0,
};
void jvgBodyToVal ( void *varPass, int nameI, char *body ) {

//	struct jvg *var = varPass;

	if ( nameI == 0 ) {
	} else if ( nameI == 1 ) {
	} else if ( nameI == 2 ) {
	}
}

int jvgNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

	struct jvg *var = data;
	if ( strcmp ( body, "eles" ) == 0 ) {
		void **ptrPtr = (void**)ret;
		*ptrPtr = var->eles;
		return jxnAlPtr;
	} else if ( strcmp ( body, "moduleList" ) == 0 ) {
		void **ptrPtr = (void**)ret;
		*ptrPtr = var->moduleList;
		return jxnAlPtr;
	} else if ( strcmp ( body, "moduleDataList" ) == 0 ) {
		void **ptrPtr = (void**)ret;
		*ptrPtr = var->moduleDataList;
		return jxnAlPtr;
	}
	return -1;
}

struct xmlFuncts jvgXml = {
	"jvg",
	jvgInitMask,
	jvgNameToIndex,
	jvgBodyToVal,
	.postInit = jvgPostInit,
};

void jvg_print ( struct jvg *stru ) {
	printf ( "jvg_print ( )\n" );
}
/** Other Functs */
