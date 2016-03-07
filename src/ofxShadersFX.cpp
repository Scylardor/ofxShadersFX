// The MIT License (MIT)
// Copyright (c) 2016 Alexandre Baron (Scylardor)

// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "ofxShadersFX.h"

namespace ofxShadersFX {
    Shader::Shader(ShaderType p_type)
    {
        setShaderType(p_type);
    }

    void Shader::begin() {
        // The shader needs reload if not loaded
        // or if modifications in attributes occurred since last frame
        if (!m_shader.isLoaded() || m_needsReload) {
            reload();
            m_needsReload = false;
        }
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
        m_shader.setupShaderFromSource(GL_VERTEX_SHADER, getShader(GL_VERTEX_SHADER));
        m_shader.setupShaderFromSource(GL_FRAGMENT_SHADER, getShader(GL_FRAGMENT_SHADER));
        if(ofIsGLProgrammableRenderer()) {
            m_shader.bindDefaults();
        }
        m_shader.linkProgram();
    }
}
