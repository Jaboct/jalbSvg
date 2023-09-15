#include "svg.h"

/** AUTO GENERATED CODE */

extern char altKeys[];

extern float colorWhite[];
extern float colorGray[];
extern float colorDGray[];
extern float colorDGray1[];
extern float colorDGray2[];
extern float colorBlack[];
extern float colorGold[];




void svg_preInit ( ) {
}


extern int svgEditId;
extern int nakedUnionEditId;
extern int gEditId;
extern int pathEditId;
extern int debugPrint_projectName_init;


extern struct draw2dStruct *draw2dApi;
extern struct draw3dStruct *draw3dApi;
extern struct jalbFont *fonts[];

//extern void (*addCanvas)(int id, void *data, int *xywh);
extern addCanvasF *addCanvas;

extern struct backbone_structStruct svg;
extern struct backbone_structStruct nakedUnion;
extern struct backbone_structStruct g;
extern struct backbone_structStruct path;

/** Functions */

/** svg */

struct svg *svgInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "svgInit ( )\n" );
	}
	struct svg *var = malloc ( sizeof ( struct svg ) );
	svgFill ( var );
	return var;
}
void svgFill ( struct svg *var ) {
	var->width[0] = '\0';
	var->height[0] = '\0';
	var->eles = initArrayList ( 10, sizeof ( struct nakedUnion* ), 10 );
}

void *svgInitMask ( ) {
	void *ret = svgInit ( );
	return ret;

}
void svgClose ( struct svg *var ) {
	if ( var->eles ) {
		freeArrayListPointerFunction ( var->eles, (void (*)(void*))nakedUnionClose );
	}
	free ( var );

}
int svg_attrib_arr[] = {
	0,
	0,
	0,
};
void svgBodyToVal ( void *varPass, int nameI, char *body ) {

	struct svg *var = varPass;

	if ( nameI == 0 ) {
		strcpy ( var->width, body );
	} else if ( nameI == 1 ) {
		strcpy ( var->height, body );
	} else if ( nameI == 2 ) {
	}
}

int svgNameToIndex ( char *body, void *data, void *ret, char **strPtr ) {

	struct svg *var = data;
	if ( strcmp ( body, "width" ) == 0 ) {
		return 0;
	} else if ( strcmp ( body, "height" ) == 0 ) {
		return 1;
	}
	return -1;
}

struct xmlFuncts svgXml = {
	"svg",
	svgInitMask,
	svgNameToIndex,
	svgBodyToVal,
};

void svg_print ( struct svg *stru ) {
	printf ( "svg_print ( )\n" );
}
/** nakedUnion */

struct nakedUnion *nakedUnionInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "nakedUnionInit ( )\n" );
	}
	struct nakedUnion *var = malloc ( sizeof ( struct nakedUnion ) );
	nakedUnionFill ( var );
	return var;
}
void nakedUnionFill ( struct nakedUnion *var ) {
	var->type = -1;
//	nakedUnionTypeChange0 ( var, 0 );
}
void nakedUnionTypeChange0 ( struct nakedUnion *var, int type ) {
	if ( var->type == type ) {
		return;
	}
	if ( var->type == 0 ) {
	} else if ( var->type == 1 ) {
	}
	if ( type == 0 ) {
		var->g = gInit ( );
	} else if ( type == 1 ) {
		var->path = pathInit ( );
	}
	var->type = type;
}


void *nakedUnionInitMask ( ) {
	void *ret = nakedUnionInit ( );
	return ret;

}
void nakedUnionClose ( struct nakedUnion *var ) {
	if ( var->type == 0 ) {
		if ( var->g ) {
			gClose ( var->g );
		}
	} else if ( var->type == 1 ) {
		if ( var->path ) {
			pathClose ( var->path );
		}
	}
	free ( var );

}
int nakedUnion_attrib_arr[] = {
	0,
};
void nakedUnionBodyToVal ( void *varPass, int nameI, char *body ) {

	struct nakedUnion *var = varPass;

	if ( nameI == 0 ) {
		if ( var->type == 0 ) {
			// wont get called?
		} else if ( var->type == 1 ) {
			// wont get called?
		}
	}
}

int nakedUnionNameToIndex ( char *body, void *data, void *ret, char **strPtr ) {

	struct nakedUnion *var = data;
	if ( strcmp ( body, "g" ) == 0 ) {
		nakedUnionTypeChange0 ( var, 0 );
		*strPtr = "g";
		void **retPtr = ret;
		*retPtr = &var->g;
		return jxnPtr;
	} else if ( strcmp ( body, "path" ) == 0 ) {
		nakedUnionTypeChange0 ( var, 1 );
		*strPtr = "path";
		void **retPtr = ret;
		*retPtr = &var->path;
		return jxnPtr;
	}
	return -1;
}

struct xmlFuncts nakedUnionXml = {
	"nakedUnion",
	nakedUnionInitMask,
	nakedUnionNameToIndex,
	nakedUnionBodyToVal,
	(void (*) (void*, int))nakedUnionTypeChange0,
};

void nakedUnion_print ( struct nakedUnion *stru ) {
	printf ( "nakedUnion_print ( )\n" );
}
/** g */

struct g *gInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "gInit ( )\n" );
	}
	struct g *var = malloc ( sizeof ( struct g ) );
	gFill ( var );
	return var;
}
void gFill ( struct g *var ) {
	var->id[0] = '\0';
	var->eles = initArrayList ( 10, sizeof ( struct nakedUnion* ), 0 );
}

void *gInitMask ( ) {
	void *ret = gInit ( );
	return ret;

}
void gClose ( struct g *var ) {
	if ( var->eles ) {
		freeArrayListPointerFunction ( var->eles, (void (*)(void*))nakedUnionClose );
	}
	free ( var );

}
int g_attrib_arr[] = {
	0,
	0,
};
void gBodyToVal ( void *varPass, int nameI, char *body ) {

	struct g *var = varPass;

	if ( nameI == 0 ) {
		strcpy ( var->id, body );
	} else if ( nameI == 1 ) {
	}
}

int gNameToIndex ( char *body, void *data, void *ret, char **strPtr ) {

	struct g *var = data;
	if ( strcmp ( body, "id" ) == 0 ) {
		return 0;
	} else if ( strcmp ( body, "eles" ) == 0 ) {
		void **ptrPtr = (void**)ret;
		*ptrPtr = var->eles;
		return jxnAlPtr;
	}
	return -1;
}

struct xmlFuncts gXml = {
	"g",
	gInitMask,
	gNameToIndex,
	gBodyToVal,
};

void g_print ( struct g *stru ) {
	printf ( "g_print ( )\n" );
}
/** path */

struct path *pathInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "pathInit ( )\n" );
	}
	struct path *var = malloc ( sizeof ( struct path ) );
	pathFill ( var );
	return var;
}
void pathFill ( struct path *var ) {
	var->style[0] = '\0';
	var->d[0] = '\0';
	var->id[0] = '\0';
	var->eles = initArrayList ( 0, sizeof ( out of range (type: -1) (typeIndex: -1)* ), 0 );
}

void *pathInitMask ( ) {
	void *ret = pathInit ( );
	return ret;

}
void pathClose ( struct path *var ) {
	free ( var );

}
int path_attrib_arr[] = {
	0,
	0,
	0,
	0,
};
void pathBodyToVal ( void *varPass, int nameI, char *body ) {

	struct path *var = varPass;

	if ( nameI == 0 ) {
		strcpy ( var->style, body );
	} else if ( nameI == 1 ) {
		strcpy ( var->d, body );
	} else if ( nameI == 2 ) {
		strcpy ( var->id, body );
	} else if ( nameI == 3 ) {
	}
}

int pathNameToIndex ( char *body, void *data, void *ret, char **strPtr ) {

	struct path *var = data;
	if ( strcmp ( body, "style" ) == 0 ) {
		return 0;
	} else if ( strcmp ( body, "d" ) == 0 ) {
		return 1;
	} else if ( strcmp ( body, "id" ) == 0 ) {
		return 2;
	} else if ( strcmp ( body, "eles" ) == 0 ) {
		void **ptrPtr = (void**)ret;
		*ptrPtr = var->eles;
		return jxnAlPtr;
	}
	return -1;
}

struct xmlFuncts pathXml = {
	"path",
	pathInitMask,
	pathNameToIndex,
	pathBodyToVal,
};

void path_print ( struct path *stru ) {
	printf ( "path_print ( )\n" );
}
/** Other Functs */
