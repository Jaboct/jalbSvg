#include "mod_ext.h"


struct svg *global_svg = NULL;


extern struct draw2dStruct *draw2dApi;

extern float colorWhite[];
extern float colorBlack[];

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

int jalbSvg_event ( SDL_Event *e, int *clickXY, int *eleWH, void *data ) {
	return 1;
}

void jalbSvg_close ( void *data ) {

}



// i need the dynamic canvas info.

void svg_render ( int *screenDims, GLuint *glBuffers, int *XYWH, struct svg *svg ) {
	printf ( "svg_render ( )\n" );

	eles_render ( screenDims, glBuffers, XYWH, svg->eles );
}

void eles_render ( int *screenDims, GLuint *glBuffers, int *XYWH, ArrayList *eles ) {
	int i;
	int len;

	i = 0;
	len = arrayListGetLength ( eles );

	printf ( "eles.len: %d\n", len );

	while ( i < len ) {
		struct nakedUnion *uni = arrayListGetPointer ( eles, i );

		printf ( "uni->type: %d\n", uni->type );

		if ( uni->type == G ) {
			struct g *g = uni->g;

			eles_render ( screenDims, glBuffers, XYWH, g->eles );
		} else if ( uni->type == Path ) {
			struct path *path = uni->path;
			path_render ( screenDims, glBuffers, XYWH, path );
		}

		i += 1;
	}
}

void path_render ( int *screenDims, GLuint *glBuffers, int *XYWH, struct path *path ) {
	printf ( "path_render ( )\n" );

	int i;
	int len;

	float lastP[2] = { 0, 0 };
	// some times lastC will not be set, i should mark this as error checking. but for now just trust what i load.
	float lastC[2] = { 0, 0 };

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
			draw2dApi->drawSeg ( screenDims, glBuffers, lastP, thisP, colorWhite );
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
		}
		lastP[0] = thisP[0];
		lastP[1] = thisP[1];

		lastC[0] = thisC[0];
		lastC[1] = thisC[1];

		i += 1;
	}
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

	while ( i < points ) {
		float s = (1.0 / points) * i;

		printf ( "s: %f\n", s );

//		sayFloatArray ( "p0", p0, len );

		float m0[2];
		float m1[2];
		float m2[2];

		// 3 points 2 lines.
		segScale ( p0, c0, m0, s, len );
		segScale ( c0, c1, m1, s, len );
		segScale ( c1, p1, m2, s, len );

		sayFloatArray ( "m0", m0, len );
		sayFloatArray ( "m1", m1, len );
		sayFloatArray ( "m2", m2, len );

		float c0[2];
		float c1[2];
		segScale ( m0, m1, c0, s, len );
		segScale ( m1, m2, c1, s, len );

		float f[2];
		segScale ( c0, c1, f, s, len );

		sayFloatArray ( "f", f, 2 );

/*
		rect[0] = f[0];
		rect[1] = f[1];
		draw2dApi->fillRect ( rect, colorWhite, screenDims, glBuffers );
*/
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
	draw2dApi->drawSeg ( screenDims, glBuffers, last, p1, colorWhite );
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


