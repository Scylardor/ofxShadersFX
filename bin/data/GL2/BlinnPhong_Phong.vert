#version 120

// varying vec4 diffuse,ambient;
// varying vec3 vertex_normal, halfVector;

// void directional_light() {
//     /* first transform the normal into eye space and
//     normalize the result */
//     vertex_normal = normalize(gl_NormalMatrix * gl_Normal);
//     /* pass the halfVector to the fragment shader */
//     halfVector = gl_LightSource[0].halfVector.xyz;
//     /* Compute the diffuse, ambient and globalAmbient terms */
//     diffuse = gl_LightSource[0].diffuse * gl_FrontMaterial.diffuse;
//     ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient + gl_FrontMaterial.emission;
//     // ambient += gl_LightModel.ambient * gl_FrontMaterial.ambient;
//     gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
// }


varying vec4 diffuse,ambientGlobal,ambient, ecPos;
varying vec3 normal,halfVector;

void main()
{
  vec3 aux;

  /* first transform the normal into eye space and normalize the result */
  normal = normalize(gl_NormalMatrix * gl_Normal);

  /* compute the vertex position  in camera space. */
  ecPos = gl_ModelViewMatrix * gl_Vertex;

  /* Normalize the halfVector to pass it to the fragment shader */
  halfVector = gl_LightSource[0].halfVector.xyz;

  /* Compute the diffuse, ambient and globalAmbient terms */
  diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;
  ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;
  ambientGlobal = gl_LightModel.ambient * gl_FrontMaterial.ambient;


  gl_Position = ftransform();
}
