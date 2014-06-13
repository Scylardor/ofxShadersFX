#include "ofxShadersFX.h"

namespace ofxShadersFX {
    Shader::Shader(ShaderType p_type)
    {
        setType(p_type);
    }

    void Shader::begin() {
        m_shader.begin();
    }

    void Shader::end() {
        m_shader.end();
    }

    ShaderType Shader::type() const {
        return m_type;
    }

    void Shader::setType(ShaderType p_type) {
        m_type = p_type;
    }

    void Shader::reload() {
        this->m_shader.unload();
        this->m_shader.load(getShaderName());
    }
}
