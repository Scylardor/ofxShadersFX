#ifndef OFXSHADERSFX_COLORKEYSHADER_H
#define OFXSHADERSFX_COLORKEYSHADER_H

#include "ofxShadersFX_MappingShader.h"

namespace ofxShadersFX {
namespace Mapping {

class ColorKeyShader : public MappingShader {
public:
    ColorKeyShader(ofImage * p_colorMap=NULL, ofImage * p_colorKeyMap=NULL, const ofFloatColor & p_color = ofColor::black);
    ColorKeyShader(const string & p_colormapPath, const string & p_colorKeyMapPath, const ofFloatColor & p_color = ofColor::black);
    ~ColorKeyShader();

    // Accessors

    const ofImage * colormap() const { return (m_imgs.size() > 0 ? m_imgs[0] : NULL); }
    const ofImage * colorKeyMap() const { return (m_imgs.size() > 1 ? m_imgs[1] : NULL); }
    const ofFloatColor & keyColor() const { return m_keyColor; }

    // Mutators

    void begin();
    void end();

    ofImage * colormap() { return (m_imgs.size() > 0 ? m_imgs[0] : NULL); }
    ofImage * colorKeyMap() { return (m_imgs.size() > 1 ? m_imgs[1] : NULL); }
    ofFloatColor & keyColor() { return m_keyColor; }

    void setColormap(ofImage * p_colormap) { setImage(p_colormap, 0); }
    void setColormap(const string & p_colormapPath) { setImage(p_colormapPath, 0); }
    void setColorKeyMap(ofImage * p_colorKeyMap) { setImage(p_colorKeyMap, 1); }
    void setColorKeyMap(const string & p_colorKeyMapPath) { setImage(p_colorKeyMapPath, 1); }
    void setKeyColor(const ofFloatColor & p_keyColor) { m_keyColor = p_keyColor; }

private:
    GLint m_oldTexParameter;
    ofFloatColor m_keyColor;
};

}
}

#endif // OFXSHADERSFX_COLORKEYSHADER_H
