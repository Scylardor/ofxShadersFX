#include "ofxShadersFX_MappingShader.h"

namespace ofxShadersFX
{
namespace Mapping
{

MappingShader::MappingShader()
: Shader()
{
    m_maps.reserve(MAPS_NUMBER);
}

MappingShader::~MappingShader()
{
}

void MappingShader::begin() {
   if (m_shader.isLoaded() == false)
    {
        this->reload();
    }
    for (unsigned int i = 0; i < m_maps.size(); ++i) {
        stringstream number("");

        number << i;
        m_shader.setUniformTexture(string("tex") + number.str(), (*m_maps[i]), i+1);
        m_maps[i]->bind();
    }
    Shader::begin();
}

void MappingShader::end() {
    Shader::end();
    for (unsigned int i = 0; i < m_maps.size(); ++i) {
        m_maps[i]->unbind();
    }

}

void MappingShader::addMap(ofImage * p_map) {
    unsigned int limit = MAPS_NUMBER;

    if (m_maps.size() < limit) {
        m_maps.push_back(p_map);
    }
    else {
        ofLogError() << "You cannot use more than " << limit << " maps" << endl;
    }
}


void MappingShader::setMaps(const vector<ofImage *> & p_maps) {
    unsigned int limit = MAPS_NUMBER;

    if (p_maps.size() <= limit) {
        m_maps = p_maps;
    }
    else {
        ofLogError() << "You cannot use more than " << limit << " maps" << endl;
    }
}

const vector<ofImage *> & MappingShader::maps() {
    return m_maps;
}

MappingMethod MappingShader::method() {
    return m_method;
}


}
}
