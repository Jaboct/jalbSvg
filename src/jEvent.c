#include "jEvent.h"


/** Includes */

#include "hand.h"
#include "jHand.h"
#include "jGroup.h"
#include "jText.h"
#include "jShapes.h"
#include "jPath.h"

#include "path.h"

#include "cursor.h"
#include "cursorIcon.h"
#include "hover.h"

#include "jEvent_path.h"
#include "canvas_util.h"

#include "mod_ext.h"

#include "complexEle.h"
#include "complexEle_ext.h"


/** Variables */

extern char altKeys[];

extern struct jalbFont *fonts[];
extern int numFonts;


extern float glob_viewScale;
extern float glob_viewLoc[];


//extern ArrayList *cursorList;
extern int cursor_depth;
// new cursor data
int temp_clickIndex = 0;
struct cursor_ele *temp_clickMem = NULL;		// used during event
struct cursor_ele *temp_clickMem_parent = NULL;		// used to store the depth info, so once i confirm that it was clicked on,

extern struct cursor_ele *glob_cursor_ele;	// contains cursorList_new
extern struct cursor_ele *temp_actualMem;		// used during render
extern int heldType;

//extern ArrayList *cursorList_new;	// (struct cursor_ele*)


extern int renderMode;


extern int vertWidth;
extern int controlPointR;


extern int selected;


int debugPrint_jvg_event = 0;
int debugPrint_jIterate = 0;
int jvg_debugPrint_jText = 1;

extern int cStart[];
extern int cEnd[];


extern int tabW;


extern int pointDist;


int jText_box_width = 10;


extern ArrayList *glob_ctrlKeys;




// uiGen
extern struct uiGen_api *uiGenApi;
char *uiGen_jTextEdit = "../jalbSvg/res/uiGen_hand/jText.xml";


/** Functions */

extern int mouseHeld;
extern int cursorInputMode;
extern struct jNakedUnion *tempEle;

extern struct jvg *glob_jvg;

extern int heldStart[];


int jalbJvg_keyDown ( SDL_Event *e, int *clickXYpass, int *eleWH, struct jvg *jvgEle,
		float *viewLoc, float viewScale ) {
	printf ( "jalbJvg_keyDown ( )\n" );

	int ret = 0;

	if ( e->key.keysym.sym == SDLK_ESCAPE ) {
		if ( tempEle ) {
			jNakedUnionClose ( tempEle );
			tempEle = NULL;
			mouseHeld = 0;
		}

		set_cursorInputMode ( ci_reg );

		ret = 1;
		goto functEnd;
	}


	// assume only 1 ele is selected?
	// i dont really care, lets drill down

	// iterate throguh all my cursor eles, and individually do event

//	ArrayList *jEles = jvgEle->eles;

	struct jNakedUnion uni;
	uni.type = -1;
	jNakedUnionTypeChange0 ( &uni, jNaked_G );
	uni.g->eles = jvgEle->eles;

	ret = keydown_cursor_ele ( e, &uni, glob_cursor_ele );

/*
	struct jNakedUnion *parent;
	struct jNakedUnion *ele;
	int vertI = -1;
	int controlI = -1;
	struct cursorMem *lastCursor;

	int selType = jIterateToSelected ( global_jEles, &parent, &ele, &vertI, &controlI, &lastCursor );

	// ctrl-click on selected ele to open a uiGen pane to edit it.
	if ( selected &&
	     altKeys[akCtrl] ) {
		if ( e->key.keysym.sym == SDLK_RETURN ) {
			if ( selType == cs_text ) {
			} else if ( selType == cs_object ) {
				if ( ele->type == jNaked_Path ) {
					printf ( "load path uiGen\n" );

					char *dir = "../jalbSvg/res/uiGen_hand/jPath.xml";

					uiGen_api->load_and_set_norm ( dir, ele->path );

					ret = 0;
					goto functEnd;
				}
			}
		}
	}

	if ( selType == cs_text &&
	     selected ) {
//		printf ( "editing text\n" );

		struct jText *text = ele->text;
		ArrayList *sb = text->sb;
		struct undoRedo *undoMem = NULL;
		struct textSearch *search = NULL;
		int searching = 0;

		int textWrap = 1;
		int maxCols = text->XYWH[2] / fonts[0]->atlasInfo.glyphW;

//		printf ( "maxCols: %d\n", maxCols );

		if ( altKeys[akCtrl] ) {
			ret = keySpecialChar ( e, sb );
		}
		if ( ret ) {
			goto functEnd;
		}


		ret = sbKey ( e->key.keysym.sym, sb, undoMem, cStart, cEnd,
			&searching, search, altKeys,
			glob_ctrlKeys, NULL, textWrap, maxCols );
//		printf ( "SB KEY RET: %d\n", ret );

		if ( ret ) {
			goto functEnd;
		}
//		printSb ( sb );
	}
*/


	functEnd:;

	say_cursor_ele ( glob_cursor_ele );

	printf ( "jalbJvg_keyDown ( ) OVER\n" );
	return ret;
}

// returns true if atleast 1 ele reacts to the event.
int keydown_cursor_ele ( SDL_Event *e, struct jNakedUnion *uni, struct cursor_ele *cursor ) {
	printf ( "keydown_cursor_ele ( )\n" );
	printf ( "cursor->payload->type: %d\n", cursor->payload->type );

	int ret = 0;

	if ( cursor->payload->type == cu_Group ) {
		if ( uni->type != jNaked_G ) {
			printf ( "error, keydown_cursor_ele\n ");
			exit ( 12 );
		}
		ArrayList *jEles = uni->g->eles;

		// iterate
		int i = 0;
		int len = arrayListGetLength ( cursor->payload->group->eles );
		while ( i < len ) {
			struct cursor_ele *subCursor = arrayListGetPointer ( cursor->payload->group->eles, i );
			struct jNakedUnion *subEle = arrayListGetPointer ( jEles, subCursor->index );

			int subRet = keydown_cursor_ele ( e, subEle, subCursor );
			if ( subRet ) {
				ret = 1;
			}

			i += 1;
		}
	} else if ( cursor->payload->type == cu_Text ) {
		printf ( "keydown text\n" );

		struct jText *text = uni->text;
		ret = keydown_text ( e, text );

	} else if ( cursor->payload->type == cu_ComplexEle ) {
		printf ( "cursor complex\n" );

		// get the complex and its info?

		struct complexEle *ele = uni->complex;

		float *viewLoc = glob_viewLoc;
		float viewScale = glob_viewScale;

		int eleWH[2] = { 0, 0 };
		int clickXYpass[2] = { 0, 0 };
		ret = complexEle_kEvent ( e, clickXYpass, eleWH, ele,
			viewLoc, viewScale );

	} else {
		printf ( "TODO, keydown_cursor_ele\n" );
	}

	return ret;
}

int keydown_text ( SDL_Event *e, struct jText *text ) {
	if ( jvg_debugPrint_jText ) {
		printf ( "keydown_text ( )\n" );
		printf ( "text: %p\n", text );
	}

	int ret = 0;

	ArrayList *sb = text->sb;
	struct undoRedo *undoMem = NULL;
	struct textSearch *search = NULL;
	int searching = 0;

	int textWrap = 1;
	int maxCols = text->XYWH[2] / fonts[0]->atlasInfo.glyphW;

//	printf ( "maxCols: %d\n", maxCols );

	if ( altKeys[akCtrl] ) {
		ret = keySpecialChar ( e, sb );
	}
	if ( ret ) {
		goto functEnd;
	}

	printf ( "a\n" );
	sayIntArray ( "cStart", cStart, 3 );
	sayIntArray ( "cEnd", cEnd, 3 );

	int glyphH = fonts[0]->atlasInfo.glyphH;
	ret = sbKey ( e->key.keysym.sym, sb, undoMem, cStart, cEnd,
		&searching, search, altKeys,
		glob_ctrlKeys, NULL, textWrap, maxCols, glyphH );
	printf ( "SB KEY RET: %d\n", ret );


	if ( ret ) {
		goto functEnd;
	}

	functEnd:;

//	printSb ( sb );

	printf ( "keydown_text ( ) OVER\n" );

	return ret;
}

// return 1 if the event is consumed
int jalbJvg_mDown ( SDL_Event *e, int *clickXYpass, int *eleWH, struct jvg *jvgEle,
		float *viewLoc, float viewScale ) {
	if ( debugPrint_jvg_event ) {
		printf ( "jalbJvg_mDown ( )\n" );
		printf ( "cursorInputMode: %d\n", cursorInputMode );
	}

	ArrayList *eles = jvgEle->eles;

	float worldXY[2];
	loc_to_pointI ( clickXYpass, worldXY, viewLoc, viewScale );

	int ret = 0;
	mouseHeld = 1;



	// adding a new ele.
	if ( cursorInputMode == ci_pen ) {
		cursorPen_click ( eles, worldXY );

		ret = 1;
		goto functEnd;

	} else if ( cursorInputMode == ci_rect ) {
			if ( tempEle ) {
				printf ( "TEMP ELE ERROR\n" );
			}
			tempEle = jNakedUnionInit ( );
			jNakedUnionTypeChange0 ( tempEle, jNaked_Rect );
			struct jRect *rect = tempEle->rect;

			float worldXY[2];
			loc_to_pointI ( clickXYpass, worldXY, viewLoc, viewScale );

			rect->XYWH[0] = worldXY[0];
			rect->XYWH[1] = worldXY[1];
			rect->XYWH[2] = 10;
			rect->XYWH[3] = 10;

			set_cursorInputMode ( ci_reg );

/*
			cursorDown;
			printf ( "cursor_depth: %d\n", cursor_depth );

			int i = 2;
			handleCursor_start;
			selected = 1;

			cursorUp;
			handleCursor;
*/

			ret = 1;
			goto functEnd;

	} else if ( cursorInputMode == ci_circ ) {
			if ( tempEle ) {
				printf ( "TEMP ELE ERROR\n" );
			}
			tempEle = jNakedUnionInit ( );
			jNakedUnionTypeChange0 ( tempEle, jNaked_Circ );
			struct jCirc *circ = tempEle->circ;

			float worldXY[2];
			loc_to_pointI ( clickXYpass, worldXY, viewLoc, viewScale );

			circ->XY[0] = worldXY[0];
			circ->XY[1] = worldXY[1];
			circ->radius = 10;

			set_cursorInputMode ( ci_reg );

			ret = 1;
			goto functEnd;

	} else if ( cursorInputMode == ci_complex ) {
			if ( tempEle ) {
				printf ( "TEMP ELE ERROR\n" );
			}

			tempEle = jNakedUnionInit ( );
			jNakedUnionTypeChange0 ( tempEle, jNaked_Complex );
			struct complexEle *complex = tempEle->complex;
			complexEle_initType ( complex, 0 );

//			complex->decType = -1;
			complex->decType = 0;

			float worldXY[2];
			loc_to_pointI ( clickXYpass, worldXY, viewLoc, viewScale );

			complex->XYWH[0] = worldXY[0];
			complex->XYWH[1] = worldXY[1];
			complex->XYWH[2] = 128;
			complex->XYWH[3] = 128;

			set_cursorInputMode ( ci_reg );

			ret = 1;
			goto functEnd;

	} else if ( cursorInputMode == ci_text ) {
	}

//	} else if ( cursorInputMode == ci_reg ) {
//	} else {
//		printf ( "cursorInputMode: %d. unhandled\n", cursorInputMode );
//	}

	if ( debugPrint_jvg_event ) {
		printf ( "presumably ( cursorInputMode == ci_reg )\n" );
		printf ( "glob_cursor_ele: %p\n", glob_cursor_ele );
	}


	// presumably ( cursorInputMode == ci_reg )

//	selected = 0;

	if ( altKeys[akShift] ) {
		// now allow the user to select multple verts.
		// leave cursor how it is.
		// might be selecting a new ele, so init a new hoverMem.
	} else {
		// wipe cursor.
		// TODO use a freeing function.
		emptyArrayList ( glob_cursor_ele->payload->group->eles );
	}


	if ( debugPrint_jvg_event ) {
		printf ( "check clickMem_parent\n" );
	}

	if ( !temp_clickMem_parent ) {
		temp_clickMem_parent = cursor_eleInit ( );
		cursor_unionTypeChange0 ( temp_clickMem_parent->payload, cu_Group );
	} else {
		printf ( "temp_clickMem_parent->payload->type: %d\n", temp_clickMem_parent->payload->type );
		// this might not be a group
		if ( temp_clickMem_parent->payload->type == cu_Group ) {
			emptyArrayList ( temp_clickMem_parent->payload->group->eles );
		} else {
			cursor_unionTypeChange0 ( temp_clickMem_parent->payload, cu_Group );
		}
	}
	temp_clickMem = temp_clickMem_parent;


	printf ( "temp_clickMem_parent: %p\n", temp_clickMem_parent );
	say_cursor_ele ( temp_clickMem_parent );

	// temp, always turn it on for mEvent
	int debugMem = debugPrint_jvg_event;
	debugPrint_jvg_event = 1;
	ret = jNakedList_mEvent_start ( e, clickXYpass, eleWH, eles,
		viewLoc, viewScale );
	debugPrint_jvg_event = debugMem;


//	if ( debugPrint_jvg_event ) {
		printf ( "naked list return: %d\n", ret );
		printf ( "selected: %d\n", selected );
//	}

	if ( ret ) {
//		sayCursor;
		goto functEnd;
	}
	// no ele was clicked on, so clear selected.
	selected = 0;

	// now handle placing eles?
	// this should be done above.



	// i did not clikc on an ele.
	if ( cursorInputMode == ci_text ) {
		cursorText_click ( eles, worldXY );

		ret = 1;
		goto functEnd;
	}


	if ( debugPrint_jvg_event ) {
		printf ( "near end\n" );
	}



	// its not clicking on an ele, and its not trying to add a type.
	if ( e->button.button == SDL_BUTTON_LEFT ) {
		heldType = ht_highlight;

		float fClickXY[2] = { clickXYpass[0], clickXYpass[1] };
		float worldXY[2];
		loc_to_point ( fClickXY, worldXY, viewLoc, viewScale );

		heldStart[0] = worldXY[0];
		heldStart[1] = worldXY[1];

		ret = 1;
		goto functEnd;

	} else if ( e->button.button == SDL_BUTTON_MIDDLE ) {
//		heldType = ht_cameraMove;

		// return 0 because i want jlui to hanlde it.
		ret = 0;
		goto functEnd;

	} else {
		heldType = ht_none;
	}

	functEnd:;

	if ( debugPrint_jvg_event ) {
		printf ( "jalbJvg_mDown ( ) OVER\n" );
	}

	return ret;
}


// return?
int jalbJvg_mMotion ( SDL_Event *e, int *clickXYpass, int *eleWH, struct jvg *jvgEle,
		float *viewLoc, float viewScale ) {
	if ( debugPrint_jvg_event ) {
		printf ( "jalbJvg_mMotion ( )\n" );
		printf ( "heldType: %d\n", heldType );
	}


	int ret = 0;

	float dx = e->motion.xrel * viewScale;
	float dy = e->motion.yrel * viewScale;
	float dXY[2] = { dx, dy };

	if ( tempEle ) {
//		printf ( "tempEle->type: %d\n", tempEle->type );
		if ( tempEle->type == jNaked_Rect ) {
			struct jRect *rect = tempEle->rect;
			rect->XYWH[2] += dx;
			rect->XYWH[3] += dy;
		} else if ( tempEle->type == jNaked_Circ ) {
			struct jCirc *circ = tempEle->circ;
			circ->radius += dx;
		}
		ret = 1;
		goto functEnd;
	}

/*
	float fXY[2] = { clickXYpass[0], clickXYpass[1] };
	loc_to_point ( fXY, cursorWorldLoc, viewLoc, viewScale );
*/

	ArrayList *jEles = jvgEle->eles;

	if ( renderMode == renderM_editAll ||
	     renderMode == renderM_edit ) {
		onHoverCheck ( clickXYpass );
	}


	if ( !selected ||
	     !mouseHeld ) {
		ret = 0;
		goto functEnd;
	}

	// go to the new eleList and handle them.
	if ( heldType == ht_eleMove ) {

		drag_cursor_new ( e, glob_cursor_ele->payload->group->eles, jEles );

		ret = 1;
		goto functEnd;
	}

	goto functEnd;

	/// old
		struct jNakedUnion *parent;
		struct jNakedUnion *ele;
		int vertI = -1;
		int controlI = -1;
		struct cursorMem *lastCursor = NULL;

		int selType = jIterateToSelected ( jEles, &parent, &ele, &vertI, &controlI, &lastCursor );


		printf ( "selType: %d\n", selType );
		printf ( "parent: %p\n", parent );
		printf ( "ele: %p\n", ele );
		printf ( "vertI: %d\n", vertI );
		printf ( "controlI: %d\n", controlI );
		printf ( "lastCursor: %p\n", lastCursor );
		if ( lastCursor ) {
			printf ( "lastCursor->selI: %d\n", lastCursor->selI );
		}


		if ( selType == cs_object ) {
			if ( ele->type == jNaked_Path ) {
				// drag the entire path around.
				dragJPath ( ele->path, dXY );
			}

		} else if ( selType == cs_vert ) {
//			struct jVert *vert = arrayListGetPointer ( ele->path->verts, vertI );
//			vert->XY[0] += dx;
//			vert->XY[1] += dy;

			move_jPathVert ( ele->path, vertI, dx, dy );

		} else if ( selType == cs_control ) {
			struct jLine *line = arrayListGetPointer ( ele->path->lines, vertI );

			if ( controlI == 0 ) {
				line->c0[0] += dx;
				line->c0[1] += dy;
			} else if ( controlI == 1 ) {
				line->c1[0] += dx;
				line->c1[1] += dy;
			}

		} else if ( selType == cs_text ) {
			struct jText *text = ele->text;

/// remove
			if ( vertI == 0 ) {
				// TODO get rid of this, 0 should only mean editing text.
//				text->XYWH[0] += dx;
//				text->XYWH[1] += dy;
			} else if ( vertI == 1 ) {
				text->XYWH[0] += dx;
				text->XYWH[1] += dy;
			} else if ( vertI == 5 ) {
				// TODO, have a minimum size.
				// if i try to make it too small, do i want to move the XY position up and to the left?

				text->XYWH[2] += dx;
				text->XYWH[3] += dy;
			}

		} else if ( selType == cs_rect ) {
			struct jRect *rect = ele->rect;
			if ( vertI == 0 ) {
				// move the whole thing.
				rect->XYWH[0] += dx;
				rect->XYWH[1] += dy;

			} else if ( vertI == 1 ) {
				// top right corner
				rect->XYWH[0] += dx;
				rect->XYWH[1] += dy;
				rect->XYWH[2] -= dx;
				rect->XYWH[3] -= dy;

			} else if ( vertI == 2 ) {
				// bot left corner
				rect->XYWH[2] += dx;
				rect->XYWH[3] += dy;
			}

		} else if ( selType == cs_circ ) {
			struct jCirc *circ = ele->circ;

			printf ( "CS_CIRC selected\n" );

			if ( vertI == 0 ) {
				// dragging

				circ->XY[0] += dx;
				circ->XY[1] += dy;

			} else if ( vertI == 1 ) {
				// reshaping

				// i can improve this at some point.
				circ->radius += dx;

			}

		} else {
			printf ( "unhandled selType: %d\n", selType );
		}

	functEnd:;
	return ret;

	if ( debugPrint_jvg_event ) {
		printf ( "jalbJvg_mMotion ( )\n" );
	}
}



int jNakedList_mEvent_start ( SDL_Event *e, int *clickXYpass, int *eleWH, ArrayList *eles,
		float *viewLoc, float viewScale ) {
	if ( debugPrint_jvg_event ) {
		printf ( "jNakedList_mEvent_start ( )\n" );
	}

	if ( renderMode != renderM_editAll &&
	     renderMode != renderM_edit ) {
		return 0;
	}

	if ( e->button.button == SDL_BUTTON_MIDDLE ) {
		// treat it like im just moving the camera around.
		return 0;
	}



//	if ( altKeys[akShift] ||
//	     altKeys[akCtrl] ) {
	if ( altKeys[akCtrl] ) {
		// if i currently have a vert seleted, the add to it the place i clicked.
		// but if i clicked on a different vert, the draw a line between them.

		struct jNakedUnion *parent;
		struct jNakedUnion *ele;
		int vertI = -1;
		int controlI = -1;
		struct cursorMem *lastCursor;

		int selType = jIterateToSelected ( eles, &parent, &ele,
			&vertI, &controlI, &lastCursor );

		printf ( "vertI: %d\n", vertI );
		if ( selType == cs_vert ) {
			// see if im clicking on another vert.
			// then make sure there is not currently a line between this vert and that.
			// if not, then create only a new line.

			// if im not clicking on another vert, then add a new vert, and a new line.

			struct jPath *path = ele->path;

			if ( altKeys[akShift] ) {
				add_line ( path, vertI, path_LineTo, clickXYpass,
					viewLoc, viewScale );
			} else if ( altKeys[akCtrl] ) {
				add_line ( path, vertI, path_CubicBez, clickXYpass,
					viewLoc, viewScale );
			}

			return 1;
		}
	}
	return jNakedList_mEvent ( e, clickXYpass, eleWH, eles,
		viewLoc, viewScale );
}

// iterate through every ele, and runs the specific mEvent funct for each one.
// If they return 1, then they are set as the selected element, and the function returns.
int jNakedList_mEvent ( SDL_Event *e, int *clickXYpass, int *eleWH, ArrayList *eles,
		float *viewLoc, float viewScale ) {
	if ( debugPrint_jvg_event ) {
		printf ( "jNakedList_mEvent ( )\n" );
	}

	int i;
	int len;

	i = 0;
	len = arrayListGetLength ( eles );
	while ( i < len ) {
		struct jNakedUnion *uni = arrayListGetPointer ( eles, i );

		// sets the index here, so if the click is good and gets added to the glob cursor, it already knows its index.
		temp_clickMem->index = i;
		temp_clickIndex = i;

		if ( uni->type == jNaked_G ) {
//			printf ( "TODO\n" );
			struct jGroup *g = uni->g;

			int ret = jNakedList_mEvent ( e, clickXYpass, eleWH, g->eles,
				viewLoc, viewScale );
			if ( ret == 1 ) {
				if ( debugPrint_jvg_event ) printf ( "group ret: %d\n", ret );
				return ret;
			}

		} else if ( uni->type == jNaked_Path ) {
			struct jPath *path = uni->path;
			int ret = jPath_mEvent ( e, clickXYpass, eleWH, path,
				viewLoc, viewScale );
			if ( ret == 1 ) {
				if ( debugPrint_jvg_event ) printf ( "path ret: %d\n", ret );
				return ret;
			}

		} else if ( uni->type == jNaked_Text ) {
			struct jText *text = uni->text;
			int ret = jText_mEvent ( e, clickXYpass, eleWH, text,
				viewLoc, viewScale );

			if ( ret == 1 ) {
				if ( debugPrint_jvg_event ) printf ( "text ret: %d\n", ret );
				return ret;
			}

		} else if ( uni->type == jNaked_Rect ) {
			struct jRect *rect = uni->rect;
			int ret = jRect_mEvent ( e, clickXYpass, eleWH, rect,
				viewLoc, viewScale );
			if ( ret == 1 ) {
				if ( debugPrint_jvg_event ) printf ( "rect ret: %d\n", ret );
				return ret;
			}

		} else if ( uni->type == jNaked_Circ ) {
			struct jCirc *circ = uni->circ;
			int ret = jCirc_mEvent ( e, clickXYpass, eleWH, circ,
				viewLoc, viewScale );
			if ( ret ) {
				if ( debugPrint_jvg_event ) printf ( "circ ret: %d\n", ret );
				return ret;
			}

		} else if ( uni->type == jNaked_Complex ) {
			struct complexEle *complex = uni->complex;
			int ret = complexEle_mEvent ( e, clickXYpass, eleWH, complex,
				viewLoc, viewScale );

			if ( ret == 1 ) {
				if ( debugPrint_jvg_event ) printf ( "complex ret: %d\n", ret );
				return ret;
			}
		}

		i += 1;
	}

	if ( debugPrint_jvg_event ) {
		printf ( "jNakedList_mEvent ( ) OVER\n" );
	}

	return 0;
}


void set_cursorList_text ( ) {
	printf ( "set_cursorList_text ( )\n" );

	// handle cursor.
	cursor_unionTypeChange0 ( temp_clickMem->payload, cu_Text );
	struct cursor_text *cuText = temp_clickMem->payload->text;
	cuText->vertI = 0;

	ArrayList *cursorList = glob_cursor_ele->payload->group->eles;
	int toggleRet = toggle_cursorEle ( cursorList, temp_clickMem_parent );
	if ( toggleRet == 0 ) {
		// TODO handle depth better.
		arrayListAddEndPointer ( cursorList, temp_clickMem_parent );
		temp_clickMem_parent = NULL;
	}

	printf ( "set_cursorList_text ( ) OVER\n" );
}

void set_cursorList_complex ( ) {
	printf ( "set_cursorList_complex ( )\n" );

	// handle cursor.
	cursor_unionTypeChange0 ( temp_clickMem->payload, cu_ComplexEle );
//	struct cursor_text *cuText = temp_clickMem->payload->text;
//	cuText->vertI = 0;

	printf ( "changed\n" );

	ArrayList *cursorList = glob_cursor_ele->payload->group->eles;
	int toggleRet = toggle_cursorEle ( cursorList, temp_clickMem_parent );
	if ( toggleRet == 0 ) {
		// TODO handle depth better.
		arrayListAddEndPointer ( cursorList, temp_clickMem_parent );
		temp_clickMem_parent = NULL;
	}

	printf ( "set_cursorList_complex ( ) OVER\n" );
}

// wrapper funct for complexEle.
int jText_event ( SDL_Event *e, int *clickXYpass, int *eleWH, struct jText *text,
		float *viewLoc, float viewScale ) {
	printf ( "jText_event ( )\n" );
	printf ( "text: %p\n", text );

	int ret = 0;
	if ( e->type == SDL_KEYDOWN ) {
		ret = keydown_text ( e, text );

	} else if ( e->type == SDL_MOUSEBUTTONDOWN ) {
		ret = jText_mEvent ( e, clickXYpass, eleWH, text,
			viewLoc, viewScale );
	}
	return ret;
}

int cursorSet_override = 0;

int jText_mEvent ( SDL_Event *e, int *clickXYpass, int *eleWH, struct jText *text,
		float *viewLoc, float viewScale ) {
	printf ( "jText_mEvent ( )\n" );
	printf ( "text: %p\n", text );

	float screenXYWH[4];
	point_to_loc ( text->XYWH, screenXYWH, viewLoc, viewScale );

	screenXYWH[2] = text->XYWH[2] / viewScale;
	screenXYWH[3] = text->XYWH[3] / viewScale;


	int ret = 0;

//	sayIntArray ( "clickXYpass", clickXYpass, 2 );
//	sayFloatArray ( "screenXYWH", screenXYWH, 4 );

	// check the entire box, for editing the text,
	// below is the resize and move boxes.
	if ( pointInsideI ( clickXYpass, screenXYWH ) ) {
		if ( altKeys[akCtrl] ) {
			printf ( "spawn text edit \n" );

			if ( uiGenApi ) {
				uiGenApi->load_and_set_norm ( uiGen_jTextEdit, text );
			} else {
				printf ( "cant open, !uiGenApi\n" );
			}
		}

		printf ( "CLICKED IN TEXT\n" );
		if ( !cursorSet_override ) {
			set_cursorList_text ( );
			selected = 1;
		}

/*
		// i doesnt matter, aslong as its 1 deeper than the text ele itself so i know im editing the internal text, not moving the ele around
		int i = 0;
		handleCursor_start;

		selected = 1;
		cStart[0] = 0;
		cEnd[0] = 0;
*/

		float glyphWH[2] = {
			fonts[0]->atlasInfo.glyphW / viewScale,
			fonts[0]->atlasInfo.glyphH / viewScale
		};
//		sayFloatArray ( "glyphWH", glyphWH, 2 );

		int charXY[2];
		charXY[0] = (clickXYpass[0] - screenXYWH[0]) / glyphWH[0] + 0.5;
		charXY[1] = (clickXYpass[1] - screenXYWH[1]) / glyphWH[1];

//		sayIntArray ( "charXY", charXY, 2 );

			
		int maxCols = text->XYWH[2] / fonts[0]->atlasInfo.glyphW;
		int textWrap = 1;

//		printf ( "maxCols: %d\n", maxCols );

		int overClickLines = -1;
		// determines the index of the click (this should also handle return the cursorXY...)
		int ret2 = newSbClickToIndex_wrap ( charXY, text->sb, maxCols, tabW, &overClickLines );

//		printf ( "ret2: %d\n", ret2 );

		cStart[0] = ret2;
		cEnd[0] = ret2;

		// takes the index and returnes the clickXY
		newSbIndexToCoords ( cStart[0], &cStart[1], text->sb, textWrap, maxCols, tabW );

//		return 1;
		ret = 1;
		goto functEnd;
	}

	// so if its 1 deeper with a value of 0 then im editing the text.
	// 0 = editing text, 1 = moving it around.
	// 2 im editing top left corner? 3 top right.
	// 4 bot left, 5 bot right.
	// see if i click on the bottom right, so adjust the size.

	int boxWidth = jText_box_width / viewScale;
	float boxXYWH[4] = {
		screenXYWH[0],
		screenXYWH[1] - boxWidth,
		screenXYWH[2],
		boxWidth,
	};

	if ( pointInsideI ( clickXYpass, boxXYWH ) ) {
		printf ( "ADJUST top BAR\n" );

		// handle cursor.
		cursor_unionTypeChange0 ( temp_clickMem->payload, cu_Text );
		struct cursor_text *cuText = temp_clickMem->payload->text;
		cuText->vertI = text_move;

		ArrayList *cursorList = glob_cursor_ele->payload->group->eles;
		int toggleRet = toggle_cursorEle ( cursorList, temp_clickMem_parent );
		if ( toggleRet == 0 ) {
			// TODO handle depth better.
			arrayListAddEndPointer ( cursorList, temp_clickMem_parent );
			temp_clickMem_parent = NULL;
		}

		heldType = ht_eleMove;


/*
		int i = 1;

//		cursorDown;
		handleCursor_start;
//		cursorUp;
*/
		selected = 1;

//		return 1;
		ret = 1;
		goto functEnd;
	}

	// check top bar for moving it around.

	// the box in "screen space"
	boxXYWH[0] = screenXYWH[0] + screenXYWH[2];
	boxXYWH[1] = screenXYWH[1] + screenXYWH[3];
	boxXYWH[2] = boxWidth;
	boxXYWH[3] = boxWidth;

	// check bottom right corner.
	if ( pointInsideI ( clickXYpass, boxXYWH ) ) {
		printf ( "ADJUST CORNER\n" );
		printf ( "cursor_depth: %d\n", cursor_depth );


		// handle cursor.
		cursor_unionTypeChange0 ( temp_clickMem->payload, cu_Text );
		struct cursor_text *cuText = temp_clickMem->payload->text;
		cuText->vertI = text_botRight;

		ArrayList *cursorList = glob_cursor_ele->payload->group->eles;
		int toggleRet = toggle_cursorEle ( cursorList, temp_clickMem_parent );
		if ( toggleRet == 0 ) {
			// TODO handle depth better.
			arrayListAddEndPointer ( cursorList, temp_clickMem_parent );
			temp_clickMem_parent = NULL;
		}

		heldType = ht_eleMove;



/*
		int i = 5;

//		cursorDown;
		handleCursor_start;
//		cursorUp;
*/
		selected = 1;

//		return 1;
		ret = 1;
		goto functEnd;
	}

	functEnd:;
	printf ( "jText_mEvent ( ) OVER\n" );
	printf ( "ret: %d\n", ret );

	return ret;
}


int jRect_mEvent ( SDL_Event *e, int *clickXYpass, int *eleWH, struct jRect *rect,
		float *viewLoc, float viewScale ) {
	printf ( "jRect_mEvent ( )\n" );

	int ret = jRect_mPos ( clickXYpass, rect,
		viewLoc, viewScale );

	printf ( "jRect_mPos ret: %d\n", ret );
//	printf ( "cursor_depth: %d\n", cursor_depth );

	int thisSelected = 0;
	if ( ret == 0 ) {
		selected = 1;
		thisSelected = 1;
	} else if ( ret == 1 ) {
		selected = 1;
		thisSelected = 1;
	} else if ( ret == 2 ) {
		selected = 1;
		thisSelected = 1;
	}


	// i want this to be the top ele
	ArrayList *cursorList = glob_cursor_ele->payload->group->eles;

	if ( thisSelected ) {
		cursor_unionTypeChange0 ( temp_clickMem->payload, cu_Rect );
		struct cursor_rect *cuRect = temp_clickMem->payload->rect;
		cuRect->type = ret;

		int toggleRet = toggle_cursorEle ( cursorList, temp_clickMem_parent );
		printf ( "toggleRet: %d\n", toggleRet );

		if ( toggleRet == 0 ) {
			heldType = ht_eleMove;
			arrayListAddEndPointer ( cursorList, temp_clickMem_parent );
			// this ele is in the list, so nexttime init a new one.
			temp_clickMem_parent = NULL;
		}

		return 1;
	}

	return 0;
}

// return 1 if its on the top left corner
// 2 if bottom right
// 0 is close enough to an edge
// -1 else
int jRect_mPos ( int *clickXYpass, struct jRect *rect,
		float *viewLoc, float viewScale ) {
//	printf ( "jRect_mPos ( )\n" );

	// vertWidth

	// first check the 2 corners, then check to see if i clicked on a line.


//	struct jVert *v0 = arrayListGetPointer ( path->verts, line->v0 );
//	struct jVert *v1 = arrayListGetPointer ( path->verts, line->v1 );

	// i feel like i should not convert the click to the world, but convert the shape to the screen.
	// whatever
	float fXY[2] = { clickXYpass[0], clickXYpass[1] };
	loc_to_point ( fXY, fXY, viewLoc, viewScale );
/*
	sayFloatArray ( "click to screen", fXY, 2 );
	sayFloatArray ( "rect->XYWH", rect->XYWH, 4 );
*/

	/// 2 corners

	// top left
	float rendWidth = vertWidth * viewScale;
//	printf ( "rendWidth: %f\n", rendWidth );

	float box[4] = {
		rect->XYWH[0] - rendWidth/2,
		rect->XYWH[1] - rendWidth/2,
		rendWidth,
		rendWidth,
	};
//	sayFloatArray ( "box", box, 4 );

	if ( pointInside ( fXY, box ) ) {
/*
		int i = 1;
		handleCursor_start;
		selected = 1;

		return 1;
*/
		return 1;
	}

	// bot right
	box[0] += rect->XYWH[2];
	box[1] += rect->XYWH[3];
	if ( pointInside ( fXY, box ) ) {
/*
		int i = 2;
		handleCursor_start;
		selected = 1;

		return 1;
*/
		return 2;
	}



	/// 4 lines

	// top line

	float topLeft[2] = {
		rect->XYWH[0],
		rect->XYWH[1],
	};
	float topRight[2] = {
		rect->XYWH[0] + rect->XYWH[2],
		rect->XYWH[1],
	};
	float botRight[2] = {
		rect->XYWH[0] + rect->XYWH[2],
		rect->XYWH[1] + rect->XYWH[3],
	};
	float botLeft[2] = {
		rect->XYWH[0],
		rect->XYWH[1] + rect->XYWH[3],
	};
/*
	loc_to_point ( topLeft, topLeft, viewLoc, viewScale );
	loc_to_point ( topRight, topRight, viewLoc, viewScale );
	loc_to_point ( botRight, botRight, viewLoc, viewScale );
	loc_to_point ( botLeft, botLeft, viewLoc, viewScale );
*/

	float dist_top = pointSegDist ( fXY, topLeft, topRight );
//	printf ( "line dist: %f\n", dist );
	float dist_right = pointSegDist ( fXY, topRight, botRight );
	float dist_bot = pointSegDist ( fXY, botRight, botLeft );
	float dist_left = pointSegDist ( fXY, botLeft, topLeft );

	dist_top /= viewScale;
	dist_right /= viewScale;
	dist_bot /= viewScale;
	dist_left /= viewScale;

/*
	printf ( "pointDist: %d\n", pointDist );
	printf ( "dist_top: %f\n", dist_top );
	printf ( "dist_right: %f\n", dist_right );
	printf ( "dist_bot: %f\n", dist_bot );
	printf ( "dist_left: %f\n", dist_left );
*/

	if ( dist_top < pointDist ||
	     dist_right < pointDist ||
	     dist_bot < pointDist ||
	     dist_left < pointDist ) {
/*
		int i = 0;
		handleCursor_start;
		selected = 1;

		return 1;
*/
		return 0;
	}

	return -1;
}

extern int controlPointWidth;

// return 1 if it is in the center, or the right.
int jCirc_mEvent ( SDL_Event *e, int *clickXYpass, int *eleWH, struct jCirc *circ,
		float *viewLoc, float viewScale ) {

	printf ( "jCirc_mEvent ( )\n" );

	int circRet = jCirc_click ( clickXYpass, eleWH, circ,
		viewLoc, viewScale );

	// empty cursorList?
	// naw its more complicated than that.

	// i want this to be the top ele
	ArrayList *cursorList = glob_cursor_ele->payload->group->eles;

	if ( circRet == circ_center ) {
		// circ center, for moving

	// unit w/ a bove
		cursor_unionTypeChange0 ( temp_clickMem->payload, cu_Circ );
		struct cursor_circ *cuCirc = temp_clickMem->payload->circ;
		cuCirc->type = circ_center;

		int toggleRet = toggle_cursorEle ( cursorList, temp_clickMem_parent );
		printf ( "toggleRet: %d\n", toggleRet );

		if ( toggleRet == 0 ) {
			heldType = ht_eleMove;
			arrayListAddEndPointer ( cursorList, temp_clickMem_parent );
			// this ele is in the list, so nexttime init a new one.
			temp_clickMem_parent = NULL;
		}

		selected = 1;
	} else if ( circRet == circ_right ) {
		// circ_right, for rescaling

	// unite w/ above
		cursor_unionTypeChange0 ( temp_clickMem->payload, cu_Circ );
		struct cursor_circ *cuCirc = temp_clickMem->payload->circ;
		cuCirc->type = circ_right;

		int toggleRet = toggle_cursorEle ( cursorList, temp_clickMem_parent );
		printf ( "toggleRet: %d\n", toggleRet );

		if ( toggleRet == 0 ) {
			heldType = ht_eleMove;
			arrayListAddEndPointer ( cursorList, temp_clickMem_parent );
			// this ele is in the list, so nexttime init a new one.
			temp_clickMem_parent = NULL;
		}

		selected = 1;
	}

//	printf ( "temp_clickMem_parent: %p\n", temp_clickMem_parent );
//	say_cursor_ele ( temp_clickMem_parent );

	printf ( "jCirc_mEvent ( ) OVER\n" );

	return circRet;
}

// return 1 if its in the center, 2 if its on the side.
// eleWH isnt necessary rn.
/// TODO unite with hover.
int jCirc_click ( int *clickXYpass, int *eleWH, struct jCirc *circ,
		float *viewLoc, float viewScale ) {
	// TODO i should not convert this to screen loc, leave it as world?

	float screenXY[4];
	point_to_loc ( circ->XY, screenXY, viewLoc, viewScale );

	int cWidth = controlPointWidth / viewScale;

	// first check the center and drag location
	float iXYWH[4];
	iXYWH[0] = screenXY[0] - (cWidth / 2);
	iXYWH[1] = screenXY[1] - (cWidth / 2);
	iXYWH[2] = cWidth;
	iXYWH[3] = cWidth;
	if ( pointInsideI ( clickXYpass, iXYWH ) ) {
		printf ( "click inside center\n" );

		return 1;
	}


	iXYWH[0] = circ->XY[0] + circ->radius;;
	iXYWH[1] = circ->XY[1];
	// now check the right side.
	point_to_loc ( iXYWH, screenXY, viewLoc, viewScale );

	// now check the right side and change radius.
	iXYWH[0] = screenXY[0] - (cWidth / 2);
	iXYWH[1] = screenXY[1] - (cWidth / 2);

	if ( pointInsideI ( clickXYpass, iXYWH ) ) {
		printf ( "click inside right\n" );

		return 2;
	}

	return 0;
}


/// Specific Pens

int cursorPen_click ( ArrayList *eles, float *worldXY ) {
//	float viewScale = glob_viewScale;
//	float *viewLoc = glob_viewLoc;

	int ret = 0;
		// see if i am connectign to an already existing path.
		// if edit all, check every path.

		int vertI = -1;

		int numTopEles = arrayListGetLength ( glob_cursor_ele->payload->group->eles );

		if ( numTopEles == 1 ) {
			struct cursor_ele *subEle = arrayListGetPointer ( glob_cursor_ele->payload->group->eles, 0 );

			struct jPath *path = onlyVertSelected ( subEle, eles, &vertI );
			printf ( "path: %p\n", path );
			printf ( "&vertI: %p\n", &vertI );
			printf ( "vertI: %d\n", vertI );
			if ( path ) {
				// in theory only 1 vert is selected.

				// am i clicking on 1?
				int newVertI = isOnVert_world ( path, worldXY );

				if ( newVertI == -1 ) {
					struct jVert *vert = jVertInit ( );
					newVertI = arrayListGetLength ( path->verts );
					arrayListAddEndPointer ( path->verts, vert );
					vert->XY[0] = worldXY[0];
					vert->XY[1] = worldXY[1];
				}

				printf ( "newVertI: %d\n", newVertI );

				struct jLine *line = jLineInit ( );
				arrayListAddEndPointer ( path->lines, line );
				line->v0 = vertI;
				line->v1 = newVertI;
				line->type = path_LineTo;

				// update cursor
				update_cursor_path ( glob_cursor_ele, newVertI );

				ret = 1;
			}
		}
		if ( !ret ) {
			// add a new path.

			int newEleI = arrayListGetLength ( eles );

//			float worldXY[2];
//			loc_to_pointI ( clickXYpass, worldXY, viewLoc, viewScale );

			struct jNakedUnion *ele = jNakedUnionInit ( );
			arrayListAddEndPointer ( eles, ele );
			jNakedUnionTypeChange0 ( ele, jNaked_Path );
			struct jPath *path = ele->path;
			struct jVert *vert = jVertInit ( );
			arrayListAddEndPointer ( path->verts, vert );
			vert->XY[0] = worldXY[0];
			vert->XY[1] = worldXY[1];

			// set the cursor to this ele.
			// TODO, am i in a vert.
			emptyArrayList ( glob_cursor_ele->payload->group->eles );
			struct cursor_ele *subCursor = cursor_eleInit ( );
			arrayListAddEndPointer ( glob_cursor_ele->payload->group->eles, subCursor );
			subCursor->index = newEleI;
			cursor_unionTypeChange0 ( subCursor->payload, cu_Path );
			int *vertI = arrayListGetNext ( subCursor->payload->path->verts );
			*vertI = 0;

//			set_cursorInputMode ( ci_reg );
		}
	return ret;
}

void cursorText_click ( ArrayList *eles, float *worldXY ) {

	printf ( "cursorText_click ( )\n" );

	// create a new jText

	int defaultWH[2] = { 300, 300 };

//	float fClickXY[2] = { clickXYpass[0], clickXYpass[1] };
//	float worldXY[2];
//	loc_to_point ( fClickXY, worldXY, viewLoc, viewScale );


//	struct jText *text = jTextInit ( );
	struct jNakedUnion *naked = jNakedUnionInit ( );
	arrayListAddEndPointer ( eles, naked );
	jNakedUnionTypeChange0 ( naked, jNaked_Text );
	struct jText *text = naked->text;
	text->XYWH[0] = worldXY[0];
	text->XYWH[1] = worldXY[1];
	text->XYWH[2] = defaultWH[0];
	text->XYWH[3] = defaultWH[1];

/*
			{
				cursor_depth = 1;
				int i = 0;	// irrelevent, just needs to be 1 deeper than the text box.
				handleCursor_start;
			}

			printf ( "set second part\n" );

			{
				cursor_depth = 0;
				int i = arrayListGetLength ( global_jEles ) - 1;
				handleCursor;
			}
*/


	selected = 1;

	cStart[0] = 0;
	cEnd[0] = 0;
	cStart[1] = 0;
	cStart[2] = 0;
	cEnd[1] = 0;
	cEnd[2] = 0;

//	sayCursor;

	set_cursorInputMode ( ci_reg );


	printf ( "cursorText_click ( ) OVER\n" );
}

/// Other


// see if only 1 vertex is selected.
// if so, return that path?
struct jPath *onlyVertSelected ( struct cursor_ele *cursor, ArrayList *eleList, int *vertI ) {
	printf ( "onlyVertSelected ( )\n" );
	printf ( "cursor->payload->type: %d\n", cursor->payload->type );

	struct jNakedUnion *uni = arrayListGetPointer ( eleList, cursor->index );

	if ( cursor->payload->type == cu_Group ) {
		// iterate through
		int numSub = arrayListGetLength ( cursor->payload->group->eles );

		if ( numSub == 1 ) {
			struct cursor_ele *subCursor = arrayListGetPointer ( cursor->payload->group->eles, 0 );

			// because cursor is of type group, then i know this ele is of type group.
			if ( uni->type == jNaked_G ) {
				struct jGroup *group = uni->g;
				struct jPath *path = onlyVertSelected ( subCursor, group->eles, vertI );
				return path;
			} else {
				// ERROR
				printf ( "ERROR, onlyVertSelected ( ) expected uni of type group, have %d\n", uni->type );
			}

		} else {
			return NULL;
		}

	} else if ( cursor->payload->type == cu_Path ) {
		struct cursor_path *cursorPath = cursor->payload->path;
		int numVertsSelected = arrayListGetLength ( cursorPath->verts );
		if ( numVertsSelected == 1 ) {
			if ( uni->type == jNaked_Path ) {
				int *vPtr = arrayListDataPointer ( cursorPath->verts, 0 );
				*vertI = *vPtr;
				return uni->path;
			} else {
				printf ( "ERROR, onlyVertSelected ( )\n" );
			}
		} else {
			return NULL;
		}
	} else {
		printf ( "TODO\n" );
	}
	return NULL;
}

// already know only 1 vert is selected.
void update_cursor_path ( struct cursor_ele *cursor, int newI ) {
	while ( 1 ) {
		if ( cursor->payload->type == cu_Group ) {
			cursor = arrayListGetPointer ( cursor->payload->group->eles, 0 );
		} else if ( cursor->payload->type == cu_Path ) {
			int *vertPtr = arrayListDataPointer ( cursor->payload->path->verts, 0 );
			*vertPtr = newI;
			break;
		} else {
			printf ( "error 1\n" );
			break;
		}
	}
}







// heldType is eleMove
void drag_cursor_new ( SDL_Event *e, ArrayList *cursorList, ArrayList *eleList ) {
	printf ( "drag_cursor_new ( )\n" );

	float viewScale = glob_viewScale;

	float dx = e->motion.xrel * viewScale;
	float dy = e->motion.yrel * viewScale;

	float dXY[2] = { dx, dy };

	int i = 0;
	int len = arrayListGetLength ( cursorList );

	printf ( "cursorList.len: %d\n", len );

	while ( i < len ) {
		struct cursor_ele *ele = arrayListGetPointer ( cursorList, i );

		struct jNakedUnion *jUni = arrayListGetPointer ( eleList, ele->index );

		if ( ele->payload->type == cu_Path ) {
			struct cursor_path *cuPath = ele->payload->path;

			if ( cuPath->itself ) {
			} else {
				drag_cursor_path ( jUni, cuPath, dXY );
				// drag the verts.
			}

		} else if ( ele->payload->type == cu_Group ) {
			printf ( "TODO, drag_cursor_new ( )\n" );

		} else if ( ele->payload->type == cu_Circ ) {
			struct cursor_circ *cuCirc = ele->payload->circ;

			struct jCirc *circ = jUni->circ;

			if ( cuCirc->type == circ_center ) {
				// dragging

				circ->XY[0] += dx;
				circ->XY[1] += dy;

			} else if ( cuCirc->type == circ_right ) {
				// reshaping

				// i can improve this at some point.
				circ->radius += dx;

			}

		} else if ( ele->payload->type == cu_Text ) {
			struct cursor_text *cuText = ele->payload->text;
			struct jText *text = jUni->text;

			int vertI = cuText->vertI;
			if ( vertI == 0 ) {
				// TODO get rid of this, 0 should only mean editing text.
//				text->XYWH[0] += dx;
//				text->XYWH[1] += dy;
			} else if ( vertI == text_move ) {
				text->XYWH[0] += dx;
				text->XYWH[1] += dy;
			} else if ( vertI == text_botRight ) {
				// TODO, have a minimum size.
				// if i try to make it too small, do i want to move the XY position up and to the left?

				text->XYWH[2] += dx;
				text->XYWH[3] += dy;
			}

		} else if ( ele->payload->type == cu_Rect ) {
			struct cursor_rect *cuRect = ele->payload->rect;

			struct jRect *rect = jUni->rect;
			if ( cuRect->type == 0 ) {
				// move the whole thing.
				rect->XYWH[0] += dx;
				rect->XYWH[1] += dy;

			} else if ( cuRect->type == 1 ) {
				// top right corner
				rect->XYWH[0] += dx;
				rect->XYWH[1] += dy;
				rect->XYWH[2] -= dx;
				rect->XYWH[3] -= dy;

			} else if ( cuRect->type == 2 ) {
				// bot left corner
				rect->XYWH[2] += dx;
				rect->XYWH[3] += dy;
			}

		} else {
			printf ( "TODO, drag_cursor_new, type: %d\n", ele->payload->type );
		}

		i += 1;
	}
}

void drag_cursor_path ( struct jNakedUnion *ele, struct cursor_path *cuPath, float *dXY ) {
	int i = 0;
	int len = arrayListGetLength ( cuPath->verts );
	while ( i < len ) {
		int *vertI = arrayListDataPointer ( cuPath->verts, i );
		move_jPathVert ( ele->path, *vertI, dXY[0], dXY[1] );

		i += 1;
	}
}


int keySpecialChar ( SDL_Event *e, ArrayList *sb ) {
	int ret = 0;
	if ( e->key.keysym.sym == SDLK_h ) {		// Math characters
		add_special ( sb, spec_therefore );
		ret = 1;

	} else if ( e->key.keysym.sym == SDLK_7 ) {
		add_special ( sb, spec_and );
		ret = 1;

	} else if ( e->key.keysym.sym == SDLK_BACKSLASH ) {
		add_special ( sb, spec_or );
		ret = 1;

	} else if ( e->key.keysym.sym == SDLK_m ) {
		add_special ( sb, spec_micro );
		ret = 1;

	} else if ( e->key.keysym.sym == SDLK_j ) {
		add_special ( sb, spec_emptySet );
		ret = 1;


	} else if ( e->key.keysym.sym == SDLK_k ) {	// Greek Letters
		add_special ( sb, spec_alphaL );
		ret = 1;

	} else if ( e->key.keysym.sym == SDLK_b ) {
		add_special ( sb, spec_betaL );
		ret = 1;

	} else if ( e->key.keysym.sym == SDLK_d ) {
		if ( altKeys[akShift] ) {
			add_special ( sb, spec_deltaU );
		} else {
			add_special ( sb, spec_deltaL );
		}
		ret = 1;

	} else if ( e->key.keysym.sym == SDLK_y ) {
		add_special ( sb, spec_thetaL );
		ret = 1;

	} else if ( e->key.keysym.sym == SDLK_u ) {
		add_special ( sb, spec_lambdaL );
		ret = 1;

	} else if ( e->key.keysym.sym == SDLK_p ) {
		add_special ( sb, spec_pi );
		ret = 1;

	} else if ( e->key.keysym.sym == SDLK_i ) {
//		add_special ( sb, spec_rhoL );
		add_special ( sb, spec_integral );
		ret = 1;

	} else if ( e->key.keysym.sym == SDLK_o ) {
		if ( altKeys[akShift] ) {
			add_special ( sb, spec_omegaU );
		} else {
			add_special ( sb, spec_omegaL );
		}
		ret = 1;

	}

	return ret;
}


/** Cursor Ext */


/// TODO move
// shift is held down, so if this partially exists, add the new info.
// if it doesnt exist at all, add it.
// if it full exists, then untoggle it.
// return 1 if it was found and handled.
// return 0 if none of it was found and needs to be added wholesale
// return 2 if it was found and unselected, and its payload is now empty, so check as u go up to see if this needs to be deleted.
// cursorList is the list from my top cursorEle.
int toggle_cursorEle ( ArrayList *cursorList, struct cursor_ele *temp ) {
	printf ( "toggle_cursorEle ( )\n" );

	printf ( "temp: %p\n", temp );
	printf ( "temp->index: %d\n", temp->index );
	printf ( "temp->payload->type: %d\n", temp->payload->type );

	int i = 0;
	int len = arrayListGetLength ( cursorList );
	printf ( "cursorList.len: %d\n", len );

	// iterates through the cursor list, looking at every element.
	// if one matches this index, then run toggle_cursorChild ( )
	while ( i < len ) {
		struct cursor_ele *ele = arrayListGetPointer ( cursorList, i );

		printf ( "ele->index: %d\n", ele->index );

		if ( ele->index == temp->index ) {
			int ret = toggle_cursorEle_child ( ele, temp );
			if ( ret == 2 ) {
				// todo free
				arrayListRemove ( cursorList, i );
			}

			printf ( "toggle_cursorEle ( ) OVER a\n" );
			return ret;
		}
		i += 1;
	}

	printf ( "toggle_cursorEle ( ) OVER b\n" );
	return 0;
}

// split these into 2 parts, cuz the parent needs to see if the ele needs to be deleted...
// actually that doesnt make a ton of sense.

// i have discovered that this ele (at this depth) is already in the list, so now check the...
// ele is from the actual cursorList
int toggle_cursorEle_child ( struct cursor_ele *ele, struct cursor_ele *temp ) {
	printf ( "toggle_cursorEle_child ( )\n" );
	printf ( "ele: %p\n", ele );
	say_cursor_ele ( ele );
	printf ( "temp: %p\n", temp );
	say_cursor_ele ( temp );

/*
	printf ( "toggle_cursorEle ( )\n" );

	printf ( "temp->index: %d\n", temp->index );
	printf ( "temp->payload->type: %d\n", temp->payload->type );

	ArrayList 

	int i = 0;
	int len = arrayListGetLength ( cursorList );
	printf ( "cursorList.len: %d\n", len );

	while ( i < len ) {
		struct cursor_ele *ele = arrayListGetPointer ( cursorList, i );

		printf ( "ele->index: %d\n", ele->index );

		if ( ele->index == temp->index ) {
			// partially exists
*/

			printf ( "partial match\n" );
			printf ( "ele->payload->type: %d\n", ele->payload->type );

			if ( ele->payload->type == cu_Group ) {
				// TODO
				printf ( "TODO group recur\n" );

			} else if ( ele->payload->type == cu_Path ) {
				// see if the index is already there.

				struct cursor_path *elePath = ele->payload->path;
				struct cursor_path *tempPath = temp->payload->path;	// todo type check

				if ( elePath->itself ) {
					// todo
				}
				// this ought to return the index.
				// al_getIndex_int

				printf ( "tempPath->verts.len: %d\n", arrayListGetLength ( tempPath->verts ) );
				printf ( "elePath->verts.len: %d\n", arrayListGetLength ( elePath->verts ) );

				int *tempIndex = arrayListDataPointer ( tempPath->verts, 0 ); // rn it only has 1 ele, but eventually allow me to select multiple at once?

printf ( "tempIndex: %p\n", tempIndex );
printf ( "*tempIndex: %d\n", *tempIndex );

				int has = al_hasInt ( elePath->verts, *tempIndex );

printf ( "has: %d\n", has );

				if ( has ) {
					// this ele was already selected, so unselect it.

					printf ( "REMOVE: %d\n", *tempIndex );
					int index = al_getIndex_int ( elePath->verts, *tempIndex );
					arrayListRemove ( elePath->verts, index );

					if ( arrayListGetLength ( elePath->verts ) == 0 ) {
						// no eles remain, so delete this.
						return 2;
					}
				} else {
					int *next = arrayListGetNext ( elePath->verts );
					*next = *tempIndex;
				}
			} else if ( ele->payload->type == cu_Text ) {
				printf ( "TODO, toggle_cursorEle ( )\n" );
			} else {
				printf ( "TODO, toggle_cursorEle ( )\n" );
			}

			printf ( "toggle_cursorEle ( ) OVER b\n" );
			return 1;

/*
		}

		i += 1;
	}

	printf ( "toggle_cursorEle  ( ) OVER a\n" );
*/
	return 0;
}

void remove_pathEle ( ) {
	// todo
	// this might lead to the deletion of this entire cursorEle.
}


/// TODO, not used anymore since i changed how jvg cursor works

// much like iterateToSelected ( ) (event.h)

// iterate to the object that cursor is selecting.
/* return enum cursorType
 * object:
 *  the object itself, and its parent.
 * vert:
 *  the object and, vert index, the cursorMem so i can update it to the newly created ele.
 * control:
 *  the object, vert index, and control index.
 */
int jIterateToSelected ( ArrayList *eleList, struct jNakedUnion **parent, struct jNakedUnion **ele,
		int *vertI, int *controlI, struct cursorMem **lastCursor ) {
	if ( debugPrint_jIterate ) {
		printf ( "jIterateToSelected ( )\n" );
	}

/*
	int i = 0;
	int len = arrayListGetLength ( cursorList );

	if ( debugPrint_jIterate ) {
		printf ( "cursorList.len: %d\n", len );
	}

	struct jNakedUnion *uni = NULL;
//	ArrayList *nextList = svg->eles;
	ArrayList *nextList = eleList;
	struct cursorMem *mem = NULL;

	if ( len == 1 ) {
		// its an object or group or something.
		// TODO

		mem = arrayListGetPointer ( cursorList, 0 );
//		printf ( "mem->selI: %d\n", mem->selI );
		uni = arrayListGetPointer ( nextList, mem->selI );
	}

	while ( i < len - 1) {
		mem = arrayListGetPointer ( cursorList, i );
//		printf ( "mem->selI: %d\n", mem->selI );

		uni = arrayListGetPointer ( nextList, mem->selI );
//		printf ( "[%d], uni->type: %d\n", i, uni->type );
		if ( uni->type == G ) {
			nextList = uni->g->eles;
			*parent = uni;
		} else {
			// this should sometimes happen.
			// at i = len-1 for object. (wont happen cuz while (len-1)
			// at i = len-2 for vert.
			// at i = len-3 for control.
			break;
		}
		i += 1;
	}

	if ( debugPrint_jIterate ) {
		printf ( "exited while: %d\n", i );
	}
*/

/* old
	*parent = uni;

	i += 1;
	mem = arrayListGetPointer ( cursorList, i );
//	printf ( "mem->selI: %d\n", mem->selI );
	uni = arrayListGetPointer ( nextList, mem->selI );
	*ele = uni;
*/

/*
	*ele = uni;
//	printf ( "set ele\n" );
	if ( i == len - 1 ) {	// == len, cuz i do i += 1 directly above
		// that means an object is selected.
		return cs_object;

	} else if ( i == len - 2 ) {
		// that means a vert is selected.
		// OR im editing text in a text box.

		if ( uni->type == jNaked_Path ) {
			i += 1;
			mem = arrayListGetPointer ( cursorList, i );
			*vertI = mem->selI;

			*lastCursor = mem;

			return cs_vert;

		} else if ( uni->type == jNaked_Text ) {
			i += 1;
			mem = arrayListGetPointer ( cursorList, i );
			*vertI = mem->selI;
			*lastCursor = mem;
			return cs_text;

		} else if ( uni->type == jNaked_Rect ) {
			i += 1;
			mem = arrayListGetPointer ( cursorList, i );
			*vertI = mem->selI;
			*lastCursor = mem;
			return cs_rect;

		} else if ( uni->type == jNaked_Circ ) {
			i += 1;
			mem = arrayListGetPointer ( cursorList, i );
			*vertI = mem->selI;
			*lastCursor = mem;
			return cs_circ;

		} else if ( uni->type == jNaked_Complex ) {
			return cs_complex;
		}

	} else if ( i == len - 3 ) {
		// that means a control is selected.

		i += 1;
		mem = arrayListGetPointer ( cursorList, i );
		*vertI = mem->selI;

		i += 1;
		mem = arrayListGetPointer ( cursorList, i );
		*controlI = mem->selI;

		return cs_control;

	} else {
		return -1;
	}

	if ( debugPrint_jIterate ) {
		printf ( "jIterateToSelected ( ) OVER\n" );
	}
*/
	return -1;
}

/** Cursor Utilities */

/*
void say_jvg_cursor ( ) {
	printf ( "say_jvg_cursor ( )\n" );

	printf ( "glob_cursor_ele: %p\n", glob_cursor_ele );

	
}

void say_cursor_ele ( struct cursor_ele *ele ) {
	printf ( "ele: %p\n", ele );
	printf ( "ele->index: %d\n", ele->index );

	struct cursor_union *payload = ele->payload;
}

// why is this a funct and not a string array?
char *cursor_union_type_to_str ( struct cursor_union *uni ) {
	if ( uni->type == cu_Path ) {
		return "path";
	} else if ( uni->type == cu_Group ) {
		return "group";
	} else if ( uni->type == cu_Circ ) {
		return "circ";
	} else if ( uni->type == cu_Text ) {
		return "text";
	} else if ( uni->type == cu_Rect ) {
		return "rect";
	} else if ( uni->type == cu_ComplexEle ) {
		return "complexEle";
	} else {
		return "type out of range";
	}
}


void say_cursor_union ( struct cursor_union *uni ) {
	printf ( "uni: %p\n", uni );
	printf ( "uni->type: %d (%s)\n", uni->type, cursor_union_type_to_str ( uni ) );
}
*/



















