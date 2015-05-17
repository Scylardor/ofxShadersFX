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
