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


/** Variables */

extern struct draw2dStruct *draw2dApi;
extern struct draw3dStruct *draw3dApi;
extern struct jalbFont *fonts[];

//extern void (*addCanvas)(int id, void *data, int *xywh);
extern addCanvasF *addCanvas;

extern struct backbone_structStruct backboneStru_svg;
extern struct backbone_structStruct backboneStru_nakedUnion;
extern struct backbone_structStruct backboneStru_g;
extern struct backbone_structStruct backboneStru_path;

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
	strcpy ( var->width, "210mm" );
	strcpy ( var->height, "297mm" );
	strcpy ( var->viewBox, "0 0 210 297" );
	strcpy ( var->version, "1.1" );
	var->id[0] = '\0';
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
	1,
	1,
	1,
	1,
	1,
	0,
};
void svgBodyToVal ( void *varPass, int nameI, char *body ) {

	struct svg *var = varPass;

	if ( nameI == 0 ) {
		strcpy ( var->width, body );
	} else if ( nameI == 1 ) {
		strcpy ( var->height, body );
	} else if ( nameI == 2 ) {
		strcpy ( var->viewBox, body );
	} else if ( nameI == 3 ) {
		strcpy ( var->version, body );
	} else if ( nameI == 4 ) {
		strcpy ( var->id, body );
	} else if ( nameI == 5 ) {
	}
}

int svgNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

	struct svg *var = data;
	if ( strcmp ( body, "width" ) == 0 ) {
		return 0;
	} else if ( strcmp ( body, "height" ) == 0 ) {
		return 1;
	} else if ( strcmp ( body, "viewBox" ) == 0 ) {
		return 2;
	} else if ( strcmp ( body, "version" ) == 0 ) {
		return 3;
	} else if ( strcmp ( body, "id" ) == 0 ) {
		return 4;
	} else {
		int r = nakedStru_nameToIndex ( body, var->eles, ret, strPtr );
		if ( r != -1 ) {
			return r;
		}
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
	} else if ( var->type == 2 ) {
	} else if ( var->type == 3 ) {
	} else if ( var->type == 4 ) {
	} else if ( var->type == 5 ) {
	}
	if ( type == 0 ) {
		var->g = gInit ( );
	} else if ( type == 1 ) {
		var->path = pathInit ( );
	} else if ( type == 2 ) {
		var->text = textInit ( );
	} else if ( type == 3 ) {
		var->rect = rectInit ( );
	} else if ( type == 4 ) {
		var->circle = circleInit ( );
	} else if ( type == 5 ) {
		var->ellipse = ellipseInit ( );
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
	} else if ( var->type == 2 ) {
		if ( var->text ) {
			textClose ( var->text );
		}
	} else if ( var->type == 3 ) {
		if ( var->rect ) {
			rectClose ( var->rect );
		}
	} else if ( var->type == 4 ) {
		if ( var->circle ) {
			circleClose ( var->circle );
		}
	} else if ( var->type == 5 ) {
		if ( var->ellipse ) {
			ellipseClose ( var->ellipse );
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
		} else if ( var->type == 2 ) {
			// wont get called?
		} else if ( var->type == 3 ) {
			// wont get called?
		} else if ( var->type == 4 ) {
			// wont get called?
		} else if ( var->type == 5 ) {
			// wont get called?
		}
	}
}

int nakedUnionNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

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
	} else if ( strcmp ( body, "text" ) == 0 ) {
		nakedUnionTypeChange0 ( var, 2 );
		*strPtr = "text";
		void **retPtr = ret;
		*retPtr = &var->text;
		return jxnPtr;
	} else if ( strcmp ( body, "rect" ) == 0 ) {
		nakedUnionTypeChange0 ( var, 3 );
		*strPtr = "rect";
		void **retPtr = ret;
		*retPtr = &var->rect;
		return jxnPtr;
	} else if ( strcmp ( body, "circle" ) == 0 ) {
		nakedUnionTypeChange0 ( var, 4 );
		*strPtr = "circle";
		void **retPtr = ret;
		*retPtr = &var->circle;
		return jxnPtr;
	} else if ( strcmp ( body, "ellipse" ) == 0 ) {
		nakedUnionTypeChange0 ( var, 5 );
		*strPtr = "ellipse";
		void **retPtr = ret;
		*retPtr = &var->ellipse;
		return jxnPtr;
	}
	return -1;
}

struct xmlFuncts nakedUnionXml = {
	"nakedUnion",
	nakedUnionInitMask,
	nakedUnionNameToIndex,
	nakedUnionBodyToVal,
	.typeChange = (void (*) (void*, int))nakedUnionTypeChange0,
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
	1,
	0,
};
void gBodyToVal ( void *varPass, int nameI, char *body ) {

	struct g *var = varPass;

	if ( nameI == 0 ) {
		strcpy ( var->id, body );
	} else if ( nameI == 1 ) {
	}
}

int gNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

	struct g *var = data;
	if ( strcmp ( body, "id" ) == 0 ) {
		return 0;
	} else {
		int r = nakedStru_nameToIndex ( body, var->eles, ret, strPtr );
		if ( r != -1 ) {
			return r;
		}
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
	var->eles = initArrayList ( 10, sizeof ( struct pathUni* ), 10 );
	strcpy ( var->fill, "none" );
	strcpy ( var->stroke, "#000000" );
	strcpy ( var->stroke_width, "1.0px" );
	strcpy ( var->stroke_linecap, "butt" );
	strcpy ( var->stroke_linejoin, "miter" );
	strcpy ( var->stroke_opacity, "1" );
}

void *pathInitMask ( ) {
	void *ret = pathInit ( );
	return ret;

}
void pathClose ( struct path *var ) {
	if ( var->eles ) {
		freeArrayListPointerFunction ( var->eles, (void (*)(void*))pathUniClose );
	}
	free ( var );

}
int path_attrib_arr[] = {
	1,
	1,
	1,
	0,
	0,
	0,
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
	} else if ( nameI == 4 ) {
		strcpy ( var->fill, body );
	} else if ( nameI == 5 ) {
		strcpy ( var->stroke, body );
	} else if ( nameI == 6 ) {
		strcpy ( var->stroke_width, body );
	} else if ( nameI == 7 ) {
		strcpy ( var->stroke_linecap, body );
	} else if ( nameI == 8 ) {
		strcpy ( var->stroke_linejoin, body );
	} else if ( nameI == 9 ) {
		strcpy ( var->stroke_opacity, body );
	}
}

int pathNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

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
	} else if ( strcmp ( body, "fill" ) == 0 ) {
		return 4;
	} else if ( strcmp ( body, "stroke" ) == 0 ) {
		return 5;
	} else if ( strcmp ( body, "stroke_width" ) == 0 ) {
		return 6;
	} else if ( strcmp ( body, "stroke_linecap" ) == 0 ) {
		return 7;
	} else if ( strcmp ( body, "stroke_linejoin" ) == 0 ) {
		return 8;
	} else if ( strcmp ( body, "stroke_opacity" ) == 0 ) {
		return 9;
	}
	return -1;
}

struct xmlFuncts pathXml = {
	"path",
	pathInitMask,
	pathNameToIndex,
	pathBodyToVal,
	.postInit = (void(*)(void*))pathPostInit,
};

void path_print ( struct path *stru ) {
	printf ( "path_print ( )\n" );
}
/** Other Functs */
