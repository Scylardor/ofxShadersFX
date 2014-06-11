#ifndef OFXSHADERSFX_LIGHTINGSHADER_H_INCLUDED
#define OFXSHADERSFX_LIGHTINGSHADER_H_INCLUDED

#include "ofxShadersFX.h"

namespace ofxShadersFX
{
namespace Lighting
{
    typedef enum
    {
        PHONG,
        BLINNPHONG
    }	LightingMethod;

class LightingShader : public Shader
{
public:
    LightingShader(LightingMethod method=BLINNPHONG, ShaderType type=PIXEL_SHADER,
                   ofCamera * cam=NULL, ofMaterial * material=NULL, ofImage * image=NULL);
    ~LightingShader();

    void begin();
    void end();

    string getShaderName();
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
    vector<string> generateLightPropsNames();
    void setLightPosition(size_t lightIndex, vector<unsigned char> & buffer, const GLint * offsets);
    void setLightColors(size_t lightIndex, vector<unsigned char> & buffer, const GLint * offsets);
    void setLightAttenuation(size_t lightIndex, vector<unsigned char> & buffer, const GLint * offsets);
    void setLightSpotProperties(size_t lightIndex, vector<unsigned char> & buffer, const GLint * offsets);

    void setupMaterial();
    void setMaterialProperties(vector<unsigned char> & buffer, const GLint * offsets);

    // Maximum number of lights
    // 8 is set to mimic legacy OpenGL limits, but
    // could be overridden
    static const size_t MAX_LIGHTS = 8;
    // Number of light properties in the shaders
    static const size_t LIGHT_PROPS_NUMBER = 11;
    // static map to choose the right shader for the right method
    static map<LightingMethod, string> shader_paths;
    LightingMethod m_method;
    vector<ofLight *> m_lights;
    ofMaterial * m_mat;
    ofCamera * m_cam;
    ofImage * m_tex;
    ofMatrix4x4 m_normalMatrix;
};
}
}

#endif // OFXSHADERSFX_LIGHTINGSHADER_H_INCLUDED
