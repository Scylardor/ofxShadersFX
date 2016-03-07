// The MIT License (MIT)
// Copyright (c) 2016 Alexandre Baron (Scylardor)

// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef OFXSHADERSFX_ALPHABLENDINGSHADER_H_INCLUDED
#define OFXSHADERSFX_ALPHABLENDINGSHADER_H_INCLUDED

#include "ofxShadersFX_MappingShader.h"

namespace ofxShadersFX {
namespace Mapping {

class AlphaBlendingShader : public MappingShader {
public:
    AlphaBlendingShader(ofImage * p_colormap=NULL, ofImage * p_alphaBlendMap=NULL, float p_blendAlpha=0.5f);
    AlphaBlendingShader(const string & p_colormapPath, const string & p_p_alphaBlendMapPath, float p_blendAlpha=0.5f);
    ~AlphaBlendingShader();

    // Accessors

    const ofImage * colormap() const { return (m_imgs.size() > 0 ? m_imgs[0] : NULL); }
    const ofImage * alphaBlendMap() const { return (m_imgs.size() > 1 ? m_imgs[1] : NULL); }
    float blendAlpha() const { return m_blendAlpha; }


    // Mutators

    void begin();

    ofImage * colormap() { return (m_imgs.size() > 0 ? m_imgs[0] : NULL); }
    ofImage * alphaBlendMap() { return (m_imgs.size() > 1 ? m_imgs[1] : NULL); }
    float & blendAlpha() { return m_blendAlpha; }

    void setColormap(ofImage * p_colormap) { setImage(p_colormap, 0); }
    void setColormap(const string & p_colormapPath) { setImage(p_colormapPath, 0); }
    void setAlphaBlendMap(ofImage * p_alphaBlendMap) { setImage(p_alphaBlendMap, 1); }
    void setAlphaBlendMap(const string & p_alphaBlendMapPath) { setImage(p_alphaBlendMapPath, 1); }
    void setBlendAlpha(float p_blendAlpha) { m_blendAlpha = p_blendAlpha; }

private:
    float m_blendAlpha;
};

}
}

#endif // OFXSHADERSFX_ALPHABLENDINGSHADER_H_INCLUDED
