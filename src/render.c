#include "render.h"

/** Vars */

extern int nakedUni_str_len;
extern char *nakedUni_str[];


extern struct draw2dStruct *draw2dApi;
extern struct jalbFont *fonts[];
extern int numFonts;

extern float colorWhite[];
extern float colorBlack[];
extern float colorOrange[];
extern float colorGray[];

// rendering var
//extern float glob_viewScale;

// editing vars
extern int selected;
extern ArrayList *selList;
extern int depth;

extern int renderMode;
extern int pointW;

// debug vars
extern int svg_debugPrint_render;
extern int svg_debugPrint_render_text;

/** Functions */


void seg_render ( int *screenDims, GLuint *glBuffers, float *p0, float *p1, float lineW,
		float *viewLoc, float viewScale ) {
	if ( svg_debugPrint_render ) {
		printf ( "seg_render ( )\n" );

		sayFloatArray ( "p0", p0, 2 );
		sayFloatArray ( "p1", p1, 2 );
	}

	float t0[2];
	float t1[2];

	point_to_loc ( p0, t0, viewLoc, viewScale );
	point_to_loc ( p1, t1, viewLoc, viewScale );

//	draw2dApi->drawSeg ( screenDims, glBuffers, t0, t1, colorWhite );

	float vect[2];
	vectSub ( t0, t1, vect, 2 );

	sayFloatArray ( "vect pre", vect, 2 );
	float temp = vect[0];
	vect[0] = -vect[1];
	vect[1] = temp;
	sayFloatArray ( "vect swap", vect, 2 );


	lineW /= viewScale;
	if ( lineW < 1.0 ) {
		lineW = 1.0;
	}


	vectNormalize ( vect, 2 );
	vectMultScalar ( vect, lineW, 2 );

	sayFloatArray ( "vect", vect, 2 );

	float verts[2 * 4];
	verts[0] = t0[0] + vect[0];
	verts[1] = t0[1] + vect[1];

	verts[2] = t0[0] - vect[0];
	verts[3] = t0[1] - vect[1];

	verts[4] = t1[0] + vect[0];
	verts[5] = t1[1] + vect[1];

	verts[6] = t1[0] - vect[0];
	verts[7] = t1[1] - vect[1];

	int numVerts = 4;
	draw2dApi->drawTriangleStrip ( verts, numVerts, colorWhite, screenDims, glBuffers );

	if ( svg_debugPrint_render ) {
		printf ( "seg_render ( ) OVER\n" );
	}
}

void cubicBez_render ( int *screenDims, GLuint *glBuffers, float *p0, float *p1, float *c0, float *c1,
		float *viewLoc, float viewScale ) {
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

	point_to_loc ( last, last, viewLoc, viewScale );

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

		point_to_loc ( f, f, viewLoc, viewScale );

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
	point_to_loc ( p1, t1, viewLoc, viewScale );
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

void spanRender ( int *screenDims, GLuint *glBuffers, int *XYWHpass, float *glyphWH, float *fXYWH, ArrayList *sb,
		float *viewLoc, float viewScale ) {
	if ( svg_debugPrint_render ||
	     svg_debugPrint_render_text ) {
		printf ( "spanRender ( )\n" );
//		printf ( "span->body: (%s)\n", span->body );
		sayFloatArray ( "glyphWH", glyphWH, 2 );
		printSb ( sb );
	}

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
	XYWH[2] = 4 / viewScale;
	XYWH[3] = glyphWH[1];

//	drawWhiteCursor ( screenDims, glBuffers, XYWH, slim->cursorStartMem, slim->cursorEndMem, indentXY, glyphWH, colorWhite, firstLine );

	if ( svg_debugPrint_render ||
	     svg_debugPrint_render_text ) {
		printf ( "spanRender ( ) OVER\n" );
	}
}

void rectRender ( int *screenDims, GLuint *glBuffers, int *XYWH, float *rXYWH,
		float *viewLoc, float viewScale ) {

	float *color = colorWhite;

	float p0[2];
	float p1[2];

	p0[0] = rXYWH[0];
	p0[1] = rXYWH[1];

	p1[0] = p0[0] + rXYWH[2];
	p1[1] = p0[1];

	float t0[2];
	float t1[2];

	point_to_loc ( p0, t0, viewLoc, viewScale );
	point_to_loc ( p1, t1, viewLoc, viewScale );
	draw2dApi->drawSeg ( screenDims, glBuffers, t0, t1, color );

	p0[0] = p1[0];
	p0[1] = p1[1] + rXYWH[3];
	point_to_loc ( p0, t0, viewLoc, viewScale );
	draw2dApi->drawSeg ( screenDims, glBuffers, t0, t1, color );

	p1[0] = rXYWH[0];
	p1[1] = rXYWH[1] + rXYWH[3];
	point_to_loc ( p1, t1, viewLoc, viewScale );
	draw2dApi->drawSeg ( screenDims, glBuffers, t0, t1, color );

	p0[0] = rXYWH[0];
	p0[1] = rXYWH[1];
	point_to_loc ( p0, t0, viewLoc, viewScale );
	draw2dApi->drawSeg ( screenDims, glBuffers, t0, t1, color );
}

void circleRender ( int *screenDims, GLuint *glBuffers, int *XYWH, float *XY, float r,
		float *viewLoc, float viewScale ) {
//	printf ( "circle->r: %f\n", circle->r );

	float p0[2];
	float p1[2];
	float c0[2];
	float c1[2];

//	float ratio = 0.5;
//	float ratio = 0.66;
	float ratio = 0.5522;

	// top left
	p0[0] = XY[0] - r;
	p0[1] = XY[1];

	p1[0] = XY[0];
	p1[1] = XY[1] - r;

	c0[0] = XY[0] - r;
	c0[1] = XY[1] - r * ratio;

	c1[0] = XY[0] - r * ratio;
	c1[1] = XY[1] - r;

	cubicBez_render ( screenDims, glBuffers, p0, p1, c0, c1,
		viewLoc, viewScale );

	// top right (+x)
	p0[0] = XY[0] + r;
	p0[1] = XY[1];

	p1[0] = XY[0];
	p1[1] = XY[1] - r;

	c0[0] = XY[0] + r;
	c0[1] = XY[1] - r * ratio;

	c1[0] = XY[0] + r * ratio;
	c1[1] = XY[1] - r;

	cubicBez_render ( screenDims, glBuffers, p0, p1, c0, c1,
		viewLoc, viewScale );


	// bottom right (+x +y)
	p0[0] = XY[0] + r;
	p0[1] = XY[1];

	p1[0] = XY[0];
	p1[1] = XY[1] + r;

	c0[0] = XY[0] + r;
	c0[1] = XY[1] + r * ratio;

	c1[0] = XY[0] + r * ratio;
	c1[1] = XY[1] + r;

	cubicBez_render ( screenDims, glBuffers, p0, p1, c0, c1,
		viewLoc, viewScale );


	// bottom left (-x +y)
	p0[0] = XY[0] - r;
	p0[1] = XY[1];

	p1[0] = XY[0];
	p1[1] = XY[1] + r;

	c0[0] = XY[0] - r;
	c0[1] = XY[1] + r * ratio;

	c1[0] = XY[0] - r * ratio;
	c1[1] = XY[1] + r;

	cubicBez_render ( screenDims, glBuffers, p0, p1, c0, c1,
		viewLoc, viewScale );
}

//void ellipseRender ( int *screenDims, GLuint *glBuffers, int *XYWH, struct ellipse *ellipse ) {
//}

















