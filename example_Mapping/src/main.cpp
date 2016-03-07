#include "ofMain.h"
#include "ofApp.h"

//#define USE_PROGRAMMABLE_GL
#ifdef USE_PROGRAMMABLE_GL
    #include "ofGLProgrammableRenderer.h"
#endif

//========================================================================
int main( ){
    ofGLWindowSettings s;

#ifdef USE_PROGRAMMABLE_GL
    s.setGLVersion(3, 2);
#else
    s.setGLVersion(2, 1);
#endif
    ofCreateWindow(s);
    ofRunApp(new ofApp());

}
