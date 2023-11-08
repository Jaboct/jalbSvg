#include "render_svg.h"


/** Variables */

extern struct draw2dStruct *draw2dApi;
extern struct jalbFont *fonts[];

extern float colorWhite[];
extern float colorBlack[];
extern float colorGray[];
extern float colorOrange[];

int thisSel = 0;

extern float glob_viewScale;

extern char *nakedUni_str[];
extern int nakedUni_str_len;

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

	int parentSel = thisSel;
	while ( i < len ) {
		struct nakedUnion *uni = arrayListGetPointer ( eles, i );

		if ( selected &&
		     parentSel ) {
			struct cursorMem *mem = arrayListGetPointer ( selList, depth );
			if ( mem->selI == i ) {
				thisSel = 1;
			}
		}


		if ( svg_debugPrint_render ) {
			if ( uni->type >= 0 ) {
				if ( uni->type < nakedUni_str_len ) {
					printf ( "%s\n", nakedUni_str[uni->type] );
				} else {
					printf ( "uni->type >= nakedUni_str_len: %d >= %d\n", uni->type, nakedUni_str_len );
				}
			} else {
				printf ( "uni->type: %d\n", uni->type );
			}
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

		} else if ( uni->type == Rect ) {
			struct rect *rect = uni->rect;
			rectRender_svg ( screenDims, glBuffers, XYWH, rect );

		} else if ( uni->type == Circle ) {
			struct circle *circle = uni->circle;
			circleRender_svg ( screenDims, glBuffers, XYWH, circle );

		} else if ( uni->type == Ellipse ) {
			struct ellipse *ellipse = uni->ellipse;
			ellipseRender_svg ( screenDims, glBuffers, XYWH, ellipse );

		}

		i += 1;
	}
	thisSel = parentSel;
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
			seg_render ( screenDims, glBuffers, lastP, thisP, path->stroke_w );
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

//			draw2dApi->drawSeg ( screenDims, glBuffers, t0, t1, colorWhite );
			seg_render ( screenDims, glBuffers, t0, t1, path->stroke_w );
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

	if ( renderMode == renderM_edit ) {
		// if i am in edit mode, then re-iterate the points, and render their edit points.
	i = 0;
	len = arrayListGetLength ( path->eles );
	while ( i < len ) {
		struct pathUni *uni = arrayListGetPointer ( path->eles, i );


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
		}

		float adjP[2];
		point_to_loc ( thisP, adjP );
		int iXYWH[4] = {
			adjP[0],
			adjP[1],
			pointW,
			pointW
		};
		float *color = colorGray;
		if ( thisSel ) {
			struct cursorMem *mem = arrayListGetPointer ( selList, depth );
			if ( mem->selI == i ) {
				color = colorOrange;
			}
		}
		// conver this to like, drawPoint, drawEditPoint, or something.
		draw2dApi->fillRect ( iXYWH, color, screenDims, glBuffers );

		i += 1;
	}
	}

	if ( svg_debugPrint_render ) {
		printf ( "path_render ( ) OVER\n" );
	}
}


void rectRender_svg ( int *screenDims, GLuint *glBuffers, int *XYWH, struct rect *rect ) {

	float *color = colorWhite;

	float p0[2];
	float p1[2];

	p0[0] = rect->x;
	p0[1] = rect->y;

	p1[0] = p0[0] + rect->width;
	p1[1] = p0[1];

	float t0[2];
	float t1[2];

	point_to_loc ( p0, t0 );
	point_to_loc ( p1, t1 );
	draw2dApi->drawSeg ( screenDims, glBuffers, t0, t1, color );

	p0[0] = p1[0];
	p0[1] = p1[1] + rect->height;
	point_to_loc ( p0, t0 );
	draw2dApi->drawSeg ( screenDims, glBuffers, t0, t1, color );

	p1[0] = rect->x;
	p1[1] = rect->y + rect->height;
	point_to_loc ( p1, t1 );
	draw2dApi->drawSeg ( screenDims, glBuffers, t0, t1, color );

	p0[0] = rect->x;
	p0[1] = rect->y;
	point_to_loc ( p0, t0 );
	draw2dApi->drawSeg ( screenDims, glBuffers, t0, t1, color );
}

void circleRender_svg ( int *screenDims, GLuint *glBuffers, int *XYWH, struct circle *circle ) {
	float XY[2] = { circle->cx, circle->cy };
	circleRender ( screenDims, glBuffers, XYWH, XY, circle->r );
}

void ellipseRender_svg ( int *screenDims, GLuint *glBuffers, int *XYWH, struct ellipse *ellipse ) {
}

void textRender ( int *screenDims, GLuint *glBuffers, int *XYWH, struct text *text ) {
	if ( svg_debugPrint_render ||
	     svg_debugPrint_render_text ) {
		printf ( "textRender ( )\n" );
	}

	// idk what text->x,y is for, when the spans just have their own.
	// maybe for outline and shit? idk.

/*
	if ( !testString ) {
		testString = initArrayList ( 100, sizeof ( char ), 80 );
		char *c = arrayListGetNext ( testString );
//		char ca = *c;
//		ca = 'z';
		*c = 'Z';
	}
*/

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
	if ( svg_debugPrint_render ||
	     svg_debugPrint_render_text ) {
		printf ( "textRender ( ) OVER\n" );
	}
}




