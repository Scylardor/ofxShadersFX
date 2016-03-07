// The MIT License (MIT)
// Copyright (c) 2016 Alexandre Baron (Scylardor)

// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef OFXSHADERSFX_DISPLACEMAPSHADER_H_INCLUDED
#define OFXSHADERSFX_DISPLACEMAPSHADER_H_INCLUDED

#include "ofxShadersFX_MappingShader.h"

namespace ofxShadersFX {
namespace Mapping {

class DisplaceMapShader : public MappingShader {
public:
    DisplaceMapShader(ofImage * p_colormap=NULL, ofImage * p_displacemap=NULL, float p_maxHeight=10.0f);
    DisplaceMapShader(const string & p_colormapPath, const string & p_displacemapPath, float p_maxHeight=10.0f);
    ~DisplaceMapShader();

    // Accessors

    const ofImage * colormap() const { return (m_imgs.size() > 0 ? m_imgs[0] : NULL); }
    const ofImage * displacemap() const { return (m_imgs.size() > 1 ? m_imgs[1] : NULL); }
    float maxHeight() const { return m_maxHeight; }
    const ofMatrix4x4 & normalMatrix() const { return m_normalMatrix; }


    // Mutators

    void begin();

    ofImage * colormap() { return (m_imgs.size() > 0 ? m_imgs[0] : NULL); }
    ofImage * displacemap() { return (m_imgs.size() > 1 ? m_imgs[1] : NULL); }
    ofMatrix4x4 & normalMatrix() { return m_normalMatrix; }

    void setColormap(ofImage * p_colormap) { setImage(p_colormap, 0); }
    void setColormap(const string & p_colormapPath) { setImage(p_colormapPath, 0); }
    void setDisplaceMap(ofImage * p_displacemap) { setImage(p_displacemap, 1); }
    void setDisplaceMap(const string & p_displacemapPath) { setImage(p_displacemapPath, 1); }
    void setMaximumHeight(float p_height) { m_maxHeight = p_height; }
    void setNormalMatrix(const ofMatrix4x4 & p_mat) { m_normalMatrix = p_mat; }

private:
    float m_maxHeight;
    ofMatrix4x4 m_normalMatrix;
};

}

}

#endif // OFXSHADERSFX_DISPLACEMAPSHADER_H_INCLUDED
