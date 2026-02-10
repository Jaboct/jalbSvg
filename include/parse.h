#pragma once


#include <jalb/jalbArrayList.h>

/** Forward Declaring */

struct moveTo;
struct lineTo;
struct cubicBez;
struct quadBez;
struct ellipArc;

struct pathUni;


/** Functions */





void pathUni_set_type ( struct pathUni *uni, int type );

void parseD ( char *d, ArrayList *eles );

int charToPathUni ( char c );
int charToPathUni2 ( char c, struct pathUni **uniPass );

int moveTo_dFill ( struct moveTo *moveTo, int i, float val );
int lineTo_dFill ( struct lineTo *lineTo, int i, float val );
int cubicBez_dFill ( struct cubicBez *cubicBez, int i, float val );
int quadBez_dFill ( struct quadBez *quadBez, int i, float val );
int ellipArc_dFill ( struct ellipArc *ellipArc, int i, float val );


void eleListToD ( ArrayList *eleList, char *d );


/** Style */

void generic_postInit ( void *var, char *str, void (*f)(void *var, char *name, char *value) );









