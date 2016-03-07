#pragma once

#include "ofMain.h"
#include "ofxShadersFX.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    ofSpherePrimitive sphere;
    ofSpherePrimitive test;
    ofLight pointLight;
    ofLight directionalLight;
    ofLight spotLight;
    ofEasyCam cam;
    ofxShadersFX::Lighting::LightingShader phong;
    ofMaterial mat;
    bool bPointLight;
    bool bSpotLight;
    bool bDirLight;
    bool bShowHelp;
    ofImage tex;
};
