#version 330

uniform mat4 modelViewProjectionMatrix; // automatically imported by OF
uniform mat4 modelViewMatrix; // automatically imported by OF
uniform mat4 normalMatrix; // the normal matrix (the inversed-then-transposed modelView matrix)
uniform vec3 cameraSpaceLightPos; // already in eye space

in vec4 position; // in local space
in vec3 normal; // in local space
out vec4 outputColor;

const vec4 lightDiffuse = vec4(0.,0., 1., 1.);
const vec4 lightSpecular = vec4(1., 1., 1., 1.);
const vec4 lightAmbient = vec4(0.,0., 0., 1.);
const vec4 materialDiffuse = vec4(0.8, 0.8, 0.8, 1.);
const vec4 materialSpecular = vec4(1., 1., 1., 1.);
const vec4 materialAmbient = vec4(0.2, 0.2, 0.2, 1.);
const vec4 materialEmission = vec4(0., 0., 0., 1.);
const float materialShininess = 50.0;

void main (void)
{
  vec3 vertex_normal = normalize((normalMatrix * vec4(normal, 0.0)).xyz);
  vec3 cameraSpaceVertexPos = vec3(modelViewMatrix * position);
  // lightDir = direction vector from light to vertex
  vec3 lightDir = normalize(cameraSpaceVertexPos - cameraSpaceLightPos);
  float intensity = max(dot(vertex_normal, lightDir), 0.0);
  vec4 diffuse, ambient, globalAmbient, specular = vec4(0.0);

  diffuse = lightDiffuse * materialDiffuse;
  if (intensity > 0.0) {
     // Blinn-Phong Shading : getting the half-vector, a vector with a direction half-way between
     // the eye vector and the light vector. OpenGL doesn't compute it for us anymore
     // H = Eye - L so we have to compute the vertex to eye vector
     vec3 eyeVector = normalize(-cameraSpaceVertexPos); // in eye space, eye is at (0,0,0)
//     vec3 halfVector = normalize(eyeVector - lightDir);
     vec3 halfVector = normalize(lightDir + eyeVector);
     float NdotHV = max(dot(vertex_normal, halfVector), 0.0);
    // Calculating the Blinn-Phong specular component
     specular = pow(NdotHV, materialShininess) * materialSpecular * lightSpecular;
  }
  ambient = materialAmbient * lightAmbient + materialEmission;
  outputColor = intensity * diffuse + ambient + specular;
  outputColor.w = 1.0;
  gl_Position = modelViewProjectionMatrix * position;
}
