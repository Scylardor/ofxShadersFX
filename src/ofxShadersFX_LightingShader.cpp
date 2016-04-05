// The MIT License (MIT)
// Copyright (c) 2016 Alexandre Baron (Scylardor)

// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "ofxShadersFX_LightingShader.h"

namespace ofxShadersFX
{
namespace Lighting
{

LightingShader::LightingShader()
: Shader(LIGHTING)
{
    // Use Phong-shaded Blinn-Phong lighting by default.
    setShadingMethod(PIXEL_SHADING);
    setLightingMethod(BLINN_PHONG_LIGHTING);
}


LightingShader::LightingShader(ShadingMethod p_shadingMethod, LightingMethod p_lightMethod,
                               ofCamera * p_cam, ofMaterial * p_material, ofImage * p_tex)
: Shader(LIGHTING)
{
    m_cam = p_cam;
    m_mat = p_material;
    m_tex = p_tex;
    setShadingMethod(p_shadingMethod);
    setLightingMethod(p_lightMethod);
}


LightingShader::~LightingShader()
{
}


ShadingMethod LightingShader::shadingMethod() const
{
    return m_shadingMethod;
}


LightingMethod LightingShader::lightingMethod() const
{
    return m_lightingMethod;
}


const ofCamera * LightingShader::camera() const
{
    return m_cam;
}


const vector<ofLight *> & LightingShader::lights() const
{
    return m_lights;
}


const ofLight * LightingShader::light(size_t p_index) const
{
    ofLight * ret = NULL;

    if (p_index < m_lights.size())
    {
        ret = m_lights[p_index];
    }
    else
    {
        ofLogError() << "ofxShadersFX::LightingShader: No light at index " << p_index << endl;
    }
    return ret;
}


const ofMaterial * LightingShader::material() const
{
    return m_mat;
}


const ofImage * LightingShader::texture() const
{
    return m_tex;
}


ofCamera * LightingShader::camera()
{
    return m_cam;
}


vector<ofLight *> & LightingShader::lights()
{
    return m_lights;
}


ofLight * LightingShader::light(size_t p_index)
{
    ofLight * ret = NULL;

    if (p_index < m_lights.size())
    {
        ret = m_lights[p_index];
    }
    else
    {
        ofLogError() << "ofxShadersFX::LightingShader: No light at index " << p_index << endl;
    }
    return ret;
}


ofMaterial * LightingShader::material()
{
    return m_mat;
}


ofImage * LightingShader::texture()
{
    return m_tex;
}


void LightingShader::setLightingMethod(LightingMethod p_method)
{
    m_lightingMethod = p_method;
    m_needsReload = true;
}


void LightingShader::setShadingMethod(ShadingMethod p_method)
{
    m_shadingMethod = p_method;
    m_needsReload = true;
}


string LightingShader::getShader(GLenum p_shaderType) const {
    const char ** shaders;
    // First get the correct shader source array.
    if (p_shaderType == GL_VERTEX_SHADER) {
        if (ofIsGLProgrammableRenderer()) {
            shaders = LightingShader::VERTEX_SHADER_SOURCES_GLSL330;
        }
        else {
            shaders = LightingShader::VERTEX_SHADER_SOURCES_GLSL120;
        }
    }
    else if (p_shaderType == GL_FRAGMENT_SHADER) {
        if (ofIsGLProgrammableRenderer()) {
            shaders = LightingShader::FRAGMENT_SHADER_SOURCES_GLSL330;
        }
        else {
            shaders = LightingShader::FRAGMENT_SHADER_SOURCES_GLSL120;
        }
    }

    // Then find the good index for the shader matching our parameters.
    ShaderSourceIndex sourceIndex;
    if (this->lightingMethod() == PHONG_LIGHTING) {
        if (this->shadingMethod() == PIXEL_SHADING) {
            sourceIndex = PIXEL_PHONG;
        }
        else {
            sourceIndex = VERTEX_PHONG;
        }
    }
    else if (this->lightingMethod() == BLINN_PHONG_LIGHTING) {
        if (this->shadingMethod() == PIXEL_SHADING) {
            sourceIndex = PIXEL_BLINN_PHONG;
        }
        else {
            sourceIndex = VERTEX_BLINN_PHONG;
        }
    }

    // Casting to int is necessary to increment.
    int shaderIndex = static_cast<int>(sourceIndex);
    if (this->texture() != NULL) {
        shaderIndex++;
    }
    return string(shaders[shaderIndex]);
}


void LightingShader::begin()
{
    Shader::begin();
    if (m_tex != NULL)
    {
        m_shader.setUniformTexture("tex", (*m_tex), 1);
        m_tex->bind();
    }

    // The camera is only necessary in programmable pipeline mode
    if (m_cam != NULL || ofIsGLProgrammableRenderer() == false)
    {
        setupLights();
        setupMaterial();
    }
    else
    {
        ofLogError() << "ofxShadersFX::LightingShader: A camera is required in programmable pipeline mode" << endl;
    }
}

void LightingShader::end()
{
    Shader::end();
    if (ofIsGLProgrammableRenderer() == false)
    {
        for (size_t i = 0; i < m_lights.size(); i++)
        {
            m_lights[i]->disable();
        }
        if (m_mat != NULL) {
            m_mat->end();
        }
        ofDisableLighting();
    }
    if (m_tex != NULL)
    {
        m_tex->unbind();
    }
}

void LightingShader::useLight(ofLight * p_light)
{
    const size_t limit = this->MAX_LIGHTS;

    if (m_lights.size() < limit)
    {
        m_lights.push_back(p_light);
    }
    else
    {
        ofLogError() << "ofxShadersFX::LightingShader: cannot use more than " << limit << " lights" << endl;
    }
}

void LightingShader::useLights(const vector<ofLight*> & p_lights, bool p_replace)
{
    const size_t limit = this->MAX_LIGHTS;

    if (p_replace)
    {
        if (p_lights.size() <= limit)
        {
            m_lights = p_lights;
        }
        else
        {
            ofLogWarning() << "ofxShadersFX::LightingShader: lights vector is too big. Using only " << limit << " lights." << endl;
            m_lights.insert(m_lights.begin(), p_lights.begin(), p_lights.begin()+limit);
        }
    }
    else
    {
        if (p_lights.size() + m_lights.size() <= limit)
        {
            // Append the vector within the limits of max lights
            m_lights.insert(m_lights.end(), p_lights.begin(), p_lights.end());
        }
        else
        {
            ofLogWarning() << "ofxShadersFX::LightingShader: cannot use more than " << limit << " lights." << endl;
            m_lights.insert(m_lights.end(), p_lights.begin(), p_lights.begin()+(limit-m_lights.size()));
        }
    }
}

void LightingShader::removeLight(ofLight * p_light)
{
    vector<ofLight *>::iterator light;

    light = std::find(m_lights.begin(), m_lights.end(), p_light);
    if (light != m_lights.end())
    {
        m_lights.erase(light);
    }
    else {
        ofLogWarning() << "ofxShadersFX::LightingShader: light isn't in this lighting shader" << endl;
    }
}

void LightingShader::useMaterial(ofMaterial * p_material)
{
    m_mat = p_material;
}


void LightingShader::removeMaterial()
{
    m_mat = NULL;
}

void LightingShader::useCamera(ofCamera * p_cam)
{
    m_cam = p_cam;
}

void LightingShader::removeCamera()
{
    m_cam = NULL;
}


void LightingShader::useTexture(ofImage * p_img)
{
    const bool bNotUsingTexture = (m_tex == NULL);

    m_tex = p_img;
    // If now using a texture whereas we didn't use one before, we're going to need another version
    // of the current shader blending in the texture color, so ask a reload.
    if (bNotUsingTexture) {
        m_needsReload = true;
    }
}


void LightingShader::removeTexture()
{
    m_tex = NULL;
    m_needsReload = true;
}


void LightingShader::setupLights()
{
    m_shader.setUniform1i("lightsNumber", m_lights.size());
    if (ofIsGLProgrammableRenderer())
    {
        setupProgrammableRendererLights();
    }
    else
    {
        setupFixedPipelineLights();
    }
}


void LightingShader::setupProgrammableRendererLights() {
        m_normalMatrix = ofMatrix4x4::getTransposedOf(m_cam->getModelViewMatrix().getInverse());
        m_shader.setUniformMatrix4f("normalMatrix", m_normalMatrix);

        GLuint lights_ubo;

        glGenBuffers(1, &lights_ubo);
        glBindBuffer(GL_UNIFORM_BUFFER, lights_ubo);

        GLuint uniformBlockIndex = glGetUniformBlockIndex (m_shader.getProgram(), "Lights");
        GLsizei uniformBlockSize(0);

        glGetActiveUniformBlockiv (m_shader.getProgram(), uniformBlockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &uniformBlockSize);

        vector<string> names = generateLightPropsNames();
        vector<const GLchar *> glnames;

        for (vector<string>::iterator str = names.begin(); str != names.end(); ++str)
        {
            glnames.push_back(str->c_str());
        }

        const GLchar **glnames_ptr = &glnames[0];
        GLuint * indices = new GLuint[glnames.size()];

        glGetUniformIndices(m_shader.getProgram(), glnames.size(), glnames_ptr, indices);

        vector<GLint> lightUniformOffsets(glnames.size());

        glGetActiveUniformsiv(m_shader.getProgram(), lightUniformOffsets.size(),
                              indices, GL_UNIFORM_OFFSET, &lightUniformOffsets[0]);

        GLint *offsets = &lightUniformOffsets[0];
        const unsigned int uboSize (uniformBlockSize);
        vector<unsigned char> buffer(uboSize);

        for (size_t i = 0; i < m_lights.size(); i++)
        {
            setLightPosition(i, buffer, offsets);
            setLightColors(i, buffer, offsets);
            setLightAttenuation(i, buffer, offsets);
            setLightSpotProperties(i, buffer, offsets);
        }
        glBufferData(GL_UNIFORM_BUFFER, uboSize, &buffer[0], GL_DYNAMIC_DRAW);
        glBindBufferBase(GL_UNIFORM_BUFFER, 0, lights_ubo);
        glUniformBlockBinding (m_shader.getProgram(), uniformBlockIndex, 0);
}


vector<string> LightingShader::generateLightPropsNames()
{
    vector<string> names;
    const char * props[] =
    {
        "].position",
        "].ambient",
        "].diffuse",
        "].specular",
        "].constant_attenuation",
        "].linear_attenuation",
        "].quadratic_attenuation",
        "].spot_direction",
        "].spot_cutoff",
        "].spot_cos_cutoff",
        "].spot_exponent"
    };

    for (size_t i = 0; i < m_lights.size(); i++)
    {
        stringstream ss_lightNumber("");
        string lightNumber;

        ss_lightNumber << i;
        lightNumber = ss_lightNumber.str();
        for (size_t s = 0; s < LIGHT_PROPS_NUMBER; s++)
        {
            names.push_back(string("Lights.light[") + lightNumber + string(props[s]));
        }
    }

    return names;
}


void LightingShader::setLightPosition(size_t lightIndex, vector<unsigned char> & buffer, const GLint * offsets)
{
    int offset = offsets[0 + lightIndex * LIGHT_PROPS_NUMBER];
    ofVec3f eyeSpaceLightPos = m_lights[lightIndex]->getGlobalPosition() * m_cam->getModelViewMatrix();

    if (m_lights[lightIndex]->getIsDirectional()) {
        ofVec4f dir;

        dir = m_lights[lightIndex]->getLookAtDir();
        dir[3] = 0.0;
        dir = dir * m_normalMatrix;
        eyeSpaceLightPos = dir;
    }
    for (int i = 0; i < 3; ++i)
    {
        *(reinterpret_cast<float*> (&buffer[0] + offset)) = eyeSpaceLightPos[i];
        offset += sizeof(GLfloat);
    }
    if (m_lights[lightIndex]->getIsDirectional())
    {
        *(reinterpret_cast<float*> (&buffer[0] + offset)) = 0.0; // light is a vector; no position
    }
    else
    {
        *(reinterpret_cast<float*> (&buffer[0] + offset)) = 1.0; // it is a position ; not a vector
    }

}


void LightingShader::setLightColors(size_t lightIndex, vector<unsigned char> & buffer, const GLint * offsets)
{
    int offset;

    // Light ambient color (vec4)
    offset = offsets[1 + lightIndex * LIGHT_PROPS_NUMBER];
    for (int i = 0; i < 3; ++i)
    {
        *(reinterpret_cast<float*> (&buffer[0] + offset)) = m_lights[lightIndex]->getAmbientColor()[i];
        offset += sizeof (GLfloat);
    }
    *(reinterpret_cast<float*> (&buffer[0] + offset)) = 1.0; // 100% alpha
    // Light diffuse color (vec4)
    offset = offsets[2 + lightIndex * LIGHT_PROPS_NUMBER];
    for (int i = 0; i < 3; ++i)
    {
        *(reinterpret_cast<float*> (&buffer[0] + offset)) = m_lights[lightIndex]->getDiffuseColor()[i];
        offset += sizeof (GLfloat);
    }
    *(reinterpret_cast<float*> (&buffer[0] + offset)) = 1.0; // 100% alpha
    // Light specular color (vec4)
    offset = offsets[3 + lightIndex * LIGHT_PROPS_NUMBER];
    for (int i = 0; i < 3; ++i)
    {
        *(reinterpret_cast<float*> (&buffer[0] + offset)) = m_lights[lightIndex]->getSpecularColor()[i];
        offset += sizeof (GLfloat);
    }
    *(reinterpret_cast<float*> (&buffer[0] + offset)) = 1.0; // 100% alpha
}


void LightingShader::setLightAttenuation(size_t lightIndex, vector<unsigned char> & buffer, const GLint * offsets)
{
    int offset;

    // Light constant attenuation (float)
    offset = offsets[4 + lightIndex * LIGHT_PROPS_NUMBER];
    *(reinterpret_cast<float*> (&buffer[0] + offset)) = m_lights[lightIndex]->getAttenuationConstant();
    // Light linear attenuation (float)
    offset = offsets[5 + lightIndex * LIGHT_PROPS_NUMBER];
    *(reinterpret_cast<float*> (&buffer[0] + offset)) = m_lights[lightIndex]->getAttenuationLinear();
    // Light quadratic attenuation (float)
    offset = offsets[6 + lightIndex * LIGHT_PROPS_NUMBER];
    *(reinterpret_cast<float*> (&buffer[0] + offset)) = m_lights[lightIndex]->getAttenuationQuadratic();
}

void LightingShader::setLightSpotProperties(size_t lightIndex, vector<unsigned char> & buffer, const GLint * offsets)
{
    int offset;
    ofVec4f spotDir = ofVec4f(0., 0., -1., 1.);

    // it that's a spotlight : compute the 'real' spot direction
    if (m_lights[lightIndex]->getIsSpotlight())
    {
        ofVec4f dir;

        dir = m_lights[lightIndex]->getLookAtDir();
        dir[3] = 1.0;
        spotDir = dir * m_normalMatrix;
    }
    else
    {
        spotDir = ofVec4f(0., 0., -1., 1.) * m_normalMatrix; // a default spot direction (it's useful to compute it only for spotlight)
    }
    // Light spot direction (vec3)
    offset = offsets[7 + lightIndex * LIGHT_PROPS_NUMBER];
    for (int i = 0; i < 3; ++i)
    {
        *(reinterpret_cast<float*> (&buffer[0] + offset)) = spotDir[i];
        offset += sizeof (GLfloat);
    }
    // Light spot cutoff (float)
    offset = offsets[8 + lightIndex * LIGHT_PROPS_NUMBER];
    if (m_lights[lightIndex]->getIsSpotlight())
    {
        *(reinterpret_cast<float*> (&buffer[0] + offset)) = m_lights[lightIndex]->getSpotlightCutOff();
    }
    else
    {
        *(reinterpret_cast<float*> (&buffer[0] + offset)) = 360.0;
    }
    offset = offsets[9 + lightIndex * LIGHT_PROPS_NUMBER];
    if (m_lights[lightIndex]->getIsSpotlight())
    {
        *(reinterpret_cast<float*> (&buffer[0] + offset)) = cos(ofDegToRad(m_lights[lightIndex]->getSpotlightCutOff()));
    }
    // Light spot exponent (float)
    offset = offsets[10 + lightIndex * LIGHT_PROPS_NUMBER];
    if (m_lights[lightIndex]->getIsSpotlight())
    {
        *(reinterpret_cast<float*> (&buffer[0] + offset)) = m_lights[lightIndex]->getSpotConcentration();
    }
}


void LightingShader::setupFixedPipelineLights() {
    ofEnableLighting();
    for (size_t i = 0; i < m_lights.size(); i++)
    {
        m_lights[i]->enable();
    }
}


void LightingShader::setupMaterial()
{
    // if no material provided, use the default one
    if (m_mat == NULL)
    {
        m_mat = &m_defaultMat;
    }
    if (ofIsGLProgrammableRenderer())
    {
        GLuint material_ubo;

        glGenBuffers(1, &material_ubo);
        glBindBuffer(GL_UNIFORM_BUFFER, material_ubo);

        const GLchar *uniformNames[5] =
        {
            "Material.ambient",
            "Material.diffuse",
            "Material.specular",
            "Material.emission",
            "Material.shininess"
        };

        GLuint uniformIndices[5];

        glGetUniformIndices (m_shader.getProgram(), 5, uniformNames, uniformIndices);

        GLint uniformOffsets[5];
        glGetActiveUniformsiv (m_shader.getProgram(), 5, uniformIndices,
                               GL_UNIFORM_OFFSET, uniformOffsets);

        GLuint uniformBlockIndex = glGetUniformBlockIndex (m_shader.getProgram(),
                                   "Material");
        GLsizei uniformBlockSize (0);

        glGetActiveUniformBlockiv (m_shader.getProgram(), uniformBlockIndex,
                                   GL_UNIFORM_BLOCK_DATA_SIZE, &uniformBlockSize);

        const unsigned int uboSize (uniformBlockSize);
        vector<unsigned char> buffer (uboSize);

        setMaterialProperties(buffer, uniformOffsets);

        glBufferData (GL_UNIFORM_BUFFER, uboSize, &buffer[0], GL_DYNAMIC_DRAW);
        glBindBufferBase (GL_UNIFORM_BUFFER, 1, material_ubo);
        glUniformBlockBinding (m_shader.getProgram(), uniformBlockIndex, 1);
    }
    else
    {
        m_mat->begin();
    }
}

void LightingShader::setMaterialProperties(vector<unsigned char> & buffer, const GLint * offsets)
{
    int offset;

    // Sphere material ambient color (vec4)
    offset = offsets[0];
    for (int i = 0; i < 3; ++i)
    {
        *(reinterpret_cast<float *> (&buffer[0] + offset)) =
            m_mat->getAmbientColor()[i];
        offset += sizeof (GLfloat);
    }
    *(reinterpret_cast<float *> (&buffer[0] + offset)) = 1.0; // 100% alpha
    // Sphere material diffuse color (vec4)
    offset = offsets[1];
    for (int i = 0; i < 3; ++i)
    {
        *(reinterpret_cast<float *> (&buffer[0] + offset)) =
            m_mat->getDiffuseColor()[i];
        offset += sizeof (GLfloat);
    }
    *(reinterpret_cast<float *> (&buffer[0] + offset)) = 1.0; // 100% alpha
    // Sphere material specular color (vec4)
    offset = offsets[2];
    for (int i = 0; i < 3; ++i)
    {
        *(reinterpret_cast<float *> (&buffer[0] + offset)) =
            m_mat->getSpecularColor()[i];
        offset += sizeof (GLfloat);
    }
    *(reinterpret_cast<float *> (&buffer[0] + offset)) = 1.0; // 100% alpha
    offset = offsets[3];
    for (int i = 0; i < 3; ++i)
    {
        *(reinterpret_cast<float *> (&buffer[0] + offset)) =
            m_mat->getEmissiveColor()[i];
        offset += sizeof (GLfloat);
    }
    *(reinterpret_cast<float *> (&buffer[0] + offset)) = 1.0; // 100% alpha

    // Sphere material shininess (float)
    offset = offsets[4];
    *(reinterpret_cast<float *> (&buffer[0] + offset)) =
        m_mat->getShininess();
}


}
}
