#include "jvg_ui.h"


/** Includes */

#include "jGroup.h"
#include "jPath.h"

/** Variables */

// uiGen
struct uiGen_api *uiGen_api = NULL;

// this aint right
char *workspaceDir_jalbJvg = "/home/jadeb/workspace/jHigh/jalbSvg/";

extern int screenDim_mem[];
extern int cursorInputMode;

extern struct jvg *glob_jvg;



/** Functions */


/// Setter

void set_uiGen_api ( void *data ) {
	printf ( "set_uiGen_api ( ) (consume)\n" );

	uiGen_api = data;

	printf ( "uiGen_api: %p\n", uiGen_api );
	printf ( "uiGen_api->uiGen_init: %p\n", uiGen_api->uiGen_init );
}


/// spawning uiGen eles

void jType_spawnEditUi ( struct jNakedUnion *uni ) {
	printf ( "jType_spawnEditUi ( )\n" );

	char *dir = NULL;
	void *data = NULL;

	switch ( uni->type ) {
		case jNaked_G:
			break;
		case jNaked_Path:
			dir = "/home/jadeb/workspace/jHigh/jalbSvg/res/uiGen_hand/jPath.xml";
			data = uni->path;

			break;
		case jNaked_Text:
			dir = "/home/jadeb/workspace/jHigh/jalbSvg/res/uiGen_hand/jText.xml";
			data = uni->text;

			break;
		case jNaked_Rect:

			break;
		case jNaked_Circ:

			break;
		case jNaked_Ellipse:

			break;
		case jNaked_Complex:
			dir = "/home/jadeb/workspace/jHigh/jalbSvg/res/uiGen_hand/complexEle.xml";
			data = uni->text;

			break;
		default:
			break;
	}

	if ( dir ) {
		uiGen_api->load_and_set_norm ( dir, data );
	}
}

void open_jVert_edit ( struct jVert *vert ) {
	printf ( "open_jVert_edit ( )\n" );
	printf ( "vert: %p\n", vert );
	sayFloatArray ( "vert->XY", vert->XY, 2 );

	printf ( "open_jVert_edit ( ) OVER\n" );

//	exit ( 12 );
}

void open_jLine_edit ( struct jLine *line ) {
	printf ( "open_jLine_edit ( )\n" );
	printf ( "line: %p\n", line );

	printf ( "line->v0: %d\n", line->v0 );
	printf ( "line->v1: %d\n", line->v1 );

//	char *workspaceDir_jalbJvg = "/home/jadeb/workspace/jHigh/jalbSvg/";
	char *fileDir = "res/uiGen_hand/jLine.xml";

	char fullDir[1024];
	sprintf ( fullDir, "%s%s", workspaceDir_jalbJvg, fileDir );

	if ( uiGen_api ) {
		uiGen_api->load_and_set_norm ( fullDir, line );
	}

	printf ( "open_jLine_edit ( ) OVER\n" );
}


/// UiGen spawning

char *jvg_projectDir = "/home/jadeb/workspace/jHigh/jalbSvg";

void open_left_toolbar ( ) {
	printf ( "open_left_toolbar ( )\n" );

//	char *fullDir = "/home/jadeb/workspace/jHigh/jalbSvg/res/uiGen_hand/eleSpawner.xml";

	char *dir = "res/uiGen_hand/eleSpawner.xml";
	char fullDir[256];
	sprintf ( fullDir, "%s/%s", jvg_projectDir, dir );


	void *data = NULL;
	int type = 1; // no red bar.

	int XYWH[4] = { 0, 54, 68, 114 };
	void *uiGen = uiGen_api->load_and_set_XYWH ( fullDir, data, XYWH, type );

	printf ( "uiGen: %p\n", uiGen );

	printf ( "open_left_toolbar ( ) OVER\n" );
}

// needs screenDim_mem so it can open on the right side of the screen.
void uiGen_open_eleList ( ) {
	printf ( "uiGen_open_eleList ( )\n" );

	char *dir = "res/uiGen_hand/eleList.xml";

	char fullDir[256];
	sprintf ( fullDir, "%s/%s", jvg_projectDir, dir );

	void *data = glob_jvg;
	int type = 0; // red bar.

	int width = 200;

	// open it on the right side of the screen.
	int XYWH[4] = { screenDim_mem[0] - width, 74, width, 400 };
	uiGen_api->load_and_set_XYWH ( fullDir, data, XYWH, type );

	printf ( "uiGen_open_eleList ( ) OVER\n" );
}

void uiGen_open_jNaked ( struct jNakedUnion *jNaked ) {
	printf ( "uiGen_open_jNaked ( )\n" );

	printf ( "projectDir: %s\n", jvg_projectDir );

	printf ( "jNaked: %p\n", jNaked );
	printf ( "jNaked->type: %d\n", jNaked->type );

//	char *dir = "/home/jadeb/workspace/jHigh/jalbSvg/res/uiGen_hand/";
	char *midDir = "res/uiGen_hand";

	int type = 0; // red bar.

	if ( jNaked->type == jNaked_G ) {
	} else if ( jNaked->type == jNaked_Path ) {
		char *name = "jPath.xml";
		char fullDir[1024];
//		sprintf ( fullDir, "%s%s", dir, name );
		sprintf ( fullDir, "%s/%s/%s", jvg_projectDir, midDir, name );

		void *data = jNaked->path;

		int XYWH[4] = { 40, 40, 400, 400 };
		uiGen_api->load_and_set_XYWH ( fullDir, data, XYWH, type );

	} else if ( jNaked->type == jNaked_Text ) {
		char *name = "jText.xml";
		char fullDir[1024];
		sprintf ( fullDir, "%s/%s/%s", jvg_projectDir, midDir, name );

		void *data = jNaked->text;

		int XYWH[4] = { 40, 40, 400, 400 };
		uiGen_api->load_and_set_XYWH ( fullDir, data, XYWH, type );

	} else if ( jNaked->type == jNaked_Rect ) {
	} else if ( jNaked->type == jNaked_Circ ) {
	} else if ( jNaked->type == jNaked_Ellipse ) {
	} else if ( jNaked->type == jNaked_Complex ) {
	}

	printf ( "uiGen_open_jNaked ( ) OVER\n" );
}

void uiGen_open_complexWrangler ( ) {
	printf ( "uiGen_open_complexWrangler ( )\n" );

	char *midDir = "res/uiGen_hand";

	char *name = "complexWrangler.xml";
	char fullDir[1024];
	sprintf ( fullDir, "%s/%s/%s", jvg_projectDir, midDir, name );

	int type = 0; // red bar.
	int XYWH[4] = { 40, 40, 420, 600 };

	void *data = glob_jvg;

	uiGen_api->load_and_set_XYWH ( fullDir, data, XYWH, type );

	printf ( "uiGen_open_complexWrangler ( ) OVER\n" );
}

void uiGen_open_complexMod ( struct complexMod *mod ) {
	printf ( "uiGen_open_complexMod ( )\n" );

	char *midDir = "res/uiGen_hand";

	char *name = "complexMod.xml";
	char fullDir[1024];
	sprintf ( fullDir, "%s/%s/%s", jvg_projectDir, midDir, name );

	int type = 0; // red bar.
	int XYWH[4] = { 40, 40, 400, 400 };

	void *data = mod;
	uiGen_api->load_and_set_XYWH ( fullDir, data, XYWH, type );

	printf ( "uiGen_open_complexMod ( ) OVER\n" );
}

void uiGen_open_complexDec ( struct complexDec *dec ) {
	printf ( "uiGen_open_complexDec ( )\n" );

	char *midDir = "res/uiGen_hand";

	char *name = "complexDec.xml";
	char fullDir[1024];
	sprintf ( fullDir, "%s/%s/%s", jvg_projectDir, midDir, name );

	int type = 0; // red bar.
	int XYWH[4] = { 40, 40, 400, 400 };

	void *data = dec;

	uiGen_api->load_and_set_XYWH ( fullDir, data, XYWH, type );

	printf ( "uiGen_open_complexDec ( ) OVER\n" );
}


/// uiGen left toolbar stuff

float retColor[4] = { 0.0 };

float *toolBar_icon_color ( int i ) {
//	printf ( "toolBar_icon_color ( )\n" );
//	printf ( "i: %d\n", i );

	if ( cursorInputMode == i ) {
		retColor[0] = 0.8;
		retColor[1] = 0.6;
		retColor[2] = 0.0;
		retColor[3] = 1.0;
	} else {
		retColor[0] = 0.4;
		retColor[1] = 0.4;
		retColor[2] = 0.4;
		retColor[3] = 1.0;
	}

	return retColor;
}




/// Loading examples for uiGen_liveDev

struct jvg *load_jvg_example_eleList ( ) {
	printf ( "load_jvg_example_eleList ( )\n" );

	struct jvg *jvg = jvgInit ( );
	struct jNakedUnion *uni = jNakedUnionInit ( );
	jNakedUnionTypeChange0 ( uni, jNaked_G );
	arrayListAddEndPointer ( jvg->eles, uni );

	uni = jNakedUnionInit ( );
	jNakedUnionTypeChange0 ( uni, jNaked_Path );
	arrayListAddEndPointer ( jvg->eles, uni );

	uni = jNakedUnionInit ( );
	jNakedUnionTypeChange0 ( uni, jNaked_Text );
	arrayListAddEndPointer ( jvg->eles, uni );

	uni = jNakedUnionInit ( );
	jNakedUnionTypeChange0 ( uni, jNaked_Rect );
	arrayListAddEndPointer ( jvg->eles, uni );

	uni = jNakedUnionInit ( );
	jNakedUnionTypeChange0 ( uni, jNaked_Circ );
	arrayListAddEndPointer ( jvg->eles, uni );

	uni = jNakedUnionInit ( );
	jNakedUnionTypeChange0 ( uni, jNaked_Ellipse );
	arrayListAddEndPointer ( jvg->eles, uni );

	uni = jNakedUnionInit ( );
	jNakedUnionTypeChange0 ( uni, jNaked_Complex );
	arrayListAddEndPointer ( jvg->eles, uni );

	glob_jvg = jvg;

	printf ( "load_jvg_example_eleList ( ) OVER\n" );

	return jvg;
}

struct jPath *load_jvg_example_jPath ( ) {
	printf ( "load_jvg_example_jPath ( )\n" );

	struct jPath *path = jPathInit ( );

	struct jVert *vert = jVertInit ( );
	arrayListAddEndPointer ( path->verts, vert );
	vert->XY[0] = 1.0;
	vert->XY[1] = -1.0;

	vert = jVertInit ( );
	arrayListAddEndPointer ( path->verts, vert );
	vert->XY[0] = 2.0;
	vert->XY[1] = -2.0;

	struct jLine *line = jLineInit ( );
	arrayListAddEndPointer ( path->lines, line );
	line->v0 = 0;
	line->v1 = 1;

	printf ( "load_jvg_example_jPath ( ) OVER\n" );

	return path;
}

struct jVert *load_jvg_example_jVert ( ) {
	printf ( "load_jvg_example_jVert ( )\n" );

	struct jVert *vert = jVertInit ( );
	vert->XY[0] = 1.0;
	vert->XY[1] = -1.0;

	printf ( "load_jvg_example_jvert ( ) OVER\n" );

	return vert;
}

struct jLine *load_jvg_example_jLine ( ) {
	printf ( "load_jvg_example_jLine ( )\n" );

	struct jLine *line = jLineInit ( );
	line->v0 = 0;
	line->v1 = 0;

	printf ( "load_jvg_example_jLine ( ) OVER\n" );

	return line;
}


