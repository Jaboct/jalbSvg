#pragma once

/** AUTO GENERATED CODE */

#include <stdio.h>
#include <stdlib.h>

#include <jalb/jalbArrayList.h>
#include <jalb/jalbSay.h>

#include <jalb/jfile.h>
#include <jalb/jalb_addCanvas.h>
#include <jalbDraw/drawCutString.h>

#include <jalbXml/jalbXml_02.h>



void complexEle_preInit ( );




/** Structs */

struct complexDec {
	char name[256];
	ArrayList *subVars;	// (struct subVar*)
	char modName[256];
	char renderFunct_name[256];
	void *renderFunct;
	ArrayList *renderParams;	// (int)
	char eventFunct_name[256];
	void *eventFunct;
	ArrayList *eventParams;	// (int)
};
struct complexEle {
	float XYWH[4];
	int decModI;
	int decType;
	ArrayList *liveSubVars;	// (struct jLiveData*)
};
struct jLiveData {
	int type;
	union  {
		int i;
		float f;
		struct complexRef *complexRef;
	};
};
enum jLiveDataEnum {
	jld_I = 0,
	jld_F,
	jld_ComplexRef,
};
struct complexRef {
	int eleI;
	struct complexEle *complexPtr;
};


/** Post Includes */

#include "complexEle_ext.h"


/** Functions */

/** complexDec */
struct complexDec *complexDecInit ( );
void complexDecFill ( struct complexDec *var );
void *complexDecInitMask ( );
void complexDecClose ( struct complexDec *var );
void complexDecBodyToVal ( void *varPass, int nameI, char *body );
int complexDecNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName );

/** complexEle */
struct complexEle *complexEleInit ( );
void complexEleFill ( struct complexEle *var );
void *complexEleInitMask ( );
void complexEleClose ( struct complexEle *var );
void complexEleBodyToVal ( void *varPass, int nameI, char *body );
int complexEleNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName );

/** jLiveData */
struct jLiveData *jLiveDataInit ( );
void jLiveDataFill ( struct jLiveData *var );
void jLiveDataTypeChange0 ( struct jLiveData *var, int type );
void *jLiveDataInitMask ( );
void jLiveDataClose ( struct jLiveData *var );
void jLiveDataBodyToVal ( void *varPass, int nameI, char *body );
int jLiveDataNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName );

/** complexRef */
struct complexRef *complexRefInit ( );
void complexRefFill ( struct complexRef *var );
void *complexRefInitMask ( );
void complexRefClose ( struct complexRef *var );
void complexRefBodyToVal ( void *varPass, int nameI, char *body );
int complexRefNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName );

/** Other Functs */
