#version 120

varying vec4 outputColor;

// void main (void)
// {
//   vec3 vertex_normal = normalize(gl_NormalMatrix * gl_Normal);
//   vec3 lightDir = normalize(gl_LightSource[0].position.xyz);//spotDirection
//   float intensity = max(dot(vertex_normal, lightDir), 0.0);
//   vec4 diffuse, ambient, globalAmbient, specular = vec4(0.0);

//   diffuse = gl_LightSource[0].diffuse *	gl_FrontMaterial.diffuse;
//   if (intensity > 0.0) {
//      // Phong Specular Highlights
//      vec3 eyeSpaceVertexPos = vec3(gl_ModelViewMatrix * gl_Vertex);
//      vec3 eyeVector = normalize(-eyeSpaceVertexPos); // in eye space, eye is at (0,0,0)
//      // For a given incident vector I and surface normal N,
//      // reflect(I, N) returns the reflection direction calculated as I - 2.0 * dot(N, I) * N,
//      // or exactly the reflection vector used by Phong shading
// //     vec3 reflexion = normalize(-reflect(lightDir, vertex_normal));
//      vec3 reflection = normalize((2.0 * dot(lightDir, vertex_normal) * vertex_normal) - lightDir);

//      specular = pow(max(dot(reflection, eyeVector), 0.0), gl_FrontMaterial.shininess) * gl_FrontMaterial.specular * gl_LightSource[0].specular;
//   }
//   ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient + gl_FrontMaterial.emission;
//   globalAmbient = gl_LightModel.ambient * gl_FrontMaterial.ambient;
//   outputColor = intensity * diffuse + ambient + specular; // + globalAmbient ;
//   outputColor.w = 1.0;
//   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
// }

void main (void)
{
  vec3 vertex_normal = normalize(gl_NormalMatrix * gl_Normal);
  vec3 eyeSpaceVertexPos = vec3(gl_ModelViewMatrix * gl_Vertex);
  vec3 lightDir = gl_LightSource[0].position.xyz - eyeSpaceVertexPos;
  vec4 diffuse, ambient, globalAmbient, specular = vec4(0.0);
  float intensity;

  globalAmbient = gl_LightModel.ambient * gl_FrontMaterial.ambient + gl_FrontMaterial.emission;
  outputColor = globalAmbient;
  intensity = max(dot(vertex_normal, normalize(lightDir)), 0.0);
  if (intensity > 0.0) {
     // Phong Specular Highlights
     vec3 eyeVector = normalize(-eyeSpaceVertexPos); // in eye space, eye is at (0,0,0)
     // For a given incident vector I and surface normal N,
     // reflect(I, N) returns the reflection direction calculated as I - 2.0 * dot(N, I) * N,
     // or exactly the reflection vector used by Phong shading
     // vec3 reflexion = normalize(-reflect(lightDir, vertex_normal));
     vec3 reflection;
     float att, dist;

     diffuse = gl_LightSource[0].diffuse * gl_FrontMaterial.diffuse;
     ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;
     dist = length(lightDir);
     att = 1.0 / (gl_LightSource[0].constantAttenuation +
		  gl_LightSource[0].linearAttenuation * dist +
		  gl_LightSource[0].quadraticAttenuation * dist * dist);
     outputColor += att * (diffuse * intensity + ambient);
     reflection = normalize((2.0 * dot(lightDir, vertex_normal) * vertex_normal) - lightDir);
     specular = pow(max(dot(reflection, eyeVector), 0.0), gl_FrontMaterial.shininess) *
     gl_FrontMaterial.specular *
     gl_LightSource[0].specular;
     outputColor += att * specular;
  }
  //  outputColor = intensity * diffuse + ambient + specular; // + globalAmbient ;
  outputColor.w = 1.0;
  gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
