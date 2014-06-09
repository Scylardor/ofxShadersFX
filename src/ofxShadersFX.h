#pragma once

#include "ofMain.h"

namespace ofxShadersFX {
  typedef enum {
    VERTEX_SHADER = 0,
    PIXEL_SHADER
  }	ShaderType;

class Shader : public ofShader {
public:
    Shader(ShaderType type=PIXEL_SHADER);
    ~Shader();

    void begin();
    void end();
    ShaderType type() const;

    void setType(ShaderType type);

protected:
    ShaderType m_type;
};
}

#include "ofxShadersFX_LightingShader.h"
