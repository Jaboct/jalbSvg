#include "backbone.h"


/** mod */



/** svg */

int svg_attributes[] = {
	0,
	0,
	0,
};
struct backbone_subVar svg_width = {
	.name = "width",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct svg, width ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar svg_height = {
	.name = "height",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct svg, height ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subAl svg_eles_subAl = {
	.overflow = 10,
	.literal = 0,
	.type = 1,
	.typeIndex = 1,
	.length = -1,
	.naked = 1,
};
struct backbone_subVar svg_eles = {
	.name = "eles",
	.type = 0,
	.typeIndex = 3,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		0,
		&svg_eles_subAl,
	},
	.external = offsetof ( struct svg, eles ),
	.saveFlag = 1,
	.naked = 1,
};
struct backbone_subVar *svg_varArr[] = {
	&svg_width,
	&svg_height,
	&svg_eles,
};
struct backbone_structStruct svg = {
	"svg",
	3,
	svg_varArr,
	"",
	"",
	0,
	0, // len?
	.structSize = sizeof ( struct svg ),
	svg_attributes,
};




int nakedUnion_attributes[] = {
	0,
};
int nakedUnion__attributes[] = {
	0,
	0,
};
struct backbone_subVar nakedUnion__g = {
	.name = "g",
	.type = 1,
	.typeIndex = 2,
	.initType = 0,
	.length = 0,
	.literal = 0,
	.data = {
		0,
	},
	.external = offsetof ( struct nakedUnion, g ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar nakedUnion__path = {
	.name = "path",
	.type = 1,
	.typeIndex = 3,
	.initType = 0,
	.length = 0,
	.literal = 0,
	.data = {
		0,
	},
	.external = offsetof ( struct nakedUnion, path ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *nakedUnion__varArr[] = {
	&nakedUnion__g,
	&nakedUnion__path,
};
struct backbone_subComplex nakedUnion__complex = {
	{
	},
	0,
	2,
	nakedUnion__varArr,
	""
};
struct backbone_subVar nakedUnion_ = {
	.name = "",
	.type = 0,
	.typeIndex = 6,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		0,
		&nakedUnion__complex,
	},
	offsetof ( struct nakedUnion, type ),
	.saveFlag = 1,
	.naked = 1,
};
struct backbone_subVar *nakedUnion_varArr[] = {
	&nakedUnion_,
};
struct backbone_structStruct nakedUnion = {
	"nakedUnion",
	1,
	nakedUnion_varArr,
	"",
	"",
	0,
	0, // len?
	.structSize = sizeof ( struct nakedUnion ),
	nakedUnion_attributes,
};




int g_attributes[] = {
	0,
	0,
};
struct backbone_subVar g_id = {
	.name = "id",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct g, id ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subAl g_eles_subAl = {
	.overflow = 0,
	.literal = 0,
	.type = 1,
	.typeIndex = 1,
	.length = -1,
	.naked = 0,
};
struct backbone_subVar g_eles = {
	.name = "eles",
	.type = 0,
	.typeIndex = 3,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		0,
		&g_eles_subAl,
	},
	.external = offsetof ( struct g, eles ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *g_varArr[] = {
	&g_id,
	&g_eles,
};
struct backbone_structStruct g = {
	"g",
	2,
	g_varArr,
	"",
	"",
	0,
	0, // len?
	.structSize = sizeof ( struct g ),
	g_attributes,
};




int path_attributes[] = {
	0,
	0,
	0,
};
struct backbone_subVar path_style = {
	.name = "style",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct path, style ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar path_d = {
	.name = "d",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct path, d ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar path_id = {
	.name = "id",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct path, id ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *path_varArr[] = {
	&path_style,
	&path_d,
	&path_id,
};
struct backbone_structStruct path = {
	"path",
	3,
	path_varArr,
	"",
	"",
	0,
	0, // len?
	.structSize = sizeof ( struct path ),
	path_attributes,
};




int len_backbone_arr = 4;
struct backbone_structStruct *backbone_arr[] = {
	&svg,
	&nakedUnion,
	&g,
	&path,
};
