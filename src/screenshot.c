#include "screenshot.h"

/** Functions */


/** Screenshot */

SDL_Window *used_window = NULL;

void set_window ( void *window ) {
	printf ( "set_window ( )\n" );
	printf ( "window: %p\n", window );

	used_window = window;

	printf ( "set_window ( ) OVER\n" );
}


void screenshot_02 ( char *dir ) {
	printf ( "screenshot_02 ( )\n" );


//	char time[256];
//	timeToString ( time );
//	printf ( "time: %s\n", time );

//	int XYWH[4] = { 40, 20, 420, 660 };
//	int XYWH[4] = { 40, 260, 420, 660 };
//	int XYWH[4] = { 0, 0, screenDims[0], screenDims[1] };

	int width;
	int height;
//	width = XYWH[2];
//	height = XYWH[3];

	if ( !used_window ) {
		printf ( "!used window\n" );
		return;
	}

	int window_width;
	int window_height;
	SDL_GetWindowSize ( used_window, &window_width, &window_height );

	printf ( "window_width: %d\n", window_width );
	printf ( "window_height: %d\n", window_height );

//	exit ( 12 );

	int XYWH[4] = { 0, 0, window_width, window_height };
	width = XYWH[2];
	height = XYWH[3];

//	width = window_width;
//	height = window_height;

	GLenum FORMAT = GL_RGBA;
	GLuint FORMAT_NBYTES = 4;

	unsigned int pixel_nbytes = FORMAT_NBYTES;

	GLubyte *pixels = malloc(FORMAT_NBYTES * width * height);

//	glReadPixels ( 0, 0, width, height, FORMAT, GL_UNSIGNED_BYTE, pixels );
	glReadPixels ( XYWH[0], window_height - (XYWH[1]+height), width, height, FORMAT, GL_UNSIGNED_BYTE, pixels );
//	glReadPixels ( XYWH[0], XYWH[1]+height, width, height, FORMAT, GL_UNSIGNED_BYTE, pixels );


//	size_t i, j, k, cur;
	size_t i, j, cur;

//	enum Constants { max_filename = 256 };
//	char filename[max_filename];

//	char *filename = "screenshot.ppm";

//	snprintf(filename, max_filename, "%s%d.ppm", prefix, frame_id);
//	FILE *f = fopen(filename, "w");
	FILE *f = fopen ( dir, "w" );


//	fprintf(f, "P3\n%d %d\n%d\n", width, height, 255);
	fprintf(f, "P7\n%d %d\n%d\n", width, height, 255);


	for (i = 0; i < height; i++) {
//		printf ( "height: %d\n", i );

		for (j = 0; j < width; j++) {
//			printf ( "width: %d\n", j );

			cur = pixel_nbytes * ((height - i - 1) * width + j);

/*
			int red = pixels[cur];
			int green = pixels[cur + 1];
			int blue = pixels[cur + 2];
			printf ( "red: %d\n", red );
			printf ( "green: %d\n", green );
			printf ( "blue: %d\n", blue );
			exit ( 12 );
*/

//			fprintf(f, "%3d %3d %3d ", pixels[cur], pixels[cur + 1], pixels[cur + 2]);
			fprintf(f, "%3d %3d %3d %3d", pixels[cur], pixels[cur + 1], pixels[cur + 2], pixels[cur + 3]);
		}
		fprintf(f, "\n");
	}
	fclose(f);


/*
	timeToString ( time );
	printf ( "time: %s\n", time );
//	exit ( 12 );
*/

	printf ( "screenshot_02 ( ) OVER\n" );
}

// a part of me wants to learn how to write a bmp by hand.
// tho i need to ignore that part...
/*
void saveBmp ( char *dir ) {
	printf ( "screenshot_02 ( )\n" );


//	char time[256];
//	timeToString ( time );
//	printf ( "time: %s\n", time );

//	int XYWH[4] = { 40, 20, 420, 660 };
//	int XYWH[4] = { 40, 260, 420, 660 };
//	int XYWH[4] = { 0, 0, screenDims[0], screenDims[1] };

	int width;
	int height;
//	width = XYWH[2];
//	height = XYWH[3];

	if ( !used_window ) {
		printf ( "!used window\n" );
		return;
	}

	int window_width;
	int window_height;
	SDL_GetWindowSize ( used_window, &window_width, &window_height );

	printf ( "window_width: %d\n", window_width );
	printf ( "window_height: %d\n", window_height );

//	exit ( 12 );

	int XYWH[4] = { 0, 0, window_width, window_height };
	width = XYWH[2];
	height = XYWH[3];

//	width = window_width;
//	height = window_height;

	GLenum FORMAT = GL_RGBA;
	GLuint FORMAT_NBYTES = 4;

	unsigned int pixel_nbytes = FORMAT_NBYTES;

	GLubyte *pixels = malloc(FORMAT_NBYTES * width * height);

//	glReadPixels ( 0, 0, width, height, FORMAT, GL_UNSIGNED_BYTE, pixels );
	glReadPixels ( XYWH[0], window_height - (XYWH[1]+height), width, height, FORMAT, GL_UNSIGNED_BYTE, pixels );
//	glReadPixels ( XYWH[0], XYWH[1]+height, width, height, FORMAT, GL_UNSIGNED_BYTE, pixels );


//	size_t i, j, k, cur;
	size_t i, j, cur;

//	enum Constants { max_filename = 256 };
//	char filename[max_filename];

//	char *filename = "screenshot.ppm";

//	snprintf(filename, max_filename, "%s%d.ppm", prefix, frame_id);
//	FILE *f = fopen(filename, "w");
	FILE *f = fopen ( dir, "w" );


//	fprintf(f, "P3\n%d %d\n%d\n", width, height, 255);
//	fprintf(f, "P7\n%d %d\n%d\n", width, height, 255);

	// Signature.
	fprintf(f, "BP" );

	// File Size (4 bytes large)
	fprintf(f, "%4X" );


	for (i = 0; i < height; i++) {
//		printf ( "height: %d\n", i );

		for (j = 0; j < width; j++) {
//			printf ( "width: %d\n", j );

			cur = pixel_nbytes * ((height - i - 1) * width + j);

//			fprintf(f, "%3d %3d %3d ", pixels[cur], pixels[cur + 1], pixels[cur + 2]);
			fprintf(f, "%3d %3d %3d %3d", pixels[cur], pixels[cur + 1], pixels[cur + 2], pixels[cur + 3]);
		}
		fprintf(f, "\n");
	}
	fclose(f);

	printf ( "screenshot_02 ( ) OVER\n" );
}
*/

void saveBmp ( char *dir, int XYWH[] ) {
	printf ( "saveBmp ( )\n" );
	printf ( "dir: %s\n", dir );


	FILE *f = fopen ( dir, "wb" );

	// Signature.
	fprintf(f, "BP" );

/* does this work?
	char sig[2] = "BP";
	fwrite (sig, sizeof(char), 2, f ) ;
*/

	// size.
	int size = 1;
//	fprintf(f, "%d", size );
	fwrite (&size, sizeof(int), 1, f ) ;

	// 2 reserved 1
	int zero;
	fwrite (&zero, sizeof(char), 2, f ) ;

	// 2 reserved 2
	fwrite (&zero, sizeof(char), 2, f ) ;

	// 4 File Offset to PixelArray
	fwrite (&zero, sizeof(char), 4, f ) ;

	/// DIB Header
	// DIB Header Size
//	int dibSize = ;
//	fwrite (&dibSize, sizeof(int), 1, f ) ;

	// width
	fwrite (&XYWH[2], sizeof(int), 1, f ) ;
	// height
	fwrite (&XYWH[3], sizeof(int), 1, f ) ;

	fclose(f);


	printf ( "saveBmp ( ) OVER\n" );
}



void window_screenshot_bmp ( char *dir ) {
	printf ( "window_screenshot ( )\n" );

	printf ( "used_window: %p\n", used_window );

/*
	fenetre = SDL_GetWindowFromId(touche.windowID); // "touche" is a   SDL_KeyboardEvent, "fenetre" is a SDL_window pointer

	r_copie=SDL_GetRenderer(fenetre);

	s_SnapSource=SDL_CreateRGBSurface(0,SCREEN_WIDTH,SCREEN_HEIGHT,32,
	rmask,
	gmask,
	bmask,
	amask); // s_SnapSource is a SDL_Surface pointer

	SDL_LockSurface(s_SnapSource);
	SDL_RenderReadPixels(r_copie,NULL,s_SnapSource->format->format,
	s_SnapSource->pixels,S_SnapSource->pitch);

	SDL_SaveBMP(s_SnapSource,NomFichier); // NomFichier is a char*
	SDL_UnlockSurface(s_SnapSource);
	SDL_FreeSurface(s_SnapSource);
*/

//	const Uint32 format = SDL_PIXELFORMAT_ARGB8888;
	const Uint32 format = SDL_PIXELFORMAT_RGB888;
//	const int width = SDL_GetWindowWidth ( global_window->window );
//	const int height = 400;
	int width;
	int height;
	SDL_GetWindowSize ( used_window, &width, &height );
//	auto renderer = sdl2Core->GetRenderer();
	struct SDL_Renderer *renderer = SDL_GetRenderer ( used_window );

	SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, format);
	printf ( "surface: %p\n", surface );
	int ret = SDL_RenderReadPixels(renderer, NULL, format, surface->pixels, surface->pitch);
	printf ( "ret: %d\n", ret );

	if ( ret != 0 ) {
		printf ( "SDL_GetError: %s\n", SDL_GetError ( ) );
		goto endFunct;
	}

//	SDL_SaveBMP ( surface, "screenshot.bmp" );
	ret = SDL_SaveBMP ( surface, dir );

	printf ( "ret: %d\n", ret );
	if ( ret != 0 ) {
		printf ( "SDL_GetError: %s\n", SDL_GetError ( ) );
	}

	endFunct:;

	SDL_FreeSurface ( surface );

	printf ( "window_screenshot ( ) OVER\n" );
}




    //////////////////////////////////////////////////
    // Grab the OpenGL screen and save it as a .tga //
    // Copyright (C) Marius Andra 2001              //
    // http://cone3d.gz.ee  EMAIL: cone3d@hot.ee    //
    //////////////////////////////////////////////////
    // (modified by me a little)
int screenShot ( char *dir ) {
	printf ( "screenShot ( )\n" );

        typedef unsigned char uchar;
        // we will store the image data here
//        uchar *pixels;

        // the thingy we use to write files
        FILE * shot;
        // we get the width/height of the screen into this array
        int screenStats[4];

        // get the width/height of the window
        glGetIntegerv(GL_VIEWPORT, screenStats);

	sayIntArray ( "screenStats", screenStats, 4 );

        // generate an array large enough to hold the pixel data 
        // (width*height*bytesPerPixel)
//        pixels = new unsigned char[screenStats[2]*screenStats[3]*3];
        // read in the pixel data, TGA's pixels are BGR aligned
//        glReadPixels(0, 0, screenStats[2], screenStats[3], 0x80E0, GL_UNSIGNED_BYTE, pixels);

	int window_width;
	int window_height;
	SDL_GetWindowSize ( used_window, &window_width, &window_height );
/*
	int XYWH[4];
	XYWH[0] = 0;
	XYWH[1] = 0;
	XYWH[2] = window_width;
	XYWH[3] = window_height;
*/

	int XYWH[4] = { screenStats[0], screenStats[1], screenStats[2], screenStats[3] };

	GLenum FORMAT = GL_RGBA;
	GLuint FORMAT_NBYTES = 4;

glEnable( GL_BLEND );
//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);
glClearColor( 0.0f, 1.0f, 0.0f, 0.0f );

	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	GLubyte *pixels = malloc ( FORMAT_NBYTES * XYWH[2] * XYWH[3] );
	glReadPixels ( XYWH[0], window_height - (XYWH[1]+XYWH[3]), XYWH[2], XYWH[3], FORMAT, GL_UNSIGNED_BYTE, pixels );

        // open the file for writing. If unsucessful, return 1
//        std::string filename = kScreenShotFileNamePrefix + Function::Num2Str(num) + ".tga";

//        shot=fopen(filename.c_str(), "wb");
        shot=fopen ( dir, "wb" );

        if (shot == NULL)
            return 1;

        // this is the tga header it must be in the beginning of 
        // every (uncompressed) .tga
//        uchar TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};
        uchar TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};

        // the header that is used to get the dimensions of the .tga
        // header[1]*256+header[0] - width
        // header[3]*256+header[2] - height
        // header[4] - bits per pixel
        // header[5] - ?

        uchar header[6]={((int)(screenStats[2]%256)),
        ((int)(screenStats[2]/256)),
        ((int)(screenStats[3]%256)),
//        ((int)(screenStats[3]/256)),24,0};
        ((int)(screenStats[3]/256)),32,0};


//	sayCharArray_hex ( "pixels", pixels, 4 );
//	exit ( 12 );

        // write out the TGA header
        fwrite(TGAheader, sizeof(uchar), 12, shot);
        // write out the header
        fwrite(header, sizeof(uchar), 6, shot);
        // write the pixels
        fwrite(pixels, sizeof(uchar), 
//        screenStats[2]*screenStats[3]*3, shot);
        screenStats[2]*screenStats[3]*4, shot);

        // close the file
        fclose(shot);
        // free the memory
//        delete [] pixels;

	printf ( "screenShot ( ) OVER\n" );

        // return success
        return 0;
}















