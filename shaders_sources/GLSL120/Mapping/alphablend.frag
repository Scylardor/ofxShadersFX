#version 120
#extension GL_ARB_texture_rectangle: enable

uniform sampler2DRect tex0;
uniform sampler2DRect tex1;
uniform float blendAlpha;

void main(void) {
    vec2 texcoord = gl_TexCoord[0].xy;
    vec4 background = texture2DRect(tex0, texcoord);
    vec4 foreground = texture2DRect(tex1, texcoord);
    gl_FragColor = foreground * blendAlpha + background;
}
