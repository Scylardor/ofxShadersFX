#version 330

struct Light {
    vec4 position;
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float constant_attenuation;
    float linear_attenuation;
    float quadratic_attenuation;
    vec3 spot_direction;
    float spot_cutoff;
    float spot_cos_cutoff;
    float spot_exponent;
};

uniform Lights {
    Light light[8];
}
lights;

uniform Material {
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec4 emission;
    float shininess;
}
material;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 normalMatrix;

in vec4 position;
in vec3 normal;
in vec2 texcoord;

out vec4 eyeSpaceVertexPos, ambientGlobal;
out vec3 vertex_normal, interp_eyePos;
out vec2 varyingtexcoord;

void main() {
    ambientGlobal = material.emission;
    eyeSpaceVertexPos = modelViewMatrix * position;
    vertex_normal = normalize((normalMatrix * vec4(normal, 0.0)).xyz);
    interp_eyePos = vec3(-eyeSpaceVertexPos);
    varyingtexcoord = vec2(texcoord.x, texcoord.y);
    gl_Position = modelViewProjectionMatrix * position;
}
