#version 120

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
