#version 120
#extension GL_ARB_texture_rectangle: enable
uniform sampler2DRect tex0;
uniform sampler2DRect tex1;
varying vec2 TexCoord;
void main(void) {
    gl_FragColor = texture2DRect(tex0, TexCoord);
}
