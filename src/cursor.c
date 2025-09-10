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
	var->address = initArrayList ( 10, sizeof ( int ), 10 );
	var->payload = cursor_unionInit ( );
}

void *cursor_eleInitMask ( ) {
	void *ret = cursor_eleInit ( );
	return ret;

}
void cursor_eleClose ( struct cursor_ele *var ) {
	if ( var->address ) {
		freeArrayList ( var->address );
	}
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
		consumeStdAl ( body, 0, 1, var->address );
	} else if ( nameI == 1 ) {
		// wont get called?
	}
}

int cursor_eleNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

	struct cursor_ele *var = data;
	if ( strcmp ( body, "address" ) == 0 ) {
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
	}
	if ( type == 0 ) {
		var->path = cursor_pathInit ( );
	}
	var->type = type;
}


void *cursor_unionInitMask ( ) {
	void *ret = cursor_unionInit ( );
	return ret;

}
void cursor_unionClose ( struct cursor_union *var ) {
	if ( var->type == 0 ) {
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
	var->vertI = 0;
}

void *cursor_pathInitMask ( ) {
	void *ret = cursor_pathInit ( );
	return ret;

}
void cursor_pathClose ( struct cursor_path *var ) {
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
		var->vertI = atoi ( body );
	}
}

int cursor_pathNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

	if ( strcmp ( body, "itself" ) == 0 ) {
		return 0;
	} else if ( strcmp ( body, "vertI" ) == 0 ) {
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
}

void *cursor_groupInitMask ( ) {
	void *ret = cursor_groupInit ( );
	return ret;

}
void cursor_groupClose ( struct cursor_group *var ) {
	free ( var );

}
int cursor_group_attrib_arr[] = {
};
void cursor_groupBodyToVal ( void *varPass, int nameI, char *body ) {


}

int cursor_groupNameToIndex ( char *body, void *data, void *ret, char **strPtr, char **modName ) {

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
/** Other Functs */
