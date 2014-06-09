#version 330

uniform mat4 modelViewProjectionMatrix; // automatically imported by OF
uniform mat4 modelViewMatrix; // automatically imported by OF
uniform mat4 normalMatrix; // the normal matrix (the inversed-then-transposed modelView matrix)
uniform vec3 cameraSpaceLightPos; // already in eye space
uniform vec4 eyeSpaceSpotDir;
uniform float cutoff;
uniform float exponent;

in vec4 position; // in local space
in vec3 normal; // in local space
out vec4 outputColor;

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
//   vec3 vertex_normal = normalize((normalMatrix * vec4(normal, 0.0)).xyz);
//   vec3 cameraSpaceVertexPos = vec3(modelViewMatrix * position);
//   // lightDir = direction vector from light to vertex
//   vec3 lightDir = normalize(cameraSpaceVertexPos - cameraSpaceLightPos);
//   float intensity = max(dot(vertex_normal, lightDir), 0.0);
//   vec4 diffuse, ambient, globalAmbient, specular = vec4(0.0);

//   diffuse = lightDiffuse * materialDiffuse;
//   if (intensity > 0.0) {
//      // Blinn-Phong Shading : getting the half-vector, a vector with a direction half-way between
//      // the eye vector and the light vector. OpenGL doesn't compute it for us anymore
//      // H = Eye - L so we have to compute the vertex to eye vector
//      vec3 eyeVector = normalize(-cameraSpaceVertexPos); // in eye space, eye is at (0,0,0)
// //     vec3 halfVector = normalize(eyeVector - lightDir);
//      vec3 halfVector = normalize(lightDir + eyeVector);
//      float NdotHV = max(dot(vertex_normal, halfVector), 0.0);
//     // Calculating the Blinn-Phong specular component
//      specular = pow(NdotHV, materialShininess) * materialSpecular * lightSpecular;
//   }
//   ambient = materialAmbient * lightAmbient + materialEmission;
//   outputColor = intensity * diffuse + ambient + specular;
//   outputColor.w = 1.0;
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

// void main()
// {
//   vec4 diffuse,ambientGlobal,ambient, ecPos;
//   vec3 vertex_normal; //,halfVector

//   /* first transform the normal into eye space and normalize the result */
//   vertex_normal = normalize((normalMatrix * vec4(normal, 0.0)).xyz);
//   /* compute the vertex position  in camera space. */
//   ecPos = modelViewMatrix * position;
//   /* Normalize the halfVector to pass it to the fragment shader */
//   //  halfVector = gl_LightSource[0].halfVector.xyz;

//   /* Compute the diffuse, ambient and globalAmbient terms */
//   ambientGlobal = globalLighting * materialAmbient + materialEmission;

//   vec3 n,halfV,viewV,lightDir;
//   float NdotL,NdotHV;
//   float att, dist;


//   outputColor = ambientGlobal;
//   // Compute the ligt direction
//   lightDir = cameraSpaceLightPos - vec3(ecPos);
//   /* compute the distance to the light source to a varying variable*/
//   dist = length(lightDir);


//   /* compute the dot product between normal and ldir */
//   NdotL = max(dot(vertex_normal, normalize(lightDir)), 0.0);

//   if (NdotL > 0.0) {
//     diffuse = materialDiffuse * lightDiffuse;
//     ambient = materialAmbient * lightAmbient;

//     att = 1.0 / (lightConstAtt +
// 		 lightLinearAtt * dist +
// 		 lightQuadraticAtt * dist * dist);
//     outputColor += att * (diffuse * NdotL + ambient);
//     halfV = normalize(lightDir - vec3(ecPos));
//     NdotHV = max(dot(vertex_normal, halfV), 0.0);
//     outputColor += att * materialSpecular * lightSpecular *
//       pow(NdotHV, materialShininess);
//   }
//   gl_Position = modelViewProjectionMatrix * position;
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

void main()
{
  vec4 diffuse,ambientGlobal,ambient, ecPos;
  vec3 vertex_normal; //,halfVector

  /* first transform the normal into eye space and normalize the result */
  vertex_normal = normalize((normalMatrix * vec4(normal, 0.0)).xyz);
  /* compute the vertex position  in camera space. */
  ecPos = modelViewMatrix * position;
  /* Normalize the halfVector to pass it to the fragment shader */
  //  halfVector = gl_LightSource[0].halfVector.xyz;

  /* Compute the diffuse, ambient and globalAmbient terms */
  ambientGlobal = /* globalLighting * */ materialAmbient + materialEmission;

  vec3 n,halfV,viewV,lightDir;
  float NdotL,NdotHV;
  float att, dist;


  outputColor = ambientGlobal;
  // Compute the ligt direction
  lightDir = cameraSpaceLightPos - vec3(ecPos);
  /* compute the distance to the light source to a varying variable*/
  dist = length(lightDir);


  /* compute the dot product between normal and ldir */
  NdotL = max(dot(vertex_normal, normalize(lightDir)), 0.0);

  if (NdotL > 0.0) {
    float clampedCosine;
    vec3 h = normalize(normalize(lightDir) + normalize(vec3(ecPos)));
    float intSpec = max(dot(h, vertex_normal), 0.0);
    vec4 specular = vec4(0.0);
    vec3 halfV;
    float NdotHV;


    clampedCosine = dot(vec3(eyeSpaceSpotDir), normalize(-lightDir));
    if (clampedCosine > cos(radians(cutoff))) // outside of spotlight cone?
      {
	clampedCosine = pow(clampedCosine, exponent);
	att = clampedCosine / (lightConstAtt +
			       lightLinearAtt * dist +
			       lightQuadraticAtt * dist * dist);

	diffuse = lightDiffuse * materialDiffuse;
	ambient = materialAmbient * lightAmbient;
	outputColor += att * (diffuse * NdotL + ambient);
	halfV = normalize(lightDir - vec3(ecPos));
	NdotHV = max(dot(vertex_normal, halfV), 0.0);
	outputColor += att * materialSpecular * lightSpecular *
	  pow(NdotHV, materialShininess);

      }
  }
  gl_Position = modelViewProjectionMatrix * position;
}
