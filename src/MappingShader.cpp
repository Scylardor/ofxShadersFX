#include "ofxShadersFX_MappingShader.h"

namespace ofxShadersFX
{
namespace Mapping
{

MappingShader::MappingShader(MappingMethod p_method)
    : Shader()
{
    m_imgs = vector<ofImage *>(MAPS_NUMBER, NULL);
    m_selfAllocated[0] = false;
    m_selfAllocated[1] = false;
    setMethod(p_method);
}

MappingShader::~MappingShader()
{
    for (unsigned int i = 0; i < MAPS_NUMBER; ++i)
    {
        clearMap(i);
    }
}


void MappingShader::begin()
{
    if (m_shader.isLoaded() == false)
    {
        this->reload();
    }
    Shader::begin();
    for (unsigned int i = 0; i < m_imgs.size(); ++i)
    {
        if (m_imgs[i] != NULL)
        {
            stringstream number("");

            number << i;
            m_shader.setUniformTexture(string("tex") + number.str(), (*m_imgs[i]), i+1);
            m_imgs[i]->bind();
        }
    }
    for (map<string, float>::iterator param = m_params.begin(); param != m_params.end(); ++param)
    {
        m_shader.setUniform1f(param->first, param->second);
    }

}


void MappingShader::end()
{
    Shader::end();
    for (unsigned int i = 0; i < m_imgs.size(); ++i)
    {
        if (m_imgs[i] != NULL)
        {
            m_imgs[i]->unbind();
        }
    }
}


string MappingShader::getShader(GLenum p_shaderType)
{
    const char ** shaders;
    string shader;
    int shaderIndex = 0;

    if (p_shaderType == GL_VERTEX_SHADER)
    {
        if (ofIsGLProgrammableRenderer())
        {
            shaders = MappingShader::VERTEX_SHADER_SOURCES_GLSL330;
        }
        else
        {
            shaders = MappingShader::VERTEX_SHADER_SOURCES_GLSL120;
        }
    }
    else if (p_shaderType == GL_FRAGMENT_SHADER)
    {
        if (ofIsGLProgrammableRenderer())
        {
            shaders = MappingShader::FRAGMENT_SHADER_SOURCES_GLSL330;
        }
        else
        {
            shaders = MappingShader::FRAGMENT_SHADER_SOURCES_GLSL120;
        }
    }
    shaderIndex = static_cast<int>(method());
    ofLogWarning() << "Getting shader index " << shaderIndex << endl;
    shader = string(shaders[shaderIndex]);
    ofLogWarning() << "Getting shader " << shader << endl;
    return shader;
}



void MappingShader::addMap(ofImage * p_map)
{
    unsigned int limit = MAPS_NUMBER;

    if (m_imgs.size() < limit)
    {
        m_imgs.push_back(p_map);
    }
    else
    {
        ofLogError() << "You cannot use more than " << limit << " maps" << endl;
    }
}


void MappingShader::setMap(MapType p_type, ofImage * p_map)
{
    if (p_type < MAPS_NUMBER)
    {
        clearMap(p_type);
        m_imgs[p_type] = p_map;
    }
    else
    {
        ofLogError() << "Unknown map type" << endl;
    }
}


void MappingShader::setMap(MapType p_type, const string & p_map_path)
{
    setMap(p_type, new ofImage(p_map_path));
    m_selfAllocated[p_type] = true;
}


void MappingShader::setPrimaryMap(ofImage * p_map)
{
    setMap(PRIMARY, p_map);
}

void MappingShader::setPrimaryMap(const string & p_map)
{
    setMap(PRIMARY, p_map);
}

void MappingShader::setSecondaryMap(ofImage * p_map)
{
    setMap(SECONDARY, p_map);
}

void MappingShader::setSecondaryMap(const string & p_map)
{
    setMap(SECONDARY, p_map);
}


void MappingShader::setMaps(const vector<ofImage *> & p_maps)
{
    unsigned int limit = MAPS_NUMBER;

    if (p_maps.size() <= limit)
    {
        m_imgs = p_maps;
    }
    else
    {
        ofLogError() << "You cannot use more than " << limit << " maps" << endl;
    }
}


void MappingShader::clearMap(unsigned int p_index)
{
    if (p_index < MAPS_NUMBER)
    {
        if (m_selfAllocated[p_index] == true)
        {
            delete m_imgs[p_index];
        }
        m_selfAllocated[p_index] = false;
        m_imgs[p_index] = NULL;
    }
    else
    {
        ofLogError() << "Map index out of range" << endl;
    }
}

}
}
