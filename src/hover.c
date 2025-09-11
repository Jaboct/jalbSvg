#include "hover.h"

#include "cursor.h"

/** Includes */

#include "jGroup.h"
#include "cursorIcon.h"

#include "canvas_util.h"


/** Variables */

extern int debugPrint_jvg_event;


extern struct jvg *glob_jvg;

extern float glob_viewScale;
extern float glob_viewLoc[];

extern int cursorInputMode;

/// render info
extern int controlPointWidth;


/// cursor globals

int hoverIndex_render = 0;
struct cursor_ele *hoverMem = NULL;	// global var, doesnt change after being inited
struct cursor_ele *temp_hoverMem = NULL;	// temp var, changes as u render and event. internal vars store the stack.

ArrayList *cursorList_new = NULL;	// (struct cursor_ele*)	// TODO
struct cursor_ele *glob_cursor_ele = NULL;	// of type group, used to contain cursorList
int isHover = 0;

/** Functions */

/// cursor glboals TODO this belongs elsewhere

void init_jvg_cursor ( ) {
	if ( !hoverMem ) {
		hoverMem = cursor_eleInit ( );
	}
	if ( !cursorList_new ) {
		// instead of using this, wrap it in a cursor_group;
		glob_cursor_ele = cursor_eleInit ( );
		cursor_unionTypeChange0 ( glob_cursor_ele->payload, cu_Group );
//		cursorList_new = initArrayList ( 10, sizeof ( struct cursor_ele* ), 10 );
		cursorList_new = glob_cursor_ele->payload->group->eles;
	}
}


// isnt used at all.
// should this be filling out some cursorInfo?
// type 1 means i have type pen.
int click_drill ( ArrayList *eleList, int *XY, int type ) {
	int i = 0;
	int len = arrayListGetLength ( eleList );
	while ( i < len ) {
		struct jNakedUnion *ele = arrayListGetPointer ( eleList, i );

		if ( ele->type == jNaked_G ) {
			printf ( "TODO\n" );
		} else if ( ele->type == jNaked_Path ) {
			// search its verts

			struct jPath *path = ele->path;

			int vertI = isOnVert ( path, XY );

			if ( vertI != -1 ) {
				if ( type == 1 ) {
					// this vert is now selected.

					return 1;
				}
			}
		} else {
			printf ( "TODO\n" );
		}

		i += 1;
	}
	return 0;
}


/// hover cursor

void onHoverCheck ( int *XY ) {
	if ( debugPrint_jvg_event ) {
		printf ( "onHoverCheck ( )\n" );
		sayIntArray ( "XY", XY, 2 );
	}

	isHover = 0;

	if ( cursorInputMode == ci_reg ) {
		// see if my cursor is on a vert.

		int ret = onHoverType ( XY );
		if ( ret == 1 ) {
			// TODO cr_move
			set_cursor_iconI ( cr_move );
		} else {
			set_cursor_iconI ( cr_reg );
		}
	}
}

// iterate throught all of the eles (rn it doesnt recur, todo)
// sees if the passed XY is hovering over an ele.
// i need to complcaite the return index.
// either simply return the icon i want.
// i think i should return something more complicated and then it gets translated into an icon.
int onHoverType ( int *XY ) {
	if ( debugPrint_jvg_event ) {
		printf ( "onHoverType ( )\n" );
	}

	if ( hoverMem ) {
//		cursor_unionTypeChange0 ( hoverMem->payload, -1 );
		cursor_unionTypeChange0 ( hoverMem->payload, cu_Group );	// always a group up top to match the jEleList
		emptyArrayList ( hoverMem->payload->group->eles );	// TODO free these.

		temp_hoverMem = hoverMem;
	}

	int ret = onHoverType_eleList ( XY, glob_jvg->eles );
	return ret;
}

int onHoverType_eleList ( int *XY, ArrayList *eleList ) {
	if ( debugPrint_jvg_event ) {
		printf ( "onHoverType_eleList ( )\n" );
	}

//	struct cursor_ele *memHover = temp_hoverMem;

	int i = 0;
	int len = arrayListGetLength ( eleList );
	while ( i < len ) {
		struct jNakedUnion *uni = arrayListGetPointer ( eleList, i );

		if ( uni->type == jNaked_Path ) {
			struct jPath *path = uni->path;

			int ret = isOnPath ( path, XY );

//			printf ( "isOnPath: %d\n", ret );

			if ( ret ) {
				// right now there can only be 1 hover ele, this will change
				if ( ret == 2 ) { // TODO i should do this for on the line aswell?
					struct cursor_ele *hoverEle = arrayListGetPointer ( temp_hoverMem->payload->group->eles, 0 );
					hoverEle->index = i;
					say_cursor_ele ( hoverMem );
				}

				isHover = 1;

				return ret;
			}

		} else if ( uni->type == jNaked_Text ) {
			struct jText *text = uni->text;

			if ( isOnText ( text, XY ) ) {
				return 1;
			}

		} else if ( uni->type == jNaked_Rect ) {
			struct jRect *rect = uni->rect;

			if ( isOnRect ( rect, XY ) ) {
				return 1;
			}

		} else if ( uni->type == jNaked_Circ ) {
			struct jCirc *circ = uni->circ;

			if ( isOnCirc ( circ, XY ) ) {
				return 1;
			}
		}

		i += 1;
	}

	return 0;
}

int pointDist = 4.0;

// used for path check.
// return 1 if its hovering over a line
// return 2 if it is hovering over a vert.
int isOnPath ( struct jPath *path, int *XY ) {
	if ( debugPrint_jvg_event ) {
		printf ( "isOnPath ( )\n" );
//		sayIntArray ( "XY", XY, 2 );
	}


//	int boxW = 10;

	float viewScale = glob_viewScale;
	float *viewLoc = glob_viewLoc;

//	printf ( "viewScale: %f\n", viewScale );
//	sayFloatArray ( "viewLoc", viewLoc, 2 );

	int vertRet = isOnVert ( path, XY );
	if ( vertRet != -1 ) {

		// set hover info
		struct cursor_ele *subHover = cursor_eleInit ( );
		arrayListAddEndPointer ( temp_hoverMem->payload->group->eles, subHover );

		cursor_unionTypeChange0 ( subHover->payload, cu_Path );
		struct cursor_path *cuPath = subHover->payload->path;
		emptyArrayList ( cuPath->verts );
		int *vertI = arrayListGetNext ( cuPath->verts );
		*vertI = vertRet;

		if ( debugPrint_jvg_event ) {
			printf ( "isOnPath ( ) OVER 2\n" );
		}
		return 2;
	}

	int i;
	int len;

	// ok now check if its on a line aswell.
	i = 0;
	len = arrayListGetLength ( path->lines );
	while ( i < len ) {
		struct jLine *l = arrayListGetPointer ( path->lines, i );

		struct jVert *v0 = arrayListGetPointer ( path->verts, l->v0 );
		struct jVert *v1 = arrayListGetPointer ( path->verts, l->v1 );

		float fXY[2] = { XY[0], XY[1] };
		loc_to_point ( fXY, fXY, viewLoc, viewScale );
		float dist = pointSegDist ( fXY, v0->XY, v1->XY );

		if ( dist < pointDist ) {
			if ( debugPrint_jvg_event ) {
				printf ( "isOnPath ( ) OVER 1\n" );
			}
			return 1;
		}

		i += 1;
	}

	if ( debugPrint_jvg_event ) {
		printf ( "isOnPath ( ) OVER 0\n" );
	}
	return 0;
}

// return the index of the vert that this cursor is on.
// takes in screenXY
int isOnVert ( struct jPath *path, int *screenXY ) {
	float viewScale = glob_viewScale;
	float *viewLoc = glob_viewLoc;

	int i;
	int len;

	i = 0;
	len = arrayListGetLength ( path->verts );
	while ( i < len ) {
		struct jVert *v = arrayListGetPointer ( path->verts, i );

		float cXY[2];
//		point_to_loc ( v->XY, cXY, viewLoc, viewScale );
		world_to_screen ( v->XY, cXY, viewLoc, viewScale );

//		sayFloatArray ( "cXY", cXY, 2 );

		cXY[0] -= screenXY[0];
		cXY[1] -= screenXY[1];

		// this is a circular check, not rect
		float d = vectNorm ( cXY, 2 );

		int boxW = controlPointWidth;

		if ( d < boxW ) {
//			printf ( "vert hover\n" );

			return i;
		}

		i += 1;
	}
	return -1;
}

int isOnVert_world ( struct jPath *path, float *worldXY ) {
	float viewScale = glob_viewScale;

	int i;
	int len;

	i = 0;
	len = arrayListGetLength ( path->verts );
	while ( i < len ) {
		struct jVert *v = arrayListGetPointer ( path->verts, i );

		float cXY[2] = {
			v->XY[0] - worldXY[0],
			v->XY[1] - worldXY[1],
		};

		// this is a circular check, not rect
		float d = vectNorm ( cXY, 2 );

		int boxW = controlPointWidth;

		if ( d < boxW * viewScale ) {
//			printf ( "vert hover\n" );

			return i;
		}

		i += 1;
	}
	return -1;
}

int isOnLine ( struct jVert *v0, struct jVert *v1, int *XY ) {
	// TODO, rn this treats everything like a straight line, ignores curves.

	

	return 0;
}

extern int jText_box_width;
extern int controlPointWidth;

int isOnText ( struct jText *text, int *XY ) {

	float viewScale = glob_viewScale;
	float *viewLoc = glob_viewLoc;

	// canvasXY, translated from the screenXY to realXY.
	float cXY[2] = { XY[0], XY[1] };
	loc_to_point ( cXY, cXY, viewLoc,  viewScale );

	// check the main box;
	float boxXYWH[4] = { text->XYWH[0], text->XYWH[1], text->XYWH[2], text->XYWH[3] };
	if ( pointInside ( cXY, boxXYWH ) ) {
		// its inside the main box.
		return 0;
	}

	// check the top box.
	boxXYWH[1] -= jText_box_width;
	boxXYWH[3] = jText_box_width;
	if ( pointInside ( cXY, boxXYWH ) ) {
		return 1;
	}

	// check the bottom right.
//	boxXYWH[0] += boxXYWH[2];
//	boxXYWH[1] += boxXYWH[3];

	boxXYWH[0] = text->XYWH[0] + text->XYWH[2];
	boxXYWH[1] = text->XYWH[1] + text->XYWH[3];
	boxXYWH[2] = jText_box_width;
	boxXYWH[3] = jText_box_width;
	if ( pointInside ( cXY, boxXYWH ) ) {
		// its inside the main box.
		return 1;
	}

	return 0;
}

int isOnRect ( struct jRect *rect, int *XY ) {
	float viewScale = glob_viewScale;
	float *viewLoc = glob_viewLoc;

	int ret = jRect_mPos ( XY, rect,
		viewLoc, viewScale );
	if ( ret >= 0 ) {
		return 1;
	}

	return 0;
}

int isOnCirc ( struct jCirc *circ, int *XY ) {
	float viewScale = glob_viewScale;
	float *viewLoc = glob_viewLoc;

	// canvasXY, translated from the screenXY to realXY.
	float cXY[2] = { XY[0], XY[1] };
	loc_to_point ( cXY, cXY, viewLoc,  viewScale );

	// check the center box;
	float boxXYWH[4] = { circ->XY[0] - controlPointWidth / 2, circ->XY[1] - controlPointWidth / 2, controlPointWidth, controlPointWidth };
	if ( pointInside ( cXY, boxXYWH ) ) {
		return 1;
	}

	// check the outer box;
	boxXYWH[0] = circ->XY[0] + circ->radius - controlPointWidth / 2;
	if ( pointInside ( cXY, boxXYWH ) ) {
		return 1;
	}

	return 0;
}


/** Util */

// return 1 if the arraylist has the int i, 0 otherwise
int al_hasInt ( ArrayList *al, int i ) {
	int j = 0;
	int len = arrayListGetLength ( al );
	while ( j < len ) {
		int *ptr = arrayListDataPointer ( al, j );
		if ( *ptr == i ) {
			return 1;
		}
		j += 1;
	}
	return 0;
}

// return -1 if the arraylist does not have the int i, otherwise it returns its index.
int al_getIndex_int ( ArrayList *al, int i ) {
	int j = 0;
	int len = arrayListGetLength ( al );
	while ( j < len ) {
		int *ptr = arrayListDataPointer ( al, j );
		if ( *ptr == i ) {
			return j;
		}
		j += 1;
	}
	return -1;
}

// al is of type (cursor_ele*)
int eleList_getIndex ( ArrayList *al, int i ) {
	int j = 0;
	int len = arrayListGetLength ( al );
	while ( j < len ) {
		struct cursor_ele *ele = arrayListGetPointer ( al, j );
		if ( ele->index == i ) {
			return j;
		}
		j += 1;
	}
	return -1;
}

int say_cursor_depth = 0;

void print_space ( int i ) {
	while ( i > 0 ) {
		printf ( "  " );

		i -= 1;
	}
}

char *cursorTypes[] = {
	"cu_Path",
	"cu_Group",
};

void say_cursor_ele ( struct cursor_ele *cursorEle ) {
//	printf ( "say_cursor_ele ( )\n" );

//	int len = arrayListGetLength ( cursorEle->address );
//	printf ( "cursorEle->address.len: %d\n", len );
//	sayIntArrayList ( "cursorEle->address", cursorEle->address );

//	printf ( "cursorEle->index: %d\n", cursorEle->index );

	print_space ( say_cursor_depth );
	printf ( "(%d, %s) ", cursorEle->index, cursorTypes[cursorEle->payload->type] );

	// cursor_union
	struct cursor_union *uni = cursorEle->payload;
//	printf ( "uni->type: %d\n", uni->type );

	if ( uni->type == cu_Path ) {
		struct cursor_path *cuPath = uni->path;
//		printf ( "cuPath->vertI: %d\n", cuPath->vertI );
		sayIntArrayList ( "cuPath->verts", cuPath->verts );

	} else if ( uni->type == cu_Group ) {
		struct cursor_group *cuGroup = uni->group;
//		printf ( "group indexes: { " );
		printf ( "{\n" );

		int i = 0;
		int len = arrayListGetLength ( cuGroup->eles );
		while ( i < len ) {
			struct cursor_ele *ele = arrayListGetPointer ( cuGroup->eles, i );
//			printf ( "(%d, %d) ", ele->index, ele->payload->type );

			say_cursor_depth += 1;
			say_cursor_ele ( ele );
			say_cursor_depth -= 1;

			i += 1;
		}
		printf ( "}\n" );

	} else {
		printf ( "ERROR, say_cursor_ele ->type unhandled (%d)\n", uni->type );
	}

//	printf ( "say_cursor_ele ( ) OVER\n" );
}

void say_cursorList_new ( ) {
	printf ( "\n" );
	printf ( "say_cursorList_new ( )\n" );

	int len = arrayListGetLength ( cursorList_new );
	printf ( "cursorList_new.len: %d\n", len );

	int i = 0;
	while ( i < len ) {
		struct cursor_ele *ele = arrayListGetPointer ( cursorList_new, i );

		say_cursor_ele ( ele );

		i += 1;
	}

	printf ( "say_cursorList_new ( ) OVER\n" );
	printf ( "\n" );
}




