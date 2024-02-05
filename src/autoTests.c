#include "autoTests.h"


/** Largely coppied from uiGen_unitTests autoTest.c */


/** Variables */

extern float *viewLoc_ptr;
extern void (*setViewScale) (float s);


int doingTests = 0;
//int testStage = 0;
extern int testStage;


char *outputDir = "/home/jadoo/workspace/jHigh/jalbSvg/res/proofs/autoTest_log.txt";
char *xmlDir = "/home/jadoo/workspace/jHigh/jalbSvg/res/proofs/svg/";
char *imgDir = "/home/jadoo/workspace/jHigh/jalbSvg/res/proofs/img/";


#define NUM_TESTS 4
int numTests = NUM_TESTS;
struct autoTest render_tests[NUM_TESTS] = {
	{
		.testName = "test_00",
		.xmlDir = "test_00.svg",
		.imgDir = "test_00.ppm",

		.XYWH = { 0, 0, 100, 100 },

		.viewLoc = { 0, 0 },
		.viewScale = 1.0,

//		.data = NULL,
//		.dataInitFunct = (void *(*)())test_00Init,
//		.dataSetFunct = (void (*)(void*,void*))run_event_00,
	},
	{
		.testName = "text_test_01",
		.xmlDir = "test_text_01.svg",
		.imgDir = "text_test_01.ppm",

		.XYWH = { 0, 100, 600, 200 },

		.viewLoc = { 0, 0 },
		.viewScale = 1.0 / 10.0,
	},
	{
		.testName = "shapes_02",
		.xmlDir = "shapes_02_trimer.svg",
		.imgDir = "shapes_02.ppm",

		.XYWH = { 0, 0, 600, 600 },

		.viewLoc = { 40, 80 },
		.viewScale = 1.0 / 10.0,
	},
	{
		.testName = "shapes_01",
		.xmlDir = "shapes_01_trim.svg",
		.imgDir = "shapes_02.ppm",

		.XYWH = { 0, 0, 600, 600 },

		.viewLoc = { 0, 0 },
		.viewScale = 1.0,
	},
};


/** Functions */

void start_allTests ( ) {
	printf ( "start_allTests ( )\n" );

	doingTests = 1;
	testStage = 0;

	set_renderMode ( 0 );

	FILE *outputFile = jfopenAT ( outputDir );

	fwrite ( "\n", sizeof ( char ), 1, outputFile );

	char buffer[2056];
	timeToString ( buffer );

	fwrite ( buffer, sizeof ( char ), strlen ( buffer ), outputFile );
	fwrite ( "\n", sizeof ( char ), 1, outputFile );

	fclose ( outputFile );
}

void run_allTests ( ) {
	printf ( "run_allTests ( )\n" );

	// this should use a file? append a known file, and add a time.

	FILE *outputFile = jfopenAT ( outputDir );

/*
	fwrite ( "\n", sizeof ( char ), 1, outputFile );

	char buffer[2056];
	timeToString ( buffer );

	fwrite ( buffer, sizeof ( char ), strlen ( buffer ), outputFile );
	fwrite ( "\n", sizeof ( char ), 1, outputFile );
*/

//	render_tests[0].data = test_00Init ( );

	int i;
	int len;
	i = testStage;
	len = numTests;
//	while ( i < len ) {
	if ( i / 2  < len ) {
		struct autoTest *autos = &render_tests[i / 2];

		char *testName = autos->testName;

		if ( i % 2 == 0 ) {
			fwrite ( testName, sizeof ( char ), strlen ( testName ), outputFile );
			fwrite ( ":", sizeof ( char ), 1, outputFile );
			fwrite ( "\t", sizeof ( char ), 1, outputFile );
//			fwrite ( "\n", sizeof ( char ), 1, outputFile );

//			int success = render_autoTest ( autos );
			render_autoTest ( autos );
		} else {
			int success = render_autoTest_end ( autos );
			char responce[256];
			if ( !success ) {
				sprintf ( responce, "ERROR !success\n" );
				fwrite ( responce, sizeof ( char ), strlen ( responce ), outputFile );
			} else {
				sprintf ( responce, "success\n" );
				fwrite ( responce, sizeof ( char ), strlen ( responce ), outputFile );
			}
		}

		i += 1;
	} else {
		doingTests = 0;
		testStage = 0;
	}

	fclose ( outputFile );

	printf ( "run_allTests ( ) OVER\n" );
}

int render_autoTest ( struct autoTest *render_auto ) {
	printf ( "render_autoTest ( )\n" );

	char *testName = render_auto->testName;

	printf ( "testName: %s\n", testName );

//	char *xmlDir = render_auto->xmlDir;
	char fullXmlDir[1024];
	sprintf ( fullXmlDir, "%s%s", xmlDir, render_auto->xmlDir );

	load_global_svg ( fullXmlDir );

	viewLoc_ptr[0] = render_auto->viewLoc[0];
	viewLoc_ptr[1] = render_auto->viewLoc[1];
	setViewScale ( render_auto->viewScale );
/*
	// load the correct struct.
	if ( render_auto->dataInitFunct ) {
		render_auto->data = render_auto->dataInitFunct ( );
	} else {
		render_auto->data = NULL;
	}
	void *data = render_auto->data;

	// load the uiGen.
	void *ret = uiGen_api->load_and_set_norm ( fullXmlDir, data );

	// set the data.
	if ( render_auto->dataSetFunct ) {
//		run_event_00 ( ret, data );
		render_auto->dataSetFunct ( ret, data );
	}

	if ( !ret ) {
		printf ( "!ret\n" );
		return 0;
	}
*/

	return 1;
}

int render_autoTest_end ( struct autoTest *render_auto ) {
	printf ( "render_autoTest_end ( )\n" );

	char *testName = render_auto->testName;
//	char *imgDir = render_auto->imgDir;
	char fullImgDir[1024];
	sprintf ( fullImgDir, "%s%s", imgDir, render_auto->imgDir );

	printf ( "testName: %s\n", testName );

//	SDL_GL_SwapWindow ( used_window );
//	screenshot_02 ( );

	int success = compare_ppm ( fullImgDir, render_auto->XYWH );

	// do the comparison by feeding it the imgDir, and grabbing the pixels from the correct part of the screen.

	// check the output some how.

	if ( !success ) {
		// maybe print info about which pixel failed?
		printf ( "%s failure\n", testName );

		// write this to a file, along with the time?

		char buffer[512];
		char *failDir = "/home/jadoo/workspace/jHigh/jalbSvg/res/proofs/fail";
		sprintf ( buffer, "%s/%s.ppm", failDir, testName );

		jalbScreenshot_ppm_xywh ( buffer, render_auto->XYWH );
//		pixels_to_ppm ( char *dir, int w, int h, int format, int format_nbytes, unsigned char *pixels );

		return 0;
	}
	return 1;
}

/*
// takes the pixels from window according to part_XYWH, the compares them to the ppm from ppmName
// return 1 if they are the same, 0 otherwise.
int compare_ppm ( char *ppmName, int part_XYWH[4] ) {
	printf ( "compare_ppm ( )\n" );

	char time[256];
	timeToString ( time );
	printf ( "time: %s\n", time );

	char *fileName = ppmName;

	printf ( "fileName: %s\n", fileName );
	FILE *f = fopen ( fileName, "r" );
	printf ( "screen shot file: %p\n", f );
	if ( !f ) {
		printf ( "ERROR!, !screen shot file\n" );
		return 0;
	}

	/// grab the pixels from the gl render


//	int XYWH[4] = { 40, 20, 420, 660 };
//	int XYWH[4] = { 40, 260, 420, 660 };



	int XYWH[4] = {
		part_XYWH[0],
		part_XYWH[1],
		part_XYWH[2],
		part_XYWH[3]
	};



	int width;
	int height;
	width = XYWH[2];
	height = XYWH[3];

        int screenStats[4];
        // get the width/height of the window
        glGetIntegerv(GL_VIEWPORT, screenStats);
//	int window_width = screenStats[2];
	int window_height = screenStats[3];

	GLenum FORMAT = GL_RGBA;
	GLuint FORMAT_NBYTES = 4;

	unsigned int pixel_nbytes = FORMAT_NBYTES;

	GLubyte *pixels = malloc(FORMAT_NBYTES * width * height);

	pixels[0] = 10;

	glReadPixels ( XYWH[0], window_height - (XYWH[1]+height), width, height, FORMAT, GL_UNSIGNED_BYTE, pixels );
	GLenum glError = glGetError ( );
	if ( glError ) {
//		printf ( "gluErrorString: %s\n", gluErrorString ( glError ) );
		printf ( "glError: %d\n", glError );
	}


	// load the proof image, and compare it.
	char type[10];

	int i = 0;

	char c;
	while ( ( c = getc ( f ) ) != '\n' && c != EOF ) {
		type[i] = c;
		if ( i == 10-1 ) {
			break;
		}
		i += 1;
	}
	type[i] = '\0';

	printf ( "type: %s\n", type );

	if ( strcmp ( type, "P3" ) == 0 ||
	     strcmp ( type, "p3" ) == 0 ) {
		
	} else {
//		printf ( "unknown file type (%s), quit\n", type );
		printf ( "unknown file type (%s), return 0\n", type );
		return 0;
	}

	int read_width;
	int read_height;
	char line[256];
	fgets ( line, 256, f );
	printf ( "line: %s\n", line );
	sscanf ( line, "%d %d", &read_width, &read_height );

	printf ( "read_width: %d\n", read_width );
	printf ( "read_height: %d\n", read_height );

	int num_bits;
	fgets ( line, 256, f );
	printf ( "line: %s\n", line );
	sscanf ( line, "%d", &num_bits );

	// ok, so how many characters does this fit into?
	int numBytes = 1;
	while ( pow ( 8, numBytes ) < num_bits ) {
		numBytes += 1;
	}

	printf ( "numBytes: %d\n", numBytes );

	// compare the width and height.

	int error = 0;

	if ( read_width != width ) {
		printf ( "width error\n" );
		error = 1;
	}
	if ( read_height != height ) {
		printf ( "height error\n" );
		error = 1;
	}
	if ( error ) {
		printf ( "ERROR, return\n" );
		return 0;
	}

//	while ( fgets ( line, 256, f ) ) {
//	}

	// ok, rn i want to read 1 pixel at a time.

//	int i, j;
	int j, cur;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			cur = pixel_nbytes * ((height - i - 1) * width + j);
//			fprintf(f, "%3d %3d %3d ", pixels[cur], pixels[cur + 1], pixels[cur + 2]);
			int red = pixels[cur];
			int green = pixels[cur + 1];
			int blue = pixels[cur + 2];

//			printf ( "r, g, b: %d, %d, %d\n", red, green, blue );

			/// TODO, dont read 256, make sure its the right number.
			// im concerned about this, is there any promis that its always printed as "%3d".
			// if not, then i cant always increment in 3's, and i might need to append, like lets say its
			// "12 0 124" but it only reads from the line "12 0 12" i need to find the 4 somehow.
			// ill handle that later.
//			fgets ( line, 256, f );
			// +1 for the space, and then another +1 for the end null ptr?
			do {
				fgets ( line, (numBytes+1)*3 + 1, f );
			} while ( line[0] == '\n' );

//			printf ( "line: (%s)\n", line );

			int read[3];
			sscanf ( line, "%d %d %d", &read[0], &read[1], &read[2] );

//			sayIntArray ( "read", read, 3 );

			if ( red != read[0] ||
			     green != read[1] ||
			     blue != read[2] ) {
				printf ( "error (y: %d) (x: %d)\n", i, j );

				printf ( "r, g, b: %d, %d, %d\n", red, green, blue );
				sayIntArray ( "read", read, 3 );

//				exit ( 12 );

				return 0;
			}
		}
		fprintf(f, "\n");
	}


	timeToString ( time );
	printf ( "time: %s\n", time );

//	printf ( "success, checked { %d, %d } pixels\n", width, height );
//	exit ( 12 );

	return 1;

	printf ( "compare_ppm ( ) OVER\n" );
}
*/


















