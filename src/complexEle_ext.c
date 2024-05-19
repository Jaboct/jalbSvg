#include "complexEle_ext.h"


/** Functions */

void hand_complex_00 ( ) {
	printf ( "hand_complex_00 ( )\n" );

	// creates "example_int" complex dec.
	struct complexDec *dec = complexDecInit ( );

	struct subVar *var = subVarInit ( );
	arrayListAddEndPointer ( dec->subVars, var );
}





