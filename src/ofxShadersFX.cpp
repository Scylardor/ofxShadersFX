#include "ofxShadersFX.h"

namespace ofxShadersFX {
    Shader::Shader(ShaderType p_type)
    : ofShader()
    {
        setType(p_type);
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

    void Shader::setType(ShaderType p_type) {
        m_type = p_type;
    }
}
