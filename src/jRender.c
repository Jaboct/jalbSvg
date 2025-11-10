#include "jRender.h"


/** Includes */

#include "jGroup.h"
#include "jPath.h"
#include "jText.h"

#include "path.h"	// for enums
#include "mod_ext.h"	// for enums
#include "render.h"

#include "cursor.h"
#include "hover.h"

#include "api/structStruct.h"


/** Variables */

/// modCore

extern char altKeys[];

extern float colorWhite[];
extern float colorOrange[];
extern float colorBlue[];
float colorGrayOpaque[4] = { 0.24, 0.24, 0.24, 0.6 };
float colorLightGrayOpaque[4] = { 0.6, 0.6, 0.6, 0.6 };

extern struct draw2dStruct *draw2dApi;

extern struct jalbFont *fonts[];
extern int numFonts;


/// Global vars

extern struct jvg *glob_jvg;

int renderCAD = 0;

int gridRender = 0;
int gridSnap = 0;
float gridWH[2] = { 100, 100 };


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

// i generally use squares for control point.
int controlPointWidth = 10;


/// NEW cursor globals

extern int hoverIndex_render;
extern struct cursor_ele *hoverMem;
// TEMP, instead of passing through the params i just keep it global for now.
// also used in event, it is filled on the way down.
extern struct cursor_ele *temp_hoverMem;

extern struct cursor_ele *glob_cursor_ele;

struct cursor_ele *temp_actualMem = NULL;	// actually selected cursor eles
extern int isHover;
int render_hoverPayload = 0;
int render_actualPayload = 0;
extern ArrayList *cursorList_new;	// (struct cursor_ele*)
int render_cursorDepth = 0;


/// debug

extern int debugPrint_jvg_render;
int debugPrint_jvg_complex_render = 0;


/** Functions */

void jNakedList_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass, ArrayList *eles,
		float *viewLoc, float viewScale ) {
	if ( debugPrint_jvg_render ) {
		printf ( "jNakedList_render ( )\n" );
		printf ( "thisSel: %d\n", thisSel );
	}

//	printf ( "jNakedList_render ( )\n" );

	int i;
	int len;

	i = 0;
	len = arrayListGetLength ( eles );

	if ( debugPrint_jvg_render ) {
		printf ( "eles.len: %d\n", len );
	}

	int parentSel = thisSel;

//	render_hoverPayload = 0;

	render_actualPayload = 0;
	struct cursor_ele *mem_cursor = temp_actualMem;
	struct cursor_ele *mem_hover = temp_hoverMem;

/*
	printf ( "mem_cursor: %p\n", mem_cursor );
	printf ( "mem_cursor.len: %d\n", arrayListGetLength ( mem_cursor->payload->group->eles ) );
	say_cursor_ele ( mem_cursor );
*/

	if ( temp_hoverMem ) {
//		printf ( "\n" );
//		printf ( "temp_hoverMem\n" );
//		say_cursor_ele ( temp_hoverMem );
//		printf ( "\n" );
	}

	while ( i < len ) {
		struct jNakedUnion *uni = arrayListGetPointer ( eles, i );

		if ( debugPrint_jvg_render ) {
			printf ( "uni: %p\n", uni );
			printf ( "uni->type: %d\n", uni->type );
		}

		// old cursor check
		thisSel = 0;
		isThisSel;

//		printf ( "mem_hover: %p\n", mem_hover );

		// new HOVER cursor check
		if ( mem_hover ) {
			ArrayList *eleList_new = mem_hover->payload->group->eles;
			// mem_hover->index is irrelevent.

			// search through eleList_new, to see if it contains an elemet with ->index = i
			int subIndex = eleList_getIndex ( eleList_new, i );
			if ( subIndex != -1 ) {
				// dont necessarily render payload...
				// keep checking as you go down
				// temp_hoverMem = tempHoverMem->payload;

//				render_hoverPayload = 1;
				temp_hoverMem = arrayListGetPointer ( eleList_new, subIndex );
			} else {
				temp_hoverMem = NULL;
			}
/*
			int len = arrayListGetLength ( temp_hoverMem->address );
			if ( hoverIndex_render < len ) {
				int *hoverArr = arrayListDataPointer ( temp_hoverMem->address, hoverIndex_render );
				if ( *hoverArr == i ) {
					// this subEle is selected

					if ( hoverIndex_render == len - 1 ) {
						// send down the payload.
//						printf ( "send down payload\n" );
						render_payload = 1;
					}
				}
			}
*/
		}

		// new ACTUAL cursor check
		// mem_cursor->index has already been matched, and we know mem_cursor is a group.
		if ( mem_cursor ) {
			ArrayList *eleList_new = mem_cursor->payload->group->eles;
			// does it contain an ele relevent to this index?
			int subIndex = eleList_getIndex ( eleList_new, i );
//			printf ( "subIndex: %d\n", subIndex );
			if ( subIndex != -1 ) {
				// it does.
				temp_actualMem = arrayListGetPointer ( eleList_new, subIndex );
				// now for all subEles deal with temp_actualMem.
				// but once it gets back to the next ele of this list, it will revert to mem_cursor.
			} else {
				// no subEles match.
				temp_actualMem = NULL;
			}
		}

		cursorDown;
		jNaked_render ( screenDims, glBuffers, XYWHpass, uni,
			viewLoc, viewScale );
		cursorUp;

		i += 1;
	}

	temp_actualMem = mem_cursor;
	temp_hoverMem = mem_hover;

	thisSel = parentSel;
}

void jNaked_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass, struct jNakedUnion *uni,
		float *viewLoc, float viewScale ) {
	if ( debugPrint_jvg_render ) {
		printf ( "jNaked_render ( )\n" );
		printf ( "uni->type: %d\n", uni->type );
	}

	if ( uni->type == jNaked_G ) {
/*
		printf ( "TODO group\n" );
		if ( temp_actualMem->payload->type == cu_Group ) {
			temp_actualMem = temp_actualMem->payload->group->
			// this gets handled elsewhere?
		} else {
			printf ( "ERROR\n" );
		}
*/
	} else if ( uni->type == jNaked_Path ) {
		struct jPath *path = uni->path;
		jPath_render ( screenDims, glBuffers, XYWHpass, path,
			viewLoc, viewScale );

	} else if ( uni->type == jNaked_Text ) {
		struct jText *text = uni->text;
		jText_render ( screenDims, glBuffers, XYWHpass, text,
			viewLoc, viewScale );

	} else if ( uni->type == jNaked_Rect ) {
		struct jRect *rect = uni->rect;
		jRectRender ( screenDims, glBuffers, XYWHpass, rect,
			viewLoc, viewScale );

	} else if ( uni->type == jNaked_Circ ) {
		struct jCirc *circ = uni->circ;
		jCircRender ( screenDims, glBuffers, XYWHpass, circ,
			viewLoc, viewScale );

	} else if ( uni->type == jNaked_Complex ) {
		struct complexEle *complex = uni->complex;
		complexEleRender ( screenDims, glBuffers, XYWHpass, complex,
			viewLoc, viewScale );
	}
}

void jPath_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass, struct jPath *path,
		float *viewLoc, float viewScale ) {
	if ( debugPrint_jvg_render ) {
		printf ( "jPath_render ( )\n" );
		printf ( "thisSel: %d\n", thisSel );
	}

/*
	printf ( "jPath_render ( )\n" );
	printf ( "temp_actualMem: %p\n", temp_actualMem );
*/

	int i;
	int len;

	i = 0;
	len = arrayListGetLength ( path->lines );

	if ( debugPrint_jvg_render ) {
		printf ( "lines.len: %d\n", len );
	}

	int thisObjEdit = thisEdit ( thisSel );

//	int endArrow = 1;

	// left, right, top, bottom
	// to draw the bounding box.
	float lrtb[4] = { 0, 0, 0, 0 };
	path_lrtb ( path, lrtb );

	// first draw the line segments.
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
				viewLoc, viewScale, XYWHpass );

//			if ( endArrow ) {
			if ( line->markerEnd == lineMark_arrow ) {
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
					viewLoc, viewScale, XYWHpass );

				vFinal[0] = vect[0];
				vFinal[1] = vect[1];

				rotateVectorXY ( vFinal, -M_PI / 6.0 );

				vFinal[0] += v1->XY[0];
				vFinal[1] += v1->XY[1];
				seg_render ( screenDims, glBuffers, v1->XY, vFinal, lineW,
					viewLoc, viewScale, XYWHpass );
			}

		} else if ( line->type == path_CubicBez ) {
			cubicBez_render ( screenDims, glBuffers, v0->XY, v1->XY, line->c0, line->c1,
				viewLoc, viewScale, XYWHpass );
		} else if ( line->type == path_QuadBez ) {
			quadBez_render ( screenDims, glBuffers, v0->XY, v1->XY, line->c0,
				viewLoc, viewScale, XYWHpass );
		}

		i += 1;
	}

	if ( thisObjEdit ) {
		// render a bounding box.
		// scale the reft accordinly.

//		sayFloatArray ( "lrtb", lrtb, 4 );

		float XYWH[4] = { lrtb[0], lrtb[2] };
		point_to_loc ( XYWH, XYWH, viewLoc, viewScale );
		XYWH[0] += XYWHpass[0];
		XYWH[1] += XYWHpass[1];

		XYWH[2] = (lrtb[1] - lrtb[0]) / viewScale;
		XYWH[3] = (lrtb[3] - lrtb[2]) / viewScale;

		draw2dApi->drawRectF ( XYWH, colorGrayOpaque, screenDims, glBuffers );

		if ( vert_subMode == vSubM_move ) {
			// draw red for scale.
			float subXYWH[4];
			int boxW = controlPointWidth;
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

	// render the verts and control points

	if ( thisObjEdit ) {
//		int cursorLen = arrayListGetLength ( cursorList );
//		printf ( "cursorLen: %d\n", cursorLen );
//		printf ( "cursor_depth: %d\n", cursor_depth );

		jVerts_render ( screenDims, glBuffers, XYWHpass, path->verts,
			viewLoc, viewScale );
		controlPoints_render ( screenDims, glBuffers, XYWHpass, path,
			viewLoc, viewScale );
	}

	if ( renderCAD ) {
		// render the vert info.
		verts_CAD_render ( screenDims, glBuffers, XYWHpass, path->verts,
			viewLoc, viewScale );
		lines_CAD_render ( screenDims, glBuffers, XYWHpass, path,
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

		int thisHover = 0;
		thisSel = 0;
		isThisSel;
		isThisIt;

//		if ( render_hoverPayload ) {
		if ( temp_hoverMem ) {
			struct cursor_ele *ele = temp_hoverMem;
			// todo type check
			if ( ele->payload->type == cu_Path ) {
				struct cursor_path *cuPath = ele->payload->path;
				if ( cuPath->itself ) {
					// ignore the verts
				} else {
					int has = al_hasInt ( cuPath->verts, i );
					if ( has ) {
//						thisSel = 1;
						thisHover = 1;
					}
				}
			} else {
				printf ( "HOVER ELE MISMATCH\n" );
			}
		}

		if ( temp_actualMem ) {
			struct cursor_ele *ele = temp_actualMem;
			// todo type check
			if ( ele->payload->type == cu_Path ) {
				struct cursor_path *cuPath = ele->payload->path;
				if ( cuPath->itself ) {
					// ignore the verts
				} else {
					int has = al_hasInt ( cuPath->verts, i );
					if ( has ) {
						thisSel = 1;
					}
				}
			} else {
				printf ( "ACTUAL ELE MISMATCH\n" );
				printf ( "glob\n" );
				say_cursor_ele ( glob_cursor_ele );
				printf ( "actual\n" );
				say_cursor_ele ( temp_actualMem );
			}
		}

/*
		if ( render_actualPayload ) {
			struct cursor_ele *ele = temp_actualMem;
			if ( ele->payload->type == cu_Path ) {
		}
*/

		float XYWH[4];
		point_to_loc ( vert->XY, XYWH, viewLoc, viewScale );
		XYWH[0] += XYWHpass[0];
		XYWH[1] += XYWHpass[1];

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

		if ( thisHover ) {
			draw2dApi->drawRect ( iXYWH, colorOrange, screenDims, glBuffers );
			// shitty way of making it 2 px wide.
			iXYWH[0] -= 1;
			iXYWH[1] -= 1;
			iXYWH[2] += 1;
			iXYWH[3] += 1;
			draw2dApi->drawRect ( iXYWH, colorOrange, screenDims, glBuffers );
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
			cp0[0] += XYWHpass[0];
			cp0[1] += XYWHpass[1];
			int icp0[2] = { cp0[0], cp0[1] };

			float cp1[2];
			point_to_loc ( line->c1, cp1, viewLoc, viewScale );
			cp1[0] += XYWHpass[0];
			cp1[1] += XYWHpass[1];
			int icp1[2] = { cp1[0], cp1[1] };


			int diameter = controlPointR * 2;

			if ( thisSel ) {
				draw2dApi->fillCircle ( icp0, diameter, colorWhite, screenDims, glBuffers );
			} else {
				draw2dApi->drawCircle ( icp0, diameter, colorWhite, screenDims, glBuffers );
			}

			// draw a line
			seg_render ( screenDims, glBuffers, v0->XY, line->c0, viewScale,
				viewLoc, viewScale, XYWHpass );

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
				viewLoc, viewScale, XYWHpass );
		} else if ( line->type == path_QuadBez ) {
			// render 1 control point.
		}

//		thisSel = parentSel;
		cursorUp;

		i += 1;
	}
}

void verts_CAD_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass, ArrayList *verts,
		float *viewLoc, float viewScale ) {

	struct jalbFont *font = fonts[0];

	int i = 0;
	int len = arrayListGetLength ( verts );
	while ( i < len ) {
		struct jVert *vert = arrayListGetPointer ( verts, i );

		float charXY[2] = {
			0,
			0,
		};
		point_to_loc ( vert->XY, charXY, viewLoc, viewScale );

		char buffer[256];
		sprintf ( buffer, "{ %f, %f }", vert->XY[0], vert->XY[1] );

		int slen = strlen ( buffer );

		float fXYWH[4] = {
			charXY[0],
			charXY[1],
			font->atlasInfo.glyphW * slen,
			font->atlasInfo.glyphH,
		};

		draw2dApi->drawCharPre ( font, colorWhite );
		draw2dApi->drawStringBounded ( screenDims, glBuffers, charXY,
			fXYWH, font, buffer );

		i += 1;
	}
}

void lines_CAD_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass, struct jPath *path,
		float *viewLoc, float viewScale ) {

	struct jalbFont *font = fonts[0];

	int i = 0;
	int len = arrayListGetLength ( path->lines );
	while ( i < len ) {
		struct jLine *line = arrayListGetPointer ( path->lines, i );
		struct jVert *v0 = arrayListGetPointer ( path->verts, line->v0 );
		struct jVert *v1 = arrayListGetPointer ( path->verts, line->v1 );

		float centerPoint[2] = {
			(v0->XY[0] + v1->XY[0]) / 2.0,
			(v0->XY[1] + v1->XY[1]) / 2.0,
		};

		sayFloatArray ( "centerPoint", centerPoint, 2 );

		float delta[2] = {
			v0->XY[0] - v1->XY[0],
			v0->XY[1] - v1->XY[1],
		};
		float l = vectNorm ( delta, 2 );

		float charXY[2] = {
			0,
			0,
		};
		point_to_loc ( centerPoint, charXY, viewLoc, viewScale );

		char buffer[256];
		sprintf ( buffer, "%f", l );

		printf ( "buffer: %s\n", buffer );

		int slen = strlen ( buffer );

		float fXYWH[4] = {
			charXY[0],
			charXY[1],
			font->atlasInfo.glyphW * slen,
			font->atlasInfo.glyphH,
		};

		draw2dApi->drawCharPre ( font, colorWhite );
		draw2dApi->drawStringBounded ( screenDims, glBuffers, charXY,
			fXYWH, font, buffer );

		i += 1;
	}
}

/// text

void jText_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass, struct jText *text,
		float *viewLoc, float viewScale ) {
	float XYWH[4];
	point_to_loc ( text->XYWH, XYWH, viewLoc, viewScale );

	XYWH[0] += XYWHpass[0];
	XYWH[1] += XYWHpass[1];

	XYWH[2] = text->XYWH[2] / viewScale;
	XYWH[3] = text->XYWH[3] / viewScale;

/*
	int iXYWH[4] = {
		XYWH[0],
		XYWH[1],
		XYWH[2],
		XYWH[3],
	};
*/

	jText_render_scaled ( screenDims, glBuffers, XYWHpass, text, XYWH,
//	jText_render_scaled ( screenDims, glBuffers, iXYWH, text,
		viewLoc, viewScale );
}

// already scaled and translated to the canvas.

void jText_render_scaled ( int *screenDims, GLuint *glBuffers, int *XYWHpass, struct jText *text, float *XYWH,
//void jText_render_scaled ( int *screenDims, GLuint *glBuffers, int *XYWHpass, struct jText *text,
		float *viewLoc, float viewScale ) {

//	debugPrint_jvg_render = 1;
	if ( debugPrint_jvg_render ) {
		printf ( "jText_render_scaled ( )\n" );
		printf ( "text: %p\n", text );
		sayFloatArray ( "text->XYWH", text->XYWH, 4 );

//		sayFloatArray ( "XYWH", XYWH, 4 );
		sayIntArray ( "XYWHpass", XYWHpass, 4 );
	}

/*
	float XYWH[4] = {
		XYWHpass[0],
		XYWHpass[1],
		XYWHpass[2],
		XYWHpass[3],
	};
*/


	float glyphWH[2];
	glyphWH[0] = fonts[0]->atlasInfo.glyphW / viewScale;
	glyphWH[1] = fonts[0]->atlasInfo.glyphH / viewScale;

//	float tempXYWH[4] = { text->XYWH[0], text->XYWH[1], text->XYWH[2], text->XYWH[3] };
	float tempXYWH[4] = { XYWH[0], XYWH[1], XYWH[2], XYWH[3] };



	int thisObjEdit = thisEdit ( thisSel );

//	int thisObjEdit = 0;
	if ( temp_actualMem ) {
		// todo type check
		thisObjEdit = 1;
		thisSel = 1;
	}


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

//	tempXYWH[0] += XYWHpass[0];
//	tempXYWH[1] += XYWHpass[1];

//	spanRender ( screenDims, glBuffers, XYWHpass, glyphWH, XYWH, text->sb,
	spanRender_scaled ( screenDims, glBuffers, XYWHpass, glyphWH, tempXYWH, text->sb,
		drawCursor, cStart, cEnd,
		viewLoc, viewScale );

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

void jRectRender ( int *screenDims, GLuint *glBuffers, int *XYWHpass, struct jRect *rect,
		float *viewLoc, float viewScale ) {
//	printf ( "jRectRender ( )\n" );
//	sayFloatArray ( "rect->XYWH", rect->XYWH, 4 );

	float screenXY[2];
	point_to_loc ( rect->XYWH, screenXY, viewLoc, viewScale );
	screenXY[0] += XYWHpass[0];
	screenXY[1] += XYWHpass[1];

	float WH[2] = {
		rect->XYWH[2] / viewScale,
		rect->XYWH[3] / viewScale,
	};

	int iXYWH[4] = {
		screenXY[0],
		screenXY[1],
		WH[0],
		WH[1],
	};

//	sayIntArray ( "iXYWH", iXYWH, 4 );

	draw2dApi->drawRect ( iXYWH, colorWhite, screenDims, glBuffers );

	int thisObjEdit = thisEdit ( thisSel );
	if ( thisObjEdit ) {
		// top left and bottom right corner for changing the XYWH.
		// top right circle to change the roundness of the rect (TODO)

		int parentSel = thisSel;

		int i = 1;
		thisSel = 0;
		isThisSel;



		int hoverType = 0;
		if ( temp_hoverMem ) {
			struct cursor_ele *ele = temp_hoverMem;
			// todo type check
			if ( ele->payload->type == cu_Rect ) {
				struct cursor_rect *cuRect= ele->payload->rect;
				hoverType = cuRect->type;
			} else {
				printf ( "HOVER ELE MISMATCH (rect)\n" );
			}
		}

		if ( hoverType == 1 ) {
			thisSel = 1;
		}

		// top left square
		float corner[4] = {
			screenXY[0] - vertWidth/2,
			screenXY[1] - vertWidth/2,
			vertWidth,
			vertWidth,
		};
		if ( thisSel ) {
			draw2dApi->fillRectF ( corner, colorOrange, screenDims, glBuffers );
		} else {
			draw2dApi->drawRectF ( corner, colorWhite, screenDims, glBuffers );
		}

		i = 2;
		thisSel = 0;
		isThisSel;


		if ( hoverType == 2 ) {
			thisSel = 1;
		}


		// bottom right square
		corner[0] += WH[0];
		corner[1] += WH[1];
		if ( thisSel ) {
			draw2dApi->fillRectF ( corner, colorOrange, screenDims, glBuffers );
		} else {
			draw2dApi->drawRectF ( corner, colorWhite, screenDims, glBuffers );
		}

		// top right circle
	}

//	printf ( "jRectRender ( ) OVER\n" );
}

// why is this not jCirc_render like other functs are
void jCircRender ( int *screenDims, GLuint *glBuffers, int *XYWHpass, struct jCirc *circ,
		float *viewLoc, float viewScale ) {
//	printf ( "jCircRender ( )\n" );
//	printf ( "thisSel: %d\n", thisSel );
//	printf ( "temp_hoverMem: %p\n", temp_hoverMem );

	float screenXY[2];
	point_to_loc ( circ->XY, screenXY, viewLoc, viewScale );
	screenXY[0] += XYWHpass[0];
	screenXY[1] += XYWHpass[1];

	float radius = circ->radius / viewScale;

	int iXY[2] = { screenXY[0], screenXY[1] };
//	draw2dApi->drawCircle ( iXY, diameter, colorWhite, screenDims, glBuffers );

	int minSides = 20;

	int sides = 20;
	// TODO this should be relative to viewScale aswell.
	// he more zoomed in i am, the more sides there are, but at the same time, i shouldnt be rendering a full circle.

	sides = circ->radius / 20;
	if ( sides < minSides ) {
		sides = minSides;
	}

	draw2dApi->drawCircle_sides ( screenDims, glBuffers,
		iXY, radius, sides, colorWhite );

	int thisObjEdit = thisEdit ( thisSel );
//	printf ( "thisObjEdit: %d\n", thisObjEdit );

	if ( thisObjEdit ) {
		// draw the control points, a square at the center, and right side.

		int cWidth = controlPointWidth / viewScale;

		// square at the center.
		int iXYWH[4];
//		iXYWH[0] = XYWHpass[0] + circ->XY[0] - (controlPointWidth / 2);
//		iXYWH[1] = XYWHpass[1] + circ->XY[1] - (controlPointWidth / 2);

		int hoverType = 0;
		if ( temp_hoverMem ) {
			struct cursor_ele *ele = temp_hoverMem;
			// todo type check
			if ( ele->payload->type == cu_Circ ) {
				struct cursor_circ *cuCirc= ele->payload->circ;
				hoverType = cuCirc->type;
			} else {
				printf ( "HOVER ELE MISMATCH (circ)\n" );
			}
		}

		iXYWH[0] = screenXY[0] - (cWidth / 2);
		iXYWH[1] = screenXY[1] - (cWidth / 2);
		iXYWH[2] = cWidth;
		iXYWH[3] = cWidth;
		if ( hoverType == 1 ) {
			draw2dApi->fillRect ( iXYWH, colorWhite, screenDims, glBuffers );
		} else {
			draw2dApi->drawRect ( iXYWH, colorOrange, screenDims, glBuffers );
		}

		// square at the right side.
		iXYWH[0] = screenXY[0] + radius - (cWidth / 2);
		iXYWH[1] = screenXY[1] - (cWidth / 2);
		iXYWH[2] = cWidth;
		iXYWH[3] = cWidth;
		if ( hoverType == 2 ) {
			draw2dApi->fillRect ( iXYWH, colorWhite, screenDims, glBuffers );
		} else {
			draw2dApi->drawRect ( iXYWH, colorOrange, screenDims, glBuffers );
		}
	}
}

void complexEleRender ( int *screenDims, GLuint *glBuffers, int *XYWHpass, struct complexEle *complex,
		float *viewLoc, float viewScale ) {

	if ( debugPrint_jvg_complex_render ) {
		printf ( "complexEleRender ( )\n" );
		printf ( "complex->decType: %d\n", complex->decType );

		printf ( "viewScale: %f\n", viewScale );
	}

	struct jalbFont *font = fonts[0];


	float fXYWH[4];
	point_to_loc ( complex->XYWH, fXYWH, viewLoc, viewScale );
	fXYWH[0] += XYWHpass[0];
	fXYWH[1] += XYWHpass[1];

	fXYWH[2] = complex->XYWH[2] / viewScale;
	fXYWH[3] = complex->XYWH[3] / viewScale;

	/// TODO, this should be retrieved.
	int modI = 0;
	struct complexMod *mod = arrayListGetPointer ( glob_jvg->moduleList, modI );
	if ( !mod ) {
		printf ( "ERROR, !mod\n" );
		return;
	}

	int drawOutline = 1;
	if ( complex->decType < 0 ) {
		drawOutline = 1;
	}
	if ( drawOutline ) {
		draw2dApi->drawRectF ( fXYWH, colorWhite, screenDims, glBuffers );
	}

	// < 0 means undefined.
	if ( complex->decType < 0 ) {
		float charXY[2] = { fXYWH[0] + 2, fXYWH[1] + 2 };

		char str[256];
		sprintf ( str, "complex->decType < 0. (%d)", complex->decType );

		draw2dApi->drawCharPre ( font, colorWhite );
		draw2dApi->drawStringBounded ( screenDims, glBuffers, charXY,
			fXYWH, font, str );
	} else {
		if ( debugPrint_jvg_complex_render ) {
			printf ( "complex->decType: %d\n", complex->decType );
		}

		struct complexDec *dec = arrayListGetPointer ( mod->complexDecList, complex->decType );

		if ( debugPrint_jvg_complex_render ) {
			printf ( "dec: %p\n", dec );
			printf ( "dec->renderFunct: %p\n", dec->renderFunct );
		}

/*
		float screenXY[2] = {
			fXYWH[0],
			fXYWH[1],
		};
//		point_to_loc ( complex->XYWH, screenXY, viewLoc, viewScale );

		int XYWH[4] = {
			screenXY[0],
			screenXY[1],
			XYWHpass[2],
			XYWHpass[3],
		};
*/



		if ( dec->renderFunct ) {
			// For normal non dynamic rendering.
//			void (*funct)(int *screenDims, GLuint *glBuffers, int *XYWHpass, void *data) = dec->renderFunct;
//			funct ( screenDims, glBuffers, XYWH, NULL );

/*
			// For dynamic rendering
			void (*funct)(int *screenDims, GLuint *glBuffers, int *XYWHpass, void *data,
				float *viewLoc, float viewScale) = dec->renderFunct;
			funct ( screenDims, glBuffers, XYWH, NULL,
				viewLoc, viewScale );
*/


			int iXYWH[4] = { fXYWH[0], fXYWH[1], fXYWH[2], fXYWH[3] };
			complexEleRender_sub ( screenDims, glBuffers, iXYWH, complex, dec,
				viewLoc, viewScale );

		} else {
//			printf ( "ERROR, !dec->renderFunct\n" );

			float charXY[2] = { fXYWH[0] + 2, fXYWH[1] + 2 };

			char buffer[1024];

			draw2dApi->drawCharPre ( font, colorWhite );

			sprintf ( buffer, "%s", dec->name );
			draw2dApi->drawStringBounded ( screenDims, glBuffers, charXY,
				fXYWH, font, buffer );
			charXY[1] += font->atlasInfo.glyphH;


			int i = 0;
			int len = arrayListGetLength ( complex->liveSubVars );
			while ( i < len ) {
				struct jLiveData *data = arrayListGetPointer ( complex->liveSubVars, i );
				struct subVar *subVar = arrayListGetPointer ( dec->subVars, i );
				if ( data->type == jld_I ) {
					sprintf ( buffer, "%s: %d", subVar->name, data->i );
				} else if ( data->type == jld_ComplexRef ) {
					sprintf ( buffer, "Complex Ref, draw line" );
				} else {
					sprintf ( buffer, "data type not handled" );
				}

				draw2dApi->drawStringBounded ( screenDims, glBuffers, charXY,
					fXYWH, font, buffer );
				charXY[1] += font->atlasInfo.glyphH;

				if ( data->type == jld_ComplexRef ) {
					struct complexEle *otherEle = data->complexRef->complexPtr;
					if ( otherEle ) {
//						printf ( "DRAWING CONNECTING LINE\n" );

						float p0[2] = { fXYWH[0], fXYWH[1] };
						float p1[2];
						point_to_loc ( otherEle->XYWH, p1, viewLoc, viewScale );

//						sayFloatArray ( "p0", p0, 2 );
//						sayFloatArray ( "p1", p1, 2 );

						// this should use svg logic to thicken it?
						draw2dApi->drawSeg ( screenDims, glBuffers, p0, p1, colorWhite );

						draw2dApi->drawCharPre ( font, colorWhite );
					}
				}

				i += 1;
			}
		}
	}
}

int jvg_debugPrint_grid = 0;

void grid_render ( int *screenDims, GLuint *glBuffers, int *XYWHpass, float *gridWH,
		float *viewLoc, float viewScale ) {
	if ( jvg_debugPrint_grid ) {
		printf ( "grid_render ( )\n" );
		sayFloatArray ( "gridWH", gridWH, 2 );
	}

	// viewLoc is the world offset that the top left renderPos is from the origin, so negative means the camera has been moved up and to the left.

	float topLeft[2] = {
		viewLoc[0],
		viewLoc[1],
	};

	// void loc_to_point ( float *p0, float *pSet, float *viewLoc, float viewScale );


	// px between each line
	// if offset is 0, then there is an error, so break.
	float offset[2] = {
		gridWH[0] / viewScale,
		gridWH[1] / viewScale,
	};

	if ( offset[0] == 0 ) {
		return;
	}
	if ( offset[1] == 0 ) {
		return;
	}

	// to stop too many lines from being rendered when zoomed out.
	// TODO, if i change it from 1 to 10 it glitches, i assume there is a glitch at 1 aswell i just cant see it.
	while ( offset[0] < 1 ) {
		offset[0] *= 10;
	}
	while ( offset[1] < 1 ) {
		offset[1] *= 10;
	}



	// x rounding
	float vx = roundUp ( topLeft[0], gridWH[0] );
	float dx = vx - topLeft[0];

	// y rounding
	float vy = roundUp ( topLeft[1], gridWH[1] );
	float dy = vy - topLeft[1];

	if ( jvg_debugPrint_grid ) {
		sayFloatArray ( "viewLoc", viewLoc, 2 );
		sayFloatArray ( "offset", offset, 2 );

		printf ( "vx: %f\n", vx );
		printf ( "vy: %f\n", vy );

		printf ( "dx: %f\n", dx );
		printf ( "dy: %f\n", dy );
	}

	// to remember which line is the origin and render it lighter
	int worldPos[2] = { vx, vy };

	// dx, dy is the worldPos to the first line.

	float XYWH[4] = {
		XYWHpass[0] + dx / viewScale,
		XYWHpass[1],
		1,
		XYWHpass[3],
	};

	if ( jvg_debugPrint_grid ) {
		sayFloatArray ( "XYWH verts", XYWH, 4 );
	}

	// draws verticle lines
	while ( 1 ) {
		if ( worldPos[0] == 0 ) {
			draw2dApi->drawRectF ( XYWH, colorLightGrayOpaque, screenDims, glBuffers );
		} else {
			draw2dApi->drawRectF ( XYWH, colorGrayOpaque, screenDims, glBuffers );
		}
		XYWH[0] += offset[0];

		worldPos[0] += gridWH[0];

		if ( XYWH[0] > screenDims[0] ) {
			break;
		}
	}

	XYWH[0] = XYWHpass[0];
	XYWH[1] = XYWHpass[1] + dy / viewScale,
	XYWH[2] = XYWHpass[2];
	XYWH[3] = 1.0;

	if ( jvg_debugPrint_grid ) {
		sayFloatArray ( "XYWH hors", XYWH, 4 );
	}

	// draws horizontal lines
	while ( 1 ) {
		if ( worldPos[1] == 0 ) {
			draw2dApi->drawRectF ( XYWH, colorLightGrayOpaque, screenDims, glBuffers );
		} else {
			draw2dApi->drawRectF ( XYWH, colorGrayOpaque, screenDims, glBuffers );
		}
		XYWH[1] += offset[1];

		worldPos[1] += gridWH[0];

		if ( XYWH[1] > screenDims[1] ) {
			break;
		}
	}

	float firstPoint[2] = {
		dx / viewScale,
		dy / viewScale,
	};

	if ( jvg_debugPrint_grid ) {
		sayFloatArray ( "firstPoint", firstPoint, 2 );

		float worldPoint[2] = { gridWH[0], gridWH[1] };
		loc_to_point ( worldPoint, worldPoint, viewLoc, viewScale );
		sayFloatArray ( "worldPoint", worldPoint, 2 );

		printf ( "grid_render ( ) OVER\n" );
	}
}

// cursorScreenXY is the cursor position relative to the JLUI element, not to the window, or screen.
void grid_render_cursor ( int *screenDims, GLuint *glBuffers, int *XYWHpass, float *gridWH,
		float *viewLoc, float viewScale, int *cursorScreenXY ) {
	if ( jvg_debugPrint_grid ) {
		printf ( "grid_render_cursor ( )\n" );
	}

	// take cursor loc, convert it to world loc, round that, convert to screen loc.
	// should it be possible to shap to positions off of the screen?

	// if offset is 0, then there is an error, so break.
	float offset[2] = {
		gridWH[0],
		gridWH[1],
	};

	if ( offset[0] == 0 ) {
		return;
	}
	if ( offset[1] == 0 ) {
		return;
	}

	// to stop too many lines from being rendered when zoomed out.
	while ( offset[0] < 1 ) {
		offset[0] *= 10;
	}
	while ( offset[1] < 1 ) {
		offset[1] *= 10;
	}

	float worldCursor[2];
	screen_to_world_i ( cursorScreenXY, worldCursor, viewLoc, viewScale );

	if ( jvg_debugPrint_grid ) {
		printf ( "viewScale: %f\n", viewScale );
		sayFloatArray ( "worldCursor", worldCursor, 2 );
		sayFloatArray ( "offset", offset, 2 );
	}

	float roundX = roundClose ( worldCursor[0], offset[0] );
	float roundY = roundClose ( worldCursor[1], offset[1] );

	if ( jvg_debugPrint_grid ) {
		sayIntArray ( "cursorScreenXY", cursorScreenXY, 2 );
		printf ( "roundXY (%f, %f)\n", roundX, roundY );
	}

	float roundedWorld[2] = {
		roundX,
		roundY,
	};

	float newScreen[2];
	world_to_screen ( roundedWorld, newScreen, viewLoc, viewScale );

	if ( jvg_debugPrint_grid ) {
		sayFloatArray ( "newScreen", newScreen, 2 );
	}

	newScreen[0] += XYWHpass[0];
	newScreen[1] += XYWHpass[1];

	// draw a circle at this pos.
	draw2dApi->drawCircle_f ( newScreen, 10, colorWhite, screenDims, glBuffers );

	if ( jvg_debugPrint_grid ) {
		printf ( "grid_render_cursor ( ) OVER\n" );
	}
}

// takes in 2 floats, and rounds up val to the nearest roundTo
// always rounds up
float roundUp ( float val, float roundTo ) {
	// do (val * 0.999)?
	int i = (val - 1) / roundTo;
	if ( i > 0 ) {
		i += 1;
	}
	float v = i * roundTo;
//	float dx = v - val;
	return v;
}

// round up or down, depending on what closer.
float roundClose ( float val, float roundTo ) {
//	int i = (val + 0.5) / roundTo;
//	printf ( "f: %f\n", val / roundTo );

	float f = (val / roundTo) + 0.5;
	int i = (val / roundTo) + 0.5;

	if ( f < 0 ) {
		i -= 1;
	}

	float v = i * roundTo;
//	float dx = v - val;
	return v;
}

// how to handle this, non efficiently.
// get the world position of the top left of my screen.
// round up to the nearest x'th.
// convert that world position to a screen position.
// render there

// how to do it more effeciently.
// 1 px on my screen = viewScale pixels in the canvas.

// get the world position of the top left of my screen.
// round up to the nearest x'th.
// get the difference in those 2 numbers, then my first line is rendered at
// x = 0 + offset * viewScale

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


/** unitTests */

void roundClose_unitTests ( ) {
	float val = 1.0;
	float roundTo = 100.0;

	float round = roundClose ( val, roundTo );
	printf ( "%f (%f -> %f)\n", roundTo, val, round );

	val = 49.0;
	round = roundClose ( val, roundTo );
	printf ( "%f (%f -> %f)\n", roundTo, val, round );

	val = 51.0;
	round = roundClose ( val, roundTo );
	printf ( "%f (%f -> %f)\n", roundTo, val, round );

	val = 99.0;
	round = roundClose ( val, roundTo );
	printf ( "%f (%f -> %f)\n", roundTo, val, round );

	val = 101.0;
	round = roundClose ( val, roundTo );
	printf ( "%f (%f -> %f)\n", roundTo, val, round );

	val = 110.0;
	round = roundClose ( val, roundTo );
	printf ( "%f (%f -> %f)\n", roundTo, val, round );

	exit ( 12 );
}

