#pragma once

#include "ofMain.h"

namespace ofxShadersFX {
  enum ShaderType {
    VERTEX_SHADER = 64,
    PIXEL_SHADER = 128
  };

class Shader {
public:
    // Available shader "types"
    enum Type {
        LIGHTING = 0,
        MAPPING
    };

    Shader(Type type);
    virtual ~Shader() {}

    void begin();
    void end();
    void reload();

    Type type() const;
    virtual string getShader(GLenum ShaderType) = 0;

    void setType(Type type);

protected:
    Type m_type;
    ofShader m_shader;
};

}

#include "ofxShadersFX_LightingShader.h"
#include "ofxShadersFX_MappingShader.h"
