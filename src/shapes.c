#include "shapes.h"

/** AUTO GENERATED CODE */

extern char altKeys[];

extern float colorWhite[];
extern float colorGray[];
extern float colorDGray[];
extern float colorDGray1[];
extern float colorDGray2[];
extern float colorBlack[];
extern float colorGold[];




void shapes_preInit ( ) {
}


extern int rectEditId;
extern int circleEditId;
extern int ellipseEditId;
extern int debugPrint_projectName_init;


extern struct draw2dStruct *draw2dApi;
extern struct draw3dStruct *draw3dApi;
extern struct jalbFont *fonts[];

//extern void (*addCanvas)(int id, void *data, int *xywh);
extern addCanvasF *addCanvas;

extern struct backbone_structStruct rect;
extern struct backbone_structStruct circle;
extern struct backbone_structStruct ellipse;

/** Functions */

/** rect */

struct rect *rectInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "rectInit ( )\n" );
	}
	struct rect *var = malloc ( sizeof ( struct rect ) );
	rectFill ( var );
	return var;
}
void rectFill ( struct rect *var ) {
	var->style[0] = '\0';
	var->id[0] = '\0';
	var->x = 0.0;
	var->y = 0.0;
	var->width = 0.0;
	var->height = 0.0;
}

void *rectInitMask ( ) {
	void *ret = rectInit ( );
	return ret;

}
void rectClose ( struct rect *var ) {
	free ( var );

}
int rect_attrib_arr[] = {
	0,
	0,
	0,
	0,
	0,
	0,
};
void rectBodyToVal ( void *varPass, int nameI, char *body ) {

	struct rect *var = varPass;

	if ( nameI == 0 ) {
		strcpy ( var->style, body );
	} else if ( nameI == 1 ) {
		strcpy ( var->id, body );
	} else if ( nameI == 2 ) {
		var->x = atof ( body );
	} else if ( nameI == 3 ) {
		var->y = atof ( body );
	} else if ( nameI == 4 ) {
		var->width = atof ( body );
	} else if ( nameI == 5 ) {
		var->height = atof ( body );
	}
}

int rectNameToIndex ( char *body, void *data, void *ret, char **strPtr ) {

	if ( strcmp ( body, "style" ) == 0 ) {
		return 0;
	} else if ( strcmp ( body, "id" ) == 0 ) {
		return 1;
	} else if ( strcmp ( body, "x" ) == 0 ) {
		return 2;
	} else if ( strcmp ( body, "y" ) == 0 ) {
		return 3;
	} else if ( strcmp ( body, "width" ) == 0 ) {
		return 4;
	} else if ( strcmp ( body, "height" ) == 0 ) {
		return 5;
	}
	return -1;
}

struct xmlFuncts rectXml = {
	"rect",
	rectInitMask,
	rectNameToIndex,
	rectBodyToVal,
};

void rect_print ( struct rect *stru ) {
	printf ( "rect_print ( )\n" );
}
/** circle */

struct circle *circleInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "circleInit ( )\n" );
	}
	struct circle *var = malloc ( sizeof ( struct circle ) );
	circleFill ( var );
	return var;
}
void circleFill ( struct circle *var ) {
	var->style[0] = '\0';
	var->id[0] = '\0';
	var->cx = 0.0;
	var->cy = 0.0;
	var->r = 0.0;
}

void *circleInitMask ( ) {
	void *ret = circleInit ( );
	return ret;

}
void circleClose ( struct circle *var ) {
	free ( var );

}
int circle_attrib_arr[] = {
	0,
	0,
	0,
	0,
	0,
};
void circleBodyToVal ( void *varPass, int nameI, char *body ) {

	struct circle *var = varPass;

	if ( nameI == 0 ) {
		strcpy ( var->style, body );
	} else if ( nameI == 1 ) {
		strcpy ( var->id, body );
	} else if ( nameI == 2 ) {
		var->cx = atof ( body );
	} else if ( nameI == 3 ) {
		var->cy = atof ( body );
	} else if ( nameI == 4 ) {
		var->r = atof ( body );
	}
}

int circleNameToIndex ( char *body, void *data, void *ret, char **strPtr ) {

	if ( strcmp ( body, "style" ) == 0 ) {
		return 0;
	} else if ( strcmp ( body, "id" ) == 0 ) {
		return 1;
	} else if ( strcmp ( body, "cx" ) == 0 ) {
		return 2;
	} else if ( strcmp ( body, "cy" ) == 0 ) {
		return 3;
	} else if ( strcmp ( body, "r" ) == 0 ) {
		return 4;
	}
	return -1;
}

struct xmlFuncts circleXml = {
	"circle",
	circleInitMask,
	circleNameToIndex,
	circleBodyToVal,
};

void circle_print ( struct circle *stru ) {
	printf ( "circle_print ( )\n" );
}
/** ellipse */

struct ellipse *ellipseInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "ellipseInit ( )\n" );
	}
	struct ellipse *var = malloc ( sizeof ( struct ellipse ) );
	ellipseFill ( var );
	return var;
}
void ellipseFill ( struct ellipse *var ) {
	var->style[0] = '\0';
	var->id[0] = '\0';
	var->cx = 0.0;
	var->cy = 0.0;
	var->rx = 0.0;
	var->ry = 0.0;
}

void *ellipseInitMask ( ) {
	void *ret = ellipseInit ( );
	return ret;

}
void ellipseClose ( struct ellipse *var ) {
	free ( var );

}
int ellipse_attrib_arr[] = {
	0,
	0,
	0,
	0,
	0,
	0,
};
void ellipseBodyToVal ( void *varPass, int nameI, char *body ) {

	struct ellipse *var = varPass;

	if ( nameI == 0 ) {
		strcpy ( var->style, body );
	} else if ( nameI == 1 ) {
		strcpy ( var->id, body );
	} else if ( nameI == 2 ) {
		var->cx = atof ( body );
	} else if ( nameI == 3 ) {
		var->cy = atof ( body );
	} else if ( nameI == 4 ) {
		var->rx = atof ( body );
	} else if ( nameI == 5 ) {
		var->ry = atof ( body );
	}
}

int ellipseNameToIndex ( char *body, void *data, void *ret, char **strPtr ) {

	if ( strcmp ( body, "style" ) == 0 ) {
		return 0;
	} else if ( strcmp ( body, "id" ) == 0 ) {
		return 1;
	} else if ( strcmp ( body, "cx" ) == 0 ) {
		return 2;
	} else if ( strcmp ( body, "cy" ) == 0 ) {
		return 3;
	} else if ( strcmp ( body, "rx" ) == 0 ) {
		return 4;
	} else if ( strcmp ( body, "ry" ) == 0 ) {
		return 5;
	}
	return -1;
}

struct xmlFuncts ellipseXml = {
	"ellipse",
	ellipseInitMask,
	ellipseNameToIndex,
	ellipseBodyToVal,
};

void ellipse_print ( struct ellipse *stru ) {
	printf ( "ellipse_print ( )\n" );
}
/** Other Functs */
