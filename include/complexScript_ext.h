#pragma once

#include <jalb/jalb_idPtr.h>
#include <jalbXml/jalbXml_02_read.h>
#include <jalbXml/jalbXml_02_write.h>

#include "api/structStruct.h"


/** Forward Declaring */

struct complexMod;


/** Structs */

struct jScriptEle {
	int type;
	union {
		struct subVar *varDec;
		struct jScriptOperator *op;
	};
};

enum jsOperator {
	jsOp_add = 0,
};

struct jScriptOperator {
	int type;
	struct jVarRef *object;
	struct jVarRef *actor;
	struct jLitRef *lit;
};

struct jVarRef {
	int index;
	struct jVarRef *subData;
};

struct jLitRef {
	int val;
};


/** Functions */

void hand_script ( );
void hand_script_2 ( );

struct jScriptEle *jScriptEleInit ( );
struct jScriptOperator *jScriptOperatorInit ( );
struct jVarRef *jVarRefInit ( );
struct jLitRef *jLitRefInit ( );

void run_script ( ArrayList *script );


/// Complex Mod

void hand_save_complexMod ( );
void save_complexMod ( char *dir, struct complexMod *mod );
void hand_load_complexMod ( );








