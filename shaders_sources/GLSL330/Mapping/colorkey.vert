#version 330

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix; in vec4 position; in vec2 texcoord;
out vec2 texCoordXY;
void main(void) {
    texCoordXY = vec2(texcoord.x, texcoord.y);
    gl_Position = modelViewProjectionMatrix * position;
}
