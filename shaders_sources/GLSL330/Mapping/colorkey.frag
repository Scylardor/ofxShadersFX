#version 330

uniform sampler2DRect tex0;
uniform sampler2DRect tex1;
uniform vec4 keyColor; in vec2 texCoordXY;
out vec4 fragColor;
void main(void) {
    vec4 colorKeyColor = texture(tex1, texCoordXY);
    if (colorKeyColor == keyColor) {
        discard;
    }
    vec4 color = texture(tex0, texCoordXY);
    fragColor = color;
}
