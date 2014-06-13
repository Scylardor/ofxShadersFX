#pragma once

#include "ofMain.h"

namespace ofxShadersFX {
  typedef enum {
    VERTEX_SHADER = 0,
    PIXEL_SHADER
  }	ShaderType;

class Shader {
public:
    Shader(ShaderType type=PIXEL_SHADER);
    virtual ~Shader() {}

    void begin();
    void end();
    void reload();

    ShaderType type() const;
    virtual string getShaderName() = 0;

    void setType(ShaderType type);

protected:
    ShaderType m_type;
    ofShader m_shader;
};
}

#include "ofxShadersFX_LightingShader.h"
