#version 330
uniform sampler2DRect tex0;
uniform sampler2DRect tex1;
uniform float blendAlpha; in vec2 myTexCoord;
out vec4 fragColor;
void main(void) {
    vec4 background = texture(tex0, myTexCoord);
    vec4 foreground = texture(tex1, myTexCoord);
    fragColor = foreground * blendAlpha + background;
}
