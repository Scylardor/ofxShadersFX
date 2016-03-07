#version 120
#extension GL_ARB_texture_rectangle: enable
uniform sampler2DRect tex0;
uniform sampler2DRect tex1;
varying vec2 TexCoord;
uniform float maxHeight;
void main(void) {
    TexCoord = gl_MultiTexCoord0.st;
    vec4 bumpColor = texture2DRect(tex1, TexCoord);
    float df = 0.30 * bumpColor.x + 0.59 * bumpColor.y + 0.11 * bumpColor.z;
    vec4 newVertexPos = vec4(gl_Normal * df * maxHeight, 0.0) + gl_Vertex;
    gl_Position = gl_ModelViewProjectionMatrix * newVertexPos;
}
