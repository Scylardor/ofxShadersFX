#ifndef OFXSHADERSFX_LIGHTINGSHADER_H_INCLUDED
#define OFXSHADERSFX_LIGHTINGSHADER_H_INCLUDED

#include "ofxShadersFX.h"

namespace ofxShadersFX
{
namespace Lighting
{
    // Gouraud shading = vertex shading ; Phong = pixel shading.
    // Phong shading is used by default since it's prettier
    enum ShadingMethod {
        GOURAUD_SHADING = 0,
        PHONG_SHADING
    };

    enum LightingMethod {
        PHONG = 256,
        BLINNPHONG = 512
    };

    // Using powers of 2 guarantees there can be only one possible mix of each descriptor using binary |'s
    // This is used to retrieve a given preset minified shader source (cf. LightingShader_sources.cpp).
    // e.g.: vertex shader in GLSL120 without texture rendering using Phong lighting with Gouraud shading,
    // or pixel shader in GLSL330 with texture rendering using Blinn-Phong lighting with Phong shading.
    enum ShaderHash {
        VERTEX_SHADER =     1 << 0,
        FRAGMENT_SHADER =   1 << 1,

        GLSL_120 =          1 << 2,
        GLSL_330 =          1 << 3,

        TEX =               1 << 4,
        NO_TEX =            1 << 5,

        PHONG_GOURAUD =     1 << 6,
        PHONG_PHONG =       1 << 7,

        BLINN_GOURAUD =     1 << 8,
        BLINN_PHONG =       1 << 9
    };


class LightingShader : public Shader
{
public:
    LightingShader();
    LightingShader(LightingMethod method, Shader::Type type,
                   ofCamera * cam=NULL, ofMaterial * material=NULL, ofImage * image=NULL);
    ~LightingShader();

    void begin();
    void end();

    LightingMethod method();
    ofCamera * camera();
    const vector<ofLight *> & lights();
    ofLight * light(size_t index);
    ofMaterial * material();
    ofImage * texture();

    void setType(ShaderType p_type);
    void setMethod(LightingMethod method);
    void useLight(ofLight * light);
    void useLights(const vector<ofLight*> & lights, bool replace=true);
    void removeLight(ofLight * light);
    void useMaterial(ofMaterial * material);
    void removeMaterial();
    void useCamera(ofCamera * cam);
    void useTexture(ofImage * image);
    void removeTexture();
    void removeCamera();

private:
    void setupLights();
    void setupProgrammableRendererLights();
    vector<string> generateLightPropsNames();
    void setLightPosition(size_t lightIndex, vector<unsigned char> & buffer, const GLint * offsets);
    void setLightColors(size_t lightIndex, vector<unsigned char> & buffer, const GLint * offsets);
    void setLightAttenuation(size_t lightIndex, vector<unsigned char> & buffer, const GLint * offsets);
    void setLightSpotProperties(size_t lightIndex, vector<unsigned char> & buffer, const GLint * offsets);
    void setupFixedPipelineLights();

    void setupMaterial();
    void setMaterialProperties(vector<unsigned char> & buffer, const GLint * offsets);

    string getShader(GLenum shaderType);
    unsigned int getShaderHash(GLenum p_shaderType);

    // Maximum number of lights
    // 8 is set to mimic legacy OpenGL limits, but
    // could be overridden
    static const size_t MAX_LIGHTS = 8;
    // Number of light properties in the shaders
    static const size_t LIGHT_PROPS_NUMBER = 11;
    // Number of different shaders types implemented
    static const size_t SHADERS_TYPES = 8;
    static const char * VERTEX_SHADER_SOURCES_GLSL120[SHADERS_TYPES];
    static const char * VERTEX_SHADER_SOURCES_GLSL330[SHADERS_TYPES];
    static const char * FRAGMENT_SHADER_SOURCES_GLSL120[SHADERS_TYPES];
    static const char * FRAGMENT_SHADER_SOURCES_GLSL330[SHADERS_TYPES];
    // The lighting method (Phong, BlinnPhong...) used by the shader
    LightingMethod m_method;
    vector<ofLight *> m_lights;
    ofMaterial * m_mat;
    // A default material avoids to make the shader compute erroneous lighting
    // in case no material is provided
    ofMaterial * m_defaultMat;
    // The camera used in programmable pipeline mode
    ofCamera * m_cam;
    // The texture the shader has to show
    ofImage * m_tex;
    // After each begin, in programmable pipeline mode, the shader computes the cam normal matrix
    // in order to feed it to the shader.
    ofMatrix4x4 m_normalMatrix;
};
}
}

#endif // OFXSHADERSFX_LIGHTINGSHADER_H_INCLUDED
