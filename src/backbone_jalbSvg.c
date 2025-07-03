#include "backbone_jalbSvg.h"


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
struct backbone_subVar backboneVar_svg_width = {
	.name = "width",
	.type = 0,
	.typeIndex = 4,
	.initType = 4,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct svg, width ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_svg_height = {
	.name = "height",
	.type = 0,
	.typeIndex = 4,
	.initType = 4,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct svg, height ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_svg_viewBox = {
	.name = "viewBox",
	.type = 0,
	.typeIndex = 4,
	.initType = 4,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct svg, viewBox ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_svg_version = {
	.name = "version",
	.type = 0,
	.typeIndex = 4,
	.initType = 4,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct svg, version ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_svg_id = {
	.name = "id",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
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
struct backbone_subVar backboneVar_svg_eles = {
	.name = "eles",
	.type = 0,
	.typeIndex = 3,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		.id = 0,
		.ptr = &svg_eles_subAl,
	},
	.external = offsetof ( struct svg, eles ),
	.saveFlag = 1,
	.naked = 1,
};
struct backbone_subVar *svg_varArr[] = {
	&backboneVar_svg_width,
	&backboneVar_svg_height,
	&backboneVar_svg_viewBox,
	&backboneVar_svg_version,
	&backboneVar_svg_id,
	&backboneVar_svg_eles,
};
struct backbone_structStruct backboneStru_svg = {
	.name = "svg",
	.varsLen = 6,
	.vars = svg_varArr,
	.overloadRenderEdit = "",
	.overloadEventEdit = "",
	.structDeclaration = 0,
	.structSize = sizeof ( struct svg ),
	.attributes = svg_attributes,
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
struct backbone_subVar backboneVar_nakedUnion__g = {
	.name = "g",
	.type = 1,
	.typeIndex = 2,
	.initType = 0,
	.length = 0,
	.literal = 0,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct nakedUnion, g ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_nakedUnion__path = {
	.name = "path",
	.type = 1,
	.typeIndex = 3,
	.initType = 0,
	.length = 0,
	.literal = 0,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct nakedUnion, path ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_nakedUnion__text = {
	.name = "text",
	.type = 1,
	.typeIndex = 10,
	.initType = 0,
	.length = 0,
	.literal = 0,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct nakedUnion, text ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_nakedUnion__rect = {
	.name = "rect",
	.type = 1,
	.typeIndex = 12,
	.initType = 0,
	.length = 0,
	.literal = 0,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct nakedUnion, rect ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_nakedUnion__circle = {
	.name = "circle",
	.type = 1,
	.typeIndex = 13,
	.initType = 0,
	.length = 0,
	.literal = 0,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct nakedUnion, circle ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_nakedUnion__ellipse = {
	.name = "ellipse",
	.type = 1,
	.typeIndex = 14,
	.initType = 0,
	.length = 0,
	.literal = 0,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct nakedUnion, ellipse ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *nakedUnion__varArr[] = {
	&backboneVar_nakedUnion__g,
	&backboneVar_nakedUnion__path,
	&backboneVar_nakedUnion__text,
	&backboneVar_nakedUnion__rect,
	&backboneVar_nakedUnion__circle,
	&backboneVar_nakedUnion__ellipse,
};
struct backbone_subComplex nakedUnion__complex = {
	.type = {
	},
	.typeDec = 0,
	.listLen = 6,
	.arr = nakedUnion__varArr,
	.prefix = ""
};
struct backbone_subVar backboneVar_nakedUnion_ = {
	.name = "",
	.type = 0,
	.typeIndex = 6,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		.id = 0,
		.ptr = &nakedUnion__complex,
	},
	.external = offsetof ( struct nakedUnion, type ),
	.saveFlag = 1,
	.naked = 1,
};
struct backbone_subVar *nakedUnion_varArr[] = {
	&backboneVar_nakedUnion_,
};
struct backbone_structStruct backboneStru_nakedUnion = {
	.name = "nakedUnion",
	.varsLen = 1,
	.vars = nakedUnion_varArr,
	.overloadRenderEdit = "",
	.overloadEventEdit = "",
	.structDeclaration = 0,
	.structSize = sizeof ( struct nakedUnion ),
	.attributes = nakedUnion_attributes,
};




int g_attributes[] = {
	1,
	0,
};
struct backbone_subVar backboneVar_g_id = {
	.name = "id",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
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
struct backbone_subVar backboneVar_g_eles = {
	.name = "eles",
	.type = 0,
	.typeIndex = 3,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		.id = 0,
		.ptr = &g_eles_subAl,
	},
	.external = offsetof ( struct g, eles ),
	.saveFlag = 1,
	.naked = 1,
};
struct backbone_subVar *g_varArr[] = {
	&backboneVar_g_id,
	&backboneVar_g_eles,
};
struct backbone_structStruct backboneStru_g = {
	.name = "g",
	.varsLen = 2,
	.vars = g_varArr,
	.overloadRenderEdit = "",
	.overloadEventEdit = "",
	.structDeclaration = 0,
	.structSize = sizeof ( struct g ),
	.attributes = g_attributes,
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
struct backbone_subVar backboneVar_path_style = {
	.name = "style",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct path, style ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_path_d = {
	.name = "d",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = 1024,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct path, d ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_path_id = {
	.name = "id",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
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
struct backbone_subVar backboneVar_path_eles = {
	.name = "eles",
	.type = 0,
	.typeIndex = 3,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		.id = 0,
		.ptr = &path_eles_subAl,
	},
	.external = offsetof ( struct path, eles ),
	.saveFlag = 99,
	.naked = 0,
};
struct backbone_subVar backboneVar_path_fill = {
	.name = "fill",
	.type = 0,
	.typeIndex = 4,
	.initType = 4,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct path, fill ),
	.saveFlag = 99,
	.naked = 0,
};
struct backbone_subVar backboneVar_path_stroke = {
	.name = "stroke",
	.type = 0,
	.typeIndex = 4,
	.initType = 4,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct path, stroke ),
	.saveFlag = 99,
	.naked = 0,
};
struct backbone_subVar backboneVar_path_stroke_width = {
	.name = "stroke_width",
	.type = 0,
	.typeIndex = 4,
	.initType = 4,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct path, stroke_width ),
	.saveFlag = 99,
	.naked = 0,
};
struct backbone_subVar backboneVar_path_stroke_linecap = {
	.name = "stroke_linecap",
	.type = 0,
	.typeIndex = 4,
	.initType = 4,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct path, stroke_linecap ),
	.saveFlag = 99,
	.naked = 0,
};
struct backbone_subVar backboneVar_path_stroke_linejoin = {
	.name = "stroke_linejoin",
	.type = 0,
	.typeIndex = 4,
	.initType = 4,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct path, stroke_linejoin ),
	.saveFlag = 99,
	.naked = 0,
};
struct backbone_subVar backboneVar_path_stroke_opacity = {
	.name = "stroke_opacity",
	.type = 0,
	.typeIndex = 4,
	.initType = 4,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct path, stroke_opacity ),
	.saveFlag = 99,
	.naked = 0,
};
struct backbone_subVar *path_varArr[] = {
	&backboneVar_path_style,
	&backboneVar_path_d,
	&backboneVar_path_id,
	&backboneVar_path_eles,
	&backboneVar_path_fill,
	&backboneVar_path_stroke,
	&backboneVar_path_stroke_width,
	&backboneVar_path_stroke_linecap,
	&backboneVar_path_stroke_linejoin,
	&backboneVar_path_stroke_opacity,
};
struct backbone_structStruct backboneStru_path = {
	.name = "path",
	.varsLen = 10,
	.vars = path_varArr,
	.overloadRenderEdit = "",
	.overloadEventEdit = "",
	.structDeclaration = 0,
	.structSize = sizeof ( struct path ),
	.attributes = path_attributes,
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
struct backbone_subVar backboneVar_pathUni__moveTo = {
	.name = "moveTo",
	.type = 1,
	.typeIndex = 5,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct pathUni, moveTo ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_pathUni__lineTo = {
	.name = "lineTo",
	.type = 1,
	.typeIndex = 6,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct pathUni, lineTo ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_pathUni__cubicBez = {
	.name = "cubicBez",
	.type = 1,
	.typeIndex = 7,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct pathUni, cubicBez ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_pathUni__quadBez = {
	.name = "quadBez",
	.type = 1,
	.typeIndex = 8,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct pathUni, quadBez ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_pathUni__ellipArc = {
	.name = "ellipArc",
	.type = 1,
	.typeIndex = 9,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct pathUni, ellipArc ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_pathUni__PathEnd = {
	.name = "PathEnd",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct pathUni, PathEnd ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *pathUni__varArr[] = {
	&backboneVar_pathUni__moveTo,
	&backboneVar_pathUni__lineTo,
	&backboneVar_pathUni__cubicBez,
	&backboneVar_pathUni__quadBez,
	&backboneVar_pathUni__ellipArc,
	&backboneVar_pathUni__PathEnd,
};
struct backbone_subComplex pathUni__complex = {
	.type = {
	},
	.typeDec = 0,
	.listLen = 6,
	.arr = pathUni__varArr,
	.prefix = "path_"
};
struct backbone_subVar backboneVar_pathUni_ = {
	.name = "",
	.type = 0,
	.typeIndex = 6,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		.id = 0,
		.ptr = &pathUni__complex,
	},
	.external = offsetof ( struct pathUni, type ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *pathUni_varArr[] = {
	&backboneVar_pathUni_,
};
struct backbone_structStruct backboneStru_pathUni = {
	.name = "pathUni",
	.varsLen = 1,
	.vars = pathUni_varArr,
	.overloadRenderEdit = "",
	.overloadEventEdit = "",
	.structDeclaration = 0,
	.structSize = sizeof ( struct pathUni ),
	.attributes = pathUni_attributes,
};




int moveTo_attributes[] = {
	0,
	0,
};
struct backbone_subVar backboneVar_moveTo_rel = {
	.name = "rel",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct moveTo, rel ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_moveTo_XY = {
	.name = "XY",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = 2,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct moveTo, XY ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *moveTo_varArr[] = {
	&backboneVar_moveTo_rel,
	&backboneVar_moveTo_XY,
};
struct backbone_structStruct backboneStru_moveTo = {
	.name = "moveTo",
	.varsLen = 2,
	.vars = moveTo_varArr,
	.overloadRenderEdit = "",
	.overloadEventEdit = "",
	.structDeclaration = 0,
	.structSize = sizeof ( struct moveTo ),
	.attributes = moveTo_attributes,
};




int lineTo_attributes[] = {
	0,
	0,
	0,
};
struct backbone_subVar backboneVar_lineTo_rel = {
	.name = "rel",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct lineTo, rel ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_lineTo_XY = {
	.name = "XY",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = 2,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct lineTo, XY ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_lineTo_type = {
	.name = "type",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct lineTo, type ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *lineTo_varArr[] = {
	&backboneVar_lineTo_rel,
	&backboneVar_lineTo_XY,
	&backboneVar_lineTo_type,
};
struct backbone_structStruct backboneStru_lineTo = {
	.name = "lineTo",
	.varsLen = 3,
	.vars = lineTo_varArr,
	.overloadRenderEdit = "",
	.overloadEventEdit = "",
	.structDeclaration = 0,
	.structSize = sizeof ( struct lineTo ),
	.attributes = lineTo_attributes,
};




int cubicBez_attributes[] = {
	0,
	0,
	0,
	0,
	0,
};
struct backbone_subVar backboneVar_cubicBez_rel = {
	.name = "rel",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct cubicBez, rel ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_cubicBez_XY = {
	.name = "XY",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = 2,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct cubicBez, XY ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_cubicBez_c0 = {
	.name = "c0",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = 2,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct cubicBez, c0 ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_cubicBez_c1 = {
	.name = "c1",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = 2,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct cubicBez, c1 ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_cubicBez_type = {
	.name = "type",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct cubicBez, type ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *cubicBez_varArr[] = {
	&backboneVar_cubicBez_rel,
	&backboneVar_cubicBez_XY,
	&backboneVar_cubicBez_c0,
	&backboneVar_cubicBez_c1,
	&backboneVar_cubicBez_type,
};
struct backbone_structStruct backboneStru_cubicBez = {
	.name = "cubicBez",
	.varsLen = 5,
	.vars = cubicBez_varArr,
	.overloadRenderEdit = "",
	.overloadEventEdit = "",
	.structDeclaration = 0,
	.structSize = sizeof ( struct cubicBez ),
	.attributes = cubicBez_attributes,
};




int quadBez_attributes[] = {
	0,
	0,
	0,
	0,
};
struct backbone_subVar backboneVar_quadBez_rel = {
	.name = "rel",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct quadBez, rel ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_quadBez_XY = {
	.name = "XY",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = 2,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct quadBez, XY ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_quadBez_control = {
	.name = "control",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = 2,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct quadBez, control ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_quadBez_type = {
	.name = "type",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct quadBez, type ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *quadBez_varArr[] = {
	&backboneVar_quadBez_rel,
	&backboneVar_quadBez_XY,
	&backboneVar_quadBez_control,
	&backboneVar_quadBez_type,
};
struct backbone_structStruct backboneStru_quadBez = {
	.name = "quadBez",
	.varsLen = 4,
	.vars = quadBez_varArr,
	.overloadRenderEdit = "",
	.overloadEventEdit = "",
	.structDeclaration = 0,
	.structSize = sizeof ( struct quadBez ),
	.attributes = quadBez_attributes,
};




int ellipArc_attributes[] = {
	0,
	0,
	0,
	0,
	0,
	0,
};
struct backbone_subVar backboneVar_ellipArc_rel = {
	.name = "rel",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct ellipArc, rel ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_ellipArc_XY = {
	.name = "XY",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = 2,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct ellipArc, XY ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_ellipArc_rXY = {
	.name = "rXY",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = 2,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct ellipArc, rXY ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_ellipArc_angle = {
	.name = "angle",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct ellipArc, angle ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_ellipArc_largeArcFlag = {
	.name = "largeArcFlag",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct ellipArc, largeArcFlag ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_ellipArc_sweepFlag = {
	.name = "sweepFlag",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct ellipArc, sweepFlag ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *ellipArc_varArr[] = {
	&backboneVar_ellipArc_rel,
	&backboneVar_ellipArc_XY,
	&backboneVar_ellipArc_rXY,
	&backboneVar_ellipArc_angle,
	&backboneVar_ellipArc_largeArcFlag,
	&backboneVar_ellipArc_sweepFlag,
};
struct backbone_structStruct backboneStru_ellipArc = {
	.name = "ellipArc",
	.varsLen = 6,
	.vars = ellipArc_varArr,
	.overloadRenderEdit = "",
	.overloadEventEdit = "",
	.structDeclaration = 0,
	.structSize = sizeof ( struct ellipArc ),
	.attributes = ellipArc_attributes,
};






/** text */

int text_attributes[] = {
	0,
	1,
	1,
	1,
	0,
};
struct backbone_subVar backboneVar_text_space = {
	.name = "space",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct text, space ),
	.saveFlag = 99,
	.naked = 0,
};
struct backbone_subVar backboneVar_text_style = {
	.name = "style",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct text, style ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_text_x = {
	.name = "x",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct text, x ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_text_y = {
	.name = "y",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
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
struct backbone_subVar backboneVar_text_spanList = {
	.name = "spanList",
	.type = 0,
	.typeIndex = 3,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		.id = 0,
		.ptr = &text_spanList_subAl,
	},
	.external = offsetof ( struct text, spanList ),
	.saveFlag = 1,
	.naked = 1,
};
struct backbone_subVar *text_varArr[] = {
	&backboneVar_text_space,
	&backboneVar_text_style,
	&backboneVar_text_x,
	&backboneVar_text_y,
	&backboneVar_text_spanList,
};
struct backbone_structStruct backboneStru_text = {
	.name = "text",
	.varsLen = 5,
	.vars = text_varArr,
	.overloadRenderEdit = "",
	.overloadEventEdit = "",
	.structDeclaration = 0,
	.structSize = sizeof ( struct text ),
	.attributes = text_attributes,
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
struct backbone_subVar backboneVar_tspan_role = {
	.name = "role",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct tspan, role ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_tspan_id = {
	.name = "id",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct tspan, id ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_tspan_style = {
	.name = "style",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct tspan, style ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_tspan_x = {
	.name = "x",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct tspan, x ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_tspan_y = {
	.name = "y",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct tspan, y ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_tspan_body = {
	.name = "body",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct tspan, body ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_tspan_fontSize = {
	.name = "fontSize",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
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
struct backbone_subVar backboneVar_tspan_stringBuilder = {
	.name = "stringBuilder",
	.type = 0,
	.typeIndex = 3,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		.id = 0,
		.ptr = &tspan_stringBuilder_subAl,
	},
	.external = offsetof ( struct tspan, stringBuilder ),
	.saveFlag = 99,
	.naked = 0,
};
struct backbone_subVar *tspan_varArr[] = {
	&backboneVar_tspan_role,
	&backboneVar_tspan_id,
	&backboneVar_tspan_style,
	&backboneVar_tspan_x,
	&backboneVar_tspan_y,
	&backboneVar_tspan_body,
	&backboneVar_tspan_fontSize,
	&backboneVar_tspan_stringBuilder,
};
struct backbone_structStruct backboneStru_tspan = {
	.name = "tspan",
	.varsLen = 8,
	.vars = tspan_varArr,
	.overloadRenderEdit = "",
	.overloadEventEdit = "",
	.structDeclaration = 0,
	.structSize = sizeof ( struct tspan ),
	.attributes = tspan_attributes,
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
struct backbone_subVar backboneVar_rect_style = {
	.name = "style",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct rect, style ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_rect_id = {
	.name = "id",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct rect, id ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_rect_x = {
	.name = "x",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct rect, x ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_rect_y = {
	.name = "y",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct rect, y ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_rect_width = {
	.name = "width",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct rect, width ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_rect_height = {
	.name = "height",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct rect, height ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_rect_fill = {
	.name = "fill",
	.type = 0,
	.typeIndex = 4,
	.initType = 4,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct rect, fill ),
	.saveFlag = 99,
	.naked = 0,
};
struct backbone_subVar backboneVar_rect_stroke = {
	.name = "stroke",
	.type = 0,
	.typeIndex = 4,
	.initType = 4,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct rect, stroke ),
	.saveFlag = 99,
	.naked = 0,
};
struct backbone_subVar backboneVar_rect_stroke_width = {
	.name = "stroke_width",
	.type = 0,
	.typeIndex = 4,
	.initType = 4,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct rect, stroke_width ),
	.saveFlag = 99,
	.naked = 0,
};
struct backbone_subVar backboneVar_rect_stroke_opacity = {
	.name = "stroke_opacity",
	.type = 0,
	.typeIndex = 4,
	.initType = 4,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct rect, stroke_opacity ),
	.saveFlag = 99,
	.naked = 0,
};
struct backbone_subVar *rect_varArr[] = {
	&backboneVar_rect_style,
	&backboneVar_rect_id,
	&backboneVar_rect_x,
	&backboneVar_rect_y,
	&backboneVar_rect_width,
	&backboneVar_rect_height,
	&backboneVar_rect_fill,
	&backboneVar_rect_stroke,
	&backboneVar_rect_stroke_width,
	&backboneVar_rect_stroke_opacity,
};
struct backbone_structStruct backboneStru_rect = {
	.name = "rect",
	.varsLen = 10,
	.vars = rect_varArr,
	.overloadRenderEdit = "",
	.overloadEventEdit = "",
	.structDeclaration = 0,
	.structSize = sizeof ( struct rect ),
	.attributes = rect_attributes,
};




int circle_attributes[] = {
	1,
	1,
	1,
	1,
	1,
};
struct backbone_subVar backboneVar_circle_style = {
	.name = "style",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct circle, style ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_circle_id = {
	.name = "id",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct circle, id ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_circle_cx = {
	.name = "cx",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct circle, cx ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_circle_cy = {
	.name = "cy",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct circle, cy ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_circle_r = {
	.name = "r",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct circle, r ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *circle_varArr[] = {
	&backboneVar_circle_style,
	&backboneVar_circle_id,
	&backboneVar_circle_cx,
	&backboneVar_circle_cy,
	&backboneVar_circle_r,
};
struct backbone_structStruct backboneStru_circle = {
	.name = "circle",
	.varsLen = 5,
	.vars = circle_varArr,
	.overloadRenderEdit = "",
	.overloadEventEdit = "",
	.structDeclaration = 0,
	.structSize = sizeof ( struct circle ),
	.attributes = circle_attributes,
};




int ellipse_attributes[] = {
	0,
	0,
	0,
	0,
	0,
	0,
};
struct backbone_subVar backboneVar_ellipse_style = {
	.name = "style",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct ellipse, style ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_ellipse_id = {
	.name = "id",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct ellipse, id ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_ellipse_cx = {
	.name = "cx",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct ellipse, cx ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_ellipse_cy = {
	.name = "cy",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct ellipse, cy ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_ellipse_rx = {
	.name = "rx",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct ellipse, rx ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_ellipse_ry = {
	.name = "ry",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct ellipse, ry ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *ellipse_varArr[] = {
	&backboneVar_ellipse_style,
	&backboneVar_ellipse_id,
	&backboneVar_ellipse_cx,
	&backboneVar_ellipse_cy,
	&backboneVar_ellipse_rx,
	&backboneVar_ellipse_ry,
};
struct backbone_structStruct backboneStru_ellipse = {
	.name = "ellipse",
	.varsLen = 6,
	.vars = ellipse_varArr,
	.overloadRenderEdit = "",
	.overloadEventEdit = "",
	.structDeclaration = 0,
	.structSize = sizeof ( struct ellipse ),
	.attributes = ellipse_attributes,
};




/// Data Array

int len_backbone_arr_jalbSvg = 15;
struct backbone_structStruct *backbone_arr_jalbSvg[] = {
	&backboneStru_svg,
	&backboneStru_nakedUnion,
	&backboneStru_g,
	&backboneStru_path,
	&backboneStru_pathUni,
	&backboneStru_moveTo,
	&backboneStru_lineTo,
	&backboneStru_cubicBez,
	&backboneStru_quadBez,
	&backboneStru_ellipArc,
	&backboneStru_text,
	&backboneStru_tspan,
	&backboneStru_rect,
	&backboneStru_circle,
	&backboneStru_ellipse,
};


/// Getters

struct backbone_structStruct **get_backbone_arr_jalbSvg ( ) {
	return backbone_arr_jalbSvg;
}

int get_backbone_arr_len_jalbSvg ( ) {
	return len_backbone_arr_jalbSvg;
}

int get_backbone_arr_total_jalbSvg ( struct backbone_structStruct ***arrPtr ) {
	*arrPtr = backbone_arr_jalbSvg;
	return len_backbone_arr_jalbSvg;
}


