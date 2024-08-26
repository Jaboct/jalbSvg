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

	struct complexDec *dec = complexDecInit ( );
	arrayListAddEndPointer ( glob_jvg->complexDecList, dec );

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

	printf ( "complexDecPostInit ( ) OVER\n" );
}




int complexEle_initType ( struct complexEle *ele, int type ) {
	int numDecs = arrayListGetPointer ( glob_jvg->complexDecList );
	if ( type < 0 ||
	     type >= numDecs ) {
		printf ( "ERROR, type out of range\n" );
		return;
	}

	struct coplexDec *dec = arrayListGetPointer ( glob_jvg->complexDecList, type );
	
}
















