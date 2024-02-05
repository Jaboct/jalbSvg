#include "backbone_jalbJvg.h"


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
	.typeIndex = 1,
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
	.typeIndex = 2,
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
	.typeIndex = 5,
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
};
struct backbone_subVar jNakedUnion__g = {
	.name = "g",
	.type = 1,
	.typeIndex = 4,
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
	.typeIndex = 0,
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
	.typeIndex = 3,
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
	.typeIndex = 7,
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
	.typeIndex = 8,
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
	.typeIndex = 9,
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
struct backbone_subVar *jNakedUnion__varArr[] = {
	&jNakedUnion__g,
	&jNakedUnion__path,
	&jNakedUnion__text,
	&jNakedUnion__rect,
	&jNakedUnion__circ,
	&jNakedUnion__ellipse,
};
struct backbone_subComplex jNakedUnion__complex = {
	{
	},
	0,
	6,
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
};
struct backbone_subAl jvg_eles_subAl = {
	.overflow = 10,
	.literal = 0,
	.type = 1,
	.typeIndex = 5,
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
struct backbone_subVar *jvg_varArr[] = {
	&jvg_eles,
};
struct backbone_structStruct jvg = {
	"jvg",
	1,
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




int len_backbone_arr_jalbJvg = 10;
struct backbone_structStruct *backbone_arr_jalbJvg[] = {
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
};
