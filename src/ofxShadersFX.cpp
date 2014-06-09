#include "ofxShadersFX.h"

namespace ofxShadersFX {
    Shader::Shader(ShaderType type)
    : ofShader()
    {
        m_type = type;
    }

    Shader::~Shader()
    {

    }

    void Shader::begin() {
        ofShader::begin();
    }

    void Shader::end() {
        ofShader::end();
    }

    ShaderType Shader::type() const {
        return m_type;
    }
}
