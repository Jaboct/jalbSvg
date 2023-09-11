#pragma once

#include <jalbXml/jalbXml_02.h>

#include "svg.h"


/** Functions */


void say_svg ( struct svg *svg );

void sayEleList ( ArrayList *eles );




void pathPostInit ( void *data );
void sayPath ( struct path *path );
