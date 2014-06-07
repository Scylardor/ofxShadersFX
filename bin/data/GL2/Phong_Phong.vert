#version 120

// varying vec4 diffuse, ambient;
// varying vec3 vertex_normal, eyeSpaceVertexPos;

// void main (void)
// {
//   vec3 lightDir = normalize(gl_LightSource[0].position.xyz);//spotDirection

//     /* first transform the normal into eye space and
//     normalize the result */
//     vertex_normal = normalize(gl_NormalMatrix * gl_Normal);
//     /* pass the reflection vector to the fragment shader */
// //    reflection = normalize((2.0 * dot(lightDir, vertex_normal) * vertex_normal) - lightDir);
//     /* Compute the diffuse, ambient and globalAmbient terms */
//     diffuse = gl_LightSource[0].diffuse * gl_FrontMaterial.diffuse;
//     ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient + gl_FrontMaterial.emission;
//     // ambient += gl_LightModel.ambient * gl_FrontMaterial.ambient;
//     eyeSpaceVertexPos = vec3(gl_ModelViewMatrix * gl_Vertex);
//     gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
// }


// varying vec4 diffuse, ambient;
// varying vec3 vertex_normal, eyeSpaceVertexPos;

// void main (void)
// {
//     /* first transform the normal into eye space and
//     normalize the result */
//     vertex_normal = normalize(gl_NormalMatrix * gl_Normal);
//     /* Compute the diffuse, ambient and globalAmbient terms */
//     diffuse = gl_LightSource[0].diffuse * gl_FrontMaterial.diffuse;
//     ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;
//     eyeSpaceVertexPos = vec3(gl_ModelViewMatrix * gl_Vertex);
//     gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
// }


varying vec4 ambientGlobal, eyeSpaceVertexPos;
varying vec3 vertex_normal;

void main()
{
  /* first transform the normal into eye space and normalize the result */
  vertex_normal = normalize(gl_NormalMatrix * gl_Normal);
  /* compute the vertex position  in eye space. */
  eyeSpaceVertexPos = gl_ModelViewMatrix * gl_Vertex;
  // Global ambient lighting is computed in any case
  ambientGlobal = gl_LightModel.ambient * gl_FrontMaterial.ambient + gl_FrontMaterial.emission;
  gl_Position = ftransform();
}
