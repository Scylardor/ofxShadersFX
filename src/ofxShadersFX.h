#pragma once

#include "ofMain.h"

namespace ofxShadersFX {
    // Available shader "types"
    enum ShaderType {
        LIGHTING = 0,
        MAPPING
    };

class Shader {
public:
    Shader(ShaderType type);
    virtual ~Shader() {}

    void begin();
    void end();

    ShaderType shaderType() const;

    void setShaderType(ShaderType type);

protected:
    virtual string getShader(GLenum ShaderType) const = 0;

    ShaderType m_type;
    ofShader m_shader;
    bool m_needsReload; // Modifications in shaders set this to true. Set back to false after reload

private:
    void reload();
};

}

#include "ofxShadersFX_LightingShader.h"
#include "ofxShadersFX_MappingShader.h"
