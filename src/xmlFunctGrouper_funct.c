#include "xmlFunctGrouper_funct.h"


#include "mod.h"
#include "svg.h"
#include "path.h"
#include "text.h"
#include "shapes.h"
#include "jMod.h"
#include "jPath.h"
#include "jText.h"
#include "jGroup.h"
#include "jShapes.h"
#include "complexEle.h"
#include "complexMod.h"
#include "complexScript.h"

void *function_arr[] = {
};

void *get_function_arr ( ) {
	return &function_arr;
}
int num_functions = 0;
void *get_num_functions ( ) {
	return &num_functions;
}
