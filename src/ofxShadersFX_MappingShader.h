// The MIT License (MIT)
// Copyright (c) 2016 Alexandre Baron (Scylardor)

// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

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
    void setImages(const vector<ofImage *> & p_imgs);

    void clearMaps() { m_imgs.clear(); }

    // Attributes

    vector<ofImage *> m_imgs;

private:
    // Mutators

    void rearrangeLists(ofImage * p_img, int p_index);
    void freeAllocatedImages();


    // Attributes

    // To track if stored ofImages have been allocated by addon or user
    // (we must not delete user-allocated images)
    vector<int> m_indicesToDelete;
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
