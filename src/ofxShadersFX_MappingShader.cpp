// The MIT License (MIT)
// Copyright (c) 2016 Alexandre Baron (Scylardor)

// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "ofxShadersFX_MappingShader.h"

namespace ofxShadersFX
{
namespace Mapping
{

MappingShader::MappingShader(MappingMethod p_method)
: Shader(MAPPING), m_method(p_method) {
}


MappingShader::~MappingShader() {
    freeAllocatedImages();
}


void MappingShader::begin() {
    Shader::begin();
    for (unsigned int i = 0; i < m_imgs.size(); ++i) {
        if (m_imgs[i] != NULL) {
            stringstream number("");
            number << i;

            m_shader.setUniformTexture(string("tex") + number.str(), (*m_imgs[i]), i + 1);
            m_imgs[i]->bind();
        }
    }
}


void MappingShader::end() {
    Shader::end();
    for (unsigned int i = 0; i < m_imgs.size(); ++i) {
        if (m_imgs[i] != NULL) {
            m_imgs[i]->unbind();
        }
    }
}


string MappingShader::getShader(GLenum p_enum) const {
    const char ** shaderSources;

    if (ofIsGLProgrammableRenderer()) { // OpenGL 3.3
        if (p_enum == GL_VERTEX_SHADER) {
            shaderSources = VERTEX_SHADER_SOURCES_GLSL330;
        } else {
            shaderSources = FRAGMENT_SHADER_SOURCES_GLSL330;
        }
    } else { // OpenGL 1.2
        if (p_enum == GL_VERTEX_SHADER) {
            shaderSources = VERTEX_SHADER_SOURCES_GLSL120;
        } else {
            shaderSources = FRAGMENT_SHADER_SOURCES_GLSL120;
        }
    }
    const int shaderIndex = static_cast<int>(m_method);
    return shaderSources[shaderIndex];
}


void MappingShader::freeAllocatedImages() {
    // Free the images that have been allocated by the shader
    // e.g. when user passed a path instead of an ofImage
    for (unsigned int i = 0; i < m_indicesToDelete.size(); ++i) {
        const int imgIdxToDelete = m_indicesToDelete[i];

        delete m_imgs[imgIdxToDelete];
    }
}


void MappingShader::rearrangeLists(ofImage * p_img, int p_index) {
    m_imgs.insert(m_imgs.begin() + p_index, p_img);
    // Update the "indices to delete" array if image at target index was allocated
    vector<int>::iterator idxToDelete = find(m_indicesToDelete.begin(), m_indicesToDelete.end(), p_index);
    if (idxToDelete != m_indicesToDelete.end()) {
        (*idxToDelete)++; // The allocated image index is now shifted by 1
    }
}


void MappingShader::addImage(ofImage * p_img, int p_index) {
    rearrangeLists(p_img, p_index);
}


void MappingShader::addImage(const string & p_imgPath, int p_index) {
    ofImage * newImage = new ofImage(p_imgPath);

    rearrangeLists(newImage, p_index);
    if (p_index != -1) {
        m_indicesToDelete.push_back(p_index);
    } else {
        m_indicesToDelete.push_back(m_imgs.size() - 1);
    }
}


void MappingShader::setImage(ofImage * p_img, int p_index) {
    // Delete the image at target index if it was allocated.
    vector<int>::iterator idxToDelete = find(m_indicesToDelete.begin(), m_indicesToDelete.end(), p_index);

    if (idxToDelete != m_indicesToDelete.end()) {
        delete m_imgs[(*idxToDelete)];
        m_indicesToDelete.erase(idxToDelete); // image at this index is no longer allocated
    }

    // Replace image in place if vector is already large enough.
    const int nbImgs = static_cast<int>(m_imgs.size());
    if (p_index < nbImgs) {
        m_imgs[p_index] = p_img;
    } else {
        m_imgs.push_back(p_img);
    }
}


void MappingShader::setImage(const string & p_imgPath, int p_index) {
    ofImage * newImage = new ofImage(p_imgPath);
    // Delete the image at target index if it was allocated.
    vector<int>::iterator idxToDelete = find(m_indicesToDelete.begin(), m_indicesToDelete.end(), p_index);

    if (idxToDelete != m_indicesToDelete.end()) {
        // Delete the old image and that's all: both old and new images are allocated, so no need to change the index
        delete m_imgs[(*idxToDelete)];
    }

    m_imgs[p_index] = newImage;
}


void MappingShader::setImages(const vector<ofImage *> & p_imgs) {
    freeAllocatedImages();
    m_imgs = p_imgs;
}

} // namespace Mapping
} // namespace ofxShadersFX
