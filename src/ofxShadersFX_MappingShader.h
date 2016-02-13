#ifndef OFXSHADERSFX_MAPPINGSHADER_H_INCLUDED
#define OFXSHADERSFX_MAPPINGSHADER_H_INCLUDED

#include "ofxShadersFX.h"

namespace ofxShadersFX
{
namespace Mapping
{
enum MappingMethod {
    DISPLACEMENT = 0,
    ALPHA_BLENDING,
    COLOR_KEY,
    NORMAL, // Not Implemented
};

class MappingShader : public Shader
{
public:
    MappingShader(MappingMethod p_method);
    virtual ~MappingShader();

    void begin();
    void end();

    // Accessors

    MappingMethod method() const { return m_method; }
    const vector<ofImage *> & maps() const { return m_imgs; }

protected:

    // Accessors

    virtual string getShader(GLenum p_enum) const;


    // Mutators

    void addImage(ofImage * p_img, int p_index = -1);
    void addImage(const string & p_imgPath, int p_index = -1);

    void setImage(ofImage * p_img, int p_index);
    void setImage(const string & p_imgPath, int p_index);
	void setImage(ofTexture * p_tex, int p_index);
	void setTexture( ofTexture * p_tex, int p_index );
    void setImages(const vector<ofImage *> & p_imgs);

	void clearMaps() { m_imgs.clear(); m_texs.clear(); }

    // Attributes

    vector<ofImage *> m_imgs;
	vector< ofTexture * >m_texs;

private:
    // Mutators

    void rearrangeLists(ofImage * p_img, int p_index);
    void freeAllocatedImages();


    // Attributes

    // To track if stored ofImages have been allocated by addon or user
    // (we must not delete user-allocated images)
    vector<int> m_indicesToDelete, m_textureIndicesToDelete;
    MappingMethod m_method;

    static const size_t SHADERS_TYPES = 3; // Number of different shaders types implemented
    static const char * VERTEX_SHADER_SOURCES_GLSL120[SHADERS_TYPES];
    static const char * FRAGMENT_SHADER_SOURCES_GLSL120[SHADERS_TYPES];
    static const char * VERTEX_SHADER_SOURCES_GLSL330[SHADERS_TYPES];
    static const char * FRAGMENT_SHADER_SOURCES_GLSL330[SHADERS_TYPES];
};
}
}

#include "ofxShadersFX_DisplaceMapShader.h"
#include "ofxShadersFX_AlphaBlendingShader.h"
#include "ofxShadersFX_ColorKeyShader.h"

#endif // OFXSHADERSFX_MAPPINGSHADER_H_INCLUDED
