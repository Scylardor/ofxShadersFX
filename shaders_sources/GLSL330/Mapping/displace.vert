#version 330

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 normalMatrix; in vec4 position; in vec3 normal; in vec2 texcoord;
out vec2 texCoordXY;
uniform sampler2DRect tex0;
uniform sampler2DRect tex1;
uniform float maxHeight;
void main(void) {
    vec4 bumpColor = texture(tex1, texcoord);
    float df = 0.30 * bumpColor.x + 0.59 * bumpColor.y + 0.11 * bumpColor.z;
    vec3 vertex_normal = normalize((normalMatrix * vec4(normal, 0.0)).xyz);
    vec4 newVertexPos = vec4(normal * df * float(maxHeight), 0.0) + position;
    texCoordXY = vec2(texcoord.x, texcoord.y);
    gl_Position = modelViewProjectionMatrix * newVertexPos;
}
