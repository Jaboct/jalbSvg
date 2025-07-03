#include "jText.h"

/** AUTO GENERATED CODE */

extern char altKeys[];

extern float colorWhite[];
extern float colorGray[];
extern float colorDGray[];
extern float colorDGray1[];
extern float colorDGray2[];
extern float colorBlack[];
extern float colorGold[];




void jText_preInit ( ) {
}


extern int jTextEditId;
extern int debugPrint_projectName_init;


/** Variables */

extern struct draw2dStruct *draw2dApi;
extern struct draw3dStruct *draw3dApi;
extern struct jalbFont *fonts[];

//extern void (*addCanvas)(int id, void *data, int *xywh);
extern addCanvasF *addCanvas;

extern struct backbone_structStruct backboneStru_jText;

/** Functions */

/** jText */

struct jText *jTextInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "jTextInit ( )\n" );
	}
	struct jText *var = malloc ( sizeof ( struct jText ) );
	jTextFill ( var );
	return var;
}
void jTextFill ( struct jText *var ) {
	var->XYWH[0] = 0.0;
	var->XYWH[1] = 0.0;
	var->XYWH[2] = 0.0;
	var->XYWH[3] = 0.0;

	var->sb = initArrayList ( 100, sizeof ( char ), 80 );
	var->fontSize = 0.0;
}

void *jTextInitMask ( ) {
	void *ret = jTextInit ( );
	return ret;

}
void jTextClose ( struct jText *var ) {
	if ( var->sb ) {
		freeArrayList ( var->sb );
	}
	free ( var );

}
int jText_attrib_arr[] = {
	0,
	0,
	0,
};
void jTextBodyToVal ( void *varPass, int nameI, char *body ) {

	struct jText *var = varPass;

	if ( nameI == 0 ) {
		consumeStdArr ( body, 1, 1, var->XYWH, 4 );
	} else if ( nameI == 1 ) {
		// is it literal?
		int literal = 1;
		consumeStdAl ( body, typeChar, literal, var->sb );
	} else if ( nameI == 2 ) {
		var->fontSize = atof ( body );
	}
}

int jTextNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

//	struct jText *var = data;
	if ( strcmp ( body, "XYWH" ) == 0 ) {
		return 0;
	} else if ( strcmp ( body, "sb" ) == 0 ) {
		return 1;
	} else if ( strcmp ( body, "fontSize" ) == 0 ) {
		return 2;
	}
	return -1;
}

struct xmlFuncts jTextXml = {
	"jText",
	jTextInitMask,
	jTextNameToIndex,
	jTextBodyToVal,
};

void jText_print ( struct jText *stru ) {
	printf ( "jText_print ( )\n" );
}
/** Other Functs */
