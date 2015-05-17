#include "ofxShadersFX_AlphaBlendingShader.h"

namespace ofxShadersFX {
namespace Mapping {

AlphaBlendingShader::AlphaBlendingShader(ofImage * p_colormap, ofImage * p_alphaBlendMap, float p_blendAlpha)
: MappingShader(ALPHA_BLENDING) {
    if (p_colormap != NULL) {
        addImage(p_colormap);
    }
    if (p_alphaBlendMap != NULL) {
        addImage(p_alphaBlendMap);
    }
    m_blendAlpha = p_blendAlpha;
}


AlphaBlendingShader::AlphaBlendingShader(const string & p_colormapPath, const string & p_alphaBlendMapPath, float p_blendAlpha)
: MappingShader(ALPHA_BLENDING) {
    addImage(p_colormapPath);
    addImage(p_alphaBlendMapPath);
    m_blendAlpha = p_blendAlpha;
}


AlphaBlendingShader::~AlphaBlendingShader() {
}

void AlphaBlendingShader::begin() {
    MappingShader::begin();
    m_shader.setUniform1f("blendAlpha", m_blendAlpha);
}

}
}
