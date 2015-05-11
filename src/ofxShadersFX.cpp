#include "ofxShadersFX.h"

namespace ofxShadersFX {
    Shader::Shader(ShaderType p_type)
    {
        setShaderType(p_type);
    }

    void Shader::begin() {
        m_shader.begin();
    }

    void Shader::end() {
        m_shader.end();
    }

    ShaderType Shader::shaderType() const {
        return m_type;
    }

    void Shader::setShaderType(ShaderType p_type) {
        m_type = p_type;
    }

    void Shader::reload() {
        this->m_shader.setupShaderFromSource(GL_VERTEX_SHADER, getShader(GL_VERTEX_SHADER));
        this->m_shader.setupShaderFromSource(GL_FRAGMENT_SHADER, getShader(GL_FRAGMENT_SHADER));
        if(ofIsGLProgrammableRenderer()) {
            this->m_shader.bindDefaults();
        }
        this->m_shader.linkProgram();
    }
}
