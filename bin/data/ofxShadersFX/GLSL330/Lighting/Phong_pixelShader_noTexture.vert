#version 330

struct Light
{
  vec4    position;
  vec4    ambient;
  vec4    diffuse;
  vec4    specular;
  float   constant_attenuation;
  float   linear_attenuation;
  float   quadratic_attenuation;
  vec3    spot_direction;
  float   spot_cutoff;
  float   spot_cos_cutoff;
  float   spot_exponent;
};

uniform Lights
{
  Light light[8];
} lights;

uniform Material
{
  vec4    ambient;
  vec4    diffuse;
  vec4    specular;
  vec4    emission;
  float   shininess;
} material;

uniform mat4 modelViewProjectionMatrix; // automatically imported by OF
uniform mat4 modelViewMatrix; // automatically imported by OF
uniform mat4 normalMatrix; // the normal matrix (the inversed-then-transposed modelView matrix)

in vec4 position; // in local space
in vec3 normal; // in local space

out vec4 eyeSpaceVertexPos, ambientGlobal;
out vec3 vertex_normal;


void main () {
  ambientGlobal = material.emission; // no global lighting for the moment
  eyeSpaceVertexPos = modelViewMatrix * position;
  vertex_normal = normalize((normalMatrix * vec4(normal, 0.0)).xyz);
  gl_Position = modelViewProjectionMatrix * position;
}
