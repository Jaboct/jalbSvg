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
struct backbone_subVar backboneVar_jPath_verts = {
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
struct backbone_subVar backboneVar_jPath_lines = {
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
	&backboneVar_jPath_verts,
	&backboneVar_jPath_lines,
};
struct backbone_structStruct backboneStru_jPath = {
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
struct backbone_subVar backboneVar_jVert_XY = {
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
	&backboneVar_jVert_XY,
};
struct backbone_structStruct backboneStru_jVert = {
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
	0,
	0,
	0,
};
struct backbone_subVar backboneVar_jLine_type = {
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
struct backbone_subVar backboneVar_jLine_v0 = {
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
struct backbone_subVar backboneVar_jLine_v1 = {
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
struct backbone_subVar backboneVar_jLine_c0 = {
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
struct backbone_subVar backboneVar_jLine_c1 = {
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
struct backbone_subVar backboneVar_jLine_markerStart = {
	.name = "markerStart",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct jLine, markerStart ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_jLine_markerMid = {
	.name = "markerMid",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct jLine, markerMid ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar backboneVar_jLine_markerEnd = {
	.name = "markerEnd",
	.type = 0,
	.typeIndex = 0,
	.initType = 0,
	.length = -1,
	.literal = 1,
	.data = {
		.id = 0,
	},
	.external = offsetof ( struct jLine, markerEnd ),
	.saveFlag = 1,
	.naked = 0,
};
struct backbone_subVar *jLine_varArr[] = {
	&backboneVar_jLine_type,
	&backboneVar_jLine_v0,
	&backboneVar_jLine_v1,
	&backboneVar_jLine_c0,
	&backboneVar_jLine_c1,
	&backboneVar_jLine_markerStart,
	&backboneVar_jLine_markerMid,
	&backboneVar_jLine_markerEnd,
};
struct backbone_structStruct backboneStru_jLine = {
	.name = "jLine",
	.varsLen = 8,
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
struct backbone_subVar backboneVar_jText_XYWH = {
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
struct backbone_subVar backboneVar_jText_sb = {
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
struct backbone_subVar backboneVar_jText_fontSize = {
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
	&backboneVar_jText_XYWH,
	&backboneVar_jText_sb,
	&backboneVar_jText_fontSize,
};
struct backbone_structStruct backboneStru_jText = {
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
struct backbone_subVar backboneVar_jGroup_eles = {
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
	&backboneVar_jGroup_eles,
};
struct backbone_structStruct backboneStru_jGroup = {
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
struct backbone_subVar backboneVar_jNakedUnion__g = {
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
struct backbone_subVar backboneVar_jNakedUnion__path = {
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
struct backbone_subVar backboneVar_jNakedUnion__text = {
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
struct backbone_subVar backboneVar_jNakedUnion__rect = {
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
struct backbone_subVar backboneVar_jNakedUnion__circ = {
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
struct backbone_subVar backboneVar_jNakedUnion__ellipse = {
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
struct backbone_subVar backboneVar_jNakedUnion__complex = {
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
	&backboneVar_jNakedUnion__g,
	&backboneVar_jNakedUnion__path,
	&backboneVar_jNakedUnion__text,
	&backboneVar_jNakedUnion__rect,
	&backboneVar_jNakedUnion__circ,
	&backboneVar_jNakedUnion__ellipse,
	&backboneVar_jNakedUnion__complex,
};
struct backbone_subComplex jNakedUnion__complex = {
	.type = {
	},
	.typeDec = 0,
	.listLen = 7,
	.arr = jNakedUnion__varArr,
	.prefix = "jNaked_"
};
struct backbone_subVar backboneVar_jNakedUnion_ = {
	.name = "",
	.type = 0,
	.typeIndex = 6,
	.initType = 0,
	.length = 0,
	.literal = 1,
	.data = {
		.id = 0,
		.ptr = &jNakedUnion__complex,
	},
	.external = offsetof ( struct jNakedUnion, type ),
	.saveFlag = 1,
	.naked = 1,
};
struct backbone_subVar *jNakedUnion_varArr[] = {
	&backboneVar_jNakedUnion_,
};
struct backbone_structStruct backboneStru_jNakedUnion = {
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
struct backbone_subVar backboneVar_jvg_eles = {
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
struct backbone_subVar backboneVar_jvg_moduleList = {
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
struct backbone_subVar backboneVar_jvg_moduleDataList = {
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
	&backboneVar_jvg_eles,
	&backboneVar_jvg_moduleList,
	&backboneVar_jvg_moduleDataList,
};
struct backbone_structStruct backboneStru_jvg = {
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
struct backbone_subVar backboneVar_jRect_XYWH = {
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
	&backboneVar_jRect_XYWH,
};
struct backbone_structStruct backboneStru_jRect = {
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
struct backbone_subVar backboneVar_jCirc_XY = {
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
struct backbone_subVar backboneVar_jCirc_radius = {
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
	&backboneVar_jCirc_XY,
	&backboneVar_jCirc_radius,
};
struct backbone_structStruct backboneStru_jCirc = {
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
struct backbone_subVar backboneVar_jEllipse_XY = {
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
struct backbone_subVar backboneVar_jEllipse_cx = {
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
struct backbone_subVar backboneVar_jEllipse_cy = {
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
struct backbone_subVar backboneVar_jEllipse_rx = {
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
struct backbone_subVar backboneVar_jEllipse_ry = {
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
	&backboneVar_jEllipse_XY,
	&backboneVar_jEllipse_cx,
	&backboneVar_jEllipse_cy,
	&backboneVar_jEllipse_rx,
	&backboneVar_jEllipse_ry,
};
struct backbone_structStruct backboneStru_jEllipse = {
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
struct backbone_subVar backboneVar_complexDec_name = {
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
struct backbone_subVar backboneVar_complexDec_subVars = {
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
struct backbone_subVar backboneVar_complexDec_modName = {
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
struct backbone_subVar backboneVar_complexDec_renderFunct_name = {
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
struct backbone_subVar backboneVar_complexDec_renderFunct = {
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
struct backbone_subVar backboneVar_complexDec_renderParams = {
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
struct backbone_subVar backboneVar_complexDec_eventFunct_name = {
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
struct backbone_subVar backboneVar_complexDec_eventFunct = {
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
struct backbone_subVar backboneVar_complexDec_eventParams = {
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
	&backboneVar_complexDec_name,
	&backboneVar_complexDec_subVars,
	&backboneVar_complexDec_modName,
	&backboneVar_complexDec_renderFunct_name,
	&backboneVar_complexDec_renderFunct,
	&backboneVar_complexDec_renderParams,
	&backboneVar_complexDec_eventFunct_name,
	&backboneVar_complexDec_eventFunct,
	&backboneVar_complexDec_eventParams,
};
struct backbone_structStruct backboneStru_complexDec = {
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
struct backbone_subVar backboneVar_complexEle_XYWH = {
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
struct backbone_subVar backboneVar_complexEle_decModI = {
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
struct backbone_subVar backboneVar_complexEle_decType = {
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
struct backbone_subVar backboneVar_complexEle_liveSubVars = {
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
	&backboneVar_complexEle_XYWH,
	&backboneVar_complexEle_decModI,
	&backboneVar_complexEle_decType,
	&backboneVar_complexEle_liveSubVars,
};
struct backbone_structStruct backboneStru_complexEle = {
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
struct backbone_subVar backboneVar_jLiveData__i = {
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
struct backbone_subVar backboneVar_jLiveData__f = {
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
struct backbone_subVar backboneVar_jLiveData__complexRef = {
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
	&backboneVar_jLiveData__i,
	&backboneVar_jLiveData__f,
	&backboneVar_jLiveData__complexRef,
};
struct backbone_subComplex jLiveData__complex = {
	.type = {
	},
	.typeDec = 0,
	.listLen = 3,
	.arr = jLiveData__varArr,
	.prefix = "jld_"
};
struct backbone_subVar backboneVar_jLiveData_ = {
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
	&backboneVar_jLiveData_,
};
struct backbone_structStruct backboneStru_jLiveData = {
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
struct backbone_subVar backboneVar_complexRef_eleI = {
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
struct backbone_subVar backboneVar_complexRef_complexPtr = {
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
	&backboneVar_complexRef_eleI,
	&backboneVar_complexRef_complexPtr,
};
struct backbone_structStruct backboneStru_complexRef = {
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
struct backbone_subVar backboneVar_complexMod_name = {
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
struct backbone_subVar backboneVar_complexMod_complexDecList = {
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
struct backbone_subVar backboneVar_complexMod_globalVars = {
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
struct backbone_subVar backboneVar_complexMod_globalScripts = {
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
	&backboneVar_complexMod_name,
	&backboneVar_complexMod_complexDecList,
	&backboneVar_complexMod_globalVars,
	&backboneVar_complexMod_globalScripts,
};
struct backbone_structStruct backboneStru_complexMod = {
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
struct backbone_subVar backboneVar_complexModData_globalData = {
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
	&backboneVar_complexModData_globalData,
};
struct backbone_structStruct backboneStru_complexModData = {
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
struct backbone_subVar backboneVar_complexScript_name = {
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
struct backbone_subVar backboneVar_complexScript_eleList = {
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
	&backboneVar_complexScript_name,
	&backboneVar_complexScript_eleList,
};
struct backbone_structStruct backboneStru_complexScript = {
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
struct backbone_subVar backboneVar_cScriptEle__varDec = {
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
struct backbone_subVar backboneVar_cScriptEle__operator = {
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
	&backboneVar_cScriptEle__varDec,
	&backboneVar_cScriptEle__operator,
};
struct backbone_subComplex cScriptEle__complex = {
	.type = {
	},
	.typeDec = 0,
	.listLen = 2,
	.arr = cScriptEle__varArr,
	.prefix = ""
};
struct backbone_subVar backboneVar_cScriptEle_ = {
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
	&backboneVar_cScriptEle_,
};
struct backbone_structStruct backboneStru_cScriptEle = {
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
	&backboneStru_jPath,
	&backboneStru_jVert,
	&backboneStru_jLine,
	&backboneStru_jText,
	&backboneStru_jGroup,
	&backboneStru_jNakedUnion,
	&backboneStru_jvg,
	&backboneStru_jRect,
	&backboneStru_jCirc,
	&backboneStru_jEllipse,
	&backboneStru_complexDec,
	&backboneStru_complexEle,
	&backboneStru_jLiveData,
	&backboneStru_complexMod,
	&backboneStru_complexScript,
	&backboneStru_cScriptEle,
	&backboneStru_complexModData,
	&backboneStru_complexRef,
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


