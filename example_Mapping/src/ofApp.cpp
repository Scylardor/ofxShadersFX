#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    //disable vertical Sync is too bad with light sometimes
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofBackground(10, 10, 10);
    ofEnableAntiAliasing();
    ofEnableDepthTest();

    displaceSphere.setPosition(-550, 0, -500);
    displaceSphere.setRadius(150);
    displaceSphere.setResolution(50);

    alphaBlendSphere.setPosition(0, 0, -500);
    alphaBlendSphere.setRadius(150);
    alphaBlendSphere.setResolution(50);

    colorKeySphere.setPosition(550, 0, -500);
    colorKeySphere.setRadius(150);
    colorKeySphere.setResolution(50);
    colorKeySphere.rotate(90, 1.0f, 0.0f, 0.0f);

    directional.setDirectional();
    directional.setOrientation( ofVec3f(0, 230, 0) );

    colormap.load("earth.jpg");
    bumpmap.load("earth-bumps.jpg");
    blendMap.load("clouds.jpg");
    colorKeyMap.load("colorkey.gif");

    displaceSphere.mapTexCoordsFromTexture(colormap.getTexture());
    alphaBlendSphere.mapTexCoordsFromTexture(colormap.getTexture());
    colorKeySphere.mapTexCoordsFromTexture(colormap.getTexture());

    target = 0; // First target at the center sphere
    bShowHelp = true;
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(ofColor::lightBlue);
    cam.begin();

    // DISPLACE SHADER

    displaceShader.setColormap(&colormap);
    displaceShader.setDisplaceMap(&bumpmap);
    if (target == 2) {
        displaceShader.setMaximumHeight(mouseX);
    }
    // Actually mandatory only in OpenGL 3.3 - don't do it if ofIsGLProgrammableRenderer() == false
    if (!ofIsGLProgrammableRenderer()) {
        const ofMatrix4x4 normalMatrix = ofMatrix4x4::getTransposedOf(cam.getModelViewMatrix().getInverse());
        displaceShader.setNormalMatrix(normalMatrix);
    }
    displaceShader.begin();
    displaceSphere.draw();
    displaceShader.end();


    // ALPHA BLENDING SHADER

    alphaBlendShader.setColormap(&colormap);
    alphaBlendShader.setAlphaBlendMap(&blendMap);
    if (target == 0) {
        const float blendAlpha = ofMap(mouseX, 0.0f, ofGetWidth() - 1, 0.0f, 1.0f);
        alphaBlendShader.setBlendAlpha(blendAlpha);
    }
    alphaBlendShader.begin();
    alphaBlendSphere.draw();
    alphaBlendShader.end();


    // COLOR KEY SHADER

    colorKeyShader.setColormap(&colormap);
    colorKeyShader.setColorKeyMap(&colorKeyMap);
    colorKeyShader.setKeyColor(ofFloatColor(1.0f, 0.0f, 0.0f, 1.0f));
    colorKeyShader.begin();
    colorKeySphere.draw();
    colorKeyShader.end();

    cam.end();

    if (bShowHelp) {
        string shaderName;
        if (target == 0) {
            shaderName = "Alpha Blending Shader";
            cam.setTarget(alphaBlendSphere.getPosition());
        } else if (target == 1) {
            shaderName = "Color Key Shader";
            cam.setTarget(colorKeySphere.getPosition());
        } else if (target == 2) {
            shaderName = "Displacement Shader";
            cam.setTarget(displaceSphere.getPosition());
        }
        ofSetColor(ofColor::black);
        ofDrawBitmapString(string("Move your mouse to trigger changes on target (except color key)\nTarget (T): " + shaderName + "\n" +
                           "Show/Hide help (E)"),
                           20, 20);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'e':
            bShowHelp = !bShowHelp;
            break;
        case 't':
            target = (target + 1) % 3;
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
