#ifndef OFXSHADERSFX_DISPLACEMAPSHADER_H_INCLUDED
#define OFXSHADERSFX_DISPLACEMAPSHADER_H_INCLUDED

#include "ofxShadersFX_MappingShader.h"

namespace ofxShadersFX {
namespace Mapping {

class DisplaceMapShader : public MappingShader {
public:
    DisplaceMapShader(ofImage * p_colormap=NULL, ofImage * p_displacemap=NULL, float p_maxHeight=50.0f);
    DisplaceMapShader(const string & p_colormapPath, const string & p_displacemapPath, float p_maxHeight=50.0f);
    ~DisplaceMapShader();

    // Accessors

    const ofImage * colormap() const { return m_imgs[0]; }
    const ofImage * displacemap() const { return m_imgs[1]; }
    float maxHeight() const { return m_maxHeight; }


    // Mutators

    void begin();

    ofImage * colormap() { return m_imgs[0]; }
    ofImage * displacemap() { return m_imgs[1]; }

    void setColormap(ofImage * p_colormap) { setImage(p_colormap, 0); }
    void setColormap(const string & p_colormapPath) { setImage(p_colormapPath, 0); }
    void setDisplaceMap(ofImage * p_displacemap) { setImage(p_displacemap, 1); }
    void setDisplaceMap(const string & p_displacemapPath) { setImage(p_displacemapPath, 1); }
    void setMaximumHeight(float p_height) { m_maxHeight = p_height; }

private:
    float m_maxHeight;
};

}

}

#endif // OFXSHADERSFX_DISPLACEMAPSHADER_H_INCLUDED
