#include "mod_ext.h"

/** Variables */

/// modCore externs 

extern char altKeys[];

extern struct draw2dStruct *draw2dApi;
extern struct jalbFont *fonts[];

extern float colorWhite[];
extern float colorBlack[];
extern float colorOrange[];
extern float colorGray[];


/// locals

struct svg *global_svg = NULL;

float *viewLoc_ptr;
float glob_viewLoc[2] = { 0.0, 0.0 };
float glob_viewScale = 1.0;;

int glob_screenDims[2];


void (*setViewScale) (float s) = NULL;


int svg_debugPrint_render = 0;
int svg_debugPrint_render_text = 0;

int svg_debugPrint_event = 0;


int renderMode = renderM_editAll;

int pointW = 10;

GLuint *glob_glBuffers = NULL;


/// proofs

extern int doingTests;
extern int testStage;

/** Functions */

void *jalbSvg_init ( ) {
	return NULL;
}

void jalbSvg_render ( int *screenDims, GLuint *glBuffers, int *XYWH, void *data ) {
	printf ( "\n" );
	printf ( "jalbSvg_render ( )\n" );

	if ( global_svg ) {
		svg_render ( screenDims, glBuffers, XYWH, global_svg );
	}
}

void jalbSvg_renderDyn ( int *screenDims, GLuint *glBuffers, int *XYWHpass, void *data,
		float *viewLoc, float viewScale ) {
	if ( svg_debugPrint_render ) {
		printf ( "\n" );

		printf ( "jalbSvg_renderDyn ( )\n" );
	}

	glob_glBuffers = glBuffers;

/*
	viewLoc[0] = 10;
	if ( setViewScale ) {
//		setViewScale ( 4.0 );
		setViewScale ( 0.5 );
	} else {
		printf ( "!setViewScale ( ) error\n" );
	}
*/

	if ( svg_debugPrint_render ) {
		sayFloatArray ( "viewLoc", viewLoc, 2 );
		printf ( "viewScale: %f\n", viewScale );
	}

	glob_screenDims[0] = screenDims[0];
	glob_screenDims[1] = screenDims[1];

	viewLoc_ptr = viewLoc;
	glob_viewLoc[0] = viewLoc[0];
	glob_viewLoc[1] = viewLoc[1];
	glob_viewScale = 1.0 / viewScale;

	if ( global_svg ) {
		svg_render ( screenDims, glBuffers, XYWHpass, global_svg );
	}

//	handle_render_proof ( );

	if ( doingTests ) {
		run_allTests ( testStage );
		testStage += 1;
	}


	if ( svg_debugPrint_render ) {
		printf ( "jalbSvg_renderDyn ( ) OVER\n" );
	}
}

int jalbSvg_event ( SDL_Event *e, int *clickXY, int *eleWH, void *data ) {
	return 1;
}

// this has recursion so needs an arraylist.
int selected = 0;
int mouseHeld = 0;

ArrayList *cursorList = NULL;
int cursor_depth = 0;

int jalbSvg_mEvent ( SDL_Event *e, int *clickXYpass, int *eleWH, void *data,
		float *viewLoc, float viewScale ) {
	if ( svg_debugPrint_event ) {
		printf ( "jalbSvg_mEvent ( )\n" );
	}

	if ( !cursorList ) {
		cursorList = initArrayList ( 10, sizeof ( void* ), 10 );
	}

	if ( !global_svg ) {
//		svg_event ( screenDims, glBuffers, XYWHpass, global_svg );
		return 0;
	}
	struct svg *svg = global_svg;
	int ret = svg_event ( e, clickXYpass, eleWH, svg,
		viewLoc, viewScale );

	if ( ret ) {
		return ret;
	}

	if ( svg_debugPrint_event ) {
		printf ( "jalbSvg_mEvent ( ) OVER\n" );
	}

	return 0;
}

void jalbSvg_close ( void *data ) {

}


/** Util */

// this only works if they are not relative?
// otherwise i need to keep track of the XY of prev ele.
void get_pathUni_XY ( struct pathUni *pUni, float *XY ) {
	if ( pUni->type == path_MoveTo ) {
		struct moveTo *ele = pUni->moveTo;
		XY[0] = ele->XY[0];
		XY[1] = ele->XY[1];

	} else if ( pUni->type == path_LineTo ) {
		struct lineTo *ele = pUni->lineTo;
		XY[0] = ele->XY[0];
		XY[1] = ele->XY[1];

	} else if ( pUni->type == path_CubicBez ) {
		struct cubicBez *ele = pUni->cubicBez;
		XY[0] = ele->XY[0];
		XY[1] = ele->XY[1];

	} else if ( pUni->type == path_QuadBez ) {
		struct quadBez *ele = pUni->quadBez;
		XY[0] = ele->XY[0];
		XY[1] = ele->XY[1];

	} else if ( pUni->type == path_EllipArc ) {
		struct ellipArc *ele = pUni->ellipArc;
		XY[0] = ele->XY[0];
		XY[1] = ele->XY[1];

	} else if ( pUni->type == path_PathEnd ) {
	}
}

void point_to_loc_glob ( float *p0, float *pSet ) {
	point_to_loc ( p0, pSet, glob_viewLoc, glob_viewScale );
}

void loc_to_point_glob ( float *p0, float *pSet ) {
	loc_to_point ( p0, pSet, glob_viewLoc, glob_viewScale );
}


/** event util */

int thisEdit ( int thisSel ) {
	if ( renderMode == renderM_editAll ) {
		return 1;
	} else if ( renderMode == renderM_edit ) {
		if ( thisSel ) {
			return 1;
		}
	}
	return 0;
}


/** Api Setter */

void set_set_viewScale ( void *f ) {
	setViewScale = f;
}


/** Debug */

void set_svg_debugPrint_render ( int i ) {
	printf ( "set_svg_debugPrint_render ( )\n" );
	printf ( "i: %d\n", i );

	svg_debugPrint_render = i;

	printf ( "set_svg_debugPrint_render ( ) OVER\n" );
}

void toggle_svg_debugPrint_render ( ) {
	printf ( "toggle_svg_debugPrint_render ( )\n" );

	if ( svg_debugPrint_render ) {
		svg_debugPrint_render = 0;
	} else {
		svg_debugPrint_render = 1;
	}

	printf ( "svg_debugPrint_render: %d\n", svg_debugPrint_render );

	printf ( "toggle_svg_debugPrint_render ( ) OVER\n" );
}

void toggle_svg_debugPrint_event ( ) {
	printf ( "toggle_svg_debugPrint_event ( )\n" );

	if ( svg_debugPrint_event ) {
		svg_debugPrint_event = 0;
	} else {
		svg_debugPrint_event = 1;
	}

	printf ( "svg_debugPrint_event: %d\n", svg_debugPrint_event );

	printf ( "toggle_svg_debugPrint_event ( ) OVER\n" );
}






