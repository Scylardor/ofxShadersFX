#ifndef OFXSHADERSFX_MAPPINGSHADER_H_INCLUDED
#define OFXSHADERSFX_MAPPINGSHADER_H_INCLUDED

#include "ofxShadersFX.h"

namespace ofxShadersFX
{
namespace Mapping
{
enum MappingMethod {
    DISPLACEMENT = 0,
    ALPHA_BLENDING = 1,
    NORMAL,
    COLOR_KEY
};

enum MapType {
    PRIMARY = 0,
    SECONDARY
};

class MappingShader : public Shader
{
public:
    MappingShader(MappingMethod p_method=DISPLACEMENT);
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
    inline void setParameter(const string & p_name, float p_value) { m_params[p_name] = p_value; }
    inline void clearParameter(const string & p_name) { m_params.erase(p_name); }
    inline void clearParameters() { m_params.clear(); }
    inline void setMethod(MappingMethod p_method) { m_method = p_method; this->reload(); }

    inline const vector<ofImage *> & maps() const { return m_maps; }
    inline const map<string, float> & parameters() const { return m_params; }
    inline MappingMethod method() const { return m_method; }

protected:
    void clearMap(unsigned int index);

    // Number of maps supported by the mapping shader.
    static const unsigned int MAPS_NUMBER = 2;
    static const size_t SHADERS_TYPES = 2;
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
