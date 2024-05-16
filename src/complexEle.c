#include "complexEle.h"

/** AUTO GENERATED CODE */

extern char altKeys[];

extern float colorWhite[];
extern float colorGray[];
extern float colorDGray[];
extern float colorDGray1[];
extern float colorDGray2[];
extern float colorBlack[];
extern float colorGold[];




void complexEle_preInit ( ) {
}


extern int complexEleEditId;
extern int debugPrint_projectName_init;


extern struct draw2dStruct *draw2dApi;
extern struct draw3dStruct *draw3dApi;
extern struct jalbFont *fonts[];

//extern void (*addCanvas)(int id, void *data, int *xywh);
extern addCanvasF *addCanvas;

extern struct backbone_structStruct complexEle;

/** Functions */

/** complexEle */

struct complexEle *complexEleInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "complexEleInit ( )\n" );
	}
	struct complexEle *var = malloc ( sizeof ( struct complexEle ) );
	complexEleFill ( var );
	return var;
}
void complexEleFill ( struct complexEle *var ) {
}

void *complexEleInitMask ( ) {
	void *ret = complexEleInit ( );
	return ret;

}
void complexEleClose ( struct complexEle *var ) {
	free ( var );

}
int complexEle_attrib_arr[] = {
};
void complexEleBodyToVal ( void *varPass, int nameI, char *body ) {


}

int complexEleNameToIndex ( char *body, void *data, void *ret, char **strPtr ) {

	return -1;
}

struct xmlFuncts complexEleXml = {
	"complexEle",
	complexEleInitMask,
	complexEleNameToIndex,
	complexEleBodyToVal,
};

void complexEle_print ( struct complexEle *stru ) {
	printf ( "complexEle_print ( )\n" );
}
/** Other Functs */
