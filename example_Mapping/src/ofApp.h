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

		ofEasyCam cam;
		ofLight directional;
		ofImage colormap;

		ofSpherePrimitive displaceSphere;
		ofSpherePrimitive alphaBlendSphere;
		ofSpherePrimitive colorKeySphere;

		ofxShadersFX::Mapping::DisplaceMapShader displaceShader;
		ofImage bumpmap;

		ofxShadersFX::Mapping::AlphaBlendingShader alphaBlendShader;
		ofImage blendMap;

		ofxShadersFX::Mapping::ColorKeyShader colorKeyShader;
		ofImage colorKeyMap;

		int target;
		bool bShowHelp;
};
