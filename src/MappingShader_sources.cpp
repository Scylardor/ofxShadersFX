#include "ofxShadersFX_MappingShader.h"

namespace ofxShadersFX {
namespace Mapping {

const char * MappingShader::VERTEX_SHADER_SOURCES_GLSL120[SHADERS_TYPES] = {
    // displacement map
    "uniform sampler2D tex0;uniform sampler2D tex1;varying vec2 TexCoord;uniform float maxHeight;void main(void){TexCoord=gl_MultiTexCoord0.st;vec4 bumpColor=texture2D(tex1,TexCoord);float df=0.30*bumpColor.x+0.59*bumpColor.y+0.11*bumpColor.z;vec4 newVertexPos=vec4(gl_Normal*df*maxHeight,0.0)+gl_Vertex;gl_Position=gl_ModelViewProjectionMatrix*newVertexPos;}",
    // alpha blending
    "void main(){gl_TexCoord[0]=gl_MultiTexCoord0;gl_Position=ftransform();}"
};

const char * MappingShader::FRAGMENT_SHADER_SOURCES_GLSL120[SHADERS_TYPES] = {
    // displacement map
    "uniform sampler2D tex0;uniform sampler2D tex1;varying vec2 TexCoord;void main(void){gl_FragColor=texture2D(tex0,TexCoord);}",
    // alpha blending
    "uniform sampler2D tex0;uniform sampler2D tex1;uniform float blendAlpha;void main(void){vec2 texcoord=gl_TexCoord[0].xy;vec4 background=texture2D(tex0,texcoord);vec4 foreground=texture2D(tex1,texcoord);gl_FragColor=foreground*blendAlpha+background;}"
 };

const char * MappingShader::VERTEX_SHADER_SOURCES_GLSL330[SHADERS_TYPES] = {
""
};

const char * MappingShader::FRAGMENT_SHADER_SOURCES_GLSL330[SHADERS_TYPES] = {
""
};

}
}
