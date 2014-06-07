#pragma once

#include "ofMain.h"

class testApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    void lights_Shader();
    vector<string> make_attributes_names();
    void set_light_position(size_t lightIndex, vector<float> & buffer, const GLint * offsets);
    void set_light_colors(size_t lightIndex, vector<float> & buffer, const GLint * offsets);
    void set_light_attenuation(size_t lightIndex, vector<float> & buffer, const GLint * offsets);
    void set_light_spot_properties(size_t lightIndex, vector<float> & buffer, const GLint * offsets);

    ofLight pointLight;
	ofLight spotLight;
	ofLight directionalLight;

	ofMaterial material;

    ofShader shader;

	float radius;
	ofVec3f center;
	bool bShiny;
    bool bSmoothLighting;
	bool bPointLight, bSpotLight, bDirLight;
    bool bUseTexture;

    ofEasyCam cam;
    ofSpherePrimitive sphere;
    ofSpherePrimitive test;
    ofMaterial mat;
    vector<ofLight *> m_lights;
};