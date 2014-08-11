#ifndef OFXSHADERSFX_MAPPINGSHADER_H_INCLUDED
#define OFXSHADERSFX_MAPPINGSHADER_H_INCLUDED

#include "ofxShadersFX.h"

namespace ofxShadersFX
{
namespace Mapping
{
typedef enum {
    BUMP = 0,
    DISPLACEMENT,
    ALPHA_BLENDING,
    NORMAL,
    COLOR_KEY
}   MappingMethod;


class MappingShader : public Shader {
public:
    MappingShader();
    ~MappingShader();

    void begin();
    void end();

    void addMap(ofImage * map);
    void setMaps(const vector<ofImage *> & maps);

    const vector<ofImage *> & maps();
    MappingMethod method();

protected:
    // Number of maps supported by the mapping shader.
    static const unsigned int MAPS_NUMBER = 2;
    vector<ofImage *> m_maps;
    MappingMethod m_method;
};
}
}

#endif // OFXSHADERSFX_MAPPINGSHADER_H_INCLUDED
