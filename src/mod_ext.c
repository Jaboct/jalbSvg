#include "mod_ext.h"


struct svg *global_svg = NULL;


extern struct draw2dStruct *draw2dApi;

extern struct jalbFont *fonts[];

extern float colorWhite[];
extern float colorBlack[];


float *viewLoc_ptr;
float glob_viewLoc[2] = { 0.0, 0.0 };
float glob_viewScale = 1.0;;

int glob_screenDims[2];


void (*setViewScale) (float s) = NULL;

int svg_debugPrint_render = 0;


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

int jalbSvg_mEvent ( SDL_Event *e, int *clickXYpass, int *eleWH, void *data,
		float *viewLoc, float viewScale ) {
	return 0;
}

void jalbSvg_close ( void *data ) {

}



// i need the dynamic canvas info.


void point_to_loc ( float *p0, float *pSet ) {
/*
	printf ( "point_to_loc ( )\n" );
	sayFloatArray ( "glob_viewLoc", glob_viewLoc, 2 );
	printf ( "glob_viewScale: %f\n", glob_viewScale );
	sayFloatArray ( "p0", p0, 2 );
*/

//	pSet[0] = p0[0] * glob_viewScale - glob_viewLoc[0];
//	pSet[1] = p0[1] * glob_viewScale - glob_viewLoc[1];

//	pSet[0] = p0[0];
//	pSet[1] = p0[1];


	pSet[0] = ( p0[0] - glob_viewLoc[0] ) / glob_viewScale;
	pSet[1] = ( p0[1] - glob_viewLoc[1] ) / glob_viewScale;


//	sayFloatArray ( "pSet", pSet, 2 );
}


void svg_render ( int *screenDims, GLuint *glBuffers, int *XYWH, struct svg *svg ) {
	if ( svg_debugPrint_render ) {
		printf ( "svg_render ( )\n" );
	}

	eles_render ( screenDims, glBuffers, XYWH, svg->eles );
}

void eles_render ( int *screenDims, GLuint *glBuffers, int *XYWH, ArrayList *eles ) {
	int i;
	int len;

	i = 0;
	len = arrayListGetLength ( eles );

	if ( svg_debugPrint_render ) {
		printf ( "eles.len: %d\n", len );
	}

	while ( i < len ) {
		struct nakedUnion *uni = arrayListGetPointer ( eles, i );

		if ( svg_debugPrint_render ) {
			printf ( "uni->type: %d\n", uni->type );
		}

		if ( uni->type == G ) {
			struct g *g = uni->g;

			eles_render ( screenDims, glBuffers, XYWH, g->eles );

		} else if ( uni->type == Path ) {
			struct path *path = uni->path;
			path_render ( screenDims, glBuffers, XYWH, path );

		} else if ( uni->type == Text ) {
			struct text *text = uni->text;
			textRender ( screenDims, glBuffers, XYWH, text );

		}

		i += 1;
	}
}

void path_render ( int *screenDims, GLuint *glBuffers, int *XYWH, struct path *path ) {
	if ( svg_debugPrint_render ) {
		printf ( "path_render ( )\n" );
	}

	int i;
	int len;

	float lastP[2] = { 0, 0 };
	// some times lastC will not be set, i should mark this as error checking. but for now just trust what i load.
	float lastC[2] = { 0, 0 };

	int start = 1;
	// does z maybe need a C?
	float startP[2];

	i = 0;
	len = arrayListGetLength ( path->eles );
	while ( i < len ) {
		struct pathUni *uni = arrayListGetPointer ( path->eles, i );

		if ( svg_debugPrint_render ) {
			printf ( "uni->type: %d\n", uni->type );
		}

		float thisP[2];
		float thisC[2];
		if ( uni->type == path_MoveTo ) {
			struct moveTo *move = uni->moveTo;
			thisP[0] = move->XY[0];
			thisP[1] = move->XY[1];
			if ( move->rel ) {
				thisP[0] += lastP[0];
				thisP[1] += lastP[1];
			}
		} else if ( uni->type == path_LineTo ) {
			struct lineTo *line = uni->lineTo;
			thisP[0] = line->XY[0];
			thisP[1] = line->XY[1];
			if ( line->rel ) {
				thisP[0] += lastP[0];
				thisP[1] += lastP[1];
			}
//			draw2dApi->drawSeg ( screenDims, glBuffers, lastP, thisP, colorWhite );
			seg_render ( screenDims, glBuffers, lastP, thisP );
		} else if ( uni->type == path_CubicBez ) {
			struct cubicBez *cBez = uni->cubicBez;
			thisP[0] = cBez->XY[0];
			thisP[1] = cBez->XY[1];

			lastC[0] = cBez->c0[0];
			lastC[1] = cBez->c0[1];

			thisC[0] = cBez->c1[0];
			thisC[1] = cBez->c1[1];

			if ( cBez->rel ) {
				thisP[0] += lastP[0];
				thisP[1] += lastP[1];

				thisC[0] += lastP[0];
				thisC[1] += lastP[1];

				lastC[0] += lastP[0];
				lastC[1] += lastP[1];
			}
			cubicBez_render ( screenDims, glBuffers, lastP, thisP, lastC, thisC );
		} else if ( uni->type == path_CubicBez ) {
		} else if ( path_PathEnd ) {


			float t0[2];
			float t1[2];

			point_to_loc ( lastP, t0 );
			point_to_loc ( startP, t1 );

			draw2dApi->drawSeg ( screenDims, glBuffers, t0, t1, colorWhite );
		}

		if ( start ) {
			startP[0] = thisP[0];
			startP[1] = thisP[1];

			start = 0;
		}

		lastP[0] = thisP[0];
		lastP[1] = thisP[1];

		lastC[0] = thisC[0];
		lastC[1] = thisC[1];

		i += 1;
	}
}

void seg_render ( int *screenDims, GLuint *glBuffers, float *p0, float *p1 ) {
	if ( svg_debugPrint_render ) {
		sayFloatArray ( "p0", p0, 2 );
		sayFloatArray ( "p1", p1, 2 );
	}

	float t0[2];
	float t1[2];

	point_to_loc ( p0, t0 );
	point_to_loc ( p1, t1 );

//	t0[0] = p0[0] * glob_viewScale - glob_viewLoc[0];
//	t0[1] = p0[1] * glob_viewScale  - glob_viewLoc[1];

//	t1[0] = p1[0] * glob_viewScale  - glob_viewLoc[0];
//	t1[1] = p1[1] * glob_viewScale  - glob_viewLoc[1];

//	draw2dApi->drawSeg ( screenDims, glBuffers, p0, p1, colorWhite );
	draw2dApi->drawSeg ( screenDims, glBuffers, t0, t1, colorWhite );
}

void cubicBez_render ( int *screenDims, GLuint *glBuffers, float *p0, float *p1, float *c0, float *c1 ) {
	int points = 10;

	int len = 2;

/*
	float l0[2];
	float l1[2];
	float l2[2];

	// final - initial
	vectSub ( c0, p0, l0, len );	// from p to c
	vectSub ( c1, c0, l1, len );	// from p to c
	vectSub ( p1, c0, l2, len );	// from c to p
*/

	// take 4 points, 3 lines.
	// convert it to 3 points 2 lines.
	// then 2 points 1 line.
	// then 1 point.

	int i;
	i = 0;

/*
	int rect[4];
	rect[2] = 4;
	rect[3] = 4;
*/

	float last[2];
	last[0] = p0[0];
	last[1] = p0[1];

//	last[0] -= glob_viewLoc[0];
//	last[1] -= glob_viewLoc[1];

	point_to_loc ( last, last );

	while ( i < points ) {
		float s = (1.0 / points) * i;

//		printf ( "s: %f\n", s );

//		sayFloatArray ( "p0", p0, len );

		float m0[2];
		float m1[2];
		float m2[2];

		// 3 points 2 lines.
		segScale ( p0, c0, m0, s, len );
		segScale ( c0, c1, m1, s, len );
		segScale ( c1, p1, m2, s, len );
/*
		sayFloatArray ( "m0", m0, len );
		sayFloatArray ( "m1", m1, len );
		sayFloatArray ( "m2", m2, len );
*/
		float c0[2];
		float c1[2];
		segScale ( m0, m1, c0, s, len );
		segScale ( m1, m2, c1, s, len );

		float f[2];
		segScale ( c0, c1, f, s, len );

//		sayFloatArray ( "f", f, 2 );

/*
		rect[0] = f[0];
		rect[1] = f[1];
		draw2dApi->fillRect ( rect, colorWhite, screenDims, glBuffers );
*/
//		f[0] -= glob_viewLoc[0];
//		f[1] -= glob_viewLoc[1];

		point_to_loc ( f, f );

		draw2dApi->drawSeg ( screenDims, glBuffers, last, f, colorWhite );
		last[0] = f[0];
		last[1] = f[1];

/*
		int p = 0;
		while ( p < len ) {
//			rect[0] = 
			draw2dApi->fillRect ( screenDims, glBuffers, lastP, thisP, colorWhite );

			p += 1;
		}
*/

		i += 1;
	}

	float t1[2];
//	t1[0] = p1[0] - glob_viewLoc[0];
//	t1[1] = p1[1] - glob_viewLoc[1];
	point_to_loc ( p1, t1 );
	draw2dApi->drawSeg ( screenDims, glBuffers, last, t1, colorWhite );
}

void segScale ( float *p0, float *p1, float *pSet, float scale, int len ) {
	float v[len];
	vectSub ( p1, p0, v, len );

	int i;
	i = 0;
	while ( i < len ) {
		pSet[i] = p0[i] + v[i] * scale;

		i += 1;
	}
}

ArrayList *testString = NULL;

void textRender ( int *screenDims, GLuint *glBuffers, int *XYWH, struct text *text ) {
	if ( svg_debugPrint_render ) {
		printf ( "textRender ( )\n" );
	}

	// idk what text->x,y is for, when the spans just have their own.
	// maybe for outline and shit? idk.


	if ( !testString ) {
		testString = initArrayList ( 100, sizeof ( char ), 80 );
		char *c = arrayListGetNext ( testString );
//		char ca = *c;
//		ca = 'z';
		*c = 'Z';
	}

	float glyphWH[2];
//	glyphWH[0] = fonts[0]->atlasInfo.glyphW / glob_viewScale;
//	glyphWH[1] = fonts[0]->atlasInfo.glyphH / glob_viewScale;

	float ratio = text->fontSize / fonts[0]->atlasInfo.glyphH;

	glyphWH[0] = fonts[0]->atlasInfo.glyphW * ratio / glob_viewScale;
	glyphWH[1] = fonts[0]->atlasInfo.glyphH * ratio / glob_viewScale;

	float fXYWH[4];
	fXYWH[2] = XYWH[2];
	fXYWH[3] = XYWH[3];

	int i;
	int len;

	i = 0;
	len = arrayListGetLength ( text->spanList );
	while ( i < len ) {
		struct tspan *span = arrayListGetPointer ( text->spanList, i );

//		fXYWH[0] = XYWH[0] + span->x - glob_viewLoc[0];
//		fXYWH[1] = XYWH[1] + span->y - glob_viewLoc[1];
		float tXY[2] = { XYWH[0] + span->x, XYWH[1] + span->y };
		point_to_loc ( tXY, fXYWH );

/*
		int XY[2] = { span->x, span->y };
		XY[0] -= glob_viewLoc[0];
		XY[1] -= glob_viewLoc[1];
		draw2dApi->drawCharPre ( fonts[0], colorWhite );
		draw2dApi->drawString ( screenDims, glBuffers, XY, fonts[0], span->body );
*/

//		spanRender ( screenDims, glBuffers, XYWH, glyphWH, fXYWH, testString );
		spanRender ( screenDims, glBuffers, XYWH, glyphWH, fXYWH, span->stringBuilder );

		i += 1;
	}

}

void spanRender ( int *screenDims, GLuint *glBuffers, int *XYWHpass, float *glyphWH, float *fXYWH, ArrayList *sb ) {
	if ( svg_debugPrint_render ) {
		printf ( "spanRender ( )\n" );
	}

	float viewScale = 1.0 / glob_viewScale;

	float desiredH = glyphWH[1];

	ArrayList *start = sb;
	int startIndex = 0;

	ArrayList *end;
	int endIndex;

	end = start;
	endIndex = startIndex;

	int XYWH[4] = { fXYWH[0], fXYWH[1], fXYWH[2], fXYWH[3] };
	int indentXY[2] = { 0, 0 };

	int tabW = 8;

	while ( 1 ) {
		newSbLine ( start, startIndex, &end, &endIndex );

		XYWH[1] = fXYWH[1];

		draw2dApi->drawCharPre ( fonts[0], colorWhite );

//		draw2dApi->drawStringBuilder ( start, startIndex, end, endIndex, screenDims, glBuffers, font16, subXYWH, tabW );
//		draw2dApi->drawStringBuilderCut ( start, startIndex, end, endIndex, screenDims, glBuffers, fonts[0], XYWH, indentXY, tabW );

		int numFonts = 1;
		draw2dApi->drawStringBuilderCut_scale ( start, startIndex, end, endIndex,
			screenDims, glBuffers, fonts, numFonts, desiredH, XYWH,
			indentXY, tabW );

		// [endIndex] is '\n'
		endIndex += 1;
		if(endIndex >= end->curEles) {
			end = end->next;
			if(!end) {
				// End of string.
				goto afterText;
			}
			endIndex = 0;
		}
		start = end;
		startIndex = endIndex;

		// should this just be XYWH += ?
		fXYWH[1] += glyphWH[1];

/*
		if(i > firstLine + numFullLines) {
			goto afterText;
		}

		i += 1;
*/
	}
	afterText:;

	XYWH[0] = XYWHpass[0];
	XYWH[1] = XYWHpass[1];
	XYWH[2] = 4 * viewScale;
	XYWH[3] = glyphWH[1];

//	drawWhiteCursor ( screenDims, glBuffers, XYWH, slim->cursorStartMem, slim->cursorEndMem, indentXY, glyphWH, colorWhite, firstLine );
}


/** Api Setter */

void set_set_viewScale ( void *f ) {
	setViewScale = f;
}








