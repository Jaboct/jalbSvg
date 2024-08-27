#pragma once

#include <jalb/backbone.h>
#include <jalbXml/jalbXml.h>

#include "jMod.h"
#include "jPath.h"
#include "jText.h"
#include "jGroup.h"
#include "jShapes.h"
#include "complexEle.h"


/** Functions */


/// Getters

struct backbone_structStruct **get_backbone_arr_jalbJvg ( );
int get_backbone_arr_len_jalbJvg ( );
int get_backbone_arr_total_jalbJvg ( struct backbone_structStruct ***arrPtr );


