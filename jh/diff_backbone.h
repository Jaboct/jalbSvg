#pragma once

#include <jalb/backbone.h>
#include <jalbXml/jalbXml.h>

#include "mod.h"
#include "svg.h"
#include "path.h"
#include "text.h"
#include "shapes.h"


/** Functions */


/// Getters

struct backbone_structStruct **get_backbone_arr_jalbSvg ( );
int get_backbone_arr_len_jalbSvg ( );
int get_backbone_arr_total_jalbSvg ( struct backbone_structStruct ***arrPtr );


