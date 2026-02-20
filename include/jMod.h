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





void jMod_preInit ( );




/** Structs */



/** Post Includes */


void *preInit ( ArrayList *keyList, ArrayList *modList );
void postInit ( ArrayList *modList, int thisMod );
void closing ( void *data );


/** Key */

//void keyWord ( char *line, void *data );

/** Getter + Setter */

void setDraw2dApi ( void *api );
void setDraw3dApi ( void *api );
void setFont16 ( void *data );
void setFont32 ( void *data );
void setAddCanvas ( void *f );
void setUiGenApi ( void *f );


/** Functions */

/** Other Functs */
