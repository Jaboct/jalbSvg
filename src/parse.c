#include "parse.h"

/** Functions */




void pathUni_set_type ( struct pathUni *uni, int type ) {
	if ( type == path_moveTo_abs ) {
		pathUniTypeChange0 ( uni, path_MoveTo );
	} else if ( type == path_moveTo_rel ) {
		pathUniTypeChange0 ( uni, path_MoveTo );
		uni->lineTo->rel = 1;

	} else if ( type == path_lineTo_abs ) {
		pathUniTypeChange0 ( uni, path_LineTo );
	} else if ( type == path_lineTo_rel ) {
		pathUniTypeChange0 ( uni, path_LineTo );
		uni->lineTo->rel = 1;

	} else if ( type == path_lineTo_vert_abs ) {
		pathUniTypeChange0 ( uni, path_LineTo );
		uni->lineTo->type = lineTo_vert;
	} else if ( type == path_lineTo_vert_rel ) {
		pathUniTypeChange0 ( uni, path_LineTo );
		uni->lineTo->type = lineTo_vert;
		uni->lineTo->rel = 1;

	} else if ( type == path_lineTo_hor_abs ) {
		pathUniTypeChange0 ( uni, path_LineTo );
		uni->lineTo->type = lineTo_hor;
	} else if ( type == path_lineTo_hor_rel ) {
		pathUniTypeChange0 ( uni, path_LineTo );
		uni->lineTo->type = lineTo_hor;
		uni->lineTo->rel = 1;

	} else if ( type == path_cubicBez_abs ) {
		pathUniTypeChange0 ( uni, path_CubicBez );
	} else if ( type == path_cubicBez_rel ) {
		pathUniTypeChange0 ( uni, path_CubicBez );
		uni->cubicBez->rel = 1;

	} else if ( type == path_cubicBez_s_abs ) {
		pathUniTypeChange0 ( uni, path_CubicBez );
		uni->cubicBez->type = 1;
	} else if ( type == path_cubicBez_s_rel ) {
		pathUniTypeChange0 ( uni, path_CubicBez );
		uni->cubicBez->type = 1;
		uni->cubicBez->rel = 1;

	} else if ( type == path_quadBez_abs ) {
		pathUniTypeChange0 ( uni, path_QuadBez );
	} else if ( type == path_quadBez_rel ) {
		pathUniTypeChange0 ( uni, path_QuadBez );
		uni->quadBez->rel = 1;

	} else if ( type == path_quadBez_t_abs ) {
		pathUniTypeChange0 ( uni, path_QuadBez );
		uni->quadBez->type = 1;
	} else if ( type == path_quadBez_t_rel ) {
		pathUniTypeChange0 ( uni, path_QuadBez );
		uni->quadBez->type = 1;
		uni->quadBez->rel = 1;

	} else if ( type == path_ellipArc_abs ) {
		pathUniTypeChange0 ( uni, path_EllipArc );
	} else if ( type == path_ellipArc_rel ) {
		pathUniTypeChange0 ( uni, path_EllipArc );
		uni->ellipArc->rel = 1;

	} else if ( type == path_pathEnd_abs ) {
		pathUniTypeChange0 ( uni, path_PathEnd );
	} else if ( type == path_pathEnd_rel ) {
		pathUniTypeChange0 ( uni, path_PathEnd );

	}
}

void parseD ( char *d, ArrayList *eles ) {
	printf ( "parseD ( )\n" );
	printf ( "d: (%s)\n", d );

	char *str = d;

	// ok, my string parsing.

	// iterate through the spaces.
	int i;
	int len;

	i = 0;
	len = strlen ( d );

	int thisType = -1;
	int lastType = -1;
	int numI = 0;

	struct pathUni *uni = NULL;

	while ( i < len ) {
		// so 3 parts, parse a float, parse a letter, parse spaces.

		// parse through the spaces.
		if ( isBlankSpace ( str[i] ) ) {
		} else if ( str[i] == ',' ) {
		} else {
			// handle it.
			if ( thisType == -1 ) {
				thisType = charToPathUni2 ( str[i], &uni );
				printf ( "parsed thisType: %d\n", thisType );

				// Incase there is not a char preceding it.
				// assume its a de-facto 'l'.
				if ( thisType == -1 ) {
					uni = pathUniInit ( );

					printf ( "lastType: %d\n", lastType );

					if ( lastType == -1 ) {
						printf ( "ERROR, thisType -1, lastType -1\n" );
exit ( -12 );

					} else if ( lastType == path_moveTo_abs ) {
						pathUniTypeChange0 ( uni, path_LineTo );

						thisType = path_lineTo_abs;

					} else if ( lastType == path_moveTo_rel ) {
						pathUniTypeChange0 ( uni, path_LineTo );
						uni->lineTo->rel = 1;

						thisType = path_lineTo_rel;

					} else {
						thisType = lastType;
						pathUni_set_type ( uni, thisType );

					}

//					thisType = 2;
					i -= 1;
				}

/*
				if ( thisType == 18 ||
				     thisType == 19 ) {
					// got a 'Z' or 'z'.
					break;
				}
*/

				if ( thisType >= 0 ) {
					arrayListAddEndPointer ( eles, uni );
				}

/*
				// expect a char, followed by a space.
				thisType = charToPathUni ( str[i] );

				if ( thisType >= 0 ) {

					uni = pathUniInit ( );
					arrayListAddEndPointer ( eles, uni );
					if ( thisType < 1 * 2 ) {
						pathUniTypeChange0 ( uni, path_MoveTo );
						if ( i % 2 == 1 ) {
							uni->moveTo->rel = 1;
						}
					} else if ( thisType < 4 * 2 ) {
						pathUniTypeChange0 ( uni, path_LineTo );
						if ( i % 2 == 1 ) {
							uni->lineTo->rel = 1;
						}
					} else if ( thisType < 6 * 2 ) {
						pathUniTypeChange0 ( uni, path_CubicBez );
						if ( i % 2 == 1 ) {
							uni->cubicBez->rel = 1;
						}
					} else if ( thisType < 8 * 2 ) {
						pathUniTypeChange0 ( uni, path_QuadBez );
						if ( i % 2 == 1 ) {
							uni->quadBez->rel = 1;
						}
					} else if ( thisType < 9 * 2 ) {
						pathUniTypeChange0 ( uni, path_EllipArc );
						if ( i % 2 == 1 ) {
// TODO							uni->ellipArc->rel = 1;
						}
					} else if ( thisType < 10 * 2 ) {
						pathUniTypeChange0 ( uni, path_PathEnd );
					} else {
						printf ( "unhandled type\n" );
					}
				}
*/
			} else {
				lastType = thisType;
//				set_debugPrint_jalbStr ( 1 );
				// expect numbers and spaces.
				float f = strToFloatIndex ( str, &i );
printf ( "&str[i]: %s\n", &str[i] );
printf ( "f: %f\n", f );
printf ( "thisType: %d\n", thisType );
				int ret = 0;
				if ( thisType < 1 * 2 ) {
					ret = moveTo_dFill ( uni->moveTo, numI, f );
				} else if ( thisType < 4 * 2 ) {
					ret = lineTo_dFill ( uni->lineTo, numI, f );
				} else if ( thisType < 6 * 2 ) {
					ret = cubicBez_dFill ( uni->cubicBez, numI, f );
				} else if ( thisType < 8 * 2 ) {
					ret = quadBez_dFill ( uni->quadBez, numI, f );
				} else if ( thisType < 9 * 2 ) {
					ret = ellipArc_dFill ( uni->ellipArc, numI, f );
				} else if ( thisType < 10 * 2 ) {
//					ret = moveTo_dFill ( uni->moveTo, numI, f );
					ret = 1;
				} else {
					printf ( "unhandled type\n" );
				}
				if ( ret ) {
					uni = NULL;
					numI = 0;
					thisType = -1;
				} else {
					numI += 1;
				}
			}
		}

		i += 1;
	}

	printf ( "i: %d\n", i );
	printf ( "len: %d\n", len );

	printf ( "parseD ( ) OVER\n" );
}

char paths[] = {
	'M',	// move to (0)
	'L',	// line to (1)
	'H',
	'V',
	'C',	// cubic bez (4)
	'S',
	'Q',	// quad bez (6)
	'T',
	'A',	// ellip arc (8)
	'Z',	// pathEnd (9)
};

int charToPathUni ( char c ) {
	int i = 0;
	int len = 10;
	while ( i < len ) {
		if ( c == paths[i] ) {
			return i * 2 + 0;

		} else if ( c == paths[i] + 32 ) {
			return i * 2 + 1;

		}
		i += 1;
	}
	return -1;
}


int charToPathUni2 ( char c, struct pathUni **uniPass ) {
	printf ( "charToPathUni2 ( )\n" );
	printf ( "c: %c\n", c );

/*
	// put this before the alloc.
	switch ( c ) {
		case 'Z':
			return 18;
			break;
		case 'z':
			return 19;
			break;
	}
*/

//	struct pathUni *uni = pathUniInit ( );
	*uniPass = pathUniInit ( );
	struct pathUni *uni = *uniPass;
//	arrayListAddEndPointer ( eles, uni );

	switch ( c ) {
		case 'M':
			pathUniTypeChange0 ( uni, path_MoveTo );
			return 0;
			break;
		case 'm':
			pathUniTypeChange0 ( uni, path_MoveTo );
			uni->moveTo->rel = 1;
			return 1;
			break;
		case 'L':
			pathUniTypeChange0 ( uni, path_LineTo );
			return 2;
			break;
		case 'l':
			pathUniTypeChange0 ( uni, path_LineTo );
			uni->lineTo->rel = 1;
			return 3;
			break;
		case 'V':
			pathUniTypeChange0 ( uni, path_LineTo );
			uni->lineTo->type = lineTo_vert;
			return 4;
			break;
		case 'v':
			pathUniTypeChange0 ( uni, path_LineTo );
			uni->lineTo->rel = 1;
			uni->lineTo->type = lineTo_vert;
			return 5;
			break;
		case 'H':
			pathUniTypeChange0 ( uni, path_LineTo );
			uni->lineTo->type = lineTo_hor;
			return 6;
			break;
		case 'h':
			pathUniTypeChange0 ( uni, path_LineTo );
			uni->lineTo->rel = 1;
			uni->lineTo->type = lineTo_hor;
			return 7;
			break;
		case 'C':
			pathUniTypeChange0 ( uni, path_CubicBez );
			return 8;
			break;
		case 'c':
			pathUniTypeChange0 ( uni, path_CubicBez );
			uni->cubicBez->rel = 1;
			return 9;
			break;
		case 'S':
			pathUniTypeChange0 ( uni, path_CubicBez );
			uni->cubicBez->type = 1;
			return 10;
			break;
		case 's':
			pathUniTypeChange0 ( uni, path_CubicBez );
			uni->cubicBez->rel = 1;
			uni->cubicBez->type = 1;
			return 11;
			break;
		case 'Q':
			pathUniTypeChange0 ( uni, path_QuadBez );
			return 12;
			break;
		case 'q':
			pathUniTypeChange0 ( uni, path_QuadBez );
			uni->quadBez->rel = 1;
			return 13;
			break;
		case 'T':
			pathUniTypeChange0 ( uni, path_QuadBez );
			uni->quadBez->type = 1;
			return 14;
			break;
		case 't':
			pathUniTypeChange0 ( uni, path_QuadBez );
			uni->quadBez->rel = 1;
			uni->quadBez->type = 1;
			return 15;
			break;
		case 'A':
			pathUniTypeChange0 ( uni, path_EllipArc );
			return 16;
			break;
		case 'a':
			pathUniTypeChange0 ( uni, path_EllipArc );
			uni->ellipArc->rel = 1;
			return 17;
			break;
		case 'Z':
			pathUniTypeChange0 ( uni, path_PathEnd );
			return 18;
			break;
		case 'z':
			pathUniTypeChange0 ( uni, path_PathEnd );
			return 19;
			break;
		default:
			break;
	}
	return -1;
}

int moveTo_dFill ( struct moveTo *moveTo, int i, float val ) {
	printf ( "moveTo_dFill ( )\n" );

	if ( i == 0 ) {
		moveTo->XY[0] = val;
	} else if ( i == 1 ) {
		moveTo->XY[1] = val;
		return 1;
	}

	printf ( "moveTo_dFill ( ) OVER\n" );
	return 0;
}

// return 1 if i need to reset the i.
// i shouldnt really need to do this, just determin when i get a char, then its time to reset.
int lineTo_dFill ( struct lineTo *lineTo, int i, float val ) {
	printf ( "lineTo_dFill ( )\n" );

	if ( lineTo->type == 0 ) {
		if ( i == 0 ) {
			lineTo->XY[0] = val;
		} else if ( i == 1 ) {
			lineTo->XY[1] = val;
			return 1;
		}
	} else if ( lineTo->type == lineTo_vert ) {	// path_lineToH - path_lineTo
		if ( i == 0 ) {
			lineTo->XY[0] = val;
			return 1;
		}
	} else if ( lineTo->type == lineTo_hor ) { 
		if ( i == 0 ) {
			lineTo->XY[1] = val;
			return 1;
		}
	}

	printf ( "lineTo_dFill ( ) OVER\n" );
	return 0;
}

int cubicBez_dFill ( struct cubicBez *cubicBez, int i, float val ) {
	printf ( "cubicBez_dFill ( )\n" );
	printf ( "i: %d\n", i );

	if ( cubicBez->type == 0 ) {
		if ( i == 0 ) {
			cubicBez->c0[0] = val;
		} else if ( i == 1 ) {
			cubicBez->c0[1] = val;

		} else if ( i == 2 ) {
			cubicBez->c1[0] = val;
		} else if ( i == 3 ) {
			cubicBez->c1[1] = val;

		} else if ( i == 4 ) {
			cubicBez->XY[0] = val;
		} else if ( i == 5 ) {
			cubicBez->XY[1] = val;
			return 1;
		}
	} else if ( cubicBez->type == 1 ) {	// smooth
		if ( i == 0 ) {
			cubicBez->c1[0] = val;
		} else if ( i == 1 ) {
			cubicBez->c1[1] = val;

		} else if ( i == 2 ) {
			cubicBez->XY[0] = val;
		} else if ( i == 3 ) {
			cubicBez->XY[1] = val;
			return 1;
		}
	}

	printf ( "cubicBez_dFill ( ) OVER\n" );
	return 0;
}

int quadBez_dFill ( struct quadBez *quadBez, int i, float val ) {
	printf ( "quadBez_dFill ( )\n" );

	if ( quadBez->type == 0 ) {
		if ( i == 0 ) {
			quadBez->control[0] = val;
		} else if ( i == 1 ) {
			quadBez->control[1] = val;
		} else if ( i == 2 ) {
			quadBez->XY[0] = val;
		} else if ( i == 3 ) {
			quadBez->XY[1] = val;
			return 1;
		}
	} else if ( quadBez->type == 1 ) {
		if ( i == 1 ) {
			quadBez->XY[0] = val;
		} else if ( i == 2 ) {
			quadBez->XY[1] = val;
			return 1;
		}
	}

	printf ( "quadBez_dFill ( ) OVER\n" );
	return 0;
}

int ellipArc_dFill ( struct ellipArc *ellipArc, int i, float val ) {
	printf ( "ellipArc_dFill ( )\n" );
	printf ( "i: %d\n", i );
	printf ( "val: %f\n", val );

	if ( i == 0 ) {
		ellipArc->rXY[0] = val;
	} else if ( i == 1 ) {
		ellipArc->rXY[1] = val;
	} else if ( i == 2 ) {
		ellipArc->angle = val;
	} else if ( i == 3 ) {
		if ( val > 0.5 ) {
			ellipArc->largeArcFlag = 1;
		} else {
			ellipArc->largeArcFlag = 0;
		}
	} else if ( i == 4 ) {
		if ( val > 0.5 ) {
			ellipArc->sweepFlag = 1;
		} else {
			ellipArc->sweepFlag = 0;
		}
	} else if ( i == 5 ) {
		ellipArc->XY[0] = val;
	} else if ( i == 6 ) {
		ellipArc->XY[1] = val;
		return 1;
	}

	printf ( "ellipArc_dFill ( ) OVER\n" );
	return 0;
}

// should this write to a file or a str.
// i should have an api to swap between them seamlessly.
void eleListToD ( ArrayList *eleList, char *d ) {
	printf ( "eleListToD ( )\n" );

	// shouldnt be necessary.
	d[0] = '\0';

	int i;
	int len;

	int si = 0;

	i = 0;
	len = arrayListGetLength ( eleList );
	while ( i < len ) {
		struct pathUni *uni = arrayListGetPointer ( eleList, i );

		if ( uni->type == path_MoveTo ) {
			struct moveTo *moveTo = uni->moveTo;
			char c;
			if ( moveTo->rel ) {
				c = 'm';
			} else {
				c = 'M';
			}
			si += sprintf ( &d[si], "%c %f,%f ", c,
				moveTo->XY[0], moveTo->XY[1] );
		} else if ( uni->type == path_LineTo ) {
			struct lineTo *lineTo = uni->lineTo;
			if ( lineTo->type == 0 ) {
				char c;
				if ( lineTo->rel ) {
					c = 'l';
				} else {
					c = 'L';
				}
				si += sprintf ( &d[si], "%c %f,%f ", c,
					lineTo->XY[0], lineTo->XY[1] );
			} else if ( lineTo->type == 1 ) {
				char c;
				if ( lineTo->rel ) {
					c = 'h';
				} else {
					c = 'H';
				}
				si += sprintf ( &d[si], "%c %f ", c, lineTo->XY[0] );
			} else if ( lineTo->type == 2 ) {
				char c;
				if ( lineTo->rel ) {
					c = 'v';
				} else {
					c = 'V';
				}
				si += sprintf ( &d[si], "%c %f ", c, lineTo->XY[1] );
			}
		} else if ( uni->type == path_CubicBez ) {
			struct cubicBez *cubicBez = uni->cubicBez;
			if ( cubicBez->type == 0 ) {
				char c;
				if ( cubicBez->rel ) {
					c = 'c';
				} else {
					c = 'C';
				}
				si += sprintf ( &d[si], "%c %f,%f %f,%f %f,%f ", c,
					cubicBez->c0[0], cubicBez->c0[1],
					cubicBez->c1[0], cubicBez->c1[1],
					cubicBez->XY[0], cubicBez->XY[1] );
			} else if ( cubicBez->type == 1 ) {
				char c;
				if ( cubicBez->rel ) {
					c = 's';
				} else {
					c = 'S';
				}
				si += sprintf ( &d[si], "%c %f,%f %f,%f ", c,
					cubicBez->c1[0], cubicBez->c1[1],
					cubicBez->XY[0], cubicBez->XY[1] );
			}
		} else if ( uni->type == path_QuadBez ) {
			struct quadBez *quadBez = uni->quadBez;
			if ( quadBez->type == 0 ) {
				char c;
				if ( quadBez->rel ) {
					c = 'q';
				} else {
					c = 'Q';
				}
				si += sprintf ( &d[si], "%c %f,%f %f,%f ", c,
					quadBez->control[0], quadBez->control[1],
					quadBez->XY[0], quadBez->XY[1] );
			} else if ( quadBez->type == 0 ) {
				char c;
				if ( quadBez->rel ) {
					c = 't';
				} else {
					c = 'T';
				}
				si += sprintf ( &d[si], "%c %f,%f ", c,
					quadBez->XY[0], quadBez->XY[1] );
			}
		} else if ( uni->type == path_EllipArc ) {
			struct ellipArc *ellipArc = uni->ellipArc;
			char c;
			if ( ellipArc->rel ) {
				c = 'a';
			} else {
				c = 'A';
			}
			si += sprintf ( &d[si], "%c %f,%f %f %d %d %f,%f ", c,
				ellipArc->rXY[0], ellipArc->rXY[1],
				ellipArc->angle,
				ellipArc->largeArcFlag, ellipArc->sweepFlag,
				ellipArc->XY[0], ellipArc->XY[1] );
		} else if ( uni->type == path_PathEnd ) {
//			struct ellipArc *ellipArc = uni->ellipArc;
			si += sprintf ( &d[si], "Z");
		}

		i += 1;
	}

	printf ( "eleListToD ( ) OVER\n" );
}


/** Style */

void generic_postInit ( void *var, char *str, void (*f)(void *var, char *name, char *value) ) {
	printf ( "text_postInit ( )\n" );
	printf ( "str: %s\n", str );
//	printf ( "text->style: %s\n", text->style );

	int i;
	int len;

//	char *style = text->style;
	char *style = str;

	int type = 0;
	int s = 0;
	char name[256];
	char value[256];

	i = 0;
	len = strlen ( style );
	while ( i < len ) {
		char c = style[i];

		if ( c == ':' ) {
			name[s] = '\0';
			type = 1;
			s = 0;
		} else if ( c == ';' ) {
			// handle.
			value[s] = '\0';
			type = 0;
			s = 0;

			f ( var, name, value );

		} else if ( type == 0 ) {
			name[s] = c;
			s += 1;
		} else if ( type == 1 ) {
			value[s] = c;
			s += 1;
		}

		i += 1;
	}

	if ( type == 1 &&
	     s != 0 ) {
		value[s] = '\0';
		f ( var, name, value );
	}
}











