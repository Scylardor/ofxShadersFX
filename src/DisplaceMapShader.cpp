#include "ofxShadersFX_DisplaceMapShader.h"

namespace ofxShadersFX {
namespace Mapping {

DisplaceMapShader::DisplaceMapShader(ofImage * p_colormap, ofImage * p_displacemap, unsigned int p_maxHeight)
: MappingShader()
{
    addMap(p_colormap);
    addMap(p_displacemap);
    m_maxHeight = p_maxHeight;
}

DisplaceMapShader::~DisplaceMapShader() {

}

ofImage * DisplaceMapShader::colormap() {
    return m_maps[0];
}

ofImage * DisplaceMapShader::displacemap() {
    return m_maps[1];
}

unsigned int DisplaceMapShader::maxHeight() {
    return m_maxHeight;
}

void DisplaceMapShader::setColormap(ofImage * p_colormap) {
    m_maps[0] = p_colormap;
}

void DisplaceMapShader::setDisplaceMap(ofImage * p_displacemap) {
    m_maps[1] = p_displacemap;
}

void DisplaceMapShader::setMaximumHeight(unsigned int p_height) {
    m_maxHeight = p_height;
}

}


}
