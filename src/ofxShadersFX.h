// The MIT License (MIT)
// Copyright (c) 2016 Alexandre Baron (Scylardor)

// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

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
    bool m_needsReload; // Modifications requiring a reload set this to true. Set back to false after reload

private:
    void reload();
};

}

#include "ofxShadersFX_LightingShader.h"
#include "ofxShadersFX_MappingShader.h"
