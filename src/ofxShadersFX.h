#pragma once

#include "ofMain.h"

namespace ofxShadersFX {
  enum ShaderType {
    VERTEX_SHADER = 64,
    PIXEL_SHADER = 128
  };

class Shader {
public:
    Shader(ShaderType type=PIXEL_SHADER);
    virtual ~Shader() {}

    void begin();
    void end();
    void reload();

    ShaderType type() const;
    virtual string getShader(GLenum ShaderType) = 0;

    void setType(ShaderType type);

protected:
    ShaderType m_type;
    ofShader m_shader;
};
}

#include "ofxShadersFX_LightingShader.h"
#include "ofxShadersFX_MappingShader.h"
