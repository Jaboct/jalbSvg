#pragma once


#include <stdio.h>
#include <stdlib.h>

#include <jalb/jfile.h>
#include <jalb/jalbUtilities.h>


/** Structs */

struct jvg_proof_test {
	char name[256];
	char knownDir[256];
	char madeDir[256];
};



/** Functions */


void jProof_test_all ( );
int hand_diff ( char *fknow, char *ftest );





