#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"
#include "ofGLProgrammableRenderer.h"

//========================================================================
int main( ){
    ofAppGlutWindow window;

    // To fall back on the fixed pipeline renderer, comment the following line
    ofSetCurrentRenderer(ofGLProgrammableRenderer::TYPE);
	ofSetupOpenGL(&window, 1024,768, OF_WINDOW);			// <-------- setup the GL context
    window.setDoubleBuffering(true);
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new testApp());

}
