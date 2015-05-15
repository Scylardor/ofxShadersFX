#include "ofxShadersFX_MappingShader.h"

namespace ofxShadersFX {
namespace Mapping {

const char * MappingShader::VERTEX_SHADER_SOURCES_GLSL120[SHADERS_TYPES] = {
    // displacement map
    "#version 120\n#extension GL_ARB_texture_rectangle : enable\n\
uniform sampler2DRect tex0;uniform sampler2DRect tex1;varying vec2 TexCoord;uniform float maxHeight;void main(void){TexCoord=gl_MultiTexCoord0.st;vec4 bumpColor=texture2DRect(tex1,TexCoord);float df=0.30*bumpColor.x+0.59*bumpColor.y+0.11*bumpColor.z;vec4 newVertexPos=vec4(gl_Normal*df*maxHeight,0.0)+gl_Vertex;gl_Position=gl_ModelViewProjectionMatrix*newVertexPos;}",
    // alpha blending
    // color key mapping
};

const char * MappingShader::FRAGMENT_SHADER_SOURCES_GLSL120[SHADERS_TYPES] = {
    // displacement map
    "#version 120\n#extension GL_ARB_texture_rectangle : enable\n\
uniform sampler2DRect tex0;uniform sampler2DRect tex1;varying vec2 TexCoord;void main(void){gl_FragColor=texture2DRect(tex0,TexCoord);}"
    // alpha blending
};

const char * MappingShader::VERTEX_SHADER_SOURCES_GLSL330[SHADERS_TYPES] = {
    // displacement map
    "#version 330\n\
    uniform mat4 modelViewProjectionMatrix;uniform mat4 modelViewMatrix;uniform mat4 normalMatrix;in vec4 position;in vec3 normal;in vec2 texcoord;out vec2 texCoordXY;uniform sampler2DRect tex0;uniform sampler2DRect tex1;uniform float maxHeight;void main(void){vec4 bumpColor=texture(tex1,texcoord);float df=0.30*bumpColor.x+0.59*bumpColor.y+0.11*bumpColor.z;vec3 vertex_normal=normalize((normalMatrix*vec4(normal,0.0)).xyz);vec4 newVertexPos=vec4(normal*df*float(maxHeight),0.0)+position;texCoordXY=vec2(texcoord.x,texcoord.y);gl_Position=modelViewProjectionMatrix*newVertexPos;}",
};

const char * MappingShader::FRAGMENT_SHADER_SOURCES_GLSL330[SHADERS_TYPES] = {
    // displacement map
    "#version 330\n\
in vec2 texCoordXY;out vec4 fragColor;uniform sampler2DRect tex0;uniform sampler2DRect tex1;void main(void){vec4 colorMap=texture(tex0,texCoordXY);fragColor=colorMap;}",
};

}
}
