#version 120

varying vec4 outputColor;

void main (void)
{
  vec3 vertex_normal = normalize(gl_NormalMatrix * gl_Normal);
  vec3 lightDir = normalize(gl_LightSource[0].position.xyz);//spotDirection
//  vec3 lightDir = gl_LightSource[0].position.xyz;//spotDirection
  float intensity = max(dot(vertex_normal, lightDir), 0.0);
  vec4 diffuse, ambient, globalAmbient, specular = vec4(0.0);

  diffuse = gl_LightSource[0].diffuse *	gl_FrontMaterial.diffuse;
  if (intensity > 0.0) {
     // Blinn-Phong Specular Highlights : getting the half-vector, a vector with a direction half-way between
     // the eye vector and the light vector. Fortunately OpenGL computes it for us
     vec3 halfVector = gl_LightSource[0].halfVector.xyz;
     float NdotHV = max(dot(vertex_normal, halfVector), 0.0);
     // Calculating the Blinn-Phong specular component
     specular = pow(NdotHV, gl_FrontMaterial.shininess) * gl_FrontMaterial.specular * gl_LightSource[0].specular;
  }
  ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient + gl_FrontMaterial.emission;
  //ambient += gl_LightModel.ambient * gl_FrontMaterial.ambient;
  globalAmbient = gl_LightModel.ambient * gl_FrontMaterial.ambient;
  outputColor = intensity * diffuse + ambient + specular; // + globalAmbient ;
  outputColor.w = 1.0;
  gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
