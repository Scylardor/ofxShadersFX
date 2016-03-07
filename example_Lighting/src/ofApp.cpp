#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    //disable vertical Sync is too bad with light sometimes
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofBackground(10, 10, 10);
    ofEnableAntiAliasing();
    ofEnableDepthTest();

    // Point light = emit light in all directions
    pointLight.setDiffuseColor( ofColor::red);
    // specular color = the highlight/shininess color
    pointLight.setSpecularColor(ofColor::white);
    pointLight.setPointLight();
    pointLight.setPosition(100, 0, -150);
    pointLight.setAttenuation(0.0, 0.005);

    // spotLight = emit a cone of light
    spotLight.setSpotlight();
    spotLight.setDiffuseColor( ofColor::green);
    spotLight.setSpecularColor( ofColor::white);
    // size of the cone of emitted light, angle between light axis and side of cone
    // angle range between 0 - 90 in degrees
    spotLight.setSpotlightCutOff(50);
    // rate of falloff, illumitation decreases as the angle from the cone axis increases
    // range 0 - 128, zero is even illumination, 128 is max falloff
    spotLight.setSpotConcentration(45);
    spotLight.setAttenuation(0.0, 0.005);
    spotLight.setPosition(0, 100, -100);
    spotLight.setOrientation( ofVec3f(-90, 0, 0) );

    // Directional Lights = emit light based on their orientation, regardless of their position
    directionalLight.setDiffuseColor(ofColor::blue);
    directionalLight.setSpecularColor(ofColor::white);
    directionalLight.setDirectional();
    directionalLight.setPosition(-100, 0, -140);
    // set the direction of the light
    directionalLight.setOrientation( ofVec3f(0, 90, 0) );

    // Activate all lights
    bPointLight = bSpotLight = bDirLight = true;
    bShowHelp = true;

    // High resolution sphere
    ofSetSphereResolution(128);
    sphere.setPosition(0, 0, -100);
    test.setPosition(0, 0, -100);

    // Shiny material
    mat.setSpecularColor(ofColor::white);
    mat.setShininess(120);
    ofSetGlobalAmbientColor(ofColor::black);

    tex.load("earth.jpg");

    phong.useLight(&spotLight);
    phong.useLight(&directionalLight);
    phong.useLight(&pointLight);
    phong.useMaterial(&mat);
    phong.useCamera(&cam);
    sphere.mapTexCoordsFromTexture(tex.getTexture());
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

    cam.begin();

    phong.begin();
    sphere.draw();
    phong.end();
    ofSetColor(ofColor::black);
    if (bDirLight) {
        ofSetColor(directionalLight.getDiffuseColor());
    }
    directionalLight.draw();
    ofSetColor(ofColor::black);
    if (bPointLight) {
        ofSetColor(pointLight.getDiffuseColor());
    }
    pointLight.draw();
    ofSetColor(ofColor::black);
    if(bSpotLight) {
        ofSetColor(spotLight.getDiffuseColor() );
    }
    spotLight.draw();

    cam.end();
    ofSetColor(255, 255, 255);
    if (bShowHelp) {
        ofDrawBitmapString(string("Shiny (H) : ") + (mat.getSpecularColor() == ofFloatColor(1., 1.,1.) ? "yes" : "no") + "\n" +
                       "Point Light (1) : " + (bPointLight ? "on" : "off") + "\n" +
                       "Spot Light On (2) : "+ (bSpotLight ? "on" : "off") + "\n" +
                       "Directional Light On (3) : "+ (bDirLight ? "on" : "off") + "\n" +
                       "Spot Light Cutoff (up/down) : "+ofToString(spotLight.getSpotlightCutOff(),0) + "\n" +
                       "Spot Light Concentration (right/left) : " + ofToString(spotLight.getSpotConcentration(),0) + "\n" +
                       "Shader (S) : " + (phong.lightingMethod() == ofxShadersFX::Lighting::PHONG_LIGHTING ? "Phong" : "Blinn-Phong") + "\n" +
                       "Shader type (Y) : " + (phong.shadingMethod() == ofxShadersFX::Lighting::VERTEX_SHADING ? "Vertex " : "Pixel ") + "shader\n" +
                       "Texture (T) : " + (phong.texture() != NULL ? "on" : "off") + "\n" +
                       "Sphere Position (Z: z/c) : " + ofToString(sphere.getPosition()) + "\n" +
                       "Show/Hide help (E)"
                        ,20, 20);
    }

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    ofVec3f pos;

    switch (key) {
    case OF_KEY_UP:
        spotLight.setSpotlightCutOff(spotLight.getSpotlightCutOff()+1);
        break;
    case OF_KEY_DOWN:
        spotLight.setSpotlightCutOff(spotLight.getSpotlightCutOff()-1);
        break;
    case OF_KEY_RIGHT:
        spotLight.setSpotConcentration(spotLight.getSpotConcentration()+1);
        break;
    case OF_KEY_LEFT:
        spotLight.setSpotConcentration(spotLight.getSpotConcentration()-1);
        break;
    case '1':
        bPointLight = !bPointLight;
        if (bPointLight) {
            phong.useLight(&pointLight);
        }
        else {
            phong.removeLight(&pointLight);
        }
        break;
    case '2':
         bSpotLight = !bSpotLight;
        if (bSpotLight) {
            phong.useLight(&spotLight);
        }
        else {
            phong.removeLight(&spotLight);
        }
        break;
    case '3':
        bDirLight = !bDirLight;
        if (bDirLight) {
            phong.useLight(&directionalLight);
        }
        else {
            phong.removeLight(&directionalLight);
        }
        break;
    case 'e':
        bShowHelp = !bShowHelp;
        break;
    case 'h':
        if (mat.getSpecularColor() == ofFloatColor(1., 1., 1.)) {
            mat.setSpecularColor(ofFloatColor(0., 0., 0.));
        }
        else {
            mat.setSpecularColor(ofFloatColor(1., 1., 1.));
        }
        break;
    case 's':
        if (phong.lightingMethod() == ofxShadersFX::Lighting::PHONG_LIGHTING) {
            phong.setLightingMethod(ofxShadersFX::Lighting::BLINN_PHONG_LIGHTING);
        }
        else {
            phong.setLightingMethod(ofxShadersFX::Lighting::PHONG_LIGHTING);
        }
        break;
    case 'y':
        if (phong.shadingMethod() == ofxShadersFX::Lighting::VERTEX_SHADING) {
            phong.setShadingMethod(ofxShadersFX::Lighting::PIXEL_SHADING);
        }
        else {
            phong.setShadingMethod(ofxShadersFX::Lighting::VERTEX_SHADING);
        }
        break;
    case 't':
        if (phong.texture() == NULL) {
            phong.useTexture(&tex);
        }
        else {
            phong.removeTexture();
        }
        break;
    case 'c':
        pos = sphere.getPosition();
        pos[2] += 5;
        sphere.setPosition(pos);
        break;
    case 'z':
        pos = sphere.getPosition();
        pos[2] -= 5;
        sphere.setPosition(pos);
        break;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
