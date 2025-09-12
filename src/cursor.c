#include "cursor.h"

/** AUTO GENERATED CODE */

extern char altKeys[];

extern float colorWhite[];
extern float colorGray[];
extern float colorDGray[];
extern float colorDGray1[];
extern float colorDGray2[];
extern float colorBlack[];
extern float colorGold[];




void cursor_preInit ( ) {
}


extern int cursor_eleEditId;
extern int cursor_unionEditId;
extern int cursor_pathEditId;
extern int cursor_groupEditId;
extern int cursor_circEditId;
extern int cursor_textEditId;
extern int cursor_rectEditId;
extern int debugPrint_projectName_init;


/** Variables */

extern struct draw2dStruct *draw2dApi;
extern struct draw3dStruct *draw3dApi;
extern struct jalbFont *fonts[];

//extern void (*addCanvas)(int id, void *data, int *xywh);
extern addCanvasF *addCanvas;

extern struct backbone_structStruct backboneStru_cursor_ele;
extern struct backbone_structStruct backboneStru_cursor_union;
extern struct backbone_structStruct backboneStru_cursor_path;
extern struct backbone_structStruct backboneStru_cursor_group;
extern struct backbone_structStruct backboneStru_cursor_circ;
extern struct backbone_structStruct backboneStru_cursor_text;
extern struct backbone_structStruct backboneStru_cursor_rect;

/** Functions */

/** cursor_ele */

struct cursor_ele *cursor_eleInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "cursor_eleInit ( )\n" );
	}
	struct cursor_ele *var = malloc ( sizeof ( struct cursor_ele ) );
	cursor_eleFill ( var );
	return var;
}
void cursor_eleFill ( struct cursor_ele *var ) {
	var->index = 0;
	var->payload = cursor_unionInit ( );
}

void *cursor_eleInitMask ( ) {
	void *ret = cursor_eleInit ( );
	return ret;

}
void cursor_eleClose ( struct cursor_ele *var ) {
	if ( var->payload ) {
		cursor_unionClose ( var->payload );
	}
	free ( var );

}
int cursor_ele_attrib_arr[] = {
	0,
	0,
};
void cursor_eleBodyToVal ( void *varPass, int nameI, char *body ) {

	struct cursor_ele *var = varPass;

	if ( nameI == 0 ) {
		var->index = atoi ( body );
	} else if ( nameI == 1 ) {
		// wont get called?
	}
}

int cursor_eleNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

	struct cursor_ele *var = data;
	if ( strcmp ( body, "index" ) == 0 ) {
		return 0;
	} else if ( strcmp ( body, "payload" ) == 0 ) {
		*strPtr = "cursor_union";
		void **retPtr = ret;
		*retPtr = &var->payload;
		return jxnPtr;
	}
	return -1;
}

struct xmlFuncts cursor_eleXml = {
	.typeName = "cursor_ele",
	.init = cursor_eleInitMask,
	.nameToIndex = cursor_eleNameToIndex,
	.bodyToVal = cursor_eleBodyToVal,
};

void cursor_ele_print ( struct cursor_ele *stru ) {
	printf ( "cursor_ele_print ( )\n" );
}
/** cursor_union */

struct cursor_union *cursor_unionInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "cursor_unionInit ( )\n" );
	}
	struct cursor_union *var = malloc ( sizeof ( struct cursor_union ) );
	cursor_unionFill ( var );
	return var;
}
void cursor_unionFill ( struct cursor_union *var ) {
	var->type = -1;
//	cursor_unionTypeChange0 ( var, 0 );
}
void cursor_unionTypeChange0 ( struct cursor_union *var, int type ) {
	if ( var->type == type ) {
		return;
	}
	if ( var->type == 0 ) {
	} else if ( var->type == 1 ) {
	} else if ( var->type == 2 ) {
	} else if ( var->type == 3 ) {
	} else if ( var->type == 4 ) {
	}
	if ( type == 0 ) {
		var->path = cursor_pathInit ( );
	} else if ( type == 1 ) {
		var->group = cursor_groupInit ( );
	} else if ( type == 2 ) {
		var->circ = cursor_circInit ( );
	} else if ( type == 3 ) {
		var->text = cursor_textInit ( );
	} else if ( type == 4 ) {
		var->rect = cursor_rectInit ( );
	}
	var->type = type;
}


void *cursor_unionInitMask ( ) {
	void *ret = cursor_unionInit ( );
	return ret;

}
void cursor_unionClose ( struct cursor_union *var ) {
	if ( var->type == 0 ) {
	} else if ( var->type == 1 ) {
	} else if ( var->type == 2 ) {
	} else if ( var->type == 3 ) {
	} else if ( var->type == 4 ) {
	}
	free ( var );

}
int cursor_union_attrib_arr[] = {
	0,
};
void cursor_unionBodyToVal ( void *varPass, int nameI, char *body ) {

	struct cursor_union *var = varPass;

	if ( nameI == 0 ) {
		if ( var->type == 0 ) {
			// wont get called?
		} else if ( var->type == 1 ) {
			// wont get called?
		} else if ( var->type == 2 ) {
			// wont get called?
		} else if ( var->type == 3 ) {
			// wont get called?
		} else if ( var->type == 4 ) {
			// wont get called?
		}
	}
}

int cursor_unionNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

	struct cursor_union *var = data;
	if ( strcmp ( body, "path" ) == 0 ) {
		cursor_unionTypeChange0 ( var, 0 );
		*strPtr = "cursor_path";
		void **retPtr = ret;
		*retPtr = &var->path;
		return jxnPtr;
	} else if ( strcmp ( body, "group" ) == 0 ) {
		cursor_unionTypeChange0 ( var, 1 );
		*strPtr = "cursor_group";
		void **retPtr = ret;
		*retPtr = &var->group;
		return jxnPtr;
	} else if ( strcmp ( body, "circ" ) == 0 ) {
		cursor_unionTypeChange0 ( var, 2 );
		*strPtr = "cursor_circ";
		void **retPtr = ret;
		*retPtr = &var->circ;
		return jxnPtr;
	} else if ( strcmp ( body, "text" ) == 0 ) {
		cursor_unionTypeChange0 ( var, 3 );
		*strPtr = "cursor_text";
		void **retPtr = ret;
		*retPtr = &var->text;
		return jxnPtr;
	} else if ( strcmp ( body, "rect" ) == 0 ) {
		cursor_unionTypeChange0 ( var, 4 );
		*strPtr = "cursor_rect";
		void **retPtr = ret;
		*retPtr = &var->rect;
		return jxnPtr;
	}
	return -1;
}

struct xmlFuncts cursor_unionXml = {
	.typeName = "cursor_union",
	.init = cursor_unionInitMask,
	.nameToIndex = cursor_unionNameToIndex,
	.bodyToVal = cursor_unionBodyToVal,
	.typeChange = (void (*) (void*, int))cursor_unionTypeChange0,
};

void cursor_union_print ( struct cursor_union *stru ) {
	printf ( "cursor_union_print ( )\n" );
}
/** cursor_path */

struct cursor_path *cursor_pathInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "cursor_pathInit ( )\n" );
	}
	struct cursor_path *var = malloc ( sizeof ( struct cursor_path ) );
	cursor_pathFill ( var );
	return var;
}
void cursor_pathFill ( struct cursor_path *var ) {
	var->itself = 0;
	var->verts = initArrayList ( 10, sizeof ( int ), 10 );
}

void *cursor_pathInitMask ( ) {
	void *ret = cursor_pathInit ( );
	return ret;

}
void cursor_pathClose ( struct cursor_path *var ) {
	if ( var->verts ) {
		freeArrayList ( var->verts );
	}
	free ( var );

}
int cursor_path_attrib_arr[] = {
	0,
	0,
};
void cursor_pathBodyToVal ( void *varPass, int nameI, char *body ) {

	struct cursor_path *var = varPass;

	if ( nameI == 0 ) {
		var->itself = atoi ( body );
	} else if ( nameI == 1 ) {
		consumeStdAl ( body, 0, 1, var->verts );
	}
}

int cursor_pathNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

//	struct cursor_path *var = data;
	if ( strcmp ( body, "itself" ) == 0 ) {
		return 0;
	} else if ( strcmp ( body, "verts" ) == 0 ) {
		return 1;
	}
	return -1;
}

struct xmlFuncts cursor_pathXml = {
	.typeName = "cursor_path",
	.init = cursor_pathInitMask,
	.nameToIndex = cursor_pathNameToIndex,
	.bodyToVal = cursor_pathBodyToVal,
};

void cursor_path_print ( struct cursor_path *stru ) {
	printf ( "cursor_path_print ( )\n" );
}
/** cursor_group */

struct cursor_group *cursor_groupInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "cursor_groupInit ( )\n" );
	}
	struct cursor_group *var = malloc ( sizeof ( struct cursor_group ) );
	cursor_groupFill ( var );
	return var;
}
void cursor_groupFill ( struct cursor_group *var ) {
	var->this = 0;
	var->eles = initArrayList ( 10, sizeof ( struct cursor_ele* ), 10 );
}

void *cursor_groupInitMask ( ) {
	void *ret = cursor_groupInit ( );
	return ret;

}
void cursor_groupClose ( struct cursor_group *var ) {
	if ( var->eles ) {
		freeArrayListPointerFunction ( var->eles, (void (*)(void*))cursor_eleClose );
	}
	free ( var );

}
int cursor_group_attrib_arr[] = {
	0,
	0,
};
void cursor_groupBodyToVal ( void *varPass, int nameI, char *body ) {

	struct cursor_group *var = varPass;

	if ( nameI == 0 ) {
		var->this = atoi ( body );
	} else if ( nameI == 1 ) {
	}
}

int cursor_groupNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

	struct cursor_group *var = data;
	if ( strcmp ( body, "this" ) == 0 ) {
		return 0;
	} else if ( strcmp ( body, "eles" ) == 0 ) {
		void **ptrPtr = (void**)ret;
		*ptrPtr = var->eles;
		return jxnAlPtr;
	}
	return -1;
}

struct xmlFuncts cursor_groupXml = {
	.typeName = "cursor_group",
	.init = cursor_groupInitMask,
	.nameToIndex = cursor_groupNameToIndex,
	.bodyToVal = cursor_groupBodyToVal,
};

void cursor_group_print ( struct cursor_group *stru ) {
	printf ( "cursor_group_print ( )\n" );
}
/** cursor_circ */

struct cursor_circ *cursor_circInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "cursor_circInit ( )\n" );
	}
	struct cursor_circ *var = malloc ( sizeof ( struct cursor_circ ) );
	cursor_circFill ( var );
	return var;
}
void cursor_circFill ( struct cursor_circ *var ) {
	var->type = 0;
}

void *cursor_circInitMask ( ) {
	void *ret = cursor_circInit ( );
	return ret;

}
void cursor_circClose ( struct cursor_circ *var ) {
	free ( var );

}
int cursor_circ_attrib_arr[] = {
	0,
};
void cursor_circBodyToVal ( void *varPass, int nameI, char *body ) {

	struct cursor_circ *var = varPass;

	if ( nameI == 0 ) {
		var->type = atoi ( body );
	}
}

int cursor_circNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

	if ( strcmp ( body, "type" ) == 0 ) {
		return 0;
	}
	return -1;
}

struct xmlFuncts cursor_circXml = {
	.typeName = "cursor_circ",
	.init = cursor_circInitMask,
	.nameToIndex = cursor_circNameToIndex,
	.bodyToVal = cursor_circBodyToVal,
};

void cursor_circ_print ( struct cursor_circ *stru ) {
	printf ( "cursor_circ_print ( )\n" );
}
/** cursor_text */

struct cursor_text *cursor_textInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "cursor_textInit ( )\n" );
	}
	struct cursor_text *var = malloc ( sizeof ( struct cursor_text ) );
	cursor_textFill ( var );
	return var;
}
void cursor_textFill ( struct cursor_text *var ) {
}

void *cursor_textInitMask ( ) {
	void *ret = cursor_textInit ( );
	return ret;

}
void cursor_textClose ( struct cursor_text *var ) {
	free ( var );

}
int cursor_text_attrib_arr[] = {
};
void cursor_textBodyToVal ( void *varPass, int nameI, char *body ) {


}

int cursor_textNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

	return -1;
}

struct xmlFuncts cursor_textXml = {
	.typeName = "cursor_text",
	.init = cursor_textInitMask,
	.nameToIndex = cursor_textNameToIndex,
	.bodyToVal = cursor_textBodyToVal,
};

void cursor_text_print ( struct cursor_text *stru ) {
	printf ( "cursor_text_print ( )\n" );
}
/** cursor_rect */

struct cursor_rect *cursor_rectInit ( ) {
	if ( debugPrint_projectName_init ) {
		printf ( "cursor_rectInit ( )\n" );
	}
	struct cursor_rect *var = malloc ( sizeof ( struct cursor_rect ) );
	cursor_rectFill ( var );
	return var;
}
void cursor_rectFill ( struct cursor_rect *var ) {
	var->type = 0;
}

void *cursor_rectInitMask ( ) {
	void *ret = cursor_rectInit ( );
	return ret;

}
void cursor_rectClose ( struct cursor_rect *var ) {
	free ( var );

}
int cursor_rect_attrib_arr[] = {
	0,
};
void cursor_rectBodyToVal ( void *varPass, int nameI, char *body ) {

	struct cursor_rect *var = varPass;

	if ( nameI == 0 ) {
		var->type = atoi ( body );
	}
}

int cursor_rectNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

	if ( strcmp ( body, "type" ) == 0 ) {
		return 0;
	}
	return -1;
}

struct xmlFuncts cursor_rectXml = {
	.typeName = "cursor_rect",
	.init = cursor_rectInitMask,
	.nameToIndex = cursor_rectNameToIndex,
	.bodyToVal = cursor_rectBodyToVal,
};

void cursor_rect_print ( struct cursor_rect *stru ) {
	printf ( "cursor_rect_print ( )\n" );
}
/** Other Functs */
