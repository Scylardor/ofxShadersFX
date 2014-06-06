#version 330

uniform mat4 modelViewProjectionMatrix; // automatically imported by OF
uniform mat4 modelViewMatrix; // automatically imported by OF
uniform mat4 normalMatrix; // the normal matrix (the inversed-then-transposed modelView matrix)
uniform vec3 cameraSpaceLightPos; // already in eye space

in vec4 diffuse, ambient;
in vec3 vertex_normal, eyeSpaceVertexPos;
out vec4 fragColor;

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
//   vec4 outputColor = vec4(0.0);
//   vec3 normal_n, lightDir;
//   float intensity;

//   lightDir = normalize(eyeSpaceVertexPos - cameraSpaceLightPos);
//   /* The ambient term will always be present */
//   outputColor = ambient;
//   /*
//    * a fragment shader can't write a varying variable
//    * hence we need a new variable to normalize them
//    */
//   normal_n = normalize(vertex_normal);
//   /* compute light intensity
//    * (the dot product between normal and light dir)
//    */
//   intensity = max(dot(normal_n, lightDir), 0.0);
//   if (intensity > 0.0) {
//     vec3 reflection;
//     vec4 specular = vec4(0.0);
//     vec3 eyeSpaceVertexPos_n = normalize(eyeSpaceVertexPos);
//     vec3 eyeVector = normalize(-eyeSpaceVertexPos_n); // in eye space, eye is at (0,0,0)

//     outputColor += diffuse * intensity;
//     // compute Phong specular component
//     reflection = normalize((2.0 * dot(lightDir, normal_n) * normal_n) - lightDir);
//     specular = pow(max(dot(reflection, eyeVector), 0.0), materialShininess) * materialSpecular * lightSpecular;
//     outputColor += specular;
//   }
//   fragColor = outputColor;
// }

const vec4 lightDiffuse = vec4(1., 0., 0., 1.);
const vec4 lightSpecular = vec4(1., 1., 1., 1.);
const vec4 lightAmbient = vec4(0.,0., 0., 1.);
const float lightConstAtt = 0.0;
const float lightLinearAtt = 0.005;
const float lightQuadraticAtt = 0.0;
const vec4 materialDiffuse = vec4(0.8, 0.8, 0.8, 1.);
const vec4 materialSpecular = vec4(1., 1., 1., 1.);
const vec4 materialAmbient = vec4(0.0, 0.0, 0.0, 1.);
const vec4 materialEmission = vec4(0.0, 0.0, 0.0, 1.);
const float materialShininess = 50.0;
const vec4 globalLighting = vec4(0.0, 0.0, 0.0, 1.);


void main()
{
  vec4 outputColor, globalAmbient = vec4(0.0);
  vec3 normal_n, lightDir;
  float intensity;

  globalAmbient = globalLighting * materialAmbient + materialEmission;
  outputColor = globalAmbient;
  lightDir = cameraSpaceLightPos - eyeSpaceVertexPos;
  /* The global ambient term will always be present */
  outputColor = globalAmbient;
  /* a fragment shader can't write a varying variable
     hence we need a new variable to normalize them */
  normal_n = normalize(vertex_normal);
  /* compute light intensity
   * (the dot product between normal and light dir)
   */
  intensity = max(dot(normal_n, normalize(lightDir)), 0.0);
  if (intensity > 0.0) {
    vec3 reflection;
    vec4 specular = vec4(0.0);
    vec3 eyeSpaceVertexPos_n = normalize(eyeSpaceVertexPos);
    vec3 eyeVector = normalize(-eyeSpaceVertexPos_n); // in eye space, eye is at (0,0,0)
    float att, dist;

    dist = length(lightDir);
    att = 1.0 / (lightConstAtt +
		 lightLinearAtt * dist +
		 lightQuadraticAtt * dist * dist);
    outputColor += att * (diffuse * intensity + ambient);
    // compute Phong specular component
    reflection = normalize((2.0 * dot(lightDir, vertex_normal) * vertex_normal) - lightDir);
    specular = pow(max(dot(reflection, eyeVector), 0.0), materialShininess) *
      materialSpecular *
      lightSpecular;
    outputColor += att * specular;
  }
  outputColor.w = 1.0;
  fragColor = outputColor;
}
