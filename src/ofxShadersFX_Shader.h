#ifndef OFXSHADERSFX_SHADER_H_INCLUDED
#define OFXSHADERSFX_SHADER_H_INCLUDED

#include "ofxShadersFX.h"

namespace ofxShadersFX
{

class Shader : public ofShader
{
public:
    Shader(ShaderName name, ShaderType type, ofCamera *cam,
           ofMaterial & material, ofLight * light);
    ~Shader();

    void begin();
    void end();
};

}


#endif // OFXSHADERSFX_SHADER_H_INCLUDED
