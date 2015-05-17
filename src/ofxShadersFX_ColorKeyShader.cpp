#include "ofxShadersFX_ColorKeyShader.h"

namespace ofxShadersFX {
namespace Mapping {

ColorKeyShader::ColorKeyShader(ofImage * p_colorMap, ofImage * p_colorKeyMap, const ofFloatColor & p_color)
: MappingShader(COLOR_KEY) {
    setImage(p_colorMap, 0);
    setImage(p_colorKeyMap, 1);
    m_keyColor = p_color;
}

ColorKeyShader::ColorKeyShader(const string & p_colormapPath, const string & p_colorKeyMapPath, const ofFloatColor & p_color)
: MappingShader(COLOR_KEY) {
    setImage(p_colormapPath, 0);
    setImage(p_colorKeyMapPath, 1);
    m_keyColor = p_color;
}

ColorKeyShader::~ColorKeyShader() {
    //dtor
}


void ColorKeyShader::begin() {
    MappingShader::begin();
    // color key needs to set tex parameter to GL_NEAREST, so store the old value and restore it later.
    glGetTexParameteriv(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, &m_oldTexParameter);
    glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    m_shader.setUniform4f("keyColor", m_keyColor.r, m_keyColor.g, m_keyColor.b, m_keyColor.a);
}

void ColorKeyShader::end() {
    MappingShader::end();
    // Restore the old tex parameter value.
    glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, m_oldTexParameter);
}


}
}
