#pragma once

#include <jalb/backbone.h>
#include <jalbXml/jalbXml.h>



/** Functions */


/// Getters

struct backbone_structStruct **get_backbone_arr_jalbSvg ( );
int get_backbone_arr_len_jalbSvg ( );
int get_backbone_arr_total_jalbSvg ( struct backbone_structStruct ***arrPtr );

/// Getters

struct backbone_structStruct **get_backbone_arr ( );
int get_backbone_arr_len ( );
int get_backbone_arr_total ( struct backbone_structStruct ***arrPtr );


