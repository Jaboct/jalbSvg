#include "render_svg.h"


/** Variables */

extern struct draw2dStruct *draw2dApi;
extern struct jalbFont *fonts[];

extern float colorWhite[];
extern float colorBlack[];
extern float colorGray[];
extern float colorOrange[];
extern float colorBlue[];

int thisSel = 0;

extern float glob_viewScale;
extern float glob_viewLoc[];

extern char *nakedUni_str[];
extern int nakedUni_str_len;

// editing vars
extern int selected;
extern ArrayList *cursorList;
extern int cursor_depth;

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

	cursor_depth = 0;
	thisSel = 0;
	// check cursor
	int cLen = arrayListGetLength ( cursorList );
	if ( cLen > cursor_depth ) {
		thisSel = 1;
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
	thisSel = 0;
	while ( i < len ) {
		struct nakedUnion *uni = arrayListGetPointer ( eles, i );

		if ( selected &&
		     parentSel ) {
			struct cursorMem *mem = arrayListGetPointer ( cursorList, cursor_depth );
			if ( mem->selI == i ) {
				thisSel = 1;
			}
		}
		cursorDown;

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

		cursorUp;

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

	// first iterate the eles
	i = 0;
	len = arrayListGetLength ( path->eles );

	if ( svg_debugPrint_render ) {
		printf ( "path->eles.len: %d\n", len );
	}

	while ( i < len ) {
		struct pathUni *uni = arrayListGetPointer ( path->eles, i );

		if ( svg_debugPrint_render ) {
			printf ( "uni: %p\n", uni );
			printf ( "uni->type: %d\n", uni->type );
			say_pathUni_type ( uni->type );
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

			if ( line->type == 0 ) {
				thisP[0] = line->XY[0];
				thisP[1] = line->XY[1];
			} else if ( line->type == lineTo_vert ) {
				thisP[0] = lastP[0];
				thisP[1] = line->XY[1];
			} else if ( line->type == lineTo_hor ) {
				thisP[0] = line->XY[0];
				thisP[1] = lastP[1];
			}

			if ( line->rel ) {
				thisP[0] += lastP[0];
				thisP[1] += lastP[1];
			}
//			draw2dApi->drawSeg ( screenDims, glBuffers, lastP, thisP, colorWhite );
			seg_render ( screenDims, glBuffers, lastP, thisP, path->stroke_w,
				glob_viewLoc, glob_viewScale, XYWH );
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
			cubicBez_render ( screenDims, glBuffers, lastP, thisP, lastC, thisC,
				glob_viewLoc, glob_viewScale, XYWH );
		} else if ( uni->type == path_QuadBez ) {
			printf ( "TODO quadBez\n" );

			struct quadBez *quad = uni->quadBez;

			thisP[0] = quad->XY[0];
			thisP[1] = quad->XY[1];

			thisC[0] = quad->control[0];
			thisC[1] = quad->control[1];

			if ( quad->rel ) {
				thisP[0] += lastP[0];
				thisP[1] += lastP[1];

				thisC[0] += lastP[0];
				thisC[1] += lastP[1];

//				lastC[0] += lastP[0];
//				lastC[1] += lastP[1];
			}
			quadBez_render ( screenDims, glBuffers, lastP, thisP, thisC,
				glob_viewLoc, glob_viewScale, XYWH );

		} else if ( uni->type == path_EllipArc ) {
			printf ( "TODO ellipArc\n" );

			struct ellipArc *ellip = uni->ellipArc;

			thisP[0] = ellip->XY[0];
			thisP[1] = ellip->XY[1];

//			seg_render ( screenDims, glBuffers, thisP, lastP, 1,
//				glob_viewLoc, glob_viewScale );

		} else if ( uni->type == path_PathEnd ) {

			float t0[2];
			float t1[2];

			// this doesnt need to be done becasue seg_render does it for me?
			point_to_loc_glob ( lastP, t0 );
			point_to_loc_glob ( startP, t1 );

//			draw2dApi->drawSeg ( screenDims, glBuffers, t0, t1, colorWhite );
			seg_render ( screenDims, glBuffers, t0, t1, path->stroke_w,
				glob_viewLoc, glob_viewScale, XYWH );
		} else {
			printf ( "TODO type unhandled (%d)\n", uni->type );
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

	if ( svg_debugPrint_render ) {
		printf ( "renderMode: %d\n", renderMode );
	}

	if ( renderMode == renderM_editAll ) {
		// if i am in edit mode, then re-iterate the points, and render their edit points.

		if ( svg_debugPrint_render ) {
			printf ( "render edit mode\n" );
		}

	i = 0;
	len = arrayListGetLength ( path->eles );
	if ( svg_debugPrint_render ) {
		printf ( "path->eles.len: %d\n", len );
	}
	while ( i < len ) {
		struct pathUni *uni = arrayListGetPointer ( path->eles, i );

		if ( svg_debugPrint_render ) {
			say_pathUni_type ( uni->type );
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

			if ( line->type == 0 ) {
				thisP[0] = line->XY[0];
				thisP[1] = line->XY[1];
			} else if ( line->type == lineTo_vert ) {
				thisP[0] = lastP[0];
				thisP[1] = line->XY[1];
			} else if ( line->type == lineTo_hor ) {
				thisP[0] = line->XY[0];
				thisP[1] = lastP[1];
			}

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

			float cP0[2];
			float cP1[2];
			point_to_loc_glob ( lastC, cP0 );
			point_to_loc_glob ( thisC, cP1 );

//			int radius = 4 / glob_viewScale;
			int radius = 8;
			int icP0[2] = { cP0[0], cP0[1] };
			int icP1[2] = { cP1[0], cP1[1] };

			// if i have this selected (via cursor) then fillCircle. else just drawCircle
			// TODO, super messy, clean this shit up.
			// use macros. from jalb_macro
			int drawn = 0;
			if ( thisSel ) {
				int cLen = arrayListGetLength ( cursorList );
				if ( cLen > cursor_depth ) {
					struct cursorMem *mem = arrayListGetPointer ( cursorList, cursor_depth );
					if ( mem->selI == i ) {
						cursorDown;
						if ( cLen > cursor_depth ) {
							struct cursorMem *mem = arrayListGetPointer ( cursorList, cursor_depth );
							if ( mem->selI == 0 ) {
								if ( cLen == cursor_depth + 1 ) {
									draw2dApi->fillCircle ( icP0, radius, colorOrange, screenDims, glBuffers );
								}
							}
						}
						cursorUp;
					}
				}
			}

			if ( !drawn ) {
				draw2dApi->drawCircle ( icP0, radius, colorOrange, screenDims, glBuffers );
			}

			drawn = 0;
			if ( thisSel ) {
				int cLen = arrayListGetLength ( cursorList );
				if ( cLen > cursor_depth ) {
					struct cursorMem *mem = arrayListGetPointer ( cursorList, cursor_depth );
					if ( mem->selI == i ) {
						cursorDown;
						if ( cLen > cursor_depth ) {
							struct cursorMem *mem = arrayListGetPointer ( cursorList, cursor_depth );
							if ( mem->selI == 1 ) {
								if ( cLen == cursor_depth + 1 ) {
									draw2dApi->fillCircle ( icP1, radius, colorOrange, screenDims, glBuffers );
								}
							}
						}
						cursorUp;
					}
				}
			}
			if ( !drawn ) {
				draw2dApi->drawCircle ( icP1, radius, colorOrange, screenDims, glBuffers );
			}

//			float t0[2];
//			point_to_loc_glob ( thisP, t0 );

			// viewScale as the width so it remains at 1 regardless of scale.
			seg_render ( screenDims, glBuffers, lastP, lastC, glob_viewScale,
				glob_viewLoc, glob_viewScale, XYWH );

			seg_render ( screenDims, glBuffers, thisP, thisC, glob_viewScale,
				glob_viewLoc, glob_viewScale, XYWH );
		} else if ( uni->type == path_QuadBez ) {
			struct quadBez *quad = uni->quadBez;
			printf ( "TODO quadBez editMode\n" );

			thisP[0] = quad->XY[0];
			thisP[1] = quad->XY[1];

		} else if ( uni->type == path_EllipArc ) {
			printf ( "TODO ellipArc editMode\n" );

			struct ellipArc *ellip = uni->ellipArc;

			thisP[0] = ellip->XY[0];
			thisP[1] = ellip->XY[1];
		} else if ( uni->type == path_PathEnd ) {
			// pathEnd, do nothing now, maybe draw control points.
		} else {
			printf ( "TODO edit mode type unhandled (%d)\n", uni->type );
		}

		float adjP[2];
		point_to_loc_glob ( thisP, adjP );
		int iXYWH[4] = {
			adjP[0],
			adjP[1],
			pointW,
			pointW
		};
		float *color = colorGray;
		if ( thisSel ) {
			int cLen = arrayListGetLength ( cursorList );
			if ( cLen == cursor_depth + 1 ) {
				struct cursorMem *mem = arrayListGetPointer ( cursorList, cursor_depth );
				if ( mem->selI == i ) {
					color = colorOrange;
				}
			}
		}
		// conver this to like, drawPoint, drawEditPoint, or something.
		draw2dApi->fillRect ( iXYWH, color, screenDims, glBuffers );


		lastP[0] = thisP[0];
		lastP[1] = thisP[1];

		lastC[0] = thisC[0];
		lastC[1] = thisC[1];

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

	point_to_loc_glob ( p0, t0 );
	point_to_loc_glob ( p1, t1 );
	draw2dApi->drawSeg ( screenDims, glBuffers, t0, t1, color );

	p0[0] = p1[0];
	p0[1] = p1[1] + rect->height;
	point_to_loc_glob ( p0, t0 );
	draw2dApi->drawSeg ( screenDims, glBuffers, t0, t1, color );

	p1[0] = rect->x;
	p1[1] = rect->y + rect->height;
	point_to_loc_glob ( p1, t1 );
	draw2dApi->drawSeg ( screenDims, glBuffers, t0, t1, color );

	p0[0] = rect->x;
	p0[1] = rect->y;
	point_to_loc_glob ( p0, t0 );
	draw2dApi->drawSeg ( screenDims, glBuffers, t0, t1, color );
}

void circleRender_svg ( int *screenDims, GLuint *glBuffers, int *XYWH, struct circle *circle ) {
	float XY[2] = { circle->cx, circle->cy };
	circleRender ( screenDims, glBuffers, XYWH, XY, circle->r,
		glob_viewLoc, glob_viewScale );
}

void ellipseRender_svg ( int *screenDims, GLuint *glBuffers, int *XYWH, struct ellipse *ellipse ) {
	if ( svg_debugPrint_render ) {
		printf ( "ellipseRender_svg ( )\n" );
	}

	float XY[2] = { ellipse->cx, ellipse->cy };
	ellipseRender ( screenDims, glBuffers, XYWH, XY, ellipse->rx, ellipse->ry,
		glob_viewLoc, glob_viewScale );

	if ( svg_debugPrint_render ) {
		printf ( "ellipseRender_svg ( ) OVER\n" );
	}
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

	float fXYWH[4];
	fXYWH[2] = XYWH[2];
	fXYWH[3] = XYWH[3];

	int i;
	int len;

	i = 0;
	len = arrayListGetLength ( text->spanList );
	while ( i < len ) {
		struct tspan *span = arrayListGetPointer ( text->spanList, i );

		float ratio = span->fontSize / fonts[0]->atlasInfo.glyphH;
		glyphWH[0] = fonts[0]->atlasInfo.glyphW * ratio / glob_viewScale;
		glyphWH[1] = fonts[0]->atlasInfo.glyphH * ratio / glob_viewScale;

//		fXYWH[0] = XYWH[0] + span->x - glob_viewLoc[0];
//		fXYWH[1] = XYWH[1] + span->y - glob_viewLoc[1];

		float tXY[2] = { XYWH[0] + span->x, XYWH[1] + span->y };
//		sayFloatArray ( "tXY", tXY, 2 );

//		point_to_loc_glob ( tXY, fXYWH );
		fXYWH[0] = tXY[0];
		fXYWH[1] = tXY[1];

/*
		int XY[2] = { span->x, span->y };
		XY[0] -= glob_viewLoc[0];
		XY[1] -= glob_viewLoc[1];
		draw2dApi->drawCharPre ( fonts[0], colorWhite );
		draw2dApi->drawString ( screenDims, glBuffers, XY, fonts[0], span->body );
*/

		int selected = 0;
//		spanRender ( screenDims, glBuffers, XYWH, glyphWH, fXYWH, testString );
		spanRender ( screenDims, glBuffers, XYWH, glyphWH, fXYWH, span->stringBuilder,
			selected, NULL, NULL,
			glob_viewLoc, glob_viewScale );

		i += 1;
	}
	if ( svg_debugPrint_render ||
	     svg_debugPrint_render_text ) {
		printf ( "textRender ( ) OVER\n" );
	}
}




