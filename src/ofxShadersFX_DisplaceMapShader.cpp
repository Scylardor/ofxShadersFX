// The MIT License (MIT)
// Copyright (c) 2016 Alexandre Baron (Scylardor)

// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "ofxShadersFX_DisplaceMapShader.h"

namespace ofxShadersFX {
namespace Mapping {

DisplaceMapShader::DisplaceMapShader(ofImage * p_colormap, ofImage * p_displacemap, float p_maxHeight)
: MappingShader(DISPLACEMENT) {
    if (p_colormap != NULL) {
        addImage(p_colormap);
    }
    if (p_displacemap != NULL) {
        addImage(p_displacemap);
    }
    m_maxHeight = p_maxHeight;
}


DisplaceMapShader::DisplaceMapShader(const string & p_colormapPath, const string & p_displacemapPath, float p_maxHeight)
: MappingShader(DISPLACEMENT) {
    addImage(p_colormapPath);
    addImage(p_displacemapPath);
    m_maxHeight = p_maxHeight;
}


DisplaceMapShader::~DisplaceMapShader() {
}

void DisplaceMapShader::begin() {
    MappingShader::begin();
    m_shader.setUniform1f("maxHeight", m_maxHeight);
    if (ofIsGLProgrammableRenderer()) {
        m_shader.setUniformMatrix4f("normalMatrix", m_normalMatrix);
    }
}

}
}
