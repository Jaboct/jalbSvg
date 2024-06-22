#include "backbone.h"


/** mod */



/** svg */

int svg_attributes[] = {
	1,
	1,
	1,
	1,
	1,
	0,
};
struct backbone_subVar svg_width = {
	.name = "width",
	.type = 0,
	.typeIndex = 4,
	.initType = 4,
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
	.initType = 4,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct svg, height ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar svg_viewBox = {
	.name = "viewBox",
	.type = 0,
	.typeIndex = 4,
	.initType = 4,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct svg, viewBox ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar svg_version = {
	.name = "version",
	.type = 0,
	.typeIndex = 4,
	.initType = 4,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct svg, version ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar svg_id = {
	.name = "id",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct svg, id ),
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
	&svg_viewBox,
	&svg_version,
	&svg_id,
	&svg_eles,
};
struct backbone_structStruct svg = {
	"svg",
	6,
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
	0,
	0,
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
struct backbone_subVar nakedUnion__text = {
	.name = "text",
	.type = 1,
	.typeIndex = 10,
	.initType = 0,
	.length = 0,
	.literal = 0,
	.data = {
		0,
	},
	.external = offsetof ( struct nakedUnion, text ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar nakedUnion__rect = {
	.name = "rect",
	.type = 1,
	.typeIndex = 12,
	.initType = 0,
	.length = 0,
	.literal = 0,
	.data = {
		0,
	},
	.external = offsetof ( struct nakedUnion, rect ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar nakedUnion__circle = {
	.name = "circle",
	.type = 1,
	.typeIndex = 13,
	.initType = 0,
	.length = 0,
	.literal = 0,
	.data = {
		0,
	},
	.external = offsetof ( struct nakedUnion, circle ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar nakedUnion__ellipse = {
	.name = "ellipse",
	.type = 1,
	.typeIndex = 14,
	.initType = 0,
	.length = 0,
	.literal = 0,
	.data = {
		0,
	},
	.external = offsetof ( struct nakedUnion, ellipse ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *nakedUnion__varArr[] = {
	&nakedUnion__g,
	&nakedUnion__path,
	&nakedUnion__text,
	&nakedUnion__rect,
	&nakedUnion__circle,
	&nakedUnion__ellipse,
};
struct backbone_subComplex nakedUnion__complex = {
	{
	},
	0,
	6,
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
	1,
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
	.naked = 1,
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
	.naked = 1,
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
	1,
	1,
	1,
	0,
	0,
	0,
	0,
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
	.length = 1024,
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
struct backbone_subAl path_eles_subAl = {
	.overflow = 10,
	.literal = 0,
	.type = 1,
	.typeIndex = 4,
	.length = -1,
	.naked = 0,
};
struct backbone_subVar path_eles = {
	.name = "eles",
	.type = 0,
	.typeIndex = 3,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		0,
		&path_eles_subAl,
	},
	.external = offsetof ( struct path, eles ),
	.saveFlag = 99,
	.naked = 0,
};
struct backbone_subVar path_fill = {
	.name = "fill",
	.type = 0,
	.typeIndex = 4,
	.initType = 4,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct path, fill ),
	.saveFlag = 99,
	.naked = 0,
};
struct backbone_subVar path_stroke = {
	.name = "stroke",
	.type = 0,
	.typeIndex = 4,
	.initType = 4,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct path, stroke ),
	.saveFlag = 99,
	.naked = 0,
};
struct backbone_subVar path_stroke_width = {
	.name = "stroke_width",
	.type = 0,
	.typeIndex = 4,
	.initType = 4,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct path, stroke_width ),
	.saveFlag = 99,
	.naked = 0,
};
struct backbone_subVar path_stroke_linecap = {
	.name = "stroke_linecap",
	.type = 0,
	.typeIndex = 4,
	.initType = 4,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct path, stroke_linecap ),
	.saveFlag = 99,
	.naked = 0,
};
struct backbone_subVar path_stroke_linejoin = {
	.name = "stroke_linejoin",
	.type = 0,
	.typeIndex = 4,
	.initType = 4,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct path, stroke_linejoin ),
	.saveFlag = 99,
	.naked = 0,
};
struct backbone_subVar path_stroke_opacity = {
	.name = "stroke_opacity",
	.type = 0,
	.typeIndex = 4,
	.initType = 4,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct path, stroke_opacity ),
	.saveFlag = 99,
	.naked = 0,
};
struct backbone_subVar *path_varArr[] = {
	&path_style,
	&path_d,
	&path_id,
	&path_eles,
	&path_fill,
	&path_stroke,
	&path_stroke_width,
	&path_stroke_linecap,
	&path_stroke_linejoin,
	&path_stroke_opacity,
};
struct backbone_structStruct path = {
	"path",
	10,
	path_varArr,
	"",
	"",
	0,
	0, // len?
	.structSize = sizeof ( struct path ),
	path_attributes,
};






/** path */

int pathUni_attributes[] = {
	0,
};
int pathUni__attributes[] = {
	0,
	0,
	0,
	0,
	0,
	0,
};
struct backbone_subVar pathUni__moveTo = {
	.name = "moveTo",
	.type = 1,
	.typeIndex = 5,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct pathUni, moveTo ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar pathUni__lineTo = {
	.name = "lineTo",
	.type = 1,
	.typeIndex = 6,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct pathUni, lineTo ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar pathUni__cubicBez = {
	.name = "cubicBez",
	.type = 1,
	.typeIndex = 7,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct pathUni, cubicBez ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar pathUni__quadBez = {
	.name = "quadBez",
	.type = 1,
	.typeIndex = 8,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct pathUni, quadBez ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar pathUni__ellipArc = {
	.name = "ellipArc",
	.type = 1,
	.typeIndex = 9,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct pathUni, ellipArc ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar pathUni__PathEnd = {
	.name = "PathEnd",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct pathUni, PathEnd ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *pathUni__varArr[] = {
	&pathUni__moveTo,
	&pathUni__lineTo,
	&pathUni__cubicBez,
	&pathUni__quadBez,
	&pathUni__ellipArc,
	&pathUni__PathEnd,
};
struct backbone_subComplex pathUni__complex = {
	{
	},
	0,
	6,
	pathUni__varArr,
	"path_"
};
struct backbone_subVar pathUni_ = {
	.name = "",
	.type = 0,
	.typeIndex = 6,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		0,
		&pathUni__complex,
	},
	offsetof ( struct pathUni, type ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *pathUni_varArr[] = {
	&pathUni_,
};
struct backbone_structStruct pathUni = {
	"pathUni",
	1,
	pathUni_varArr,
	"",
	"",
	0,
	0, // len?
	.structSize = sizeof ( struct pathUni ),
	pathUni_attributes,
};




int moveTo_attributes[] = {
	0,
	0,
};
struct backbone_subVar moveTo_rel = {
	.name = "rel",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct moveTo, rel ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar moveTo_XY = {
	.name = "XY",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = 2,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct moveTo, XY ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *moveTo_varArr[] = {
	&moveTo_rel,
	&moveTo_XY,
};
struct backbone_structStruct moveTo = {
	"moveTo",
	2,
	moveTo_varArr,
	"",
	"",
	0,
	0, // len?
	.structSize = sizeof ( struct moveTo ),
	moveTo_attributes,
};




int lineTo_attributes[] = {
	0,
	0,
	0,
};
struct backbone_subVar lineTo_rel = {
	.name = "rel",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct lineTo, rel ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar lineTo_XY = {
	.name = "XY",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = 2,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct lineTo, XY ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar lineTo_type = {
	.name = "type",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct lineTo, type ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *lineTo_varArr[] = {
	&lineTo_rel,
	&lineTo_XY,
	&lineTo_type,
};
struct backbone_structStruct lineTo = {
	"lineTo",
	3,
	lineTo_varArr,
	"",
	"",
	0,
	0, // len?
	.structSize = sizeof ( struct lineTo ),
	lineTo_attributes,
};




int cubicBez_attributes[] = {
	0,
	0,
	0,
	0,
	0,
};
struct backbone_subVar cubicBez_rel = {
	.name = "rel",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct cubicBez, rel ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar cubicBez_XY = {
	.name = "XY",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = 2,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct cubicBez, XY ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar cubicBez_c0 = {
	.name = "c0",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = 2,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct cubicBez, c0 ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar cubicBez_c1 = {
	.name = "c1",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = 2,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct cubicBez, c1 ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar cubicBez_type = {
	.name = "type",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct cubicBez, type ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *cubicBez_varArr[] = {
	&cubicBez_rel,
	&cubicBez_XY,
	&cubicBez_c0,
	&cubicBez_c1,
	&cubicBez_type,
};
struct backbone_structStruct cubicBez = {
	"cubicBez",
	5,
	cubicBez_varArr,
	"",
	"",
	0,
	0, // len?
	.structSize = sizeof ( struct cubicBez ),
	cubicBez_attributes,
};




int quadBez_attributes[] = {
	0,
	0,
	0,
	0,
};
struct backbone_subVar quadBez_rel = {
	.name = "rel",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct quadBez, rel ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar quadBez_XY = {
	.name = "XY",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = 2,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct quadBez, XY ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar quadBez_control = {
	.name = "control",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = 2,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct quadBez, control ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar quadBez_type = {
	.name = "type",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct quadBez, type ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *quadBez_varArr[] = {
	&quadBez_rel,
	&quadBez_XY,
	&quadBez_control,
	&quadBez_type,
};
struct backbone_structStruct quadBez = {
	"quadBez",
	4,
	quadBez_varArr,
	"",
	"",
	0,
	0, // len?
	.structSize = sizeof ( struct quadBez ),
	quadBez_attributes,
};




int ellipArc_attributes[] = {
	0,
	0,
	0,
	0,
	0,
	0,
};
struct backbone_subVar ellipArc_rel = {
	.name = "rel",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct ellipArc, rel ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar ellipArc_XY = {
	.name = "XY",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = 2,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct ellipArc, XY ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar ellipArc_rXY = {
	.name = "rXY",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = 2,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct ellipArc, rXY ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar ellipArc_angle = {
	.name = "angle",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct ellipArc, angle ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar ellipArc_largeArcFlag = {
	.name = "largeArcFlag",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct ellipArc, largeArcFlag ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar ellipArc_sweepFlag = {
	.name = "sweepFlag",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct ellipArc, sweepFlag ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *ellipArc_varArr[] = {
	&ellipArc_rel,
	&ellipArc_XY,
	&ellipArc_rXY,
	&ellipArc_angle,
	&ellipArc_largeArcFlag,
	&ellipArc_sweepFlag,
};
struct backbone_structStruct ellipArc = {
	"ellipArc",
	6,
	ellipArc_varArr,
	"",
	"",
	0,
	0, // len?
	.structSize = sizeof ( struct ellipArc ),
	ellipArc_attributes,
};






/** text */

int text_attributes[] = {
	0,
	1,
	1,
	1,
	0,
};
struct backbone_subVar text_space = {
	.name = "space",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct text, space ),
	.saveFlag = 99,
	.naked = 0,
};
struct backbone_subVar text_style = {
	.name = "style",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct text, style ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar text_x = {
	.name = "x",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct text, x ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar text_y = {
	.name = "y",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct text, y ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subAl text_spanList_subAl = {
	.overflow = 10,
	.literal = 0,
	.type = 1,
	.typeIndex = 11,
	.length = -1,
	.naked = 0,
};
struct backbone_subVar text_spanList = {
	.name = "spanList",
	.type = 0,
	.typeIndex = 3,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		0,
		&text_spanList_subAl,
	},
	.external = offsetof ( struct text, spanList ),
	.saveFlag = 1,
	.naked = 1,
};
struct backbone_subVar *text_varArr[] = {
	&text_space,
	&text_style,
	&text_x,
	&text_y,
	&text_spanList,
};
struct backbone_structStruct text = {
	"text",
	5,
	text_varArr,
	"",
	"",
	0,
	0, // len?
	.structSize = sizeof ( struct text ),
	text_attributes,
};




int tspan_attributes[] = {
	1,
	1,
	1,
	1,
	1,
	0,
	0,
	0,
};
struct backbone_subVar tspan_role = {
	.name = "role",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct tspan, role ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar tspan_id = {
	.name = "id",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct tspan, id ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar tspan_style = {
	.name = "style",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct tspan, style ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar tspan_x = {
	.name = "x",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct tspan, x ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar tspan_y = {
	.name = "y",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct tspan, y ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar tspan_body = {
	.name = "body",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct tspan, body ),
	.saveFlag = 1,
	.naked = 1,
};
struct backbone_subVar tspan_fontSize = {
	.name = "fontSize",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct tspan, fontSize ),
	.saveFlag = 99,
	.naked = 0,
};
struct backbone_subAl tspan_stringBuilder_subAl = {
	.overflow = 160,
	.literal = 1,
	.type = 0,
	.typeIndex = 2,
	.length = -1,
	.naked = 0,
};
struct backbone_subVar tspan_stringBuilder = {
	.name = "stringBuilder",
	.type = 0,
	.typeIndex = 3,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		0,
		&tspan_stringBuilder_subAl,
	},
	.external = offsetof ( struct tspan, stringBuilder ),
	.saveFlag = 99,
	.naked = 0,
};
struct backbone_subVar *tspan_varArr[] = {
	&tspan_role,
	&tspan_id,
	&tspan_style,
	&tspan_x,
	&tspan_y,
	&tspan_body,
	&tspan_fontSize,
	&tspan_stringBuilder,
};
struct backbone_structStruct tspan = {
	"tspan",
	8,
	tspan_varArr,
	"",
	"",
	0,
	0, // len?
	.structSize = sizeof ( struct tspan ),
	tspan_attributes,
};






/** shapes */

int rect_attributes[] = {
	1,
	1,
	1,
	1,
	1,
	1,
	0,
	0,
	0,
	0,
};
struct backbone_subVar rect_style = {
	.name = "style",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct rect, style ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar rect_id = {
	.name = "id",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct rect, id ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar rect_x = {
	.name = "x",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct rect, x ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar rect_y = {
	.name = "y",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct rect, y ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar rect_width = {
	.name = "width",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct rect, width ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar rect_height = {
	.name = "height",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct rect, height ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar rect_fill = {
	.name = "fill",
	.type = 0,
	.typeIndex = 4,
	.initType = 4,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct rect, fill ),
	.saveFlag = 99,
	.naked = 0,
};
struct backbone_subVar rect_stroke = {
	.name = "stroke",
	.type = 0,
	.typeIndex = 4,
	.initType = 4,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct rect, stroke ),
	.saveFlag = 99,
	.naked = 0,
};
struct backbone_subVar rect_stroke_width = {
	.name = "stroke_width",
	.type = 0,
	.typeIndex = 4,
	.initType = 4,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct rect, stroke_width ),
	.saveFlag = 99,
	.naked = 0,
};
struct backbone_subVar rect_stroke_opacity = {
	.name = "stroke_opacity",
	.type = 0,
	.typeIndex = 4,
	.initType = 4,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct rect, stroke_opacity ),
	.saveFlag = 99,
	.naked = 0,
};
struct backbone_subVar *rect_varArr[] = {
	&rect_style,
	&rect_id,
	&rect_x,
	&rect_y,
	&rect_width,
	&rect_height,
	&rect_fill,
	&rect_stroke,
	&rect_stroke_width,
	&rect_stroke_opacity,
};
struct backbone_structStruct rect = {
	"rect",
	10,
	rect_varArr,
	"",
	"",
	0,
	0, // len?
	.structSize = sizeof ( struct rect ),
	rect_attributes,
};




int circle_attributes[] = {
	1,
	1,
	1,
	1,
	1,
};
struct backbone_subVar circle_style = {
	.name = "style",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct circle, style ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar circle_id = {
	.name = "id",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct circle, id ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar circle_cx = {
	.name = "cx",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct circle, cx ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar circle_cy = {
	.name = "cy",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct circle, cy ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar circle_r = {
	.name = "r",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct circle, r ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *circle_varArr[] = {
	&circle_style,
	&circle_id,
	&circle_cx,
	&circle_cy,
	&circle_r,
};
struct backbone_structStruct circle = {
	"circle",
	5,
	circle_varArr,
	"",
	"",
	0,
	0, // len?
	.structSize = sizeof ( struct circle ),
	circle_attributes,
};




int ellipse_attributes[] = {
	0,
	0,
	0,
	0,
	0,
	0,
};
struct backbone_subVar ellipse_style = {
	.name = "style",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct ellipse, style ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar ellipse_id = {
	.name = "id",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct ellipse, id ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar ellipse_cx = {
	.name = "cx",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct ellipse, cx ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar ellipse_cy = {
	.name = "cy",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct ellipse, cy ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar ellipse_rx = {
	.name = "rx",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct ellipse, rx ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar ellipse_ry = {
	.name = "ry",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct ellipse, ry ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *ellipse_varArr[] = {
	&ellipse_style,
	&ellipse_id,
	&ellipse_cx,
	&ellipse_cy,
	&ellipse_rx,
	&ellipse_ry,
};
struct backbone_structStruct ellipse = {
	"ellipse",
	6,
	ellipse_varArr,
	"",
	"",
	0,
	0, // len?
	.structSize = sizeof ( struct ellipse ),
	ellipse_attributes,
};






/** jMod */



/** jPath */

int jPath_attributes[] = {
	0,
	0,
};
struct backbone_subAl jPath_verts_subAl = {
	.overflow = 10,
	.literal = 0,
	.type = 1,
	.typeIndex = 16,
	.length = -1,
	.naked = 0,
};
struct backbone_subVar jPath_verts = {
	.name = "verts",
	.type = 0,
	.typeIndex = 3,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		0,
		&jPath_verts_subAl,
	},
	.external = offsetof ( struct jPath, verts ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subAl jPath_lines_subAl = {
	.overflow = 10,
	.literal = 0,
	.type = 1,
	.typeIndex = 17,
	.length = -1,
	.naked = 0,
};
struct backbone_subVar jPath_lines = {
	.name = "lines",
	.type = 0,
	.typeIndex = 3,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		0,
		&jPath_lines_subAl,
	},
	.external = offsetof ( struct jPath, lines ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *jPath_varArr[] = {
	&jPath_verts,
	&jPath_lines,
};
struct backbone_structStruct jPath = {
	"jPath",
	2,
	jPath_varArr,
	"",
	"",
	0,
	0, // len?
	.structSize = sizeof ( struct jPath ),
	jPath_attributes,
};




int jVert_attributes[] = {
	0,
};
struct backbone_subVar jVert_XY = {
	.name = "XY",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = 2,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct jVert, XY ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *jVert_varArr[] = {
	&jVert_XY,
};
struct backbone_structStruct jVert = {
	"jVert",
	1,
	jVert_varArr,
	"",
	"",
	0,
	0, // len?
	.structSize = sizeof ( struct jVert ),
	jVert_attributes,
};




int jLine_attributes[] = {
	0,
	0,
	0,
	0,
	0,
};
struct backbone_subVar jLine_type = {
	.name = "type",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct jLine, type ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar jLine_v0 = {
	.name = "v0",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct jLine, v0 ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar jLine_v1 = {
	.name = "v1",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct jLine, v1 ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar jLine_c0 = {
	.name = "c0",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = 2,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct jLine, c0 ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar jLine_c1 = {
	.name = "c1",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = 2,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct jLine, c1 ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *jLine_varArr[] = {
	&jLine_type,
	&jLine_v0,
	&jLine_v1,
	&jLine_c0,
	&jLine_c1,
};
struct backbone_structStruct jLine = {
	"jLine",
	5,
	jLine_varArr,
	"",
	"",
	0,
	0, // len?
	.structSize = sizeof ( struct jLine ),
	jLine_attributes,
};






/** jText */

int jText_attributes[] = {
	0,
	0,
	0,
};
struct backbone_subVar jText_XYWH = {
	.name = "XYWH",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = 4,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct jText, XYWH ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subAl jText_sb_subAl = {
	.overflow = 80,
	.literal = 1,
	.type = 0,
	.typeIndex = 2,
	.length = -1,
	.naked = 0,
};
struct backbone_subVar jText_sb = {
	.name = "sb",
	.type = 0,
	.typeIndex = 3,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		0,
		&jText_sb_subAl,
	},
	.external = offsetof ( struct jText, sb ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar jText_fontSize = {
	.name = "fontSize",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct jText, fontSize ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *jText_varArr[] = {
	&jText_XYWH,
	&jText_sb,
	&jText_fontSize,
};
struct backbone_structStruct jText = {
	"jText",
	3,
	jText_varArr,
	"",
	"",
	0,
	0, // len?
	.structSize = sizeof ( struct jText ),
	jText_attributes,
};






/** jGroup */

int jGroup_attributes[] = {
	0,
};
struct backbone_subAl jGroup_eles_subAl = {
	.overflow = 10,
	.literal = 0,
	.type = 1,
	.typeIndex = 20,
	.length = -1,
	.naked = 0,
};
struct backbone_subVar jGroup_eles = {
	.name = "eles",
	.type = 0,
	.typeIndex = 3,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		0,
		&jGroup_eles_subAl,
	},
	.external = offsetof ( struct jGroup, eles ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *jGroup_varArr[] = {
	&jGroup_eles,
};
struct backbone_structStruct jGroup = {
	"jGroup",
	1,
	jGroup_varArr,
	"",
	"",
	0,
	0, // len?
	.structSize = sizeof ( struct jGroup ),
	jGroup_attributes,
};




int jNakedUnion_attributes[] = {
	0,
};
int jNakedUnion__attributes[] = {
	0,
	0,
	0,
	0,
	0,
	0,
	0,
};
struct backbone_subVar jNakedUnion__g = {
	.name = "g",
	.type = 1,
	.typeIndex = 19,
	.initType = 0,
	.length = 0,
	.literal = 0,
	.data = {
		0,
	},
	.external = offsetof ( struct jNakedUnion, g ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar jNakedUnion__path = {
	.name = "path",
	.type = 1,
	.typeIndex = 15,
	.initType = 0,
	.length = 0,
	.literal = 0,
	.data = {
		0,
	},
	.external = offsetof ( struct jNakedUnion, path ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar jNakedUnion__text = {
	.name = "text",
	.type = 1,
	.typeIndex = 18,
	.initType = 0,
	.length = 0,
	.literal = 0,
	.data = {
		0,
	},
	.external = offsetof ( struct jNakedUnion, text ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar jNakedUnion__rect = {
	.name = "rect",
	.type = 1,
	.typeIndex = 22,
	.initType = 0,
	.length = 0,
	.literal = 0,
	.data = {
		0,
	},
	.external = offsetof ( struct jNakedUnion, rect ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar jNakedUnion__circ = {
	.name = "circ",
	.type = 1,
	.typeIndex = 23,
	.initType = 0,
	.length = 0,
	.literal = 0,
	.data = {
		0,
	},
	.external = offsetof ( struct jNakedUnion, circ ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar jNakedUnion__ellipse = {
	.name = "ellipse",
	.type = 1,
	.typeIndex = 24,
	.initType = 0,
	.length = 0,
	.literal = 0,
	.data = {
		0,
	},
	.external = offsetof ( struct jNakedUnion, ellipse ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar jNakedUnion__complex = {
	.name = "complex",
	.type = 1,
	.typeIndex = 25,
	.initType = 0,
	.length = 0,
	.literal = 0,
	.data = {
		0,
	},
	.external = offsetof ( struct jNakedUnion, complex ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *jNakedUnion__varArr[] = {
	&jNakedUnion__g,
	&jNakedUnion__path,
	&jNakedUnion__text,
	&jNakedUnion__rect,
	&jNakedUnion__circ,
	&jNakedUnion__ellipse,
	&jNakedUnion__complex,
};
struct backbone_subComplex jNakedUnion__complex = {
	{
	},
	0,
	7,
	jNakedUnion__varArr,
	"jNaked_"
};
struct backbone_subVar jNakedUnion_ = {
	.name = "",
	.type = 0,
	.typeIndex = 6,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		0,
		&jNakedUnion__complex,
	},
	offsetof ( struct jNakedUnion, type ),
	.saveFlag = 1,
	.naked = 1,
};
struct backbone_subVar *jNakedUnion_varArr[] = {
	&jNakedUnion_,
};
struct backbone_structStruct jNakedUnion = {
	"jNakedUnion",
	1,
	jNakedUnion_varArr,
	"",
	"",
	0,
	0, // len?
	.structSize = sizeof ( struct jNakedUnion ),
	jNakedUnion_attributes,
};




int jvg_attributes[] = {
	0,
	0,
};
struct backbone_subAl jvg_eles_subAl = {
	.overflow = 10,
	.literal = 0,
	.type = 1,
	.typeIndex = 20,
	.length = -1,
	.naked = 0,
};
struct backbone_subVar jvg_eles = {
	.name = "eles",
	.type = 0,
	.typeIndex = 3,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		0,
		&jvg_eles_subAl,
	},
	.external = offsetof ( struct jvg, eles ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar jvg_complexDecList = {
	.name = "complexDecList",
	.type = 1,
	.typeIndex = 25,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct jvg, complexDecList ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *jvg_varArr[] = {
	&jvg_eles,
	&jvg_complexDecList,
};
struct backbone_structStruct jvg = {
	"jvg",
	2,
	jvg_varArr,
	"",
	"",
	0,
	0, // len?
	.structSize = sizeof ( struct jvg ),
	jvg_attributes,
};






/** jShapes */

int jRect_attributes[] = {
	0,
};
struct backbone_subVar jRect_XYWH = {
	.name = "XYWH",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = 4,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct jRect, XYWH ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *jRect_varArr[] = {
	&jRect_XYWH,
};
struct backbone_structStruct jRect = {
	"jRect",
	1,
	jRect_varArr,
	"",
	"",
	0,
	0, // len?
	.structSize = sizeof ( struct jRect ),
	jRect_attributes,
};




int jCirc_attributes[] = {
	0,
	0,
};
struct backbone_subVar jCirc_XY = {
	.name = "XY",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = 2,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct jCirc, XY ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar jCirc_radius = {
	.name = "radius",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct jCirc, radius ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *jCirc_varArr[] = {
	&jCirc_XY,
	&jCirc_radius,
};
struct backbone_structStruct jCirc = {
	"jCirc",
	2,
	jCirc_varArr,
	"",
	"",
	0,
	0, // len?
	.structSize = sizeof ( struct jCirc ),
	jCirc_attributes,
};




int jEllipse_attributes[] = {
	0,
	0,
	0,
	0,
	0,
};
struct backbone_subVar jEllipse_XY = {
	.name = "XY",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = 2,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct jEllipse, XY ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar jEllipse_cx = {
	.name = "cx",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct jEllipse, cx ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar jEllipse_cy = {
	.name = "cy",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct jEllipse, cy ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar jEllipse_rx = {
	.name = "rx",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct jEllipse, rx ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar jEllipse_ry = {
	.name = "ry",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct jEllipse, ry ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *jEllipse_varArr[] = {
	&jEllipse_XY,
	&jEllipse_cx,
	&jEllipse_cy,
	&jEllipse_rx,
	&jEllipse_ry,
};
struct backbone_structStruct jEllipse = {
	"jEllipse",
	5,
	jEllipse_varArr,
	"",
	"",
	0,
	0, // len?
	.structSize = sizeof ( struct jEllipse ),
	jEllipse_attributes,
};






/** complexEle */

int complexDec_attributes[] = {
	0,
	0,
};
struct backbone_subVar complexDec_name = {
	.name = "name",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct complexDec, name ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subAl complexDec_subVars_subAl = {
	.overflow = 10,
	.literal = 0,
	.type = 1,
	.typeIndex = 5,
	.length = 0,
	.naked = 0,
	.modNick = "jHigh",
	.typeName = "subVar",
};
struct backbone_subVar complexDec_subVars = {
	.name = "subVars",
	.type = 0,
	.typeIndex = 3,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		0,
		&complexDec_subVars_subAl,
	},
	.external = offsetof ( struct complexDec, subVars ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *complexDec_varArr[] = {
	&complexDec_name,
	&complexDec_subVars,
};
struct backbone_structStruct complexDec = {
	"complexDec",
	2,
	complexDec_varArr,
	"",
	"",
	0,
	0, // len?
	.structSize = sizeof ( struct complexDec ),
	complexDec_attributes,
};




int complexEle_attributes[] = {
	0,
	0,
};
struct backbone_subVar complexEle_name = {
	.name = "name",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		0,
	},
	.external = offsetof ( struct complexEle, name ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subAl complexEle_subVars_subAl = {
	.overflow = 10,
	.literal = 0,
	.type = 0,
	.typeIndex = 5,
	.length = 0,
	.naked = 0,
};
struct backbone_subVar complexEle_subVars = {
	.name = "subVars",
	.type = 0,
	.typeIndex = 3,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		0,
		&complexEle_subVars_subAl,
	},
	.external = offsetof ( struct complexEle, subVars ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *complexEle_varArr[] = {
	&complexEle_name,
	&complexEle_subVars,
};
struct backbone_structStruct complexEle = {
	"complexEle",
	2,
	complexEle_varArr,
	"",
	"",
	0,
	0, // len?
	.structSize = sizeof ( struct complexEle ),
	complexEle_attributes,
};




int len_backbone_arr = 27;
struct backbone_structStruct *backbone_arr[] = {
	&svg,
	&nakedUnion,
	&g,
	&path,
	&pathUni,
	&moveTo,
	&lineTo,
	&cubicBez,
	&quadBez,
	&ellipArc,
	&text,
	&tspan,
	&rect,
	&circle,
	&ellipse,
	&jPath,
	&jVert,
	&jLine,
	&jText,
	&jGroup,
	&jNakedUnion,
	&jvg,
	&jRect,
	&jCirc,
	&jEllipse,
	&complexDec,
	&complexEle,
};
