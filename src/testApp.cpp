#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    ofSetLogLevel(OF_LOG_VERBOSE);

    //disable vertical Sync tooo bad with light sometimes!!!!
    ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofBackground(10, 10, 10);
	ofEnableDepthTest();


    // lets make a high-res sphere //
    // default is 20 //
    ofSetSphereResolution(128);

    // radius of the sphere //
	radius		= 180.f;
	center.set(ofGetWidth()*.5, ofGetHeight()*.5, 0);

    // Point lights emit light in all directions //
    // set the diffuse color, color reflected from the light source //
    pointLight.setDiffuseColor( ofColor(255.f, 0.f, 0.f));

    // specular color, the highlight/shininess color //
	pointLight.setSpecularColor( ofColor(255.f, 255.f, 255.f));
	pointLight.setPointLight();
//
//	 spotLight.setDiffuseColor( ofColor(255.f, 0.f, 0.f));
//	spotLight.setSpecularColor( ofColor(255.f, 255.f, 255.f));

///spotlight doesn't works yet with my shader!!

    // turn the light into spotLight, emit a cone of light //
    spotLight.setSpotlight();

    spotLight.setDiffuseColor( ofColor(0.f, 255.f, 0.f));

    // specular color, the highlight/shininess color //
	spotLight.setSpecularColor( ofColor(255.f, 255.f, 255.f));
    // size of the cone of emitted light, angle between light axis and side of cone //
    // angle range between 0 - 90 in degrees //
    spotLight.setSpotlightCutOff( 50 );

    // rate of falloff, illumitation decreases as the angle from the cone axis increases //
    // range 0 - 128, zero is even illumination, 128 is max falloff //
    spotLight.setSpotConcentration( 45 );


    // Directional Lights emit light based on their orientation, regardless of their position //
	directionalLight.setDiffuseColor(ofColor(0.f, 0.f, 255.f));
	directionalLight.setSpecularColor(ofColor(255.f, 255.f, 255.f));
	directionalLight.setDirectional();

    // set the direction of the light
    // set it pointing from left to right -> //
	directionalLight.setOrientation( ofVec3f(0, 90, 0) );


	bShiny = true;
    // shininess is a value between 0 - 128, 128 being the most shiny //
	material.setShininess( 120 );
	material.setDiffuseColor(ofColor(10.0f,200.0f,0.0f,255));
    // the light highlight of the material //
    material.setSpecularColor(ofColor(255, 255, 255, 255));

	bPointLight = bSpotLight = bDirLight = true;

    if(ofIsGLProgrammableRenderer()) {
        shader.load("GL3/BlinnPhong_Phong");
    }
    else {
        shader.load("GL2/Phong_Gouraud");
    }
    bSpotLight = true;
    bPointLight = true;
    bDirLight = true;
    directionalLight.setPosition(100, 100, 0);
    sphere.setPosition(0, 0, -100);
    test.setPosition(0, 50, -100);
    mat.setSpecularColor(ofFloatColor(1.,1.,1.));
    mat.setShininess(50);
    ofSetGlobalAmbientColor(ofColor::black);
    pointLight.setPosition(100, 0, -150);
    pointLight.setAttenuation(0.0, 0.005);
    spotLight.setAttenuation(0.0, 0.005);
    cout << "const " << pointLight.getAttenuationConstant() << endl;
    cout << "linear " << pointLight.getAttenuationLinear() << endl;
    cout << "quadratic " << pointLight.getAttenuationQuadratic() << endl;
    cout << "spot cutoff " << spotLight.getSpotlightCutOff() << endl;
    cout << "spot exponent " << spotLight.getSpotConcentration() << endl;
    cout << "spot orientation " << spotLight.getOrientationEuler() << endl;
    cout << "spot lookatdir " << spotLight.getLookAtDir() << endl;
    m_lights.push_back(&pointLight);
    m_lights.push_back(&spotLight);
}

//--------------------------------------------------------------
void testApp::update() {
 //   ofVec3f lookAtDir = (spotLight.getGlobalTransformMatrix().getInverse() * ofVec4f(0,0,-1, 1));

  //  cout << lookAtDir << endl;
}

//--------------------------------------------------------------
void testApp::draw(){


    // enable lighting //
    cam.begin();
   ofEnableLighting();

    lights_Shader();
    mat.begin();

    sphere.draw();
  shader.end();
    //sphere.drawNormals(10, true);
  test.draw();
  mat.end();

	if (!bPointLight) pointLight.disable();
	if (!bSpotLight) spotLight.disable();
	if (!bDirLight) directionalLight.disable();

	// turn off lighting //
   ofDisableLighting();

    ofPushStyle();
    ofSetColor(directionalLight.getDiffuseColor());
    directionalLight.draw();
    ofPopStyle();
	ofSetColor( pointLight.getDiffuseColor() );
	if(bPointLight) pointLight.draw();

    ofSetColor(255, 255, 255);
	ofSetColor( spotLight.getDiffuseColor() );
	if(bSpotLight) spotLight.draw();
    cam.end();
	ofSetColor(255, 255, 255);
	ofDrawBitmapString("Point Light On (1) : "+ofToString(bPointLight) +"\n"+
					   "Spot Light On (2) : "+ofToString(bSpotLight) +"\n"+
					   "Directional Light On (3) : "+ofToString(bDirLight)+"\n"+
					   "Shiny Objects On (s) : "+ofToString(bShiny)+"\n"+
                       "Spot Light Cutoff (up/down) : "+ofToString(spotLight.getSpotlightCutOff(),0)+"\n"+
                       "Spot Light Concentration (right/left) : " + ofToString(spotLight.getSpotConcentration(),0)+"\n"+
                       "Smooth Lighting enabled (x) : "+ofToString(bSmoothLighting,0)+"\n"

					   ,20, 20);

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    ofVec3f pos;

    switch (key) {
		case '1':
			bPointLight = !bPointLight;
			break;
		case '2':
			bSpotLight = !bSpotLight;
			break;
		case '3':
			bDirLight = !bDirLight;
			break;
		case 's':
			bShiny	= !bShiny;
			if (bShiny) material.setShininess( 120 );
			else material.setShininess( 30 );
			break;
        case 'x':
            bSmoothLighting = !bSmoothLighting;
            ofSetSmoothLighting(bSmoothLighting);
            break;
        case 't':
            bUseTexture = !bUseTexture;
            break;
        case OF_KEY_UP:
                        pos = test.getPosition();
            pos[0] += 10;
           // test.setPosition(pos);
     //        setSpotlightCutOff is clamped between 0 - 90 degrees //
            spotLight.setSpotlightCutOff(spotLight.getSpotlightCutOff()+1);
           //spotLight.setSpotConcentration(spotLight.getSpotConcentration()+1);
            break;
        case OF_KEY_DOWN:
                        pos = test.getPosition();
            pos[0] -= 10;
           // test.setPosition(pos);
            // setSpotlightCutOff is clamped between 0 - 90 degrees //
           spotLight.setSpotlightCutOff(spotLight.getSpotlightCutOff()-1);
           //spotLight.setSpotConcentration(spotLight.getSpotConcentration()-1);
            break;
        case OF_KEY_RIGHT:
            pos = sphere.getPosition();
            pos[2] += 10;
            sphere.setPosition(pos);
            // setSpotConcentration is clamped between 0 - 128 //
            spotLight.setSpotConcentration(spotLight.getSpotConcentration()+1);
            break;
        case OF_KEY_LEFT:
            pos = sphere.getPosition();
            pos[2] -= 10;
            sphere.setPosition(pos);
            // setSpotConcentration is clamped between 0 - 128 //
           spotLight.setSpotConcentration(spotLight.getSpotConcentration()-1);
            break;
		default:
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


void testApp::lights_Shader() {
   // activate the lights //
	if (bPointLight) pointLight.enable();
	if (bSpotLight) spotLight.enable();
	if (bDirLight) directionalLight.enable();

    shader.begin();
    ofMatrix4x4 normalMatrix = ofMatrix4x4::getTransposedOf(cam.getModelViewMatrix().getInverse());
  //  ofVec3f cameraSpaceLightPos = directionalLight.getGlobalPosition() * cam.getModelViewMatrix() ;
    ofVec3f cameraSpaceLightPos = spotLight.getGlobalPosition() * cam.getModelViewMatrix() ;
    ofVec4f spotDir = ofVec4f(0., 0., -1., 1.) * normalMatrix;

  //  cout << "spot dir " << spotDir << endl;
    shader.setUniformMatrix4f("normalMatrix", normalMatrix);
    shader.setUniform3f("cameraSpaceLightPos", cameraSpaceLightPos.x, cameraSpaceLightPos.y, cameraSpaceLightPos.z);
    shader.setUniform4f("eyeSpaceSpotDir", spotDir.x, spotDir.y, spotDir.z, spotDir.w);
    shader.setUniform1f("cutoff", spotLight.getSpotlightCutOff());
    shader.setUniform1f("exponent", spotLight.getSpotConcentration());
    shader.setUniform1i("lightsNumber", 3);

    if(ofIsGLProgrammableRenderer()) {
        GLuint lights_ubo;

        glGenBuffers(1, &lights_ubo);
        glBindBuffer(GL_UNIFORM_BUFFER, lights_ubo);
        const GLchar *uniformNames[1] = { "Lights.light" };
        GLuint uniformIndices;

        glGetUniformIndices(shader.getProgram(), 1, uniformNames, &uniformIndices);
        GLint uniformOffsets[1];

        glGetActiveUniformsiv(shader.getProgram(), 1, &uniformIndices, GL_UNIFORM_OFFSET, uniformOffsets);
        GLuint uniformBlockIndex = glGetUniformBlockIndex (shader.getProgram(), "Lights");
        GLsizei uniformBlockSize(0);

        glGetActiveUniformBlockiv (shader.getProgram(), uniformBlockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &uniformBlockSize);
        vector<string> names = make_attributes_names();
        vector<const GLchar *> glnames;

        for (vector<string>::iterator str = names.begin(); str != names.end(); ++str) {
            glnames.push_back(str->c_str());
        }
        const GLchar **glnames_ptr = &glnames[0];
        GLuint indices[glnames.size()];

        glGetUniformIndices(shader.getProgram(), glnames.size(), glnames_ptr, indices);
        vector<GLint> lightUniformOffsets(glnames.size());

        glGetActiveUniformsiv(shader.getProgram(), lightUniformOffsets.size(),
        indices, GL_UNIFORM_OFFSET, &lightUniformOffsets[0]);
        GLint *offsets = &lightUniformOffsets[0];
        const unsigned int uboSize (uniformBlockSize);
        vector<float> buffer(uboSize);

        for (size_t i = 0; i < m_lights.size(); i++) {
            set_light_position(i, buffer, offsets);
            set_light_colors(i, buffer, offsets);
            set_light_attenuation(i, buffer, offsets);
            set_light_spot_properties(i, buffer, offsets);
        }

    }
}



vector<string> testApp::make_attributes_names() {
    vector<string> names;

    for (size_t i = 0; i < m_lights.size(); i++) {
        stringstream lightNumber("");
        vector<string>::iterator it;
        size_t old_size = names.size();

        lightNumber << i;
        names.push_back("Lights.light[X].position");
        names.push_back("Lights.light[X].ambient");
        names.push_back("Lights.light[X].diffuse");
        names.push_back("Lights.light[X].specular");
        names.push_back("Lights.light[X].constant_attenuation");
        names.push_back("Lights.light[X].linear_attenuation");
        names.push_back("Lights.light[X].quadratic_attenuation");
        names.push_back("Lights.light[X].spot_direction");
        names.push_back("Lights.light[X].spot_cutoff");
        names.push_back("Lights.light[X].spot_exponent");
        for (vector<string>::iterator str = names.begin()+ old_size; str != names.end(); ++str) {
            // Replace the 'X' by the current light index
            str->replace(13, 1, lightNumber.str());
        }
    }
    return names;
}

void testApp::set_light_position(size_t lightIndex, vector<float> & buffer, const GLint * offsets) {
    int offset = offsets[0 + lightIndex * 10]; // 10 = number of light props
    float * fbuf = &buffer[0];

    for (int i = 0; i < 3; ++i)
    {
        fbuf[offset] = m_lights[lightIndex]->getPosition()[i];
        offset += sizeof(GLfloat);
    }
    fbuf[offset] = 1.0; // it is a position ; not a vector
}

void testApp::set_light_colors(size_t lightIndex, vector<float> & buffer, const GLint * offsets) {
    int offset;
    float *fbuf = &buffer[0];

    // Light ambient color (vec4)
    offset = offsets[1 + lightIndex * 10];
    for (int i = 0; i < 3; ++i)
    {
        fbuf[offset] = m_lights[lightIndex]->getAmbientColor()[i];
        offset += sizeof (GLfloat);
    }
    fbuf[offset] = 1.0; // 100% alpha
    // Light diffuse color (vec4)
    offset = offsets[2 + lightIndex * 10];
    for (int i = 0; i < 3; ++i)
    {
        fbuf[offset] = m_lights[lightIndex]->getDiffuseColor()[i];
        offset += sizeof (GLfloat);
    }
    fbuf[offset] = 1.0; // 100% alpha
    // Light specular color (vec4)
    offset = offsets[3 + lightIndex * 10];
    for (int i = 0; i < 3; ++i)
    {
        fbuf[offset] = m_lights[lightIndex]->getSpecularColor()[i];
        offset += sizeof (GLfloat);
    }
    fbuf[offset] = 1.0; // 100% alpha
}

void testApp::set_light_attenuation(size_t lightIndex, vector<float> & buffer, const GLint * offsets) {
    float *fbuf = &buffer[0];
    int offset;

    // Light constant attenuation (float)
    offset = offsets[4 + lightIndex * 10];
    fbuf[offset] = m_lights[lightIndex]->getAttenuationConstant();
    // Light linear attenuation (float)
    offset = offsets[5 + lightIndex * 10];
    fbuf[offset] = m_lights[lightIndex]->getAttenuationLinear();
    // Light quadratic attenuation (float)
    offset = offsets[6 + lightIndex * 10];
    fbuf[offset] = m_lights[lightIndex]->getAttenuationQuadratic();
}

void testApp::set_light_spot_properties(size_t lightIndex, vector<float> & buffer, const GLint * offsets) {
    float *fbuf = &buffer[0];
    int offset;
    ofVec4f spotDir = ofVec4f(0., 0., -1., 1.);

    // it that's a spotlight : compute the 'real' spot direction
    if (m_lights[i]->getIsSpotlight()) {
        ofMatrix4x4 normalMatrix = ofMatrix4x4::getTransposedOf(cam.getModelViewMatrix().getInverse());

        spotDir = ofVec4f(0., 0., -1., 1.) * normalMatrix;
    }
    else {
        spotDir = ofVec4f(0., 0., -1., 1.); // a default spot direction (it's useful to compute it only for spotlight)
    }
    // Light spot direction (vec3)
    offset = offsets[7 + lightIndex * 10];
    for (int i = 0; i < 3; ++i)
    {
        if (m_lights[i]->getIsSpotlight()) {
            ofMatrix4x4 normalMatrix = ofMatrix4x4::getTransposedOf(cam.getModelViewMatrix().getInverse());
            ofVec3f cameraSpaceLightPos = spotLight.getGlobalPosition() * cam.getModelViewMatrix() ;
            ofVec4f spotDir = ofVec4f(0., 0., -1., 1.) * normalMatrix;
        }
        *(reinterpret_cast<float*> (&buffer[0] + offset)) =
            _lights[n].spotDirection[i];
        offset += sizeof (GLfloat);
    }
    // Light spot cutoff (float)
    offset = offsets[8 + lightIndex * 10];
    *(reinterpret_cast<float*> (&buffer[0] + offset)) =
            _lights[n].spotCutoff;
    // Light spot exponent (float)
    offset = offsets[9 + lightIndex * 10];
    *(reinterpret_cast<float*> (&buffer[0] + offset)) =
            _lights[n].spotExponent;
}

