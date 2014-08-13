#include "ofxShadersFX_MappingShader.h"

namespace ofxShadersFX {
namespace Mapping {

const char * MappingShader::VERTEX_SHADER_SOURCES_GLSL120[SHADERS_TYPES] = {
    "uniform sampler2D tex0;uniform sampler2D tex1;varying vec2 TexCoord;uniform float maxHeight;void main(void){TexCoord=gl_MultiTexCoord0.st;vec4 bumpColor=texture2D(tex1,TexCoord);float df=0.30*bumpColor.x+0.59*bumpColor.y+0.11*bumpColor.z;vec4 newVertexPos=vec4(gl_Normal*df*maxHeight,0.0)+gl_Vertex;gl_Position=gl_ModelViewProjectionMatrix*newVertexPos;}"
};

const char * MappingShader::FRAGMENT_SHADER_SOURCES_GLSL120[SHADERS_TYPES] = {
"uniform sampler2D tex0;uniform sampler2D tex1;varying vec2 TexCoord;void main(void){gl_FragColor=texture2D(tex0,TexCoord);}"
};

const char * MappingShader::VERTEX_SHADER_SOURCES_GLSL330[SHADERS_TYPES] = {
""
};

const char * MappingShader::FRAGMENT_SHADER_SOURCES_GLSL330[SHADERS_TYPES] = {
""
};

}
}
