// The MIT License (MIT)
// Copyright (c) 2016 Alexandre Baron (Scylardor)

// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "ofxShadersFX_MappingShader.h"

namespace ofxShadersFX {
namespace Mapping {

const char * MappingShader::VERTEX_SHADER_SOURCES_GLSL120[SHADERS_TYPES] = {
    // displacement map
    "#version 120\n#extension GL_ARB_texture_rectangle : enable\n\
uniform sampler2DRect tex0;uniform sampler2DRect tex1;varying vec2 TexCoord;uniform float maxHeight;void main(void){TexCoord=gl_MultiTexCoord0.st;vec4 bumpColor=texture2DRect(tex1,TexCoord);float df=0.30*bumpColor.x+0.59*bumpColor.y+0.11*bumpColor.z;vec4 newVertexPos=vec4(gl_Normal*df*maxHeight,0.0)+gl_Vertex;gl_Position=gl_ModelViewProjectionMatrix*newVertexPos;}",
    // alpha blending
    "#version 120\n#extension GL_ARB_texture_rectangle : enable\n\
void main(){gl_TexCoord[0]=gl_MultiTexCoord0;gl_Position=ftransform();}",
    // color key mapping
    "#version 120\n\
varying vec2 texCoord;void main(void){texCoord=vec2(gl_MultiTexCoord0);gl_Position=gl_ModelViewProjectionMatrix*gl_Vertex;}",
};

const char * MappingShader::FRAGMENT_SHADER_SOURCES_GLSL120[SHADERS_TYPES] = {
    // displacement map
    "#version 120\n#extension GL_ARB_texture_rectangle : enable\n\
uniform sampler2DRect tex0;uniform sampler2DRect tex1;varying vec2 TexCoord;void main(void){gl_FragColor=texture2DRect(tex0,TexCoord);}",
    // alpha blending
    "#version 120\n#extension GL_ARB_texture_rectangle : enable\n\
uniform sampler2DRect tex0;uniform sampler2DRect tex1;uniform float blendAlpha;void main(void){vec2 texcoord=gl_TexCoord[0].xy;vec4 background=texture2DRect(tex0,texcoord);vec4 foreground=texture2DRect(tex1,texcoord);gl_FragColor=foreground*blendAlpha+background;}",
    // color key mapping
    "#version 120\n#extension GL_ARB_texture_rectangle : enable\n\
uniform sampler2DRect tex0;uniform sampler2DRect tex1;uniform vec4 keyColor;varying vec2 texCoord;void main(void){vec4 colorKeyColor=texture2DRect(tex1,texCoord);if(colorKeyColor==keyColor){discard;}vec4 color=texture2DRect(tex0,texCoord);gl_FragColor=color;}",
};

const char * MappingShader::VERTEX_SHADER_SOURCES_GLSL330[SHADERS_TYPES] = {
    // displacement map
    "#version 330\n\
    uniform mat4 modelViewProjectionMatrix;uniform mat4 modelViewMatrix;uniform mat4 normalMatrix;in vec4 position;in vec3 normal;in vec2 texcoord;out vec2 texCoordXY;uniform sampler2DRect tex0;uniform sampler2DRect tex1;uniform float maxHeight;void main(void){vec4 bumpColor=texture(tex1,texcoord);float df=0.30*bumpColor.x+0.59*bumpColor.y+0.11*bumpColor.z;vec3 vertex_normal=normalize((normalMatrix*vec4(normal,0.0)).xyz);vec4 newVertexPos=vec4(normal*df*float(maxHeight),0.0)+position;texCoordXY=vec2(texcoord.x,texcoord.y);gl_Position=modelViewProjectionMatrix*newVertexPos;}",
    // alpha blending
    "#version 330\n\
uniform mat4 modelViewProjectionMatrix;uniform mat4 modelViewMatrix;in vec4 position;in vec2 texcoord;out vec2 myTexCoord;void main(){myTexCoord=vec2(texcoord.x,texcoord.y);gl_Position=modelViewProjectionMatrix*position;}",
    // color key mapping
    "#version 330\n\
uniform mat4 modelViewProjectionMatrix;uniform mat4 modelViewMatrix;in vec4 position;in vec2 texcoord;out vec2 texCoordXY;void main(void){texCoordXY=vec2(texcoord.x,texcoord.y);gl_Position=modelViewProjectionMatrix*position;}",
};

const char * MappingShader::FRAGMENT_SHADER_SOURCES_GLSL330[SHADERS_TYPES] = {
    // displacement map
    "#version 330\n\
in vec2 texCoordXY;out vec4 fragColor;uniform sampler2DRect tex0;uniform sampler2DRect tex1;void main(void){vec4 colorMap=texture(tex0,texCoordXY);fragColor=colorMap;}",
    // alpha blending
    "#version 330\n\
uniform sampler2DRect tex0;uniform sampler2DRect tex1;uniform float blendAlpha;in vec2 myTexCoord;out vec4 fragColor;void main(void){vec4 background=texture(tex0,myTexCoord);vec4 foreground=texture(tex1,myTexCoord);fragColor=foreground*blendAlpha+background;}",
    // color key mapping
    "#version 330\n\
uniform sampler2DRect tex0;uniform sampler2DRect tex1;uniform vec4 keyColor;in vec2 texCoordXY;out vec4 fragColor;void main(void){vec4 colorKeyColor=texture(tex1,texCoordXY);if(colorKeyColor==keyColor){discard;}vec4 color=texture(tex0,texCoordXY);fragColor=color;}",
};

}
}
