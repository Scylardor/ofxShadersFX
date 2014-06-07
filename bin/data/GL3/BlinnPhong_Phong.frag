#version 330

uniform mat4 modelViewProjectionMatrix; // automatically imported by OF
uniform mat4 modelViewMatrix; // automatically imported by OF
uniform mat4 normalMatrix; // the normal matrix (the inversed-then-transposed modelView matrix)
uniform vec3 cameraSpaceLightPos; // already in eye space
uniform vec4 eyeSpaceSpotDir;
uniform float cutoff;
uniform float exponent;

// in vec3 interp_normal, interp_eyeVector, eyeSpaceVertexPos;
// out vec4 fragColor;

// const vec4 lightDiffuse = vec4(0.,0., 1., 1.);
// const vec4 lightSpecular = vec4(1., 1., 1., 1.);
// const vec4 lightAmbient = vec4(0.,0., 0., 1.);
// const vec4 materialDiffuse = vec4(0.8, 0.8, 0.8, 1.);
// const vec4 materialSpecular = vec4(1., 1., 1., 1.);
// const vec4 materialAmbient = vec4(0.2, 0.2, 0.2, 1.);
// const vec4 materialEmission = vec4(0., 0., 0., 1.);
// const float materialShininess = 50.0;

// void main()
// {
//     vec4 outputColor = vec4(0.0);
//     vec3 normal, eyeVector, lightDir;
//     vec4 diffuse, ambient, globalAmbient, specular = vec4(0.0);
//     float intensity;

//     /* normalize both input vectors
//      * a fragment shader can't write a varying variable
//      * hence we need a new variable to normalize them
//      */
//     normal = normalize(interp_normal);
//     eyeVector = normalize(interp_eyeVector);
//     lightDir = normalize(eyeSpaceVertexPos - cameraSpaceLightPos);
//     /* The ambient term will always be present */
//     ambient = materialAmbient * lightAmbient + materialEmission;
//     outputColor += ambient;
//     /* compute light intensity
//      * (the dot product between normal and light dir)
//      */
//     intensity = max(dot(normal, lightDir), 0.0);
//     if (intensity > 0.0) {
//        vec3 halfVector;
//        float NdotHV;

//        diffuse = lightDiffuse * materialDiffuse;
//        outputColor += diffuse * intensity;
//        // compute Blinn-Phong specular component
//        halfVector = normalize(lightDir + eyeVector);
//        NdotHV = max(dot(normal, halfVector), 0.0);
//        specular = pow(NdotHV, materialShininess) *
// 		  materialSpecular * lightSpecular;
//         outputColor += specular;
//     }
//     outputColor.w = 1.0;
//     fragColor = outputColor;
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

in vec3 vertex_normal, eyePos, lightDir;

out vec4 colorOut;

// void main() {
//   vec4 diffuse, ambient, globalAmbient, specular = vec4(0.0);
//   // Re-normalize the interpolated data
//   vec3 n = normalize(vertex_normal);
//   vec3 l = normalize(lightDir);
//   vec3 e = normalize(eyePos);
//   float intensity = max(dot(n,l), 0.0);

//   /* The material ambient term will always be present */
//   colorOut = materialEmission + materialAmbient;
//   if (intensity > 0.0) {
//     vec3 h = normalize(l + e);
//     float intSpec = max(dot(h,n), 0.0);
//     float dist, att;

//     dist = length(lightDir);
//     att = 1.0 / (lightConstAtt +
// 		 lightLinearAtt * dist +
// 		 lightQuadraticAtt * dist * dist);
//     diffuse = lightDiffuse * materialDiffuse;
//     ambient = materialAmbient * lightAmbient;
//     colorOut += att * (diffuse * intensity + ambient);

//     specular = pow(intSpec, materialShininess) *
//       materialSpecular * lightSpecular;
//     colorOut += att * specular;
//   }
//   colorOut.w = 1.0;
//   //colorOut = max(intensity * diffuse + specular, materialAmbient);
// }


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

void main() {
  vec4 diffuse, ambient, globalAmbient, specular = vec4(0.0);
  // Re-normalize the interpolated data
  vec3 n = normalize(vertex_normal);
  vec3 l = normalize(lightDir);
  vec3 e = normalize(eyePos);
  float intensity = max(dot(n,l), 0.0);
  float dist, att;

  /* The material ambient term will always be present */
  colorOut = materialEmission + materialAmbient;

  dist = length(lightDir);
  if (intensity > 0.0) {
    float clampedCosine;
    vec3 h = normalize(l + e);
    float intSpec = max(dot(h,n), 0.0);

    clampedCosine = dot(vec3(eyeSpaceSpotDir), normalize(-lightDir));
    if (clampedCosine > cos(radians(cutoff))) // outside of spotlight cone?
      {
	clampedCosine = pow(clampedCosine, exponent);
	att = clampedCosine / (lightConstAtt +
			       lightLinearAtt * dist +
			       lightQuadraticAtt * dist * dist);

	diffuse = lightDiffuse * materialDiffuse;
	ambient = materialAmbient * lightAmbient;
	colorOut += att * (diffuse * intensity + ambient);
	specular = pow(intSpec, materialShininess) *
	  materialSpecular * lightSpecular;
	colorOut += att * specular;
      }
  }
  colorOut.w = 1.0;
  //colorOut = max(intensity * diffuse + specular, materialAmbient);
}
