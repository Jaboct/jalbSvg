#include "complexEle_ext.h"


/** Includes */

// this should be in the header?
#include "api/structStruct.h"

#include "jEvent.h"
#include "jGroup.h"

#include "jText.h"

#include "cursorIcon.h"
#include "recursiveCursor.h"

#include "canvas_util.h"

#include "complexMod.h"
#include "complexEle.h"
#include "complexScript_ext.h"


/** Variables */

extern struct jvg *glob_jvg;

struct jalbLayMod *(*modCore_modGetter) ( char *modNick ) = NULL;


extern struct jalbFont *fonts[];
extern int numFonts;

extern int debugPrint_jvg_complex_render;

extern int cursorSet_override;


/** Functions */

void hand_complex_00 ( ) {
	printf ( "hand_complex_00 ( )\n" );

	// creates "example_int" complex dec.
	struct complexDec *dec = complexDecInit ( );

	struct subVar *var = subVarInit ( );
	arrayListAddEndPointer ( dec->subVars, var );
}

void hand_complex_01 ( ) {
	printf ( "hand_complex_01 ( )\n" );

	/// TODO, this should be retrieved.
	int modI = 0;
	struct complexMod *mod = arrayListGetPointer ( glob_jvg->moduleList, modI );

	struct complexDec *dec = complexDecInit ( );
	arrayListAddEndPointer ( mod->complexDecList, dec );

	struct subVar *var = subVarInit ( );
	arrayListAddEndPointer ( dec->subVars, var );


	strcpy ( dec->modName, "jalbCalc" );
//	strcpy ( dec->renderFunct_name, "rendEquation_render" );
//	strcpy ( dec->renderFunct_name, "jalbCalc_render" );
	strcpy ( dec->renderFunct_name, "rendEquation_render_dynamic" );

	strcpy ( dec->eventFunct_name, "jalbCalc_event" );

	// reach into another mod, and grab the functs.

	complexDecPostInit ( dec );

	printf ( "hand_complex_01 ( ) OVER\n" );
}


/** Multi Mod Backbone */

ArrayList *jvg_modList = NULL;	// (struct modWrap*)

void hand_grab_mod ( char *modNick, char *jvgNick, char *realName ) {
	printf ( "hand_grab_mod ( )\n" );

	printf ( "modNick: %p\n", modNick );
	printf ( "modNick: %s\n", modNick );
	printf ( "jvgNick: %p\n", jvgNick );
	printf ( "jvgNick: %s\n", jvgNick );
	printf ( "realName: %p\n", realName );
	printf ( "realName: %s\n", realName );

	struct jalbLayMod *jMod = modCore_modGetter ( modNick );

	recieveMod ( jvgNick, jMod->handle, realName );
}

void recieveMod ( char *nick, void *handle, char *realName ) {
	printf ( "recieveMod ( )\n" );
	printf ( "nick: %s\n", nick );
	printf ( "handle: %p\n", handle );

	if ( !jvg_modList ) {
		jvg_modList = initArrayList ( 10, sizeof ( void* ), 10 );
	}

	struct modWrap *mod = malloc ( sizeof ( *mod ) );
	strcpy ( mod->nick, nick );
	strcpy ( mod->realName, nick );
	mod->handle = handle;

	arrayListAddEndPointer ( jvg_modList, mod );

	grabBackbone ( nick, realName, handle );
}


// its modName not modNick, because it grabs the function.
// just pass the modWrap.
void grabBackbone ( char *jvgNick, char *modName, void *handle ) {
	printf ( "grabBackbone ( )\n" );
	printf ( "jvgNick: %s\n", jvgNick );
	printf ( "modName: %s\n", modName );
	printf ( "handle: %p\n", handle );

	// goes through the backbones looking for the modNick.

//	void *funct = NULL;
//	int (*funct)( void*** ) = NULL;
	int (*funct)( struct backbone_structStruct*** ) = NULL;


	char functName[256];
	sprintf ( functName, "get_backbone_arr_total_%s", modName );


	printf ( "functName: %s\n", functName );


//	GET_FUNCT ( funct, handle, functName );
	funct = dlsym ( handle, functName );

	printf ( "funct: %p\n", funct );

	if ( funct ) {
//		void **arr;
		struct backbone_structStruct **arr;
		int len = funct ( &arr );

		// jalbXml function.
		wrangleBackbone ( jvgNick, len, arr );
	} else {
		printf ( "ERROR, can grab backbone total getter\n" );
	}

	return;
}

struct modWrap *modWrap_fromNick ( char *nick ) {
	printf ( "modWrap_fromNick ( )\n" );
	printf ( "nick: %s\n", nick );

	int i;
	int len;
	i = 0;
	len = arrayListGetLength ( jvg_modList );
	while ( i < len ) {
		struct modWrap *mod = arrayListGetPointer ( jvg_modList, i );

		if ( strcmp ( mod->nick, nick ) == 0 ) {
			return mod;
		}

		i += 1;
	}
	return NULL;
}


/// Setter

void set_modCore_modGetter ( void *mod ) {
	printf ( "set_modCore_modGetter ( )\n" );

	modCore_modGetter = mod;
}


/// Other

void complexDecPostInit ( struct complexDec *dec ) {
	printf ( "complexDecPostInit ( )\n" );
	printf ( "dec: %p\n", dec );
	printf ( "dec->modName: %s\n", dec->modName );

	struct modWrap *wrap = modWrap_fromNick ( dec->modName );
	if ( !wrap ) {
		printf ( "ERROR, !wrap\n" );
		printf ( "cant find modName: %s\n", dec->modName );
		return;
	}

//	int (*funct)( struct backbone_structStruct*** ) = NULL;

	GET_FUNCT ( dec->renderFunct, wrap->handle, dec->renderFunct_name );
	printf ( "dec->renderFunct: %p\n", dec->renderFunct );
	if ( !dec->renderFunct ) {
		printf ( "cant find function: %s\n", dec->renderFunct_name );
	}

	GET_FUNCT ( dec->eventFunct, wrap->handle, dec->eventFunct_name );
	printf ( "dec->eventFunct: %p\n", dec->eventFunct );
	if ( !dec->eventFunct ) {
		printf ( "cant find event function: %s\n", dec->eventFunct_name );
	}

	printf ( "complexDecPostInit ( ) OVER\n" );
}



// type is the index of the complexDecList
void complexEle_initType ( struct complexEle *ele, int type ) {

	/// TODO, this should be retrieved.
	int modI = 0;
	struct complexMod *mod = arrayListGetPointer ( glob_jvg->moduleList, modI );

	int numDecs = arrayListGetLength ( mod->complexDecList );
	if ( type < 0 ||
	     type >= numDecs ) {
		printf ( "ERROR, type out of range\n" );
		return;
	}

	ele->decType = type;

	struct complexDec *dec = arrayListGetPointer ( mod->complexDecList, type );
	int i = 0;
	int len = arrayListGetLength ( dec->subVars );
	while ( i < len ) {
		struct subVar *var = arrayListGetPointer ( dec->subVars, i );

		if ( var->type == jalbType_std ) {
			struct jLiveData *jLive = jLiveDataInit ( );
			arrayListAddEndPointer ( ele->liveSubVars, jLive );

			// TODO better type changing between subVar and jLiveData.
			int type = var->typeIndex;
			if ( type == 8 ) {
				type = jld_ComplexRef;
			}

			jLiveDataTypeChange0 ( jLive, type );
		} else {
			arrayListAddEndPointer ( ele->liveSubVars, NULL );
		}

		i += 1;
	}
}


/** Render */

void complexEleRender_sub ( int *screenDims, GLuint *glBuffers, int *XYWHpass, struct complexEle *complex, struct complexDec *dec,
		float *viewLoc, float viewScale ) {
	if ( debugPrint_jvg_complex_render ) {
		printf ( "complexEleRender_sub ( )\n" );
		printf ( "complex: %p\n", complex );
		printf ( "dec: %p\n", dec );
		sayIntArray ( "XYWHpass", XYWHpass, 4 );
	}
		sayIntArray ( "XYWHpass", XYWHpass, 4 );

	int numParams = arrayListGetLength ( dec->renderParams );

//	printf ( "numParams: %d\n", numParams );

	if ( numParams <= 0 ) {

		// this is shitty.
		struct jLiveData *liveData = arrayListGetPointer ( complex->liveSubVars, 0 );
		void *data = NULL;
		if ( liveData->type == jld_V ) {
			data = liveData->v;
		}


		// For dynamic rendering
		void (*funct)(int *screenDims, GLuint *glBuffers, int *XYWHpass, void *data,
			float *viewLoc, float viewScale) = dec->renderFunct;
		funct ( screenDims, glBuffers, XYWHpass, data,
			viewLoc, viewScale );
	} else {
		void *params[numParams];
		int i = 0;
		while ( i < numParams ) {
			int *pIndex = arrayListDataPointer ( dec->renderParams, i );

			printf ( "*pIndex: %d\n", *pIndex );

			struct jLiveData *data = arrayListGetPointer ( complex->liveSubVars, *pIndex );
			if ( data->type == jld_I ) {
				params[i] = &data->i;
			} else if ( data->type == jld_F ) {
				params[i] = &data->f;
			} else if ( data->type == jld_ComplexRef ) {
				params[i] = data->complexRef->complexPtr;
			}

			i += 1;
		}
		printf ( "params[0]: %p\n", params[0] );
		printf ( "params[1]: %p\n", params[1] );

		if ( numParams == 2 ) {
			void (*funct)(int *screenDims, GLuint *glBuffers, int *XYWHpass,
				float *viewLoc, float viewScale,
				void *p0, void *p1);
			funct = dec->renderFunct;

			funct ( screenDims, glBuffers, XYWHpass,
				viewLoc, viewScale,
				params[0], params[1] );
		} else if ( numParams == 3 ) {
			void (*funct)(int *screenDims, GLuint *glBuffers, int *XYWHpass,
				float *viewLoc, float viewScale,
				void *p0, void *p1, void *p2);
			funct = dec->renderFunct;

			funct ( screenDims, glBuffers, XYWHpass,
				viewLoc, viewScale,
				params[0], params[1], params[2] );
		}
	}
}


/** Event */

int complexEle_mEvent ( SDL_Event *e, int *clickXYpass, int *eleWH, struct complexEle *ele,
		float *viewLoc, float viewScale ) {
	printf ( "complexEle_mEvent ( )\n" );

	int ret = 0;

	/// TODO, this should be retrieved.
	int modI = 0;
	struct complexMod *mod = arrayListGetPointer ( glob_jvg->moduleList, modI );

	if ( !mod ) {
		printf ( "ERROR, !mod, complexEle_mEvent ( )\n" );
		return 0;
	}

	int numDec = arrayListGetLength ( mod->complexDecList );

	if ( ele->decType < 0 ||
	     ele->decType >= numDec ) {
		printf ( "ERROR, ele->decType out of range\n" );

		return 0;
	}

	float screenXYWH[4];
	point_to_loc ( ele->XYWH, screenXYWH, viewLoc, viewScale );

	screenXYWH[2] = ele->XYWH[2] / viewScale;
	screenXYWH[3] = ele->XYWH[3] / viewScale;

	if ( !pointInsideI ( clickXYpass, screenXYWH ) ) {
		// clicked outside the box.
		return 0;
	}

	struct complexDec *dec = arrayListGetPointer ( mod->complexDecList, ele->decType );

	printf ( "dec->eventFunct: %p\n", dec->eventFunct );

	if ( dec->eventFunct ) {
		// do i want to send viewLoc and viewScale?
		// or just convert clickXY to a float and send it?
//		dec->eventFunct ( SDL_Event *e, int *clickXYpass, int *eleWH, struct complexEle *ele,
//			float *viewLoc, float viewScale );

		float worldXY[2];
		loc_to_pointI ( clickXYpass, worldXY, viewLoc, viewScale );

/*
		int clickXY[2] = {
			worldXY[0],
			worldXY[1],
		};
*/



		void *data = NULL;
//		if ( numParams <= 0 ) {
			// this is shitty.
			struct jLiveData *liveData = arrayListGetPointer ( ele->liveSubVars, 0 );
			if ( liveData->type == jld_V ) {
				data = liveData->v;
			}
//		}
		printf ( "data: %p\n", data );


//		int (*funct)(SDL_Event *e, int *clickXYpass, int *eleWH, void *data) = dec->eventFunct;
//		ret = funct ( e, clickXY, eleWH, ele );

		// TODO, this is bad.
		int relClick[2] = { clickXYpass[0] - ele->XYWH[0], clickXYpass[1] - ele->XYWH[1] };

		sayIntArray ( "relClick", relClick, 2 );

		int (*funct)(SDL_Event *e, int *clickXYpass, int *eleWH, void *data,
			float *viewLoc, float viewScale) = dec->eventFunct;
//		ret = funct ( e, relClick, eleWH, ele,

		int cursorSet_override_mem = cursorSet_override;
		cursorSet_override = 1;
		ret = funct ( e, relClick, eleWH, data,
			viewLoc, viewScale );
		cursorSet_override = 1;
		cursorSet_override = cursorSet_override_mem;
	}

	// TODO, check ret
	set_cursorList_complex ( );

	printf ( "complexEle_mEvent ( ) OVER\n" );

	return ret;
}

int complexEle_kEvent ( SDL_Event *e, int *clickXYpass, int *eleWH, struct complexEle *ele,
		float *viewLoc, float viewScale ) {
	printf ( "complexEle_kEvent ( )\n" );


	int ret = 0;


	/// TODO, this should be retrieved.
	int modI = 0;
	struct complexMod *mod = arrayListGetPointer ( glob_jvg->moduleList, modI );

	if ( !mod ) {
		printf ( "ERROR, !mod, complexEle_mEvent ( )\n" );
		return 0;
	}



	struct complexDec *dec = arrayListGetPointer ( mod->complexDecList, ele->decType );

	printf ( "dec->eventFunct: %p\n", dec->eventFunct );

	if ( dec->eventFunct ) {
		float worldXY[2];
		loc_to_pointI ( clickXYpass, worldXY, viewLoc, viewScale );

		int relClick[2] = { clickXYpass[0] - ele->XYWH[0], clickXYpass[1] - ele->XYWH[1] };

		sayIntArray ( "relClick", relClick, 2 );


		void *data = NULL;
			// this is shitty.
			struct jLiveData *liveData = arrayListGetPointer ( ele->liveSubVars, 0 );
			if ( liveData->type == jld_V ) {
				data = liveData->v;
			}

		int (*funct)(SDL_Event *e, int *clickXYpass, int *eleWH, void *data,
			float *viewLoc, float viewScale) = dec->eventFunct;
		ret = funct ( e, relClick, eleWH, data,
			viewLoc, viewScale );
	}
	return ret;
}

extern char altKeys[];

extern ArrayList *scopeData;	// (struct idPtr*)


// cursor
extern ArrayList *cursorList;	// (struct cursorMem *mem)
extern int cursor_depth;

extern int selected;


// for complexRef linking
void jvgPostInit ( struct jvg *jvg ) {
	printf ( "jvgPostInit ( )\n" );

	// multiply ways to do this, iterate through the complexDecs to determine which have complexRefs, then only update those eles.
	// iterate through naked unions, if it is a complex of uknown type, iterate throught its vars, if it finds a complexRef, then mark that type as good,
	//  if not, then mark it is bad. what if i make unions?
	// im going to simply iterate every naked union, and then search every complex


	int i = 0;
	int len = arrayListGetLength ( jvg->eles );
	while ( i < len ) {
		struct jNakedUnion *uni = arrayListGetPointer ( jvg->eles, i );

		if ( uni->type == jNaked_Complex ) {
			struct complexEle *ele = uni->complex;

			complexEle_ref_link ( jvg, ele );
		}

		i += 1;
	}

	printf ( "jvgPostInit ( ) OVER\n" );
}

// converts complexRef ptr to eleI
void jvgPreSave ( struct jvg *jvg ) {
	printf ( "jvgPreSave ( )\n" );

	int i = 0;
	int len = arrayListGetLength ( jvg->eles );
	while ( i < len ) {
		struct jNakedUnion *uni = arrayListGetPointer ( jvg->eles, i );

		if ( uni->type == jNaked_Complex ) {
			struct complexEle *ele = uni->complex;

			complexEle_index_link ( jvg, ele );
		}

		i += 1;
	}

	printf ( "jvgPreSave ( ) OVER\n" );
}

void complexEle_ref_link ( struct jvg *jvg, struct complexEle *ele ) {
	printf ( "complexEle_ref_link ( )\n" );

	int i = 0;
	int len = arrayListGetLength ( ele->liveSubVars );
	while ( i < len ) {
		struct jLiveData *data = arrayListGetPointer ( ele->liveSubVars, i );
		if ( data->type == jld_ComplexRef ) {
			struct complexRef *ref = data->complexRef;

			printf ( "get ptr for ref->eleI: %d\n", ref->eleI );

			struct jNakedUnion *uni = arrayListGetPointer ( jvg->eles, ref->eleI );
			if ( uni->type == jNaked_Complex ) {
				data->complexRef->complexPtr = uni->complex;
			} else {
				printf ( "ERROR, ele [%d] is not a complexEle\n", ref->eleI );
			}
		}

		i += 1;
	}
}

void complexEle_index_link ( struct jvg *jvg, struct complexEle *ele ) {
	int i = 0;
	int len = arrayListGetLength ( ele->liveSubVars );
	while ( i < len ) {
		struct jLiveData *data = arrayListGetPointer ( ele->liveSubVars, i );
		if ( data->type == jld_ComplexRef ) {
			data->complexRef->eleI = complexEle_toIndex ( jvg, data->complexRef->complexPtr );
		}
		i += 1;
	}
}

int complexEle_toIndex ( struct jvg *jvg, struct complexEle *ele ) {
	int i = 0;
	int len = arrayListGetLength ( jvg->eles );
	while ( i < len ) {
		struct jNakedUnion *uni = arrayListGetPointer ( jvg->eles, i );

		if ( uni->type == jNaked_Complex ) {
			if ( uni->complex == ele ) {
				return i;
			}
		}

		i += 1;
	}
	return -1;
}

/** Temp Hand Electrical Engineering Functions */


extern float colorWhite[];

extern struct draw2dStruct *draw2dApi;

void hand_voltageSource_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass,
		float *viewLoc, float viewScale,
		int *voltage, struct complexEle *linkTo, struct complexEle *linkFrom ) {

	printf ( "hand_voltageSource_render ( )\n" );
	printf ( "*voltage: %d\n", *voltage );

	sayIntArray ( "XYWHpass", XYWHpass, 4 );

	struct jalbFont *font = fonts[0];

	float XYWH[4] = { XYWHpass[0], XYWHpass[1], XYWHpass[2], XYWHpass[3] };

	// i need to bound it better.
	float centerXY[2] = {
		XYWH[0] + XYWH[2] / 2,
		XYWH[1] + XYWH[3] / 2,
	};

	float radius = 32.0 / viewScale;

	printf ( "radius: %f\n", radius );

//	float canvasXY[2];
//	point_to_loc ( XYWH, canvasXY, viewLoc, viewScale );

	int sides = 20;

//	int XY[2] = { canvasXY[0], canvasXY[1] };
//	int XY[2] = { XYWH[0], XYWH[1] };
	int XY[2] = { centerXY[0], centerXY[1] };

	// draw the circle.
	draw2dApi->drawCircle_sides ( screenDims, glBuffers,
		XY, radius, sides, colorWhite );

	// this is total width, i shouldnt need to care about orient in this situation
	float glyphW = (font->atlasInfo.glyphW - font->atlasInfo.orientX) / viewScale;
	float glyphH = (font->atlasInfo.glyphH) / viewScale;

	float fXY[2] = {
		centerXY[0] - glyphW / 2,
		centerXY[1] - radius,
	};

	sayFloatArray ( "centerXY", centerXY, 2 );
	sayFloatArray ( "fXY", fXY, 2 );

	// draw plus and minus
/*
	char buffer[32];
	buffer[0] = '+';
	buffer[1] = '\0';
*/

	draw2dApi->drawCharPre ( font, colorWhite );
/*
	draw2dApi->drawStringBounded ( screenDims, glBuffers, fXY,
		XYWH, font, buffer );
*/
	int c = '+';
	unsigned int relC = draw2dApi->charToIndex ( font, c );
	draw2dApi->drawCharBounded_scale ( screenDims, glBuffers, fXY,
		XYWH, font, relC, viewScale );

	fXY[1] += radius * 1.4;
	c = '-';
	relC = draw2dApi->charToIndex ( font, c );
	draw2dApi->drawCharBounded_scale ( screenDims, glBuffers, fXY,
		XYWH, font, relC, viewScale );

	// draw the voltage string
	char buffer[256];
	sprintf ( buffer, "%d [V]", *voltage );

	int slen = strlen ( buffer );
	fXY[0] = centerXY[0] - (slen * glyphW) / 2;
	fXY[1] = centerXY[1] - glyphH / 2;
	draw2dApi->drawStringBounded_scale ( screenDims, glBuffers, fXY,
		XYWH, font, buffer, viewScale );

	// node elements
	float nodeRadius = 8.0 / viewScale;
	float offset = 10.0 / viewScale;
	float nodeLoc[2] = {
		centerXY[0],
		centerXY[1] - radius - offset,
	};

	float eleTop[2] = {
		centerXY[0],
		centerXY[1] - radius,
	};

	draw2dApi->drawSeg ( screenDims, glBuffers, eleTop, nodeLoc, colorWhite );

	nodeLoc[1] = centerXY[1] - radius - offset - nodeRadius;
	int iNode[2] = { nodeLoc[0], nodeLoc[1], };
	draw2dApi->drawCircle_sides ( screenDims, glBuffers,
		iNode, nodeRadius, sides, colorWhite );

/*
	// link to the next ele.
	float linkFromXY[2] = {
		centerXY[0],
		centerXY[1] - radius,
	};
*/


	int nodeType = 1;	// 1 for input
	float linkToXY[2];
	complexEleNodePosition ( viewLoc, viewScale,
		linkTo, nodeType, linkToXY );

	draw2dApi->drawSeg ( screenDims, glBuffers, nodeLoc, linkToXY, colorWhite );


	// draw the bottom node
	float eleBot[2] = {
		centerXY[0],
		centerXY[1] + radius,
	};
	nodeLoc[1] = eleBot[1] + offset;
	draw2dApi->drawSeg ( screenDims, glBuffers, eleBot, nodeLoc, colorWhite );

	iNode[0] = nodeLoc[0];
	iNode[1] = nodeLoc[1] + nodeRadius;
	draw2dApi->drawCircle_sides ( screenDims, glBuffers,
		iNode, nodeRadius, sides, colorWhite );

	printf ( "hand_voltageSource_render ( ) OVER\n" );
}

void hand_resistor_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass,
		float *viewLoc, float viewScale,
		int *resistance, struct complexEle *linkTo, struct complexEle *linkFrom ) {

	printf ( "hand_resistor_render ( )\n" );
	printf ( "*resistance: %d\n", *resistance );

	sayIntArray ( "XYWHpass", XYWHpass, 4 );

	struct jalbFont *font = fonts[0];

	float XYWH[4] = { XYWHpass[0], XYWHpass[1], XYWHpass[2], XYWHpass[3] };

	// i need to bound it better.
	float centerXY[2] = {
		XYWH[0] + XYWH[2] / 2,
		XYWH[1] + XYWH[3] / 2,
	};

	float radius = 32.0 / viewScale;

	printf ( "radius: %f\n", radius );

//	float canvasXY[2];
//	point_to_loc ( XYWH, canvasXY, viewLoc, viewScale );

	int sides = 20;

//	int XY[2] = { canvasXY[0], canvasXY[1] };
//	int XY[2] = { XYWH[0], XYWH[1] };
//	int XY[2] = { centerXY[0], centerXY[1] };

/*
	// draw the circle.
	draw2dApi->drawCircle_sides ( screenDims, glBuffers,
		XY, radius, sides, colorWhite );
*/

	float v0[2];
	v0[0] = centerXY[0];
	v0[1] = centerXY[1] - radius;

	float v1[2];
	v1[0] = centerXY[0];
	v1[1] = centerXY[1] - radius * 0.4;
	draw2dApi->drawSeg ( screenDims, glBuffers, v0, v1, colorWhite );

	v0[0] = centerXY[0] + radius * 0.8;
	v0[1] = centerXY[1] - radius * 0.2;
	draw2dApi->drawSeg ( screenDims, glBuffers, v0, v1, colorWhite );

	v1[0] = centerXY[0] - radius * 0.8;
	v1[1] = centerXY[1] + radius * 0.2;
	draw2dApi->drawSeg ( screenDims, glBuffers, v0, v1, colorWhite );

	v0[0] = centerXY[0];
	v0[1] = centerXY[1] + radius * 0.4;
	draw2dApi->drawSeg ( screenDims, glBuffers, v0, v1, colorWhite );

	v1[0] = centerXY[0];
	v1[1] = centerXY[1] + radius;
	draw2dApi->drawSeg ( screenDims, glBuffers, v0, v1, colorWhite );

	// this is total width, i shouldnt need to care about orient in this situation
	float glyphW = (font->atlasInfo.glyphW - font->atlasInfo.orientX) / viewScale;
	float glyphH = (font->atlasInfo.glyphH) / viewScale;

	float fXY[2] = {
		centerXY[0] - glyphW / 2,
		centerXY[1] - radius,
	};

	sayFloatArray ( "centerXY", centerXY, 2 );
	sayFloatArray ( "fXY", fXY, 2 );

	// draw plus and minus
/*
	char buffer[32];
	buffer[0] = '+';
	buffer[1] = '\0';
*/

	draw2dApi->drawCharPre ( font, colorWhite );
/*
	draw2dApi->drawStringBounded ( screenDims, glBuffers, fXY,
		XYWH, font, buffer );
*/
	int c = '+';
	unsigned int relC = draw2dApi->charToIndex ( font, c );
	draw2dApi->drawCharBounded_scale ( screenDims, glBuffers, fXY,
		XYWH, font, relC, viewScale );

	fXY[1] += radius * 1.4;
	c = '-';
	relC = draw2dApi->charToIndex ( font, c );
	draw2dApi->drawCharBounded_scale ( screenDims, glBuffers, fXY,
		XYWH, font, relC, viewScale );



	// draw the voltage string
	char buffer[256];
	sprintf ( buffer, "%d [omega]", *resistance );

	int slen = strlen ( buffer );
	fXY[0] = centerXY[0] - (slen * glyphW) / 2;
	fXY[1] = centerXY[1] - glyphH / 2;
	draw2dApi->drawStringBounded_scale ( screenDims, glBuffers, fXY,
		XYWH, font, buffer, viewScale );




	// node elements
	float nodeRadius = 8.0 / viewScale;
	float offset = 10.0 / viewScale;
	float nodeLoc[2] = {
		centerXY[0],
		centerXY[1] - radius - offset,
	};

	float eleTop[2] = {
		centerXY[0],
		centerXY[1] - radius,
	};

	draw2dApi->drawSeg ( screenDims, glBuffers, eleTop, nodeLoc, colorWhite );

	nodeLoc[1] = centerXY[1] - radius - offset - nodeRadius;
	int iNode[2] = { nodeLoc[0], nodeLoc[1], };
	draw2dApi->drawCircle_sides ( screenDims, glBuffers,
		iNode, nodeRadius, sides, colorWhite );
	
/*
	// link to the next ele.
	float linkFromXY[2] = {
		centerXY[0],
		centerXY[1] - radius,
	};
*/


	int nodeType = 1;	// 1 for input
	float linkToXY[2];
	complexEleNodePosition ( viewLoc, viewScale,
		linkTo, nodeType, linkToXY );

	draw2dApi->drawSeg ( screenDims, glBuffers, nodeLoc, linkToXY, colorWhite );


	// draw the bottom node
	float eleBot[2] = {
		centerXY[0],
		centerXY[1] + radius,
	};
	nodeLoc[1] = eleBot[1] + offset;
	draw2dApi->drawSeg ( screenDims, glBuffers, eleBot, nodeLoc, colorWhite );

	iNode[0] = nodeLoc[0];
	iNode[1] = nodeLoc[1] + nodeRadius;
	draw2dApi->drawCircle_sides ( screenDims, glBuffers,
		iNode, nodeRadius, sides, colorWhite );

	printf ( "hand_voltageSource_render ( ) OVER\n" );
}


// i need further node info.
// type 0 is output, type 1 is input
void complexEleNodePosition ( float *viewLoc, float viewScale,
		struct complexEle *complexEle, int type, float *fillXY ) {

	float canvasXYWH[4];
	point_to_loc ( complexEle->XYWH, canvasXYWH, viewLoc, viewScale );
	canvasXYWH[2] = complexEle->XYWH[2] / viewScale;
	canvasXYWH[3] = complexEle->XYWH[3] / viewScale;

	float center[2];
	center[0] = canvasXYWH[0] + canvasXYWH[2] / 2;
	center[1] = canvasXYWH[1] + canvasXYWH[3] / 2;

	float radius = 32 / viewScale;
	float nodeRadius = 8.0 / viewScale;
	float offset = 10.0 / viewScale;

	float totalOffset = -(radius + offset + nodeRadius);
	if ( type == 1 ) {
		totalOffset = -totalOffset;
	}

	fillXY[0] = center[0];
	fillXY[1] = center[1] + totalOffset;
}

int hand_ee_event ( SDL_Event *e, int *clickXYpass, int *eleWH, struct complexEle *ele ) {
	printf ( "hand_ee_event ( )\n" );
	printf ( "ele->decType: %d\n", ele->decType );

	sayCharArray_hex ( "altKeys", altKeys, akNum );

	int modI = 0;
	struct complexMod *mod = arrayListGetPointer ( glob_jvg->moduleList, modI );
	if ( !mod ) {
		printf ( "ERROR, !mod\n" );
	}

	if ( altKeys[akShift] ) {
		// set cursor.
		// ok, so i need to get data.

		// or i want to run a cursor script...

		if ( selected ) {
			struct jNakedUnion *parent;
			struct jNakedUnion *nakedEle;
			int vertI = -1;
			int controlI = -1;
			struct cursorMem *lastCursor;

			int selType = jIterateToSelected ( glob_jvg->eles, &parent, &nakedEle, &vertI, &controlI, &lastCursor );
			printf ( "selType: %d\n", selType );
			if ( selType == cs_complex ) {
				struct complexEle *selEle = nakedEle->complex;
				if ( selEle == ele ) {
					printf ( "CLICKING ON ITSELf\n" );
				} else {
//					if ( selEle->decModI == modI ) {
						// it is from this mod, so continue.

						// it is a seperate ele, from the same mod.
						// i know i am clicking on this's "node" cuz of shift.
						// TODO, is the old eles node selected?
						// now lets link them.

						printf ( "the mods are the same\n" );

						// this is specific stuff
						if ( selEle->decType == 0 ) {
							// the complexRef is ele[1]
							struct jLiveData *data = arrayListGetPointer ( ele->liveSubVars, 1 );
							data->complexRef->complexPtr = selEle;
						}
//					}
				}
			}
		} else {
			printf ( "NO ELE SELECTED\n" );
		}

		// this ele is now selected
		selected = 1;

/*
		// idk if i need a specific i.
		int i = 0;

		handleCursor_start;
*/
		return 1;
	}

	if ( !scopeData ) {
		scopeData = initArrayList ( 10, sizeof ( void* ), 10 );	
	}

	// TEMP
	// this particular event adds the complexEle.
	struct idPtr *id = malloc ( sizeof ( *id ) );
	id->id = 0;
	id->ptr = ele;
	arrayListAddEndPointer ( scopeData, id );

	// run the script on this event.

	hand_script_2 ( );

	// subtraction propogation script.
	struct jLiveData *data = arrayListGetPointer ( ele->liveSubVars, 1 );
	struct complexEle *other = data->complexRef->complexPtr;
	if ( other ) {
		struct jLiveData *subData = arrayListGetPointer ( other->liveSubVars, 0 );
		subData->i -= 1;
	}

	return 2;
}



void add_global_complexMod ( ) {
	printf ( "add_global_complexMod ( )\n" );

	if ( !glob_jvg ) {
		goto functEnd;
	}

	struct jvg *jvg = glob_jvg;

	struct complexMod *mod = complexModInit ( );
	arrayListAddEndPointer ( jvg->moduleList, mod );

	functEnd:;

	printf ( "add_global_complexMod ( ) OVER\n" );
}



/// Complex List

void complexList_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass, struct complexList *ele,
		float *viewLoc, float viewScale ) {
	printf ( "complexList_render ( )\n" );

	

	printf ( "complexList_render ( ) OVER\n" );
}


/// TEMP

void spawn_complexEle ( ) {
	printf ( "spawn_complexEle ( )\n" );


	struct jvg *jvg = glob_jvg;

	// add complexEle
	struct jNakedUnion *uni = jNakedUnionInit ( );
	jNakedUnionTypeChange0 ( uni, jNaked_Complex );
	uni->complex->XYWH[0] = 637;
	uni->complex->XYWH[1] = 418;
	uni->complex->XYWH[2] = 400;
	uni->complex->XYWH[3] = 100;

	arrayListAddEndPointer ( jvg->eles, uni );


	// do postInits.
	int i = 0;
	int len = arrayListGetLength ( jvg->moduleList );
	while ( i < len ) {
		struct complexMod *mod = arrayListGetPointer ( jvg->moduleList, i );

		int j = 0;
		int numDecs = arrayListGetLength ( mod->complexDecList );
		while ( j < numDecs ) {
			struct complexDec *dec = arrayListGetPointer ( mod->complexDecList, i );
			complexDecPostInit ( dec );
			j += 1;
		}

		i += 1;
	}


	printf ( "spawn_complexEle ( ) OVER\n" );
}

void spawn_textEle ( ) {
	printf ( "spawn_textEle ( )\n" );

	struct jvg *jvg = glob_jvg;

	struct jNakedUnion *uni = jNakedUnionInit ( );
	arrayListAddEndPointer ( jvg->eles, uni );
	jNakedUnionTypeChange0 ( uni, jNaked_Text );

	int XYWH[4] = {
		100,
		100,
		300,
		100,
	};

	uni->text->XYWH[0] = XYWH[0];
	uni->text->XYWH[1] = XYWH[1];
	uni->text->XYWH[2] = XYWH[2];
	uni->text->XYWH[3] = XYWH[3];

	printf ( "spawn_textEle ( ) OVER\n" );
}















