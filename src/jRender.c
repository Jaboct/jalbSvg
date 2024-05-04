#include "jRender.h"


/** Variables */

/// modCore

extern char altKeys[];

extern float colorWhite[];
extern float colorOrange[];
extern float colorBlue[];
float colorGrayOpaque[4] = { 0.24, 0.24, 0.24, 0.6 };

extern struct draw2dStruct *draw2dApi;

extern struct jalbFont *fonts[];
extern int numFonts;

/// normal vars

extern int cStart[];
extern int cEnd[];

extern int renderMode;
extern int vert_subMode;

int vertWidth = 10;
extern int controlPointR;


extern int jText_box_width;


extern ArrayList *cursorList;
extern int cursor_depth;

extern int selected;
extern int thisSel;


/// debug

extern int debugPrint_jvg_render;


/** Functions */

void jNakedList_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass, ArrayList *eles,
		float *viewLoc, float viewScale ) {
	if ( debugPrint_jvg_render ) {
		printf ( "jNakedList_render ( )\n" );
		printf ( "thisSel: %d\n", thisSel );
	}

	int i;
	int len;

	i = 0;
	len = arrayListGetLength ( eles );

	if ( debugPrint_jvg_render ) {
		printf ( "eles.len: %d\n", len );
	}

	int parentSel = thisSel;

	while ( i < len ) {
		struct jNakedUnion *uni = arrayListGetPointer ( eles, i );

		if ( debugPrint_jvg_render ) {
			printf ( "uni: %p\n", uni );
			printf ( "uni->type: %d\n", uni->type );
		}

		thisSel = 0;
		isThisSel;

		cursorDown;
		jNaked_render ( screenDims, glBuffers, XYWHpass, uni,
			viewLoc, viewScale );
		cursorUp;

		i += 1;
	}
	thisSel = parentSel;
}

void jNaked_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass, struct jNakedUnion *uni,
		float *viewLoc, float viewScale ) {
	if ( uni->type == jNaked_G ) {
	} else if ( uni->type == jNaked_Path ) {
		struct jPath *path = uni->path;
		jPath_render ( screenDims, glBuffers, XYWHpass, path,
			viewLoc, viewScale );

	} else if ( uni->type == jNaked_Text ) {
		struct jText *text = uni->text;
		jText_render ( screenDims, glBuffers, XYWHpass, text,
			viewLoc, viewScale );

	} else if ( uni->type == jNaked_Circ ) {
		struct jCirc *circ = uni->circ;
		jCircRender ( screenDims, glBuffers, XYWHpass, circ,
			viewLoc, viewScale );
	}
}

void jPath_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass, struct jPath *path,
		float *viewLoc, float viewScale ) {
	if ( debugPrint_jvg_render ) {
		printf ( "jPath_render ( )\n" );
		printf ( "thisSel: %d\n", thisSel );
	}

	int i;
	int len;

	i = 0;
	len = arrayListGetLength ( path->lines );

	if ( debugPrint_jvg_render ) {
		printf ( "lines.len: %d\n", len );
	}

	int thisObjEdit = thisEdit ( thisSel );

	int endArrow = 1;

	// left, right, top, bottom
	float lrtb[4] = { 0, 0, 0, 0 };
	path_lrtb ( path, lrtb );

	while ( i < len ) {
		struct jLine *line = arrayListGetPointer ( path->lines, i );

		struct jVert *v0 = arrayListGetPointer ( path->verts, line->v0 );
		struct jVert *v1 = arrayListGetPointer ( path->verts, line->v1 );

		if ( debugPrint_jvg_render ) {
			sayFloatArray ( "v0->XY", v0->XY, 2 );
			sayFloatArray ( "v1->XY", v1->XY, 2 );
		}

		float lineW = 1.0;
		if ( line->type == path_LineTo ) {
			seg_render ( screenDims, glBuffers, v0->XY, v1->XY, lineW,
				viewLoc, viewScale );

			if ( endArrow ) {
				float vect[2];
				vectSub ( v0->XY, v1->XY, vect, 2 );
				float arrowLen = 10.0;	// maybe do 10 * lineW? so the thicker the line the larger the arrow.
				vectScaleTo ( vect, arrowLen, 2 );
				// rotate this by 15 deg?

				float vFinal[2] = { vect[0], vect[1] };

				rotateVectorXY ( vFinal, M_PI / 6.0 );

				vFinal[0] += v1->XY[0];
				vFinal[1] += v1->XY[1];
				seg_render ( screenDims, glBuffers, v1->XY, vFinal, lineW,
					viewLoc, viewScale );

				vFinal[0] = vect[0];
				vFinal[1] = vect[1];

				rotateVectorXY ( vFinal, -M_PI / 6.0 );

				vFinal[0] += v1->XY[0];
				vFinal[1] += v1->XY[1];
				seg_render ( screenDims, glBuffers, v1->XY, vFinal, lineW,
					viewLoc, viewScale );
			}

		} else if ( line->type == path_CubicBez ) {
			cubicBez_render ( screenDims, glBuffers, v0->XY, v1->XY, line->c0, line->c1,
				viewLoc, viewScale );
		} else if ( line->type == path_QuadBez ) {
			quadBez_render ( screenDims, glBuffers, v0->XY, v1->XY, line->c0,
				viewLoc, viewScale );
		}

		i += 1;
	}

	if ( thisObjEdit ) {
		// render a bounding box.
		// scale the reft accordinly.

//		sayFloatArray ( "lrtb", lrtb, 4 );

		float XYWH[4] = { lrtb[0], lrtb[2] };
		point_to_loc ( XYWH, XYWH, viewLoc, viewScale );
		XYWH[2] = (lrtb[1] - lrtb[0]) / viewScale;
		XYWH[3] = (lrtb[3] - lrtb[2]) / viewScale;

		draw2dApi->drawRectF ( XYWH, colorGrayOpaque, screenDims, glBuffers );

		if ( vert_subMode == vSubM_move ) {
			// draw red for scale.
			float subXYWH[4];
			int boxW = 10;
			subXYWH[0] = XYWH[0] - boxW / 2;
			subXYWH[1] = XYWH[1] - boxW / 2;
			subXYWH[2] = boxW;
			subXYWH[3] = boxW;

			// top left
			draw2dApi->drawRectF ( subXYWH, colorOrange, screenDims, glBuffers );

			// top right
			subXYWH[0] += XYWH[2];
			draw2dApi->drawRectF ( subXYWH, colorOrange, screenDims, glBuffers );

			// bot right
			subXYWH[1] += XYWH[3];
			draw2dApi->drawRectF ( subXYWH, colorOrange, screenDims, glBuffers );

			// bot left
			subXYWH[0] = XYWH[0] - boxW / 2;
			draw2dApi->drawRectF ( subXYWH, colorOrange, screenDims, glBuffers );
		}
	}


	if ( thisObjEdit ) {
//		int cursorLen = arrayListGetLength ( cursorList );
//		printf ( "cursorLen: %d\n", cursorLen );
//		printf ( "cursor_depth: %d\n", cursor_depth );

		jVerts_render ( screenDims, glBuffers, XYWHpass, path->verts,
			viewLoc, viewScale );
		controlPoints_render ( screenDims, glBuffers, XYWHpass, path,
			viewLoc, viewScale );
	}
}

// i want to pass cursorInfo to this...
void jVerts_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass, ArrayList *verts,
		float *viewLoc, float viewScale ) {
	int i;
	int len;

	int parentSel = thisSel;

	i = 0;
	len = arrayListGetLength ( verts );

	while ( i < len ) {
		struct jVert *vert = arrayListGetPointer ( verts, i );

		thisSel = 0;
		isThisSel;
		isThisIt;

		float XYWH[4];
		point_to_loc ( vert->XY, XYWH, viewLoc, viewScale );

		XYWH[0] -= vertWidth / 2;
		XYWH[1] -= vertWidth / 2;
		XYWH[2] = vertWidth;
		XYWH[3] = vertWidth;
		int iXYWH[4] = { XYWH[0], XYWH[1], XYWH[2], XYWH[3] };

		if ( thisSel ) {
			draw2dApi->fillRect ( iXYWH, colorWhite, screenDims, glBuffers );
		} else {
			draw2dApi->drawRect ( iXYWH, colorWhite, screenDims, glBuffers );
		}

		i += 1;
	}

	thisSel = parentSel;
}

// should this be in the same funct as jVerts_render?
void controlPoints_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass, struct jPath *path,
		float *viewLoc, float viewScale ) {
	int i;
	int len;

	int parentSel = thisSel;

	i = 0;
	len = arrayListGetLength ( path->lines );

	while ( i < len ) {
		struct jLine *line = arrayListGetPointer ( path->lines, i );

		thisSel = 0;
		isThisSel;
		int parentSel = thisSel;
		cursorDown;

		struct jVert *v0 = arrayListGetPointer ( path->verts, line->v0 );
		struct jVert *v1 = arrayListGetPointer ( path->verts, line->v1 );

		if ( line->type == path_CubicBez ) {
			// render 2 control points

			thisSel = 0;
			{
				int i = 0;
				isThisSel;
				isThisIt;
			}

			float cp0[2];
			point_to_loc ( line->c0, cp0, viewLoc, viewScale );
			int icp0[2] = { cp0[0], cp0[1] };

			float cp1[2];
			point_to_loc ( line->c1, cp1, viewLoc, viewScale );
			int icp1[2] = { cp1[0], cp1[1] };


			int diameter = controlPointR * 2;

			if ( thisSel ) {
				draw2dApi->fillCircle ( icp0, diameter, colorWhite, screenDims, glBuffers );
			} else {
				draw2dApi->drawCircle ( icp0, diameter, colorWhite, screenDims, glBuffers );
			}

			// draw a line
			seg_render ( screenDims, glBuffers, v0->XY, line->c0, viewScale,
				viewLoc, viewScale );

			thisSel = 0;
			{
				int i = 1;
				isThisSel;
				isThisIt;
			}
			if ( thisSel ) {
				draw2dApi->fillCircle ( icp1, diameter, colorWhite, screenDims, glBuffers );
			} else {
				draw2dApi->drawCircle ( icp1, diameter, colorWhite, screenDims, glBuffers );
			}

			// draw a line
			seg_render ( screenDims, glBuffers, v1->XY, line->c1, viewScale,
				viewLoc, viewScale );
		} else if ( line->type == path_QuadBez ) {
			// render 1 control point.
		}

//		thisSel = parentSel;
		cursorUp;

		i += 1;
	}
}


void jText_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass, struct jText *text,
		float *viewLoc, float viewScale ) {
	if ( debugPrint_jvg_render ) {
		printf ( "jText_render ( )\n" );
	}

	float XYWH[4];
	point_to_loc ( text->XYWH, XYWH, viewLoc, viewScale );
	XYWH[0] += XYWHpass[0];
	XYWH[1] += XYWHpass[1];

	XYWH[2] = text->XYWH[2] / viewScale;
	XYWH[3] = text->XYWH[3] / viewScale;

	float glyphWH[2];
	glyphWH[0] = fonts[0]->atlasInfo.glyphW / viewScale;
	glyphWH[1] = fonts[0]->atlasInfo.glyphH / viewScale;

	float tempXYWH[4] = { text->XYWH[0], text->XYWH[1], text->XYWH[2], text->XYWH[3] };

	int drawCursor = 0;
	if ( thisSel ) {
		drawCursor = 1;
	}

/*
	if ( tempXYWH[0] > XYWHpass[2] ||	// off to the right
	     tempXYWH[1] > XYWHpass[1] ||	// off below
	     tempXYWH[0] + tempXYWH[2] < 0 ||	// off to the left.
	     tempXYWH[1] + tempXYWH[3] < 0 ) {	// off above
		printf ( "text off screen\n" );
		return;
	}
*/

//	spanRender ( screenDims, glBuffers, XYWHpass, glyphWH, XYWH, text->sb,
	spanRender ( screenDims, glBuffers, XYWHpass, glyphWH, tempXYWH, text->sb,
		drawCursor, cStart, cEnd,
		viewLoc, viewScale );

	int thisObjEdit = thisEdit ( thisSel );

//	if ( renderMode == renderM_editAll ) {
	if ( thisObjEdit ) {
		// draw the white edit box around the text.
		int iXYWH[4] = { XYWH[0], XYWH[1], XYWH[2], XYWH[3] };
		draw2dApi->drawRect ( iXYWH, colorWhite, screenDims, glBuffers );

		if ( thisSel ) {
			// draw the bar at the top
			iXYWH[1] -= (jText_box_width / viewScale);
			iXYWH[3] = (jText_box_width / viewScale);
			draw2dApi->drawRect ( iXYWH, colorBlue, screenDims, glBuffers );
		}

		// how do i determine if i am currently dragging this ele.
		int expanding = 0;
		// ok, so i also need to see if the enxt cursor is of type5.
		if ( thisSel ) {
//			printf ( "Cursor_depth: %d\n", cursor_depth );
//			sayCursor;

			int i = 5;
			int parentSel = thisSel;
			thisSel = 0;
			isThisSel;
			if ( thisSel ) {
				expanding = 1;
			}
		}

		// draw a little expand point in the bottom right.
		iXYWH[0] += iXYWH[2];
//		iXYWH[1] += iXYWH[3];
		iXYWH[1] = XYWH[1] + XYWH[3];

		iXYWH[2] = 10 / viewScale;
		iXYWH[3] = 10 / viewScale;
		if ( expanding ) {
			draw2dApi->fillRect ( iXYWH, colorOrange, screenDims, glBuffers );
		} else {
			draw2dApi->drawRect ( iXYWH, colorOrange, screenDims, glBuffers );
		}
	}

	if ( debugPrint_jvg_render ) {
		printf ( "jText_render ( ) OVER\n" );
	}
}

void jCircRender ( int *screenDims, GLuint *glBuffers, int *XYWHpass, struct jCirc *circ,
		float *viewLoc, float viewScale ) {
//	printf ( "jCircRender ( )\n" );

	float screenXY[2];
	point_to_loc ( circ->XY, screenXY, viewLoc, viewScale );

	float diameter = circ->radius / viewScale * 2;

	int iXY[2] = { screenXY[0], screenXY[1] };
	draw2dApi->drawCircle ( iXY, diameter, colorWhite, screenDims, glBuffers );
}


/** Util */

void path_lrtb ( struct jPath *path, float *lrtb ) {
//	printf ( "path_lrtb ( )\n" );

	int i;
	int len;
	i = 0;
	len = arrayListGetLength ( path->verts );
	while ( i < len ) {
		struct jVert *v = arrayListGetPointer ( path->verts, i );

		if ( i == 0 ) {
			lrtb[0] = v->XY[0];
			lrtb[1] = v->XY[0];
			lrtb[2] = v->XY[1];
			lrtb[3] = v->XY[1];
		}

		// check left right.
		if ( v->XY[0] < lrtb[0] ) {
			lrtb[0] = v->XY[0];
		} else if ( v->XY[0] > lrtb[1] ) {
			lrtb[1] = v->XY[0];
		}

		// check top bottom.
		if ( v->XY[1] < lrtb[2] ) {
			lrtb[2] = v->XY[1];
		} else if ( v->XY[1] > lrtb[3] ) {
			lrtb[3] = v->XY[1];
		}

		i += 1;
	}
}




