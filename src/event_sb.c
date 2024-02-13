#include "event_sb.h"

/** Variables */

extern struct jalbFont *fonts[2];

extern int tabW;

// what is this?
extern int ctrlMemLast;

/** coppied from jalbText */

int debugPrint_newSb = 0;


// return 0 regularly.
// maybe 1 if something happens, idk.
// 2 if ur supposed to save.

// wht about tickMarker? i think that means im supposed to re-render.


// TODO do i want to care about newSbClickToIndex_wrap last param?
// TODO, allow me to add UTF keys
// TODO, fix return type, it generally returns 0 when i want it to return 1?
int sbKey ( SDL_Keycode key, ArrayList *sb, struct undoRedo *undoMem, int *cursorStartMem, int *cursorEndMem,
	    int *searching, struct textSearch *search, char *altKeys,
	    ArrayList *ctrlKeys, struct scrollMem *sm, int wrap, int maxCols ) {

	printf ( "sbKey ( )\n" );

//	return 0;

	// i think i should always check undoMem before i use it?
	// unless i check it in the subFuncts.

	if ( debugPrint_newSb ) {
		printf ( "sbKey ( )\n" );
		printf ( "wrap: %d\n", wrap );
		printf ( "maxCols: %d\n", maxCols );

		printf ( "key: %d\n", key );
		sayIntArray ( "cursorStartMem", cursorStartMem, 3 );
		sayIntArray ( "cursorEndMem", cursorEndMem, 3 );
	}

	int ret = 0;

	int glyphH = fonts[0]->atlasInfo.glyphH;

	if ( key >= 32 && key <= 126 ) { // Uppercase, Lowercase, All relevent ASCII
		// this is >= ' ' && <= '~'
/*
		if ( lastTextEle ) {	 // TODO
			lastTextEle->ticMarker[0] = 1;
		}
*/
		if ( altKeys[akCtrl] ) {
			if ( key == 'z' ) {
				if ( altKeys[akShift] ) {
					if ( undoRedo ( undoMem, sb, cursorStartMem ) ) {
//						sbIndexToCoords ( cursorStartMem[0], &cursorStartMem[1], sb, eleWH );
						cursorEndMem[0] = cursorStartMem[0];
						newSbIndexToCoords ( cursorStartMem[0], &cursorStartMem[1], sb, wrap, maxCols, tabW );
					}
				} else {
					if ( undoUndo ( undoMem, sb, cursorStartMem ) ) {
//						sbIndexToCoords ( cursorStartMem[0], &cursorStartMem[1], sb, eleWH );
						cursorEndMem[0] = cursorStartMem[0];
//						sbIndexToCoords ( cursorStartMem[0], &cursorStartMem[1], sb, eleWH );
						newSbIndexToCoords ( cursorStartMem[0], &cursorStartMem[1], sb, wrap, maxCols, tabW );
					}
				}

			} else if ( key == 'c' ) { // Copy hotkey.
				copyFrom ( sb, undoMem, cursorStartMem[0], cursorEndMem[0] );

			} else if ( key == 'v' ) {
				pasteTo_clipboard ( sb, undoMem, cursorStartMem, cursorEndMem );
				newSbIndexToCoords ( cursorStartMem[0], &cursorStartMem[1], sb, wrap, maxCols, tabW );

			} else if ( key == 'x' ) {
				copyFrom ( sb, undoMem, cursorStartMem[0], cursorEndMem[0] );
				highlightRemove ( sb, cursorStartMem, cursorEndMem, undoMem );
				newSbIndexToCoords ( cursorStartMem[0], &cursorStartMem[1], sb, wrap, maxCols, tabW );

			} else if ( key == 'b' ) {
//				int len = arrayListGetLength(sb);

//				int lastI;
//				ArrayList *lastP;

//				arrayListIterateBack(sb, len-1, sayChar, &lastP, &lastI);

//				printf("\n");
//				printf("arrayListIterateBack() (%p, %d)\n", lastP, lastI);

			} else if ( key == 'f' ) {
				if ( searching ) {
					*searching = 1 - *searching;
				}

			} else if ( key == 's' ) { // _s
				if ( altKeys[akShift] ) {
				} else {
					// Save this file.
//					textTabSave ( tab );
					if ( debugPrint_newSb ) {
						printf ( "return 2\n" );
					}
					ret = 2;
					goto functEnd;
//					return 2;
				}
			}
		} else if ( cursorStartMem[0] != -1 ) {
			// ctrl is not pressed, and its a regular ascii character.

			if ( altKeys[akShift] ) {
				key = shiftKeys ( key );
			}

			highlightRemove ( sb, cursorStartMem, cursorEndMem, undoMem );

			if ( undoMem ) {
				undoCheck ( undoMem, key, 0, sb, cursorStartMem );
			}

			arrayListAdd ( sb, cursorStartMem[0], &key );
			cursorStartMem[0] += 1;
			cursorEndMem[0] = cursorStartMem[0];

//			sbIndexToCoords ( cursorStartMem[0], &cursorStartMem[1], sb, eleWH );
			newSbIndexToCoords ( cursorStartMem[0], &cursorStartMem[1], sb, wrap, maxCols, tabW );
		}
		// Parse recheck.
		if ( search ) {
			if ( arrayListGetLength ( search->searchReturn ) > 0 ) {
//				sbSearch(sb, search, eleWH);
				newSbSearch ( sb, search, tabW );
			}
		}
	} else if ( key == SDLK_TAB ) {
/*
		if ( lastTextEle ) { // TODO
			lastTextEle->ticMarker[0] = 1;
		}
*/
		if ( cursorStartMem[0] != -1 ) {
			if ( altKeys[akShift] ) {
				key = shiftKeys ( key );
			}

			highlightRemove ( sb, cursorStartMem, cursorEndMem, undoMem );
			undoCheck ( undoMem, key, 0, sb, cursorStartMem );

			arrayListAdd ( sb, cursorStartMem[0], &key );
			cursorStartMem[0] += 1;
			cursorEndMem[0] = cursorStartMem[0];
			newSbIndexToCoords ( cursorStartMem[0], &cursorStartMem[1], sb, wrap, maxCols, tabW );
		}
		// Parse recheck.
		if ( arrayListGetLength ( search->searchReturn ) > 0 ) {
//			sbSearch(sb, search, eleWH);
			newSbSearch ( sb, search, tabW );
		}
	} else if ( key == SDLK_BACKSPACE ) {
		printf ( "SDLK_BACKSPACE\n" );
/*
		if ( lastTextEle ) { // TODO
			lastTextEle->ticMarker[0] = 1;
		}
*/
		if ( cursorStartMem[0] > 0 ) {
			int highlightRet = highlightRemove ( sb, cursorStartMem, cursorEndMem, undoMem );
			printf ( "highlightRet: %d\n", highlightRet );
			if ( highlightRet ) { // There is no highlight. So do regular shit.
				if ( altKeys[akCtrl] ) {
					// Find the last
					int lastI;
					ArrayList *lastP;
					ctrlMemLast = -1;
					arrayListIterateBackList ( sb, cursorStartMem[0] - 1, isCtrlCharChange, &lastP, &lastI, ctrlKeys );
					cursorEndMem[0] = arrayListPartToAbs ( sb, lastP, lastI );
					highlightRemove ( sb, cursorStartMem, cursorEndMem, undoMem );
				} else {
//					printf ( "!ctrl\n" );
					char *c = arrayListDataPointer ( sb, cursorStartMem[0] - 1 );
//					printf("*c: %c\n", *c);
					if ( undoMem ) {
						undoCheck ( undoMem, key, 1, sb, cursorStartMem );
						if ( undoMem->undoLength - 1 >= undoMem->removeMax ) {
							// -1 because undoCheck increases length already.
							undoAdd ( undoMem, sb, cursorStartMem );
						}
						undoMem->removeMem[undoMem->undoLength - 1] = *c;
					}

					// for ascii
					int numChars = charLen_back ( sb, cursorStartMem[0] );
					int i = 0;
					while ( i < numChars ) {
						arrayListRemove ( sb, cursorStartMem[0] - 1 );
						cursorStartMem[0] -= 1;

						i += 1;
					}

//					arrayListRemove ( sb, cursorStartMem[0] - 1 );
//					cursorStartMem[0] -= 1;

					cursorEndMem[0] = cursorStartMem[0];
				}
			}
//			printf ( "itc\n" );
			newSbIndexToCoords ( cursorStartMem[0], &cursorStartMem[1], sb, wrap, maxCols, tabW );
			// Parse recheck.
//			printf ( "serach\n" );
			if ( search ) {
				if ( arrayListGetLength ( search->searchReturn ) ) {
//					sbSearch(sb, search, eleWH);
					newSbSearch ( sb, search, tabW );
				}
			}
//			printf ( "final\n" );
		}
	} else if ( key == SDLK_DELETE ) {
		printf ( "SDLK_DELETE: %d\n", SDLK_DELETE );

/*
		if ( lastTextEle ) { // TODO
			lastTextEle->ticMarker[0] = 1;
		}
*/
		int numChars = arrayListGetLength ( sb );

//		printf ( "numChars: %d\n", numChars );
//		printf ( "cursorStartMem[0]: %d\n", cursorStartMem[0] );

		if ( cursorStartMem[0] != -1 ) {
			int highlightRet = highlightRemove ( sb, cursorStartMem, cursorEndMem, undoMem );
//			printf ( "highlightRet: %d\n", highlightRet );

			if ( highlightRet ) {
				// nothing is highlighted so continue to delete a single char.

				if ( cursorStartMem[0] < numChars ) {
					if ( altKeys[akCtrl] ) {
						// Find the last
						int lastI;
						ArrayList *lastP;
						ctrlMemLast = -1;
						arrayListIterateList ( sb, cursorStartMem[0] + 1, isCtrlCharChange, &lastP, &lastI, ctrlKeys );
						cursorEndMem[0] = arrayListPartToAbs ( sb, lastP, lastI );
						highlightRemove ( sb, cursorStartMem, cursorEndMem, undoMem );
					} else {
//						printf ( "!ctrl\n" );

						char *c = arrayListDataPointer ( sb, cursorStartMem[0] );
						undoCheck ( undoMem, key, 2, sb, cursorStartMem );
						if ( undoMem ) {
							if ( undoMem->undoLength - 1 >= undoMem->removeMax ) {
								// -1 because undoCheck increases length already.
								undoAdd ( undoMem, sb, cursorStartMem );
							}
							undoMem->removeMem[undoMem->undoLength - 1] = *c;
						}

						int numChars = charLen_forward ( sb, cursorStartMem[0] );
						int i = 0;
						while ( i < numChars ) {
							arrayListRemove ( sb, cursorStartMem[0] );
							i += 1;
						}

//						arrayListRemove ( sb, cursorStartMem[0] );

						cursorEndMem[0] = cursorStartMem[0];
					}
				}
			}
//			printf ( "about to. newSbIndexToCoords ( )\n" );
			newSbIndexToCoords ( cursorStartMem[0], &cursorStartMem[1], sb, wrap, maxCols, tabW );
			// Parse recheck.
//			printf ( "search: %p\n", search );
			if ( search ) {
				if ( arrayListGetLength ( search->searchReturn ) > 0 ) {
//					sbSearch(sb, search, eleWH);
					newSbSearch ( sb, search, tabW );
				}
			}
		}
	} else if ( key == SDLK_RETURN ) {
/*
		if ( lastTextEle ) { // TODO
			lastTextEle->ticMarker[0] = 1;
		}
*/
		if ( cursorStartMem[0] != -1 ) {
			highlightRemove ( sb, cursorStartMem, cursorEndMem, undoMem );
			undoCheck ( undoMem, key, 0, sb, cursorStartMem );

			char nl = '\n';

			arrayListAdd ( sb, cursorStartMem[0], &nl );
			cursorStartMem[0] += 1;
			cursorEndMem[0] = cursorStartMem[0];
//			sbIndexToCoords ( cursorStartMem[0], &cursorStartMem[1], sb, eleWH );
			newSbIndexToCoords ( cursorStartMem[0], &cursorStartMem[1], sb, wrap, maxCols, tabW );
		}
	} else if ( key == SDLK_LEFT ) {
		int *setCursor;
		if ( altKeys[akShift] ) {
			setCursor = cursorEndMem;
		} else {
			setCursor = cursorStartMem;
		}
		if ( altKeys[akCtrl] ) {
			if ( setCursor[0] > 0 ) {
				// Find the last
				int lastI;
				ArrayList *lastP;
				ctrlMemLast = -1;
				arrayListIterateBackList ( sb, setCursor[0] - 1, isCtrlCharChange, &lastP, &lastI, ctrlKeys );
				printf ( "preCursor: %d\n", setCursor[0] );
				setCursor[0] = arrayListPartToAbs ( sb, lastP, lastI );
//				setCursor[0] += 1;
				printf ( "setCursor: %d\n", setCursor[0] );

				// So using the last index and and ptr lets set the cursor index, and xy.
				// later on ill start rendering from a relative ptr and index. that perfect, so along the line if i find cursor ill handle it.
			}
		} else {
			if ( setCursor[0] > 0 ) {
				int len = charLen_back ( sb, setCursor[0] );
				printf ( "LEFT ARROW len: %d\n", len );
//				setCursor[0] -= 1;
				setCursor[0] -= len;
			}
		}

		if ( !altKeys[akShift] ) {
			cursorEndMem[0] = cursorStartMem[0];
		}
//		sbIndexToCoords ( setCursor[0], &setCursor[1], sb, eleWH );
		newSbIndexToCoords ( setCursor[0], &setCursor[1], sb, wrap, maxCols, tabW );

		sayIntArray ( "setCursor", setCursor, 3 );

	} else if ( key == SDLK_RIGHT ) {
		int numChars = arrayListGetLength ( sb );

		int *setCursor;
		if ( altKeys[akShift] ) {
			setCursor = cursorEndMem;
		} else {
			setCursor = cursorStartMem;
		}

		if ( altKeys[akCtrl] ) {
			if ( setCursor[0] < numChars - 1 ) {
				// Find the last
				int lastI;
				ArrayList *lastP;
				ctrlMemLast = -1;
				arrayListIterateList ( sb, setCursor[0] + 1, isCtrlCharChange, &lastP, &lastI, ctrlKeys );
//				printf("preCursor: %d\n", setCursor[0]);
				setCursor[0] = arrayListPartToAbs ( sb, lastP, lastI );
//				printf("setCursor: %d\n", setCursor[0]);
			}
		} else {
			printf ( "cursorStartMem[0]: %d\n", cursorStartMem[0] );
			printf ( "numChars: %d\n", numChars );

//			if ( cursorStartMem[0] < numChars - 1 ) {
//			if ( setCursor[0] < numChars - 1 ) {	// why is this numChars -1?
			if ( setCursor[0] < numChars ) {
				int len = charLen_forward ( sb, setCursor[0] );
				printf ( "RIGHT charLen: %d\n", len );
//				setCursor[0] += 1;
				setCursor[0] += len;
			}

//			cursorEndMem[0] = cursorStartMem[0];
//			sbIndexToCoords ( setCursor[0], &setCursor[1], sb, eleWH );

			newSbIndexToCoords ( setCursor[0], &setCursor[1], sb, wrap, maxCols, tabW );
		}

		if ( !altKeys[akShift] ) {
			cursorEndMem[0] = cursorStartMem[0];
		}

		// this is the 2nd time i run this???
//		sbIndexToCoords ( setCursor[0], &setCursor[1], sb, eleWH );
		newSbIndexToCoords ( setCursor[0], &setCursor[1], sb, wrap, maxCols, tabW );

//		sayIntArray ( "setCursor", setCursor, 3 );

	} else if ( key == SDLK_UP ) {
		if ( altKeys[akCtrl] ) {
//			struct scrollMem *sm = &sm;

			if ( !sm ) {
				ret = 0;
				goto functEnd;

//				return 0;
			}

			if ( altKeys[akShift] ) {
				sm->curScroll -= glyphH * 4;
			} else {
				sm->curScroll -= glyphH;
			}
			if ( sm->curScroll > sm->maxScroll ) {
				sm->curScroll = sm->maxScroll;
			} else if ( sm->curScroll < 0 ) {
				sm->curScroll = 0;
			}

			ret = 0;
			goto functEnd;

//			return 0;
		}
		int *setCursor;
		if ( altKeys[akShift] ) {
			setCursor = cursorEndMem;

			if ( cursorEndMem[0] == cursorStartMem[0] ) {
				// Make sure XY are the same also.
				cursorEndMem[1] = cursorStartMem[1];
				cursorEndMem[2] = cursorStartMem[2];
			}

		} else {
			setCursor = cursorStartMem;
		}

		setCursor[2] -= 1;
//		setCursor[0] = sbClickToIndex( &setCursor[1], sb, eleWH );
		if ( wrap ) {
			setCursor[0] = newSbClickToIndex_wrap ( &setCursor[1], sb, maxCols, tabW, NULL );
		} else {
			setCursor[0] = newSbClickToIndex ( &setCursor[1], sb, tabW );
		}

		if ( !altKeys[akShift] ) {
			cursorEndMem[0] = cursorStartMem[0];
		}

	} else if ( key == SDLK_DOWN ) {
		if ( altKeys[akCtrl] ) {
//			struct scrollMem *sm = &sm;

			if ( !sm ) {
				ret = 0;
				goto functEnd;

//				return 0;
			}

			if ( altKeys[akShift] ) {
				sm->curScroll += glyphH * 4;
			} else {
				sm->curScroll += glyphH;
			}
			if ( sm->curScroll > sm->maxScroll ) {
				sm->curScroll = sm->maxScroll;
			} else if ( sm->curScroll < 0 ) {
				sm->curScroll = 0;
			}

			ret = 0;
			goto functEnd;

//			return 0;
		}
		int *setCursor;
		if ( altKeys[akShift] ) {
			setCursor = cursorEndMem;

			if ( cursorEndMem[0] == cursorStartMem[0] ) {
				// Make sure XY are the same also.
				cursorEndMem[1] = cursorStartMem[1];
				cursorEndMem[2] = cursorStartMem[2];
			}

		} else {
			setCursor = cursorStartMem;
		}

		setCursor[2] += 1;
//		setCursor[0] = sbClickToIndex( &setCursor[1], sb, eleWH );
		if ( wrap ) {
			setCursor[0] = newSbClickToIndex_wrap ( &setCursor[1], sb, maxCols, tabW, NULL );
		} else {
			setCursor[0] = newSbClickToIndex ( &setCursor[1], sb, tabW );
		}

		printf ( "down over\n" );
		sayIntArray ( "setCursor", setCursor, 3 );

		if ( !altKeys[akShift] ) {
			cursorEndMem[0] = cursorStartMem[0];
		}

	} else if ( key == SDLK_HOME ) {
		int *setCursor;
		if ( altKeys[akShift] ) {
			setCursor = cursorEndMem;

			if ( cursorEndMem[0] == cursorStartMem[0] ) {
				// Make sure XY are the same also.
				cursorEndMem[1] = cursorStartMem[1];
				cursorEndMem[2] = cursorStartMem[2];
			}

		} else {
			setCursor = cursorStartMem;
		}

		setCursor[1] = 0;
//		setCursor[0] = sbClickToIndex( &setCursor[1], sb, eleWH );
		if ( wrap ) {
			setCursor[0] = newSbClickToIndex_wrap ( &setCursor[1], sb, maxCols, tabW, NULL );
		} else {
			setCursor[0] = newSbClickToIndex ( &setCursor[1], sb, tabW );
		}

		if ( !altKeys[akShift] ) {
			cursorEndMem[0] = cursorStartMem[0];
		}
	} else if ( key == SDLK_END ) {
		int *setCursor;
		if ( altKeys[akShift] ) {
			setCursor = cursorEndMem;

			if ( cursorEndMem[0] == cursorStartMem[0] ) {
				// Make sure XY are the same also.
				cursorEndMem[1] = cursorStartMem[1];
				cursorEndMem[2] = cursorStartMem[2];
			}

		} else {
			setCursor = cursorStartMem;
		}

		// this is lazy and shitty and i need a better function.
		setCursor[1] = 1000;
//		setCursor[0] = sbClickToIndex( &setCursor[1], sb, eleWH );
		if ( wrap ) {
			setCursor[0] = newSbClickToIndex_wrap ( &setCursor[1], sb, maxCols, tabW, NULL );
		} else {
			setCursor[0] = newSbClickToIndex ( &setCursor[1], sb, tabW );
		}

		if ( !altKeys[akShift] ) {
			cursorEndMem[0] = cursorStartMem[0];
		}
	}

	functEnd:;

	if ( debugPrint_newSb ) {
		printf ( "sb->len: %d\n", arrayListGetLength ( sb ) );
		printSb ( sb );
		printf ( "sbKey ( ) OVER\n" );
	}


	printf ( "sbKey ( ) OVER\n" );

	return ret;
}

// is this just a generic arraylist function?
void arrayListIterateBackList ( ArrayList *al, int startIndex, int ( *funct ) ( char *, ArrayList * ), ArrayList **retPart, int *retIndex,
		ArrayList *param ) {
//	 printf ( "arrayListIterateBackList ( )\n" );

	if ( !param ) {
		/// TODO i should do a single iteration.
		return;
	}

	ArrayList *curPart = al;
	int i = 0;
	while ( 1 ) {
		if ( i + curPart->curEles >= startIndex ) {
			break;
		}
		i += curPart->curEles;
		curPart = curPart->next;
		if ( !curPart ) {
			printf ( "BUG: arrayListIterateBack() !curPart\n" );
		}
	}

	i = startIndex - i;
	while ( 1 ) {
		while ( i >= 0 ) {
			void *dataPtr = curPart->data + ( i * curPart->eleSize );
			if ( funct ( dataPtr, param ) ) {
				// funct returned 1, which means set retI and retPart and end this iterating.
				*retPart = curPart;
				*retIndex = i; /// TODO i want to return -(-1), but is that the other part?

				return;
			}
			i -= 1;
		}
		// Iterate back a part.
		if ( curPart == al ) {
			// Reached the start, aka the end.

			*retPart = al;
			*retIndex = 0;

			return;
		}

		ArrayList *tempPart = al;
		while ( tempPart->next != curPart ) {
			tempPart = tempPart->next;
		}
		curPart = tempPart;

		i = curPart->curEles;
	}
}

void arrayListIterateList ( ArrayList *al, int startIndex, int ( *funct ) ( char *, ArrayList * ), ArrayList **retPart, int *retIndex,
		ArrayList *param ) {
	printf ( "arrayListIterateList ( )\n" );

	if ( !param ) {
		/// TODO i should do a single iteration.
		return;
	}

	ArrayList *curPart = al;
	int i = 0;
	while ( 1 ) {
		if ( i + curPart->curEles >= startIndex ) {
			break;
		}
		i += curPart->curEles;
		curPart = curPart->next;
		if ( !curPart ) {
			printf ( "BUG: arrayListIterateBack() !curPart\n" );
		}
	}

	// I reached startIndex.

	i = startIndex - i;
	while ( 1 ) {
		while ( i < curPart->curEles ) {
			void *dataPtr = curPart->data + ( i * curPart->eleSize );
			if ( funct ( dataPtr, param ) ) {
				// funct returned 1, which means set retI and retPart and end this iterating.
				*retPart = curPart;
				*retIndex = i; /// TODO i want to return -(-1), but is that the other part?

				return;
			}
			i += 1;
		}
		// Iterate forward a part.
		if ( !curPart->next ) {
			// Reached the end.

			*retPart = curPart;
			*retIndex = curPart->curEles - 1;

			return;
		}
		curPart = curPart->next;
		i = 0;
	}
}

// So i want this to be accessable by
int isCtrlCharChange ( char *cPtr, ArrayList *charList ) {
	int numCtrl = arrayListGetLength ( charList );
//	printf("isCtrlCharChange()\n");

//	printf("numCtrl Change: %d\n", numCtrl);

	int thisType = -1;

	int i = 0;
	while ( i < numCtrl ) {
		char *c = arrayListDataPointer ( charList, i );
		if ( *cPtr == *c ) {
			thisType = i;
			goto typeCheck;
		}
		i += 1;
	}
	if ( *cPtr >= 65 && *cPtr <= 90 ) {
		// type == caps (2)
		thisType = -2;
		goto typeCheck;
	}
	thisType = -3;

	typeCheck:;

//	printf("TypeCheck(mem, this) (%d, %d)\n", ctrlMemLast, thisType);
	if ( ctrlMemLast == thisType ) {
		return 0;
	}
	if ( ctrlMemLast == -1 ) {
		ctrlMemLast = thisType;
		return 0;
	}
	ctrlMemLast = thisType;
	return 1;
}

// I guess i just want alPartIndex, then i can add partI on my own.
int arrayListPartToAbs ( ArrayList *al, ArrayList *part, int partI ) {
	int total = 0;
	while ( 1 ) {
		if ( !al ) {
			printf ( "BUG!!! arrayListPartToAbs() !al\n" );
			return -1;
		}
		if ( al == part ) {
			return total + partI;
		}
		total += al->curEles;
		al = al->next;
	}
}

// look to the left of index, to see if its a unicode char, if so, figure how long it is.
// right now i only need to iterate back 2 chars, cuz i dont handle unicode larger than that.
// maybe one day i need to convert my string builders to ints to handle this?
int charLen_back ( ArrayList *sb, int index ) {
	printSb_x ( sb );
	printf ( "index: %d\n", index );

	int ret = 1;

	while ( index > 0 ) {
		index -= 1;
		unsigned char *c = arrayListDataPointer ( sb, index );
		printf ( "*c: %d\n", *c );

		unsigned char max = 0b10000000;
		printf ( "max: %d\n", max );

		if ( *c >= 0b10000000 &&	// lowest possible non-first byte.
		     *c <  0b11000000 ) { // lowest possible first byte (also 1 more than the highest possible non-first byte)
			ret += 1;
		} else {
			break;
		}
		if ( ret > 4 ) {
			printf ( "ERROR, charLen\n" );
			return 1;
		}
	}
	return ret;

/*
	if ( index > 1 ) {
		unsigned char *c = arrayListDataPointer ( sb, index - 2 );
		// this might be in the middle of a unicode char, so i needto go back farther.
		// is the only right way to do this by going forward?
		if ( *c > 126 ) {
			// they are unicode.
			return 2;
		} else {
			return 1;
		}

	} else {
		return 1;
	}
*/
}

// this should use unsigned int nextCharRender_sb ( ArrayList *start, int *startI );?

// if the next char is a firstChar, then iterate through.
int charLen_forward ( ArrayList *sb, int index ) {
	printSb_x ( sb );
	printf ( "index: %d\n", index );

	int len = arrayListGetLength ( sb );

	int ret = 0;

	while ( index < len ) {
		unsigned char *c = arrayListDataPointer ( sb, index );
		printf ( "*c: %d\n", *c );

		if ( ret == 0 ) {
			if ( *c >= 0b11000000 ) { // lowest possible first byte (also 1 more than the highest possible non-first byte)
				// this is a first byte, so keep iterating.
				ret += 1;
//				index += 1;
			} else {
				// ther first char is just a regular char.
				ret = 1;
				break;
			}
		} else {
			if ( *c >= 0b10000000 &&	// lowest possible none first byte, which is also less than every first byte
			     *c <  0b11000000 ) { // lowest possible first byte (also 1 more than the highest possible non-first byte)
				ret += 1;
//				index += 1;
			} else {
				break;
			}
		}
/*
		unsigned char max = 0b10000000;
		printf ( "max: %d\n", max );

		if ( *c >= 0b10000000 &&	// lowest possible none first byte, which is also less than every first byte
		     *c <  0b11000000 ) { // lowest possible first byte (also 1 more than the highest possible non-first byte)
			ret += 1;
		} else {
			break;
		}
*/
		if ( ret > 4 ) {
			printf ( "ERROR, charLen\n" );
			return 1;
		}

		index += 1;
	}
	return ret;

/*
	if ( index > 1 ) {
		unsigned char *c = arrayListDataPointer ( sb, index - 2 );
		// this might be in the middle of a unicode char, so i needto go back farther.
		// is the only right way to do this by going forward?
		if ( *c > 126 ) {
			// they are unicode.
			return 2;
		} else {
			return 1;
		}

	} else {
		return 1;
	}
*/
}




