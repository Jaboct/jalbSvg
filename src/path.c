#include "path.h"

/** AUTO GENERATED CODE */

extern char altKeys[];

extern float colorWhite[];
extern float colorGray[];
extern float colorDGray[];
extern float colorDGray1[];
extern float colorDGray2[];
extern float colorBlack[];
extern float colorGold[];




void path_preInit ( ) {
}


extern int pathUniEditId;
extern int moveToEditId;
extern int lineToEditId;
extern int cubicBezEditId;
extern int quadBezEditId;
extern int ellipArcEditId;
extern int debugPrint_projectName_init;


extern struct draw2dStruct *draw2dApi;
extern struct draw3dStruct *draw3dApi;
extern struct jalbFont *fonts[];

//extern void (*addCanvas)(int id, void *data, int *xywh);
extern addCanvasF *addCanvas;

extern struct backbone_structStruct pathUni;
extern struct backbone_structStruct moveTo;
extern struct backbone_structStruct lineTo;
extern struct backbone_structStruct cubicBez;
extern struct backbone_structStruct quadBez;
extern struct backbone_structStruct ellipArc;

/** Functions */

/** pathUni */

struct pathUni *pathUniInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "pathUniInit ( )\n" );
	}
	struct pathUni *var = malloc ( sizeof ( struct pathUni ) );
	pathUniFill ( var );
	return var;
}
void pathUniFill ( struct pathUni *var ) {
	var->type = -1;
//	pathUniTypeChange0 ( var, 0 );
}
void pathUniTypeChange0 ( struct pathUni *var, int type ) {
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
		var->moveTo = moveToInit ( );
	} else if ( type == 1 ) {
		var->lineTo = lineToInit ( );
	} else if ( type == 2 ) {
		var->cubicBez = cubicBezInit ( );
	} else if ( type == 3 ) {
		var->quadBez = quadBezInit ( );
	} else if ( type == 4 ) {
		var->ellipArc = ellipArcInit ( );
	} else if ( type == 5 ) {
		var->PathEnd = 0;
	}
	var->type = type;
}


void *pathUniInitMask ( ) {
	void *ret = pathUniInit ( );
	return ret;

}
void pathUniClose ( struct pathUni *var ) {
	if ( var->type == 0 ) {
	} else if ( var->type == 1 ) {
	} else if ( var->type == 2 ) {
	} else if ( var->type == 3 ) {
	} else if ( var->type == 4 ) {
	} else if ( var->type == 5 ) {
	}
	free ( var );

}
int pathUni_attrib_arr[] = {
	0,
};
void pathUniBodyToVal ( void *varPass, int nameI, char *body ) {

	struct pathUni *var = varPass;

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
			var->PathEnd = atoi ( body );
		}
	}
}

int pathUniNameToIndex ( char *body, void *data, void *ret, char **strPtr ) {

	struct pathUni *var = data;
	if ( strcmp ( body, "moveTo" ) == 0 ) {
		pathUniTypeChange0 ( var, 0 );
		*strPtr = "moveTo";
		void **retPtr = ret;
		*retPtr = &var->moveTo;
		return jxnPtr;
	} else if ( strcmp ( body, "lineTo" ) == 0 ) {
		pathUniTypeChange0 ( var, 1 );
		*strPtr = "lineTo";
		void **retPtr = ret;
		*retPtr = &var->lineTo;
		return jxnPtr;
	} else if ( strcmp ( body, "cubicBez" ) == 0 ) {
		pathUniTypeChange0 ( var, 2 );
		*strPtr = "cubicBez";
		void **retPtr = ret;
		*retPtr = &var->cubicBez;
		return jxnPtr;
	} else if ( strcmp ( body, "quadBez" ) == 0 ) {
		pathUniTypeChange0 ( var, 3 );
		*strPtr = "quadBez";
		void **retPtr = ret;
		*retPtr = &var->quadBez;
		return jxnPtr;
	} else if ( strcmp ( body, "ellipArc" ) == 0 ) {
		pathUniTypeChange0 ( var, 4 );
		*strPtr = "ellipArc";
		void **retPtr = ret;
		*retPtr = &var->ellipArc;
		return jxnPtr;
	} else if ( strcmp ( body, "PathEnd" ) == 0 ) {
		pathUniTypeChange0 ( var, 5 );
		return 0;
	}
	return -1;
}

struct xmlFuncts pathUniXml = {
	"pathUni",
	pathUniInitMask,
	pathUniNameToIndex,
	pathUniBodyToVal,
	(void (*) (void*, int))pathUniTypeChange0,
};

void pathUni_print ( struct pathUni *stru ) {
	printf ( "pathUni_print ( )\n" );
}
/** moveTo */

struct moveTo *moveToInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "moveToInit ( )\n" );
	}
	struct moveTo *var = malloc ( sizeof ( struct moveTo ) );
	moveToFill ( var );
	return var;
}
void moveToFill ( struct moveTo *var ) {
	var->rel = 0;
	var->XY[0] = 0.0;
	var->XY[1] = 0.0;

}

void *moveToInitMask ( ) {
	void *ret = moveToInit ( );
	return ret;

}
void moveToClose ( struct moveTo *var ) {
	free ( var );

}
int moveTo_attrib_arr[] = {
	0,
	0,
};
void moveToBodyToVal ( void *varPass, int nameI, char *body ) {

	struct moveTo *var = varPass;

	if ( nameI == 0 ) {
		var->rel = atoi ( body );
	} else if ( nameI == 1 ) {
		consumeStdArr ( body, 1, 1, var->XY, 2 );
	}
}

int moveToNameToIndex ( char *body, void *data, void *ret, char **strPtr ) {

	if ( strcmp ( body, "rel" ) == 0 ) {
		return 0;
	} else if ( strcmp ( body, "XY" ) == 0 ) {
		return 1;
	}
	return -1;
}

struct xmlFuncts moveToXml = {
	"moveTo",
	moveToInitMask,
	moveToNameToIndex,
	moveToBodyToVal,
};

void moveTo_print ( struct moveTo *stru ) {
	printf ( "moveTo_print ( )\n" );
}
/** lineTo */

struct lineTo *lineToInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "lineToInit ( )\n" );
	}
	struct lineTo *var = malloc ( sizeof ( struct lineTo ) );
	lineToFill ( var );
	return var;
}
void lineToFill ( struct lineTo *var ) {
	var->rel = 0;
	var->XY[0] = 0.0;
	var->XY[1] = 0.0;

	var->type = 0;
}

void *lineToInitMask ( ) {
	void *ret = lineToInit ( );
	return ret;

}
void lineToClose ( struct lineTo *var ) {
	free ( var );

}
int lineTo_attrib_arr[] = {
	0,
	0,
	0,
};
void lineToBodyToVal ( void *varPass, int nameI, char *body ) {

	struct lineTo *var = varPass;

	if ( nameI == 0 ) {
		var->rel = atoi ( body );
	} else if ( nameI == 1 ) {
		consumeStdArr ( body, 1, 1, var->XY, 2 );
	} else if ( nameI == 2 ) {
		var->type = atoi ( body );
	}
}

int lineToNameToIndex ( char *body, void *data, void *ret, char **strPtr ) {

	if ( strcmp ( body, "rel" ) == 0 ) {
		return 0;
	} else if ( strcmp ( body, "XY" ) == 0 ) {
		return 1;
	} else if ( strcmp ( body, "type" ) == 0 ) {
		return 2;
	}
	return -1;
}

struct xmlFuncts lineToXml = {
	"lineTo",
	lineToInitMask,
	lineToNameToIndex,
	lineToBodyToVal,
};

void lineTo_print ( struct lineTo *stru ) {
	printf ( "lineTo_print ( )\n" );
}
/** cubicBez */

struct cubicBez *cubicBezInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "cubicBezInit ( )\n" );
	}
	struct cubicBez *var = malloc ( sizeof ( struct cubicBez ) );
	cubicBezFill ( var );
	return var;
}
void cubicBezFill ( struct cubicBez *var ) {
	var->rel = 0;
	var->XY[0] = 0.0;
	var->XY[1] = 0.0;

	var->c0[0] = 0.0;
	var->c0[1] = 0.0;

	var->c1[0] = 0.0;
	var->c1[1] = 0.0;

	var->type = 0;
}

void *cubicBezInitMask ( ) {
	void *ret = cubicBezInit ( );
	return ret;

}
void cubicBezClose ( struct cubicBez *var ) {
	free ( var );

}
int cubicBez_attrib_arr[] = {
	0,
	0,
	0,
	0,
	0,
};
void cubicBezBodyToVal ( void *varPass, int nameI, char *body ) {

	struct cubicBez *var = varPass;

	if ( nameI == 0 ) {
		var->rel = atoi ( body );
	} else if ( nameI == 1 ) {
		consumeStdArr ( body, 1, 1, var->XY, 2 );
	} else if ( nameI == 2 ) {
		consumeStdArr ( body, 1, 1, var->c0, 2 );
	} else if ( nameI == 3 ) {
		consumeStdArr ( body, 1, 1, var->c1, 2 );
	} else if ( nameI == 4 ) {
		var->type = atoi ( body );
	}
}

int cubicBezNameToIndex ( char *body, void *data, void *ret, char **strPtr ) {

	if ( strcmp ( body, "rel" ) == 0 ) {
		return 0;
	} else if ( strcmp ( body, "XY" ) == 0 ) {
		return 1;
	} else if ( strcmp ( body, "c0" ) == 0 ) {
		return 2;
	} else if ( strcmp ( body, "c1" ) == 0 ) {
		return 3;
	} else if ( strcmp ( body, "type" ) == 0 ) {
		return 4;
	}
	return -1;
}

struct xmlFuncts cubicBezXml = {
	"cubicBez",
	cubicBezInitMask,
	cubicBezNameToIndex,
	cubicBezBodyToVal,
};

void cubicBez_print ( struct cubicBez *stru ) {
	printf ( "cubicBez_print ( )\n" );
}
/** quadBez */

struct quadBez *quadBezInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "quadBezInit ( )\n" );
	}
	struct quadBez *var = malloc ( sizeof ( struct quadBez ) );
	quadBezFill ( var );
	return var;
}
void quadBezFill ( struct quadBez *var ) {
	var->rel = 0;
	var->XY[0] = 0.0;
	var->XY[1] = 0.0;

	var->control[0] = 0.0;
	var->control[1] = 0.0;

	var->type = 0;
}

void *quadBezInitMask ( ) {
	void *ret = quadBezInit ( );
	return ret;

}
void quadBezClose ( struct quadBez *var ) {
	free ( var );

}
int quadBez_attrib_arr[] = {
	0,
	0,
	0,
	0,
};
void quadBezBodyToVal ( void *varPass, int nameI, char *body ) {

	struct quadBez *var = varPass;

	if ( nameI == 0 ) {
		var->rel = atoi ( body );
	} else if ( nameI == 1 ) {
		consumeStdArr ( body, 1, 1, var->XY, 2 );
	} else if ( nameI == 2 ) {
		consumeStdArr ( body, 1, 1, var->control, 2 );
	} else if ( nameI == 3 ) {
		var->type = atoi ( body );
	}
}

int quadBezNameToIndex ( char *body, void *data, void *ret, char **strPtr ) {

	if ( strcmp ( body, "rel" ) == 0 ) {
		return 0;
	} else if ( strcmp ( body, "XY" ) == 0 ) {
		return 1;
	} else if ( strcmp ( body, "control" ) == 0 ) {
		return 2;
	} else if ( strcmp ( body, "type" ) == 0 ) {
		return 3;
	}
	return -1;
}

struct xmlFuncts quadBezXml = {
	"quadBez",
	quadBezInitMask,
	quadBezNameToIndex,
	quadBezBodyToVal,
};

void quadBez_print ( struct quadBez *stru ) {
	printf ( "quadBez_print ( )\n" );
}
/** ellipArc */

struct ellipArc *ellipArcInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "ellipArcInit ( )\n" );
	}
	struct ellipArc *var = malloc ( sizeof ( struct ellipArc ) );
	ellipArcFill ( var );
	return var;
}
void ellipArcFill ( struct ellipArc *var ) {
	var->rel = 0;
	var->XY[0] = 0.0;
	var->XY[1] = 0.0;

	var->rXY[0] = 0.0;
	var->rXY[1] = 0.0;

	var->angle = 0.0;
	var->largeArcFlag = 0;
	var->sweepFlag = 0;
}

void *ellipArcInitMask ( ) {
	void *ret = ellipArcInit ( );
	return ret;

}
void ellipArcClose ( struct ellipArc *var ) {
	free ( var );

}
int ellipArc_attrib_arr[] = {
	0,
	0,
	0,
	0,
	0,
	0,
};
void ellipArcBodyToVal ( void *varPass, int nameI, char *body ) {

	struct ellipArc *var = varPass;

	if ( nameI == 0 ) {
		var->rel = atoi ( body );
	} else if ( nameI == 1 ) {
		consumeStdArr ( body, 1, 1, var->XY, 2 );
	} else if ( nameI == 2 ) {
		consumeStdArr ( body, 1, 1, var->rXY, 2 );
	} else if ( nameI == 3 ) {
		var->angle = atof ( body );
	} else if ( nameI == 4 ) {
		var->largeArcFlag = atoi ( body );
	} else if ( nameI == 5 ) {
		var->sweepFlag = atoi ( body );
	}
}

int ellipArcNameToIndex ( char *body, void *data, void *ret, char **strPtr ) {

	if ( strcmp ( body, "rel" ) == 0 ) {
		return 0;
	} else if ( strcmp ( body, "XY" ) == 0 ) {
		return 1;
	} else if ( strcmp ( body, "rXY" ) == 0 ) {
		return 2;
	} else if ( strcmp ( body, "angle" ) == 0 ) {
		return 3;
	} else if ( strcmp ( body, "largeArcFlag" ) == 0 ) {
		return 4;
	} else if ( strcmp ( body, "sweepFlag" ) == 0 ) {
		return 5;
	}
	return -1;
}

struct xmlFuncts ellipArcXml = {
	"ellipArc",
	ellipArcInitMask,
	ellipArcNameToIndex,
	ellipArcBodyToVal,
};

void ellipArc_print ( struct ellipArc *stru ) {
	printf ( "ellipArc_print ( )\n" );
}
/** Other Functs */
