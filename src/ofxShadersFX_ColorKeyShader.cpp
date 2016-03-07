// The MIT License (MIT)
// Copyright (c) 2016 Alexandre Baron (Scylardor)

// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


#include "ofxShadersFX_ColorKeyShader.h"

namespace ofxShadersFX {
namespace Mapping {

ColorKeyShader::ColorKeyShader(ofImage * p_colorMap, ofImage * p_colorKeyMap, const ofFloatColor & p_color)
: MappingShader(COLOR_KEY) {
    setImage(p_colorMap, 0);
    setImage(p_colorKeyMap, 1);
    m_keyColor = p_color;
}

ColorKeyShader::ColorKeyShader(const string & p_colormapPath, const string & p_colorKeyMapPath, const ofFloatColor & p_color)
: MappingShader(COLOR_KEY) {
    setImage(p_colormapPath, 0);
    setImage(p_colorKeyMapPath, 1);
    m_keyColor = p_color;
}

ColorKeyShader::~ColorKeyShader() {
    //dtor
}


void ColorKeyShader::begin() {
    MappingShader::begin();
    // color key needs to set tex parameter to GL_NEAREST, so store the old value and restore it later.
    glGetTexParameteriv(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, &m_oldTexParameter);
    glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    m_shader.setUniform4f("keyColor", m_keyColor.r, m_keyColor.g, m_keyColor.b, m_keyColor.a);
}

void ColorKeyShader::end() {
    MappingShader::end();
    // Restore the old tex parameter value.
    glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, m_oldTexParameter);
}


}
}
