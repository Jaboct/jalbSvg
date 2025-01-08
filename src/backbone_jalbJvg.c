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
		.id = 0,
		.ptr = &jPath_verts_subAl,
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
		.id = 0,
		.ptr = &jPath_lines_subAl,
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
	.name = "jPath",
	.varsLen = 2,
	.vars = jPath_varArr,
	.overloadRenderEdit = "",
	.overloadEventEdit = "",
	.structDeclaration = 0,
	.structSize = sizeof ( struct jPath ),
	.attributes = jPath_attributes,
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
		.id = 0,
	},
	.external = offsetof ( struct jVert, XY ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *jVert_varArr[] = {
	&jVert_XY,
};
struct backbone_structStruct jVert = {
	.name = "jVert",
	.varsLen = 1,
	.vars = jVert_varArr,
	.overloadRenderEdit = "",
	.overloadEventEdit = "",
	.structDeclaration = 0,
	.structSize = sizeof ( struct jVert ),
	.attributes = jVert_attributes,
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
		.id = 0,
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
		.id = 0,
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
		.id = 0,
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
		.id = 0,
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
		.id = 0,
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
	.name = "jLine",
	.varsLen = 5,
	.vars = jLine_varArr,
	.overloadRenderEdit = "",
	.overloadEventEdit = "",
	.structDeclaration = 0,
	.structSize = sizeof ( struct jLine ),
	.attributes = jLine_attributes,
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
		.id = 0,
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
		.id = 0,
		.ptr = &jText_sb_subAl,
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
		.id = 0,
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
	.name = "jText",
	.varsLen = 3,
	.vars = jText_varArr,
	.overloadRenderEdit = "",
	.overloadEventEdit = "",
	.structDeclaration = 0,
	.structSize = sizeof ( struct jText ),
	.attributes = jText_attributes,
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
		.id = 0,
		.ptr = &jGroup_eles_subAl,
	},
	.external = offsetof ( struct jGroup, eles ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *jGroup_varArr[] = {
	&jGroup_eles,
};
struct backbone_structStruct jGroup = {
	.name = "jGroup",
	.varsLen = 1,
	.vars = jGroup_varArr,
	.overloadRenderEdit = "",
	.overloadEventEdit = "",
	.structDeclaration = 0,
	.structSize = sizeof ( struct jGroup ),
	.attributes = jGroup_attributes,
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
	.typeIndex = 4,
	.initType = 0,
	.length = 0,
	.literal = 0,
	.data = {
		.id = 0,
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
		.id = 0,
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
		.id = 0,
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
		.id = 0,
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
		.id = 0,
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
		.id = 0,
	},
	.external = offsetof ( struct jNakedUnion, ellipse ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar jNakedUnion__complex = {
	.name = "complex",
	.type = 1,
	.typeIndex = 11,
	.initType = 0,
	.length = 0,
	.literal = 0,
	.data = {
		.id = 0,
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
struct backbone_subComplex jNakedUnion_complex = {
	.type = {
	},
	.typeDec = 0,
	.listLen = 7,
	.arr = jNakedUnion__varArr,
	.prefix = "jNaked_"
};
struct backbone_subVar jNakedUnion_ = {
	.name = "",
	.type = 0,
	.typeIndex = 6,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		.id = 0,
		.ptr = &jNakedUnion_complex,
	},
	.external = offsetof ( struct jNakedUnion, type ),
	.saveFlag = 1,
	.naked = 1,
};
struct backbone_subVar *jNakedUnion_varArr[] = {
	&jNakedUnion_,
};
struct backbone_structStruct jNakedUnion = {
	.name = "jNakedUnion",
	.varsLen = 1,
	.vars = jNakedUnion_varArr,
	.overloadRenderEdit = "",
	.overloadEventEdit = "",
	.structDeclaration = 0,
	.structSize = sizeof ( struct jNakedUnion ),
	.attributes = jNakedUnion_attributes,
};




int jvg_attributes[] = {
	0,
	0,
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
		.id = 0,
		.ptr = &jvg_eles_subAl,
	},
	.external = offsetof ( struct jvg, eles ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subAl jvg_moduleList_subAl = {
	.overflow = 10,
	.literal = 0,
	.type = 1,
	.typeIndex = 13,
	.length = -1,
	.naked = 0,
};
struct backbone_subVar jvg_moduleList = {
	.name = "moduleList",
	.type = 0,
	.typeIndex = 3,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		.id = 0,
		.ptr = &jvg_moduleList_subAl,
	},
	.external = offsetof ( struct jvg, moduleList ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subAl jvg_moduleDataList_subAl = {
	.overflow = 10,
	.literal = 0,
	.type = 1,
	.typeIndex = 16,
	.length = -1,
	.naked = 0,
};
struct backbone_subVar jvg_moduleDataList = {
	.name = "moduleDataList",
	.type = 0,
	.typeIndex = 3,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		.id = 0,
		.ptr = &jvg_moduleDataList_subAl,
	},
	.external = offsetof ( struct jvg, moduleDataList ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *jvg_varArr[] = {
	&jvg_eles,
	&jvg_moduleList,
	&jvg_moduleDataList,
};
struct backbone_structStruct jvg = {
	.name = "jvg",
	.varsLen = 3,
	.vars = jvg_varArr,
	.overloadRenderEdit = "",
	.overloadEventEdit = "",
	.structDeclaration = 0,
	.structSize = sizeof ( struct jvg ),
	.attributes = jvg_attributes,
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
		.id = 0,
	},
	.external = offsetof ( struct jRect, XYWH ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *jRect_varArr[] = {
	&jRect_XYWH,
};
struct backbone_structStruct jRect = {
	.name = "jRect",
	.varsLen = 1,
	.vars = jRect_varArr,
	.overloadRenderEdit = "",
	.overloadEventEdit = "",
	.structDeclaration = 0,
	.structSize = sizeof ( struct jRect ),
	.attributes = jRect_attributes,
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
		.id = 0,
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
		.id = 0,
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
	.name = "jCirc",
	.varsLen = 2,
	.vars = jCirc_varArr,
	.overloadRenderEdit = "",
	.overloadEventEdit = "",
	.structDeclaration = 0,
	.structSize = sizeof ( struct jCirc ),
	.attributes = jCirc_attributes,
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
		.id = 0,
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
		.id = 0,
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
		.id = 0,
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
		.id = 0,
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
		.id = 0,
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
	.name = "jEllipse",
	.varsLen = 5,
	.vars = jEllipse_varArr,
	.overloadRenderEdit = "",
	.overloadEventEdit = "",
	.structDeclaration = 0,
	.structSize = sizeof ( struct jEllipse ),
	.attributes = jEllipse_attributes,
};






/** complexEle */

int complexDec_attributes[] = {
	0,
	0,
	0,
	0,
	0,
	0,
	0,
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
		.id = 0,
	},
	.external = offsetof ( struct complexDec, name ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subAl complexDec_subVars_subAl = {
	.overflow = 10,
	.literal = 0,
	.type = 1,
	.typeIndex = 0,
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
		.id = 0,
		.ptr = &complexDec_subVars_subAl,
	},
	.external = offsetof ( struct complexDec, subVars ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar complexDec_modName = {
	.name = "modName",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct complexDec, modName ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar complexDec_renderFunct_name = {
	.name = "renderFunct_name",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct complexDec, renderFunct_name ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar complexDec_renderFunct = {
	.name = "renderFunct",
	.type = 0,
	.typeIndex = 5,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct complexDec, renderFunct ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subAl complexDec_renderParams_subAl = {
	.overflow = 10,
	.literal = 1,
	.type = 0,
	.typeIndex = 0,
	.length = -1,
	.naked = 0,
};
struct backbone_subVar complexDec_renderParams = {
	.name = "renderParams",
	.type = 0,
	.typeIndex = 3,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		.id = 0,
		.ptr = &complexDec_renderParams_subAl,
	},
	.external = offsetof ( struct complexDec, renderParams ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar complexDec_eventFunct_name = {
	.name = "eventFunct_name",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct complexDec, eventFunct_name ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar complexDec_eventFunct = {
	.name = "eventFunct",
	.type = 0,
	.typeIndex = 5,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct complexDec, eventFunct ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subAl complexDec_eventParams_subAl = {
	.overflow = 10,
	.literal = 1,
	.type = 0,
	.typeIndex = 0,
	.length = -1,
	.naked = 0,
};
struct backbone_subVar complexDec_eventParams = {
	.name = "eventParams",
	.type = 0,
	.typeIndex = 3,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		.id = 0,
		.ptr = &complexDec_eventParams_subAl,
	},
	.external = offsetof ( struct complexDec, eventParams ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *complexDec_varArr[] = {
	&complexDec_name,
	&complexDec_subVars,
	&complexDec_modName,
	&complexDec_renderFunct_name,
	&complexDec_renderFunct,
	&complexDec_renderParams,
	&complexDec_eventFunct_name,
	&complexDec_eventFunct,
	&complexDec_eventParams,
};
struct backbone_structStruct complexDec = {
	.name = "complexDec",
	.varsLen = 9,
	.vars = complexDec_varArr,
	.overloadRenderEdit = "",
	.overloadEventEdit = "",
	.structDeclaration = 0,
	.structSize = sizeof ( struct complexDec ),
	.attributes = complexDec_attributes,
};




int complexEle_attributes[] = {
	0,
	0,
	0,
	0,
};
struct backbone_subVar complexEle_XYWH = {
	.name = "XYWH",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = 4,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct complexEle, XYWH ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar complexEle_decModI = {
	.name = "decModI",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct complexEle, decModI ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar complexEle_decType = {
	.name = "decType",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct complexEle, decType ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subAl complexEle_liveSubVars_subAl = {
	.overflow = 10,
	.literal = 0,
	.type = 1,
	.typeIndex = 12,
	.length = 0,
	.naked = 0,
};
struct backbone_subVar complexEle_liveSubVars = {
	.name = "liveSubVars",
	.type = 0,
	.typeIndex = 3,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		.id = 0,
		.ptr = &complexEle_liveSubVars_subAl,
	},
	.external = offsetof ( struct complexEle, liveSubVars ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *complexEle_varArr[] = {
	&complexEle_XYWH,
	&complexEle_decModI,
	&complexEle_decType,
	&complexEle_liveSubVars,
};
struct backbone_structStruct complexEle = {
	.name = "complexEle",
	.varsLen = 4,
	.vars = complexEle_varArr,
	.overloadRenderEdit = "",
	.overloadEventEdit = "",
	.structDeclaration = 0,
	.structSize = sizeof ( struct complexEle ),
	.attributes = complexEle_attributes,
};




int jLiveData_attributes[] = {
	0,
};
int jLiveData__attributes[] = {
	0,
	0,
	0,
};
struct backbone_subVar jLiveData__i = {
	.name = "i",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct jLiveData, i ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar jLiveData__f = {
	.name = "f",
	.type = 0,
	.typeIndex = 1,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct jLiveData, f ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar jLiveData__complexRef = {
	.name = "complexRef",
	.type = 1,
	.typeIndex = 17,
	.initType = 0,
	.length = 0,
	.literal = 0,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct jLiveData, complexRef ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *jLiveData__varArr[] = {
	&jLiveData__i,
	&jLiveData__f,
	&jLiveData__complexRef,
};
struct backbone_subComplex jLiveData__complex = {
	.type = {
	},
	.typeDec = 0,
	.listLen = 3,
	.arr = jLiveData__varArr,
	.prefix = "jld_"
};
struct backbone_subVar jLiveData_ = {
	.name = "",
	.type = 0,
	.typeIndex = 6,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		.id = 0,
		.ptr = &jLiveData__complex,
	},
	.external = offsetof ( struct jLiveData, type ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *jLiveData_varArr[] = {
	&jLiveData_,
};
struct backbone_structStruct jLiveData = {
	.name = "jLiveData",
	.varsLen = 1,
	.vars = jLiveData_varArr,
	.overloadRenderEdit = "",
	.overloadEventEdit = "",
	.structDeclaration = 0,
	.structSize = sizeof ( struct jLiveData ),
	.attributes = jLiveData_attributes,
};




int complexRef_attributes[] = {
	0,
	0,
};
struct backbone_subVar complexRef_eleI = {
	.name = "eleI",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct complexRef, eleI ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar complexRef_complexPtr = {
	.name = "complexPtr",
	.type = 1,
	.typeIndex = 11,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct complexRef, complexPtr ),
	.saveFlag = 99,
	.naked = 0,
};
struct backbone_subVar *complexRef_varArr[] = {
	&complexRef_eleI,
	&complexRef_complexPtr,
};
struct backbone_structStruct complexRef = {
	.name = "complexRef",
	.varsLen = 2,
	.vars = complexRef_varArr,
	.overloadRenderEdit = "",
	.overloadEventEdit = "",
	.structDeclaration = 0,
	.structSize = sizeof ( struct complexRef ),
	.attributes = complexRef_attributes,
};






/** complexMod */

int complexMod_attributes[] = {
	0,
	0,
	0,
	0,
};
struct backbone_subVar complexMod_name = {
	.name = "name",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct complexMod, name ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subAl complexMod_complexDecList_subAl = {
	.overflow = 10,
	.literal = 0,
	.type = 1,
	.typeIndex = 10,
	.length = -1,
	.naked = 0,
};
struct backbone_subVar complexMod_complexDecList = {
	.name = "complexDecList",
	.type = 0,
	.typeIndex = 3,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		.id = 0,
		.ptr = &complexMod_complexDecList_subAl,
	},
	.external = offsetof ( struct complexMod, complexDecList ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subAl complexMod_globalVars_subAl = {
	.overflow = 10,
	.literal = 0,
	.type = 1,
	.typeIndex = 0,
	.length = -1,
	.naked = 0,
	.modNick = "jHigh",
	.typeName = "subVar",
};
struct backbone_subVar complexMod_globalVars = {
	.name = "globalVars",
	.type = 0,
	.typeIndex = 3,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		.id = 0,
		.ptr = &complexMod_globalVars_subAl,
	},
	.external = offsetof ( struct complexMod, globalVars ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subAl complexMod_globalScripts_subAl = {
	.overflow = 10,
	.literal = 0,
	.type = 1,
	.typeIndex = 14,
	.length = -1,
	.naked = 0,
};
struct backbone_subVar complexMod_globalScripts = {
	.name = "globalScripts",
	.type = 0,
	.typeIndex = 3,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		.id = 0,
		.ptr = &complexMod_globalScripts_subAl,
	},
	.external = offsetof ( struct complexMod, globalScripts ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *complexMod_varArr[] = {
	&complexMod_name,
	&complexMod_complexDecList,
	&complexMod_globalVars,
	&complexMod_globalScripts,
};
struct backbone_structStruct complexMod = {
	.name = "complexMod",
	.varsLen = 4,
	.vars = complexMod_varArr,
	.overloadRenderEdit = "",
	.overloadEventEdit = "",
	.structDeclaration = 0,
	.structSize = sizeof ( struct complexMod ),
	.attributes = complexMod_attributes,
};




int complexModData_attributes[] = {
	0,
};
struct backbone_subAl complexModData_globalData_subAl = {
	.overflow = 10,
	.literal = 0,
	.type = 1,
	.typeIndex = 12,
	.length = -1,
	.naked = 0,
};
struct backbone_subVar complexModData_globalData = {
	.name = "globalData",
	.type = 0,
	.typeIndex = 3,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		.id = 0,
		.ptr = &complexModData_globalData_subAl,
	},
	.external = offsetof ( struct complexModData, globalData ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *complexModData_varArr[] = {
	&complexModData_globalData,
};
struct backbone_structStruct complexModData = {
	.name = "complexModData",
	.varsLen = 1,
	.vars = complexModData_varArr,
	.overloadRenderEdit = "",
	.overloadEventEdit = "",
	.structDeclaration = 0,
	.structSize = sizeof ( struct complexModData ),
	.attributes = complexModData_attributes,
};






/** complexScript */

int complexScript_attributes[] = {
	0,
	0,
};
struct backbone_subVar complexScript_name = {
	.name = "name",
	.type = 0,
	.typeIndex = 4,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct complexScript, name ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subAl complexScript_eleList_subAl = {
	.overflow = 10,
	.literal = 0,
	.type = 1,
	.typeIndex = 15,
	.length = -1,
	.naked = 0,
};
struct backbone_subVar complexScript_eleList = {
	.name = "eleList",
	.type = 0,
	.typeIndex = 3,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		.id = 0,
		.ptr = &complexScript_eleList_subAl,
	},
	.external = offsetof ( struct complexScript, eleList ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *complexScript_varArr[] = {
	&complexScript_name,
	&complexScript_eleList,
};
struct backbone_structStruct complexScript = {
	.name = "complexScript",
	.varsLen = 2,
	.vars = complexScript_varArr,
	.overloadRenderEdit = "",
	.overloadEventEdit = "",
	.structDeclaration = 0,
	.structSize = sizeof ( struct complexScript ),
	.attributes = complexScript_attributes,
};




int cScriptEle_attributes[] = {
	0,
};
int cScriptEle__attributes[] = {
	0,
	0,
};
struct backbone_subVar cScriptEle__varDec = {
	.name = "varDec",
	.type = 0,
	.typeIndex = -1,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct cScriptEle, varDec ),
	.saveFlag = 1,
	.naked = 0,
	.modNick = "jHigh",
	.typeName = "subVar",
};
struct backbone_subVar cScriptEle__operator = {
	.name = "operator",
	.type = 0,
	.typeIndex = -1,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct cScriptEle, operator ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *cScriptEle__varArr[] = {
	&cScriptEle__varDec,
	&cScriptEle__operator,
};
struct backbone_subComplex cScriptEle__complex = {
	.type = {
	},
	.typeDec = 0,
	.listLen = 2,
	.arr = cScriptEle__varArr,
	.prefix = ""
};
struct backbone_subVar cScriptEle_ = {
	.name = "",
	.type = 0,
	.typeIndex = 6,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		.id = 0,
		.ptr = &cScriptEle__complex,
	},
	.external = offsetof ( struct cScriptEle, type ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *cScriptEle_varArr[] = {
	&cScriptEle_,
};
struct backbone_structStruct cScriptEle = {
	.name = "cScriptEle",
	.varsLen = 1,
	.vars = cScriptEle_varArr,
	.overloadRenderEdit = "",
	.overloadEventEdit = "",
	.structDeclaration = 0,
	.structSize = sizeof ( struct cScriptEle ),
	.attributes = cScriptEle_attributes,
};




/// Data Array

int len_backbone_arr_jalbJvg = 18;
struct backbone_structStruct *backbone_arr_jalbJvg[] = {
	&jPath,
	&jVert,
	&jLine,
	&jText,
	&jGroup,
	&jNakedUnion,	// 5
	&jvg,
	&jRect,
	&jCirc,
	&jEllipse,
	&complexDec,	// 10
	&complexEle,
	&jLiveData,
	&complexMod,
	&complexScript,
	&cScriptEle,	// 15
	&complexModData,
	&complexRef,
};


/// Getters

struct backbone_structStruct **get_backbone_arr_jalbJvg ( ) {
	return backbone_arr_jalbJvg;
}

int get_backbone_arr_len_jalbJvg ( ) {
	return len_backbone_arr_jalbJvg;
}

int get_backbone_arr_total_jalbJvg ( struct backbone_structStruct ***arrPtr ) {
	*arrPtr = backbone_arr_jalbJvg;
	return len_backbone_arr_jalbJvg;
}


