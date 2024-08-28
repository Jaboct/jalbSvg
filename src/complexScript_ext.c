#include "complexScript_ext.h"


/** Variables */

// the vars and their data for this scope and all the higher scopes.
// stackData not scopeData?
ArrayList *scopeData;	// (struct *idPtr)

// idk if i should use idPtr.
// or find something better.

// id 0 is complexEle
// id 1 is jLitRef


// ints which reflect the size of the scopeEle list of all the higher scopes, so i know how much to free.
// there will be scope data which considered are unaccessable, like from a previously ran function.
// so for globals i iterate forward from the start, for scope vars i iterate backwards from the end. or moybe just forward from the last scopeData index.
ArrayList *scopeInfo;


/** Functions */

ArrayList *thisFunctScript;

void hand_script ( ) {
	// so make a jHigh function.
	// then pass it through the script parser.
	// then run it.


	if ( !thisFunctScript ) {
		thisFunctScript = initArrayList ( 10, sizeof ( void* ), 10 );
	}

	// first ele declares a var.

	struct jScriptEle *ele = jScriptEleInit ( );
	arrayListAddEndPointer ( thisFunctScript, ele );
	ele->type = 0;
	ele->varDec = subVarInit ( );

	// second ele adds a literal to it.

	ele = jScriptEleInit ( );
	arrayListAddEndPointer ( thisFunctScript, ele );
	ele->type = 1;
	ele->op = jScriptOperatorInit ( );
	ele->op->object = jVarRefInit ( );
	ele->op->object->index = 0;	// 0th ele on the stack, i should probably iterate backwards stack wise cuz idk how bis the stack is once it gets here.

	ele->op->type = jsOp_add;

	ele->op->actor = NULL;
	ele->op->lit = jLitRefInit ( );
	ele->op->lit->val = 12;

	run_script ( thisFunctScript );
}

void hand_script_2 ( ) {
	printf ( "hand_script_2 ( )\n" );

	if ( !thisFunctScript ) {
		thisFunctScript = initArrayList ( 10, sizeof ( void* ), 10 );
	} else {
		// free the script
		int i = 0;
		int len = arrayListGetLength ( thisFunctScript );
		while ( i < len ) {
			struct jScriptEle *ele = arrayListGetPointer ( thisFunctScript, i );
			free ( ele );
			arrayListRemove ( thisFunctScript, i );
//			i += 1;
			len -= 1;
		}
	}

	struct jScriptEle *ele = NULL;


	// first ele declares a var.
/*
	struct jScriptEle *ele = jScriptEleInit ( );
	arrayListAddEndPointer ( thisFunctScript, ele );
	ele->type = 0;
	ele->varDec = subVarInit ( );
*/

	// second ele adds a literal to it.

	ele = jScriptEleInit ( );
	arrayListAddEndPointer ( thisFunctScript, ele );
	ele->type = 1;
	ele->op = jScriptOperatorInit ( );
	ele->op->object = jVarRefInit ( );
	ele->op->object->index = 0;	// 0th ele on the stack, i should probably iterate backwards stack wise cuz idk how bis the stack is once it gets here.
	ele->op->object->subData = jVarRefInit ( );
	ele->op->object->subData->index = 0;

	ele->op->type = jsOp_add;

	ele->op->actor = NULL;
	ele->op->lit = jLitRefInit ( );
	ele->op->lit->val = 12;

	run_script ( thisFunctScript );
}

struct jScriptEle *jScriptEleInit ( ) {
	struct jScriptEle *ele = malloc ( sizeof ( *ele ) );
	ele->type = -1;
	return ele;
}

struct jScriptOperator *jScriptOperatorInit ( ) {
	struct jScriptOperator *op = malloc ( sizeof ( *op ) );
	op->type = -1;
	return op;
}

struct jVarRef *jVarRefInit ( ) {
	struct jVarRef *ref = malloc ( sizeof ( *ref ) );
	return ref;
}

struct jLitRef *jLitRefInit ( ) {
	struct jLitRef *ref = malloc ( sizeof ( *ref ) );
	return ref;
}



void run_script ( ArrayList *script ) {
	printf ( "run_script ( )\n" );

	if ( !scopeData ) {
		scopeData = initArrayList ( 10, sizeof ( void* ), 10 );	
	}

	int i = 0;
	int len = arrayListGetLength ( script );
	while ( i < len ) {
		struct jScriptEle *ele = arrayListGetPointer ( script, i );

		printf ( "[%d] ele->type: %d\n", i, ele->type );

		if ( ele->type == 0 ) {
			// allocate a temp var.
			struct jLitRef *lit = jLitRefInit ( );
			lit->val = 0;	// init it to 0.

			struct idPtr *id = malloc ( sizeof ( *id ) );
			id->id = 1;
			id->ptr = lit;
			arrayListAddEndPointer ( scopeData, id );

		} else if ( ele->type == 1 ) {
			struct jScriptOperator *op = ele->op;
			printf ( "op->type: %d\n", op->type );

			if ( op->type == jsOp_add ) {
				struct jVarRef *obj = op->object;

				printf ( "obj->index: %d\n", obj->index );

				struct idPtr *id = arrayListGetPointer ( scopeData, obj->index );

				printf ( "id->id: %d\n", id->id );

				if ( id->id == 0 ) {
					struct complexEle *complex = id->ptr;
					struct jLiveData *live = NULL;
					if ( obj->subData ) {
						obj = obj->subData;
						live = arrayListGetPointer ( complex->liveSubVars, obj->index );
					}
					if ( op->actor ) {
						printf ( "TODO\n" );
					} else if ( op->lit ) {
						struct jLitRef *lit = op->lit;
printf ( "add op->lit->val: %d\n", lit->val );
						if ( live->type == 0 ) {
							live->i += lit->val;
						} else {
printf ( "ERROr\n" );
						}
					}

				} else if ( id->id == 1 ) {
					struct jLitRef *obj_val = NULL;
					obj_val = id->ptr;
					if ( op->actor ) {
						printf ( "TODO\n" );
					} else if ( op->lit ) {
						struct jLitRef *lit = op->lit;
						obj_val->val += lit->val;
					}

				}
			}
		}

		i += 1;
	}

	// print data stack
	i = 0;
	len = arrayListGetLength ( scopeData );
	while ( i < len ) {
		struct idPtr *id = arrayListGetPointer ( scopeData, i );
		if ( id->id == 0 ) {
			struct complexEle *complex = id->ptr;
			printf ( "scopeData[%d] { ", i );
			int j = 0;
			int subLen = arrayListGetLength ( complex->liveSubVars );
			while ( j < subLen ) {
				struct jLiveData *live = arrayListGetPointer ( complex->liveSubVars, j );
				if ( live->type == 0 ) {
printf ( "%d, ", live->i );
				}
				j += 1;
			}
printf ( "}\n" );
		} else if ( id->id == 1 ) {
			struct jLitRef *lit = id->ptr;
			printf ( "scopeData[%d]: %d\n", i, lit->val );
		}

		i += 1;
	}

	// free the scope data.
	i = 0;
	len = arrayListGetLength ( scopeData );

	printf ( "free scopeData, len: %d\n", len );

	while ( i < len ) {
		struct idPtr *id = arrayListGetPointer ( scopeData, i );

		if ( id->id == 1 ) {
			struct jLitRef *lit = id->ptr;
			free ( lit );
		}
		free ( id );
		arrayListRemove ( scopeData, i );

//		i += 1;
		len -= 1;
	}

	printf ( "post len: %d\n", arrayListGetLength ( scopeData ) );

	printf ( "run_script ( ) OVER\n" );
}

