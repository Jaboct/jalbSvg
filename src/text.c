#include "text.h"

/** AUTO GENERATED CODE */

extern char altKeys[];

extern float colorWhite[];
extern float colorGray[];
extern float colorDGray[];
extern float colorDGray1[];
extern float colorDGray2[];
extern float colorBlack[];
extern float colorGold[];




void text_preInit ( ) {
}


extern int textEditId;
extern int tspanEditId;
extern int debugPrint_projectName_init;


extern struct draw2dStruct *draw2dApi;
extern struct draw3dStruct *draw3dApi;
extern struct jalbFont *fonts[];

//extern void (*addCanvas)(int id, void *data, int *xywh);
extern addCanvasF *addCanvas;

extern struct backbone_structStruct text;
extern struct backbone_structStruct tspan;

/** Functions */

/** text */

struct text *textInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "textInit ( )\n" );
	}
	struct text *var = malloc ( sizeof ( struct text ) );
	textFill ( var );
	return var;
}
void textFill ( struct text *var ) {
	var->space[0] = '\0';
	var->style[0] = '\0';
	var->x = 0.0;
	var->y = 0.0;
	var->spanList = initArrayList ( 10, sizeof ( struct text* ), 10 );
}

void *textInitMask ( ) {
	void *ret = textInit ( );
	return ret;

}
void textClose ( struct text *var ) {
	if ( var->spanList ) {
		freeArrayListPointerFunction ( var->spanList, (void (*)(void*))textClose );
	}
	free ( var );

}
int text_attrib_arr[] = {
	0,
	0,
	0,
	0,
	0,
};
void textBodyToVal ( void *varPass, int nameI, char *body ) {

	struct text *var = varPass;

	if ( nameI == 0 ) {
		strcpy ( var->space, body );
	} else if ( nameI == 1 ) {
		strcpy ( var->style, body );
	} else if ( nameI == 2 ) {
		var->x = atof ( body );
	} else if ( nameI == 3 ) {
		var->y = atof ( body );
	} else if ( nameI == 4 ) {
	}
}

int textNameToIndex ( char *body, void *data, void *ret, char **strPtr ) {

	struct text *var = data;
	if ( strcmp ( body, "space" ) == 0 ) {
		return 0;
	} else if ( strcmp ( body, "style" ) == 0 ) {
		return 1;
	} else if ( strcmp ( body, "x" ) == 0 ) {
		return 2;
	} else if ( strcmp ( body, "y" ) == 0 ) {
		return 3;
	} else if ( strcmp ( body, "spanList" ) == 0 ) {
		void **ptrPtr = (void**)ret;
		*ptrPtr = var->spanList;
		return jxnAlPtr;
	} else if ( strcmp ( body, "tspan" ) == 0 ) {
		struct tspan *span = tspanInit ( );
		arrayListAddEndPointer ( var->spanList, span );

		printf ( "span: %p\n", span );
		printf ( "ret: %p\n", ret );

		*strPtr = "tspan";
		void **retPtr = ret;
//		*retPtr = &span;
		*retPtr = span;

		printf ( "&span: %p\n", &span );
		printf ( "retPtr: %p\n", retPtr );
		printf ( "*retPtr: %p\n", *retPtr );

//		return jxnPtr;
		return jxnPtrActual;
	}
	return -1;
}

struct xmlFuncts textXml = {
	"text",
	textInitMask,
	textNameToIndex,
	textBodyToVal,

	.postInit = (void (*)(void*)) text_postInit,
};

void text_print ( struct text *stru ) {
	printf ( "text_print ( )\n" );
}
/** tspan */

struct tspan *tspanInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "tspanInit ( )\n" );
	}
	struct tspan *var = malloc ( sizeof ( struct tspan ) );
	tspanFill ( var );
	return var;
}
void tspanFill ( struct tspan *var ) {
	var->role[0] = '\0';
	var->id[0] = '\0';
	var->style[0] = '\0';
	var->x = 0.0;
	var->y = 0.0;
	var->body[0] = '\0';
	var->stringBuilder = initArrayList ( 200, sizeof ( char ), 160 );
}

void *tspanInitMask ( ) {
	void *ret = tspanInit ( );
	return ret;

}
void tspanClose ( struct tspan *var ) {
	if ( var->stringBuilder ) {
		freeArrayList ( var->stringBuilder );
	}
	free ( var );

}
int tspan_attrib_arr[] = {
	0,
	0,
	0,
	0,
	0,
	0,
	0,
};
void tspanBodyToVal ( void *varPass, int nameI, char *body ) {

	struct tspan *var = varPass;

	if ( nameI == 0 ) {
		strcpy ( var->role, body );
	} else if ( nameI == 1 ) {
		strcpy ( var->id, body );
	} else if ( nameI == 2 ) {
		strcpy ( var->style, body );
	} else if ( nameI == 3 ) {
		var->x = atof ( body );
	} else if ( nameI == 4 ) {
		var->y = atof ( body );
	} else if ( nameI == 5 ) {
		strcpy ( var->body, body );
	} else if ( nameI == 6 ) {
		// 
	} else if ( nameI == -2 ) {
		// load this string into the body.

		printf ( "copy to body\n" );
		printf ( "(%s)\n", body );

		strcpy ( var->body, body );

		int i;
		int len;
		i = 0;
		len = strlen ( body );
		while ( i < len ) {
			char *c = arrayListGetNext ( var->stringBuilder );
			*c = body[i];
			i += 1;
		}
	}
}

int tspanNameToIndex ( char *body, void *data, void *ret, char **strPtr ) {

//	struct tspan *var = data;
	if ( strcmp ( body, "role" ) == 0 ) {
		return 0;
	} else if ( strcmp ( body, "id" ) == 0 ) {
		return 1;
	} else if ( strcmp ( body, "style" ) == 0 ) {
		return 2;
	} else if ( strcmp ( body, "x" ) == 0 ) {
		return 3;
	} else if ( strcmp ( body, "y" ) == 0 ) {
		return 4;
	} else if ( strcmp ( body, "body" ) == 0 ) {
		return 5;
	} else if ( strcmp ( body, "stringBuilder" ) == 0 ) {
		return 6;
	}
	return -1;
}

struct xmlFuncts tspanXml = {
	"tspan",
	tspanInitMask,
	tspanNameToIndex,
	tspanBodyToVal,

	.postInit = (void (*)(void*)) tspan_postInit,
};

void tspan_print ( struct tspan *stru ) {
	printf ( "tspan_print ( )\n" );
}
/** Other Functs */
