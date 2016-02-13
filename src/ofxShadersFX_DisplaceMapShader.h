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
	void setColorMap( ofTexture * p_colormap ) { setTexture( p_colormap, 0 ); }
    void setDisplaceMap(ofImage * p_displacemap) { setImage(p_displacemap, 1); }
    void setDisplaceMap(const string & p_displacemapPath) { setImage(p_displacemapPath, 1); }
	void setDisplaceMap( ofTexture * p_displacemapPath ) { setTexture( p_displacemapPath, 1 ); }
    void setMaximumHeight(float p_height) { m_maxHeight = p_height; }
    void setNormalMatrix(const ofMatrix4x4 & p_mat) { m_normalMatrix = p_mat; }

private:
    float m_maxHeight;
    ofMatrix4x4 m_normalMatrix;
};

}

}

#endif // OFXSHADERSFX_DISPLACEMAPSHADER_H_INCLUDED
