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
