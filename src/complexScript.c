#include "complexScript.h"

// the vars and their data for this scope and all the higher scopes.
ArrayList *scopeData;	// stackData not scopeData?
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

		if ( ele->type == 0 ) {
			// allocate a var.
			struct jLitRef *lit = jLitRefInit ( );
			arrayListAddEndPointer ( scopeData, lit );
			lit->val = 0;	// init it to 0.
		} else if ( ele->type == 1 ) {
			struct jScriptOperator *op = ele->op;
			if ( op->type == jsOp_add ) {
				struct jVarRef *obj = op->object;
				struct jLitRef *obj_val = arrayListGetPointer ( scopeData, obj->index );

				if ( op->actor ) {
					printf ( "TODO\n" );
				} else if ( op->lit ) {
					struct jLitRef *lit = op->lit;
					obj_val->val += lit->val;
				}
			}
		}

		i += 1;
	}

	// print data stack
	i = 0;
	len = arrayListGetLength ( scopeData );
	while ( i < len ) {
		struct jLitRef *lit = arrayListGetPointer ( scopeData, i );

		printf ( "scopeData[%d]: %d\n", i, lit->val );

		i += 1;
	}

	printf ( "run_script ( ) OVER\n" );
}

