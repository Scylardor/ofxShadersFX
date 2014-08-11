#ifndef OFXSHADERSFX_DISPLACEMAPSHADER_H_INCLUDED
#define OFXSHADERSFX_DISPLACEMAPSHADER_H_INCLUDED

#include "ofxShadersFX_MappingShader.h"

namespace ofxShadersFX {
namespace Mapping {

class DisplaceMapShader : public MappingShader {
public:
    DisplaceMapShader(ofImage * colormap=NULL, ofImage * displacemap=NULL, unsigned int maxHeight=50);
    ~DisplaceMapShader();

    ofImage * colormap();
    ofImage * displacemap();
    unsigned int maxHeight();

    void setColormap(ofImage * colormap);
    void setDisplaceMap(ofImage * displacemap);
    void setMaximumHeight(unsigned int height);

private:
    ofImage * m_colormap;
    ofImage * m_displacemap;
    unsigned int m_maxHeight;
};

}

}

#endif // OFXSHADERSFX_DISPLACEMAPSHADER_H_INCLUDED
