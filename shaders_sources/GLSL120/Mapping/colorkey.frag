#version 120
#extension GL_ARB_texture_rectangle: enable
uniform sampler2DRect tex0;
uniform sampler2DRect tex1;
uniform vec4 keyColor;
varying vec2 texCoord;
void main(void) {
    vec4 colorKeyColor = texture2DRect(tex1, texCoord);
    if (colorKeyColor == keyColor) {
        discard;
    }
    vec4 color = texture2DRect(tex0, texCoord);
    gl_FragColor = color;
}
