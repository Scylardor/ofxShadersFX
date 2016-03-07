// The MIT License (MIT)
// Copyright (c) 2016 Alexandre Baron (Scylardor)

// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef OFXSHADERSFX_LIGHTINGSHADER_H_INCLUDED
#define OFXSHADERSFX_LIGHTINGSHADER_H_INCLUDED

#include "ofxShadersFX.h"

namespace ofxShadersFX
{
namespace Lighting
{
    // For reference:
    // - flat shading = Lambert shading (this is unsupported);
    // - vertex shading = Gouraud shading;
    // - pixel shading = Phong shading.
    // Phong shading is used by default since it's prettier.
    // We use VERTEX/PIXEL SHADING names to avoid confusion with some Lighting names.
    enum ShadingMethod {
        VERTEX_SHADING = 0,
        PIXEL_SHADING
    };

    enum LightingMethod {
        PHONG_LIGHTING = 0,
        BLINN_PHONG_LIGHTING
    };

class LightingShader : public Shader
{
public:
    LightingShader();
    LightingShader(ShadingMethod p_shadingMethod, LightingMethod p_lightMethod, ofCamera * p_cam=NULL,
                   ofMaterial * p_material=NULL, ofImage * p_image=NULL);
    virtual ~LightingShader();


    // Base shader functions
    void begin();
    void end();


    // Accessors

    ShadingMethod shadingMethod() const;
    LightingMethod lightingMethod() const;
    const ofCamera * camera() const;
    const vector<ofLight *> & lights() const;
    const ofLight * light(size_t index) const;
    const ofMaterial * material() const;
    const ofImage * texture() const;


    // Mutators

    ofCamera * camera();
    vector<ofLight *> & lights();
    ofLight * light(size_t index);
    ofMaterial * material();
    ofImage * texture();

    void setShadingMethod(ShadingMethod p_method);
    void setLightingMethod(LightingMethod p_method);
    void useLight(ofLight * p_light);
    void useLights(const vector<ofLight*> & p_lights, bool replace=true);
    void removeLight(ofLight * p_light);
    void useMaterial(ofMaterial * p_mat);
    void removeMaterial();
    void useCamera(ofCamera * p_cam);
    void useTexture(ofImage * p_img);
    void removeTexture();
    void removeCamera();

private:
    // Used internally to retrieve shader sources in the sources array without using "magic numbers".
    enum ShaderSourceIndex {
        VERTEX_PHONG = 0,
        TEXTURED_VERTEX_PHONG,
        VERTEX_BLINN_PHONG,
        TEXTURED_VERTEX_BLINN_PHONG,
        PIXEL_PHONG,
        TEXTURED_PIXEL_PHONG,
        PIXEL_BLINN_PHONG,
        TEXTURED_PIXEL_BLINN_PHONG,
    };

    void setupLights();
    void setupProgrammableRendererLights();
    vector<string> generateLightPropsNames();
    void setLightPosition(size_t p_lightIndex, vector<unsigned char> & p_buffer, const GLint * p_offsets);
    void setLightColors(size_t p_lightIndex, vector<unsigned char> & p_buffer, const GLint * p_offsets);
    void setLightAttenuation(size_t p_lightIndex, vector<unsigned char> & p_buffer, const GLint * p_offsets);
    void setLightSpotProperties(size_t p_lightIndex, vector<unsigned char> & p_buffer, const GLint * p_offsets);
    void setupFixedPipelineLights();

    void setupMaterial();
    void setMaterialProperties(vector<unsigned char> & p_buffer, const GLint * p_offsets);

    virtual string getShader(GLenum p_shaderType) const;

    // The shading method (Lambert/flat, Gouraud/vertex, Phong/pixel) used by the shader
    ShadingMethod m_shadingMethod;
    LightingMethod m_lightingMethod; // The lighting method (Phong, BlinnPhong...) used by the shader
    vector<ofLight *> m_lights;
    // A default material avoids to make the shader compute erroneous lighting
    // in case no material is provided
    ofMaterial m_defaultMat;
    ofCamera * m_cam; // The camera used in programmable pipeline mode
    ofMaterial * m_mat; // The material which properties are passed to the shaders.
    ofImage * m_tex; // The texture the shader has to show
    // After each begin, in programmable pipeline mode, the shader computes the cam normal matrix
    // in order to feed it to the shader.
    ofMatrix4x4 m_normalMatrix;

    // Maximum number of lights 8 is set to mimic legacy OpenGL limits, but could be overridden.
    static const size_t MAX_LIGHTS = 8;
    static const size_t LIGHT_PROPS_NUMBER = 11; // Number of light properties in the shaders
    static const size_t SHADERS_TYPES = 8; // Number of different shaders types implemented
    static const char * VERTEX_SHADER_SOURCES_GLSL120[SHADERS_TYPES];
    static const char * VERTEX_SHADER_SOURCES_GLSL330[SHADERS_TYPES];
    static const char * FRAGMENT_SHADER_SOURCES_GLSL120[SHADERS_TYPES];
    static const char * FRAGMENT_SHADER_SOURCES_GLSL330[SHADERS_TYPES];
};
}
}

#endif // OFXSHADERSFX_LIGHTINGSHADER_H_INCLUDED
