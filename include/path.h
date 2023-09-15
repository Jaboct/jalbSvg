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



void path_preInit ( );


/** Structs */

struct pathUni {
	int type;
	union  {
		struct moveTo *moveTo;
		struct lineTo *lineTo;
		struct cubicBez *cubicBez;
		struct quadBez *quadBez;
		struct ellipArc *ellipArc;
		int PathEnd;
	};
};
enum pathUniEnum {
	MoveTo = 0,
	LineTo,
	CubicBez,
	QuadBez,
	EllipArc,
	PathEnd,	// 5
};
struct moveTo {
	int rel;
	float XY[2];
};
struct lineTo {
	int rel;
	float XY[2];
	int type;
};
struct cubicBez {
	int rel;
	float XY[2];
	float c0[2];
	float c1[2];
	int type;
};
struct quadBez {
	int rel;
	float XY[2];
	float control[2];
	int type;
};
struct ellipArc {
	int rel;
	float XY[2];
	float rXY[2];
	float angle;
	int largeArcFlag;
	int sweepFlag;
};


/** Post Includes */


/** Functions */

/** pathUni */
struct pathUni *pathUniInit ( );
void pathUniFill ( struct pathUni *var );
void pathUniTypeChange0 ( struct pathUni *var, int type );
void *pathUniInitMask ( );
void pathUniClose ( struct pathUni *var );
void pathUniBodyToVal ( void *varPass, int nameI, char *body );
int pathUniNameToIndex ( char *body, void *data, void *ret, char **strPtr );

/** moveTo */
struct moveTo *moveToInit ( );
void moveToFill ( struct moveTo *var );
void *moveToInitMask ( );
void moveToClose ( struct moveTo *var );
void moveToBodyToVal ( void *varPass, int nameI, char *body );
int moveToNameToIndex ( char *body, void *data, void *ret, char **strPtr );

/** lineTo */
struct lineTo *lineToInit ( );
void lineToFill ( struct lineTo *var );
void *lineToInitMask ( );
void lineToClose ( struct lineTo *var );
void lineToBodyToVal ( void *varPass, int nameI, char *body );
int lineToNameToIndex ( char *body, void *data, void *ret, char **strPtr );

/** cubicBez */
struct cubicBez *cubicBezInit ( );
void cubicBezFill ( struct cubicBez *var );
void *cubicBezInitMask ( );
void cubicBezClose ( struct cubicBez *var );
void cubicBezBodyToVal ( void *varPass, int nameI, char *body );
int cubicBezNameToIndex ( char *body, void *data, void *ret, char **strPtr );

/** quadBez */
struct quadBez *quadBezInit ( );
void quadBezFill ( struct quadBez *var );
void *quadBezInitMask ( );
void quadBezClose ( struct quadBez *var );
void quadBezBodyToVal ( void *varPass, int nameI, char *body );
int quadBezNameToIndex ( char *body, void *data, void *ret, char **strPtr );

/** ellipArc */
struct ellipArc *ellipArcInit ( );
void ellipArcFill ( struct ellipArc *var );
void *ellipArcInitMask ( );
void ellipArcClose ( struct ellipArc *var );
void ellipArcBodyToVal ( void *varPass, int nameI, char *body );
int ellipArcNameToIndex ( char *body, void *data, void *ret, char **strPtr );

/** Other Functs */
