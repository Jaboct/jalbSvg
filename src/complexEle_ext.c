#include "complexEle_ext.h"


/** Variables */

extern struct jvg *glob_jvg;

struct jalbLayMod *(*modCore_modGetter) ( char *modNick ) = NULL;


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

			jLiveDataTypeChange0 ( jLive, var->typeIndex );
		} else {
			arrayListAddEndPointer ( ele->liveSubVars, NULL );
		}

		i += 1;
	}
}


/** Event */

int complexEle_mEvent ( SDL_Event *e, int *clickXYpass, int *eleWH, struct complexEle *ele,
		float *viewLoc, float viewScale ) {
	printf ( "complexEle_mEvent ( )\n" );

	/// TODO, this should be retrieved.
	int modI = 0;
	struct complexMod *mod = arrayListGetPointer ( glob_jvg->moduleList, modI );

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
		int clickXY[2] = {
			worldXY[0],
			worldXY[1],
		};

		int (*funct)(SDL_Event *e, int *clickXYpass, int *eleWH, void *data) = dec->eventFunct;
		funct ( e, clickXY, eleWH, ele );
	}

	printf ( "complexEle_mEvent ( ) OVER\n" );

	return 0;
}


extern char altKeys[];

extern ArrayList *scopeData;	// (struct idPtr*)

extern int selected;

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
			if ( selType == jNaked_Complex ) {
				struct complexEle *selEle = nakedEle->complex;
				if ( selEle == ele ) {
					printf ( "CLICKING ON ITSELf\n" );
				}

//				if ( selEle->decModI == modI ) {
					// it is from this mod, so continue.

					printf ( "the mods linked\n" );
//				}
			}
		} else {
			printf ( "NO ELE SELECTED\n" );
		}

		// this ele is now selected
		selected = 1;
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

	return 2;
}









