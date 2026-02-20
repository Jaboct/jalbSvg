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

#include <jalb/typeEnum.h>



void structStruct_preInit ( );




/** Structs */

struct structStruct {
	char name[256];
	ArrayList *vars;	// (struct subVar*)
	char overloadRenderEdit[1024];
	char overloadEventEdit[1024];
	int structDeclaration;
	int hide_edit;
	int isTypedef;
	int typedefType;
	int typedefTypeIndex;
	// Should this be a string so i can have w/e name i want?
	int postInit;
};
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




/** Functions */

/** structStruct */
struct structStruct *structStructInit ( );
void structStructFill ( struct structStruct *var );
void *structStructInitMask ( );
void structStructClose ( struct structStruct *var );
void structStructBodyToVal ( void *varPass, int nameI, char *body );
int structStructNameToIndex ( char *body, void *data, void *ret, char **strPtr );

/** subVar */
struct subVar *subVarInit ( );
void subVarFill ( struct subVar *var );
void subVarTypeChange0 ( struct subVar *var, int type );
void *subVarInitMask ( );
void subVarClose ( struct subVar *var );
void subVarBodyToVal ( void *varPass, int nameI, char *body );
int subVarNameToIndex ( char *body, void *data, void *ret, char **strPtr );

/** subAl */
struct subAl *subAlInit ( );
void subAlFill ( struct subAl *var );
void *subAlInitMask ( );
void subAlClose ( struct subAl *var );
void subAlBodyToVal ( void *varPass, int nameI, char *body );
int subAlNameToIndex ( char *body, void *data, void *ret, char **strPtr );

/** initTypeData */
struct initTypeData *initTypeDataInit ( );
void initTypeDataFill ( struct initTypeData *var );
void initTypeDataTypeChange0 ( struct initTypeData *var, int type );
void *initTypeDataInitMask ( );
void initTypeDataClose ( struct initTypeData *var );
void initTypeDataBodyToVal ( void *varPass, int nameI, char *body );
int initTypeDataNameToIndex ( char *body, void *data, void *ret, char **strPtr );

/** Other Functs */
