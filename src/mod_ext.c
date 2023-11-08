#include "mod_ext.h"


struct svg *global_svg = NULL;


extern struct draw2dStruct *draw2dApi;
extern struct jalbFont *fonts[];

extern float colorWhite[];
extern float colorBlack[];
extern float colorOrange[];
extern float colorGray[];


float *viewLoc_ptr;
float glob_viewLoc[2] = { 0.0, 0.0 };
float glob_viewScale = 1.0;;

int glob_screenDims[2];


void (*setViewScale) (float s) = NULL;


int svg_debugPrint_render = 1;
int svg_debugPrint_render_text = 1;

int svg_debugPrint_event = 1;


int renderMode = renderM_edit;

int pointW = 10;

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
		printf ( "jalbSvg_renderDyn ( )\n" );
	}

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

	handle_render_proof ( );
}

int jalbSvg_event ( SDL_Event *e, int *clickXY, int *eleWH, void *data ) {
	return 1;
}

// this has recursion so needs an arraylist.
int selected = 0;
ArrayList *selList = NULL;

int depth = 0;

int jalbSvg_mEvent ( SDL_Event *e, int *clickXYpass, int *eleWH, void *data,
		float *viewLoc, float viewScale ) {
	if ( svg_debugPrint_event ) {
		printf ( "jalbSvg_mEvent ( )\n" );
	}

	if ( !selList ) {
		selList = initArrayList ( 10, sizeof ( void* ), 10 );
	}

	if ( !global_svg ) {
//		svg_event ( screenDims, glBuffers, XYWHpass, global_svg );
		return 0;
	}
	struct svg *svg = global_svg;


	if ( e->type == SDL_MOUSEMOTION ) {
		if ( selected ) {
			int i = 0;
			int len = arrayListGetLength ( selList );
			printf ( "selList.len: %d\n", len );

			struct nakedUnion *uni = NULL;
			ArrayList *nextList = svg->eles;
			struct cursorMem *mem = NULL;

			while ( i < len-1 ) {
				mem = arrayListGetPointer ( selList, i );

				printf ( "mem->selI: %d\n", mem->selI );

				uni = arrayListGetPointer ( nextList, mem->selI );;
				nextList = uni->g->eles;
				i += 1;
			}

			printf ( "i: %d\n", i );

			mem = arrayListGetPointer ( selList, i );

			printf ( "mem->selI: %d\n", mem->selI );

//			printf ( "nextList.len: %d\n", arrayListGetLength ( nextList ) );
//			struct nakedUnion *uni = arrayListGetPointer ( nextList, mem->selI );

			if ( uni->type == Path ) {
				printf ( "uni->path->eles.len: %d\n", arrayListGetLength ( uni->path->eles ) );

				struct pathUni *pUni = arrayListGetPointer ( uni->path->eles, mem->selI );

				float dx = e->motion.xrel / viewScale;
				float dy = e->motion.yrel / viewScale;
				move_pUni ( pUni, dx, dy );
			}
			return 1;
		}

		return 0;
	}

	selected = 0;
	if ( e->type == SDL_MOUSEBUTTONUP ) {
	}

	if ( e->type == SDL_MOUSEBUTTONDOWN ) {
	int ret = nakedList_mEvent ( e, clickXYpass, eleWH, svg->eles,
		viewLoc, viewScale );
	if ( ret ) {
		printf ( "finish set cursor\n" );
		printf ( "selList.len: %d\n", arrayListGetLength ( selList ) );

		int i = 0;
		int len = arrayListGetLength ( selList );
		while ( i < len ) {
			struct cursorMem *mem = arrayListGetPointer ( selList, i );
			printf ( "%d, ", mem->selI );
			i += 1;
		}
		printf ( "\n" );
	}
	}

	if ( svg_debugPrint_event ) {
		printf ( "jalbSvg_mEvent ( ) OVER\n" );
	}

	return 0;
}

void jalbSvg_close ( void *data ) {

}


void move_pUni ( struct pathUni *pUni, float dx, float dy ) {
	if ( svg_debugPrint_event ) {
		printf ( "move_pUni ( )\n" );
	}

	if ( pUni->type == path_MoveTo ) {
		struct moveTo *ele = pUni->moveTo;
		ele->XY[0] += dx;
		ele->XY[1] += dy;
	} else if ( pUni->type == path_LineTo ) {
		struct lineTo *ele = pUni->lineTo;
		ele->XY[0] += dx;
		ele->XY[1] += dy;
	} else if ( pUni->type == path_CubicBez ) {
		struct cubicBez *ele = pUni->cubicBez;
		ele->XY[0] += dx;
		ele->XY[1] += dy;
	} else if ( pUni->type == path_QuadBez ) {
		struct quadBez *ele = pUni->quadBez;
		ele->XY[0] += dx;
		ele->XY[1] += dy;
	} else if ( pUni->type == path_EllipArc ) {
		struct ellipArc *ele = pUni->ellipArc;
		ele->XY[0] += dx;
		ele->XY[1] += dy;
	} else if ( pUni->type == path_PathEnd ) {
	}

	if ( svg_debugPrint_event ) {
		printf ( "move_pUni ( ) OVER\n" );
	}
}


/** Util */

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

/** Api Setter */

void set_set_viewScale ( void *f ) {
	setViewScale = f;
}








