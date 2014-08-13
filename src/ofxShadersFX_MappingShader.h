#ifndef OFXSHADERSFX_MAPPINGSHADER_H_INCLUDED
#define OFXSHADERSFX_MAPPINGSHADER_H_INCLUDED

#include "ofxShadersFX.h"

namespace ofxShadersFX
{
namespace Mapping
{
typedef enum
{
    BUMP = 0,
    DISPLACEMENT,
    ALPHA_BLENDING,
    NORMAL,
    COLOR_KEY
}   MappingMethod;

typedef enum {
    PRIMARY = 0,
    SECONDARY
}   MapType;

class MappingShader : public Shader
{
public:
    MappingShader();
    ~MappingShader();

    void begin();
    void end();
    string getShader(GLenum ShaderType);

    void addMap(ofImage * map);
    void setMap(MapType type, ofImage * map);
    void setMap(MapType type, const string & map);
    void setPrimaryMap(ofImage * map);
    void setPrimaryMap(const string & map);
    void setSecondaryMap(ofImage * map);
    void setSecondaryMap(const string & map);
    void setMaps(const vector<ofImage *> & maps);
    void setParameter(const string & name, float value);
    void clearParameter(const string & name);
    void clearParameters();

    const vector<ofImage *> & maps();
    const map<string, float> & parameters();
    MappingMethod method();

protected:
    void clearMap(unsigned int index);

    // Number of maps supported by the mapping shader.
    static const unsigned int MAPS_NUMBER = 2;
    static const size_t SHADERS_TYPES = 1;
    static const char * VERTEX_SHADER_SOURCES_GLSL120[SHADERS_TYPES];
    static const char * FRAGMENT_SHADER_SOURCES_GLSL120[SHADERS_TYPES];
    static const char * VERTEX_SHADER_SOURCES_GLSL330[SHADERS_TYPES];
    static const char * FRAGMENT_SHADER_SOURCES_GLSL330[SHADERS_TYPES];
    vector<ofImage *> m_maps;
    // To track if stored ofImages have been allocated by addon or user
    // (we must not delete user-allocated images)
    bool m_selfAllocated[2];
    // Values used to give parameters to the shaders
    map<string, float> m_params;
    MappingMethod m_method;
};
}
}

#endif // OFXSHADERSFX_MAPPINGSHADER_H_INCLUDED
