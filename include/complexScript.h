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



void complexScript_preInit ( );




/** Structs */

struct complexScript {
	char name[256];
	ArrayList *eleList;	// (struct cScriptEle*)
};
struct cScriptEle {
	int type;
	union  {
		struct subVar *varDec;
//		out of range (type: 0) (typeIndex: -1) *operator;
		void *operator;
	};
};
enum cScriptEleEnum {
	VarDec = 0,
	Operator,
};


/** Post Includes */


/** Functions */

/** complexScript */
struct complexScript *complexScriptInit ( );
void complexScriptFill ( struct complexScript *var );
void *complexScriptInitMask ( );
void complexScriptClose ( struct complexScript *var );
void complexScriptBodyToVal ( void *varPass, int nameI, char *body );
int complexScriptNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName );

/** cScriptEle */
struct cScriptEle *cScriptEleInit ( );
void cScriptEleFill ( struct cScriptEle *var );
void cScriptEleTypeChange0 ( struct cScriptEle *var, int type );
void *cScriptEleInitMask ( );
void cScriptEleClose ( struct cScriptEle *var );
void cScriptEleBodyToVal ( void *varPass, int nameI, char *body );
int cScriptEleNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName );

/** Other Functs */
