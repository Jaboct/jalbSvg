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
extern int debugPrint_projectName_init;


extern struct draw2dStruct *draw2dApi;
extern struct draw3dStruct *draw3dApi;
extern struct jalbFont *fonts[];

//extern void (*addCanvas)(int id, void *data, int *xywh);
extern addCanvasF *addCanvas;

extern struct backbone_structStruct svg;

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
	var->eles = initArrayList ( 10, sizeof ( struct svg* ), 10 );
}

void *svgInitMask ( ) {
	void *ret = svgInit ( );
	return ret;

}
void svgClose ( struct svg *var ) {
	if ( var->eles ) {
		freeArrayListPointerFunction ( var->eles, (void (*)(void*))svgClose );
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
	} else if ( strcmp ( body, "eles" ) == 0 ) {
		void **ptrPtr = (void**)ret;
		*ptrPtr = var->eles;
		return jxnAlPtr;
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
/** Other Functs */
