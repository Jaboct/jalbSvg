
# JalbSvg / jalbJvg

High performance vector editor focusing on taking notes and creating diagrams while doing work or studying.

This project is broken into two parts:
- **jalbSvg**, a true SVG editor: edit, load, and save .svg files.
- **jalbJvg**, extending the SVG core to add additional features, most notibly the "Complex Ele", which allows hooking into other .dll's or .so's to render their application inside jalbJvg, for example a LaTeX renderer.

![jalbJvg example_00](https://github.com/Jaboct/jalbSvg/releases/download/Resources/example_00.png)

![jalbJvg example zoomout](https://github.com/Jaboct/jalbSvg/releases/download/Resources/zoomout.png)

Video showing a few features:
- Loading from file
- Lagless zoomout
- Shape editing (bezier curve)
- Text editing
- Textbox resizing and text wrapping
- Shape drawing and editing
- Circle drawing

(downloads mp4)

![JalbJvg exmaple video](https://github.com/Jaboct/jalbSvg/releases/download/Resources/jalbJvg.mp4)

# Framework
This program is built upon a **framework** so there is no main function, instead these functions are called by the frameworks render and event loop.

 jalbSvg_renderDyn()

 jalbJvg_renderDyn()

are the main render functions, and 

 jalbSvg_mEvent()

 jalbJvg_mEvent()

are the main event functions.

# Libraries
**OpenGL** is the rendering framework called through an api
 struct draw2dStruct \*draw2dApi;

**SDL2** handles the windowing and event handling.


