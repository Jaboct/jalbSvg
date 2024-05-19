#pragma once

/** AUTO GENERATED CODE */
/** Hand Trimmed */

#include <stdio.h>
#include <stdlib.h>

#include <jalb/jalbArrayList.h>
#include <jalb/jalbSay.h>

#include <jalb/jfile.h>
#include <jalb/jalb_addCanvas.h>
#include <jalbDraw/drawCutString.h>

#include <jalbXml/jalbXml_02.h>



#include <jalb/typeEnum.h>

//#include "stdTypeUnion.h"

void structStruct_preInit ( );




/** Structs */

struct subVar {
	char name[256];
	int type;
	int typeIndex;
	int initType;
	struct initTypeData *initTypeData;
	int closeType;
	int length;
	int literal;
	int union_type;
	union  {
		struct subAl *subAl;
		struct subComplex *subComplex;
		struct bakein *bakein;
		void *highStruct;
		int structNameOffset;
	};
	int external;
	int attribute;
	int saveFlag;
	int naked;
	char comment[256];
};
enum subVarEnum {
	SubAl = 0,
	SubComplex,
	Bakein,
	HighStruct,
	StructNameOffset,
};
struct subAl {
	int curEles;
	int eleSize;
	int overflow;
	int literal;
	int type;
	int typeIndex;
	int length;
	int naked;
};
struct initTypeData {
	int type;
	union  {
		struct stdTypeUnion *std;
	};
};
enum initTypeDataEnum {
	Std = 0,
};


/** Post Includes */


//#include "structStruct_ext.h"


