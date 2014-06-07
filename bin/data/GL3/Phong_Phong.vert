#version 330

uniform mat4 modelViewProjectionMatrix; // automatically imported by OF
uniform mat4 modelViewMatrix; // automatically imported by OF
uniform mat4 normalMatrix; // the normal matrix (the inversed-then-transposed modelView matrix)
uniform vec3 cameraSpaceLightPos; // already in eye space

in vec4 position; // in local space
in vec3 normal; // in local space
out vec4 diffuse, ambient;
out vec3 vertex_normal, eyeSpaceVertexPos;

// const vec4 lightDiffuse = vec4(0.,0., 1., 1.);
// const vec4 lightSpecular = vec4(1., 1., 1., 1.);
// const vec4 lightAmbient = vec4(0.,0., 0., 1.);
// const vec4 materialDiffuse = vec4(0.8, 0.8, 0.8, 1.);
// const vec4 materialSpecular = vec4(1., 1., 1., 1.);
// const vec4 materialAmbient = vec4(0.2, 0.2, 0.2, 1.);
// const vec4 materialEmission = vec4(0., 0., 0., 1.);
// const float materialShininess = 50.0;

// void main (void)
// {
//   vertex_normal = normalize((normalMatrix * vec4(normal, 0.0)).xyz);
//   eyeSpaceVertexPos = vec3(modelViewMatrix * position);
//   diffuse = lightDiffuse * materialDiffuse;
//   ambient = lightAmbient * materialAmbient + materialEmission;
//   // ambient += gl_LightModel.ambient * gl_FrontMaterial.ambient;
//   gl_Position = modelViewProjectionMatrix * position;
// }


// const vec4 lightDiffuse = vec4(1., 0., 0., 1.);
// const vec4 lightSpecular = vec4(1., 1., 1., 1.);
// const vec4 lightAmbient = vec4(0.,0., 0., 1.);
// const float lightConstAtt = 0.0;
// const float lightLinearAtt = 0.005;
// const float lightQuadraticAtt = 0.0;
// const vec4 materialDiffuse = vec4(0.8, 0.8, 0.8, 1.);
// const vec4 materialSpecular = vec4(1., 1., 1., 1.);
// const vec4 materialAmbient = vec4(0.0, 0.0, 0.0, 1.);
// const vec4 materialEmission = vec4(0.0, 0.0, 0.0, 1.);
// const float materialShininess = 50.0;
// const vec4 globalLighting = vec4(0.0, 0.0, 0.0, 1.);


const vec4 lightDiffuse = vec4(0., 1., 0., 1.);
const vec4 lightSpecular = vec4(1., 1., 1., 1.);
const vec4 lightAmbient = vec4(0.,0., 0., 1.);
const float lightConstAtt = 0.0;
const float lightLinearAtt = 0.005;
const float lightQuadraticAtt = 0.0;
const float lightCutoff = 50.0;
const float lightExponent = 45.0;
vec3 spotDirection = vec3(0., 0., -0.707107);
const vec4 materialDiffuse = vec4(0.8, 0.8, 0.8, 1.);
const vec4 materialSpecular = vec4(1., 1., 1., 1.);
const vec4 materialAmbient = vec4(0.0, 0.0, 0.0, 1.);
const vec4 materialEmission = vec4(0.0, 0.0, 0.0, 1.);
const float materialShininess = 50.0;

void main (void)
{
  /* first transform the normal into eye space and
     normalize the result */
  vertex_normal = normalize((normalMatrix * vec4(normal, 0.0)).xyz);
  /* Compute the diffuse, ambient and globalAmbient terms */
  diffuse = lightDiffuse * materialDiffuse;
  ambient = materialAmbient * lightAmbient;
  eyeSpaceVertexPos = vec3(modelViewMatrix * position);
  gl_Position = modelViewProjectionMatrix * position;
}
