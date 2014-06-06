#version 120

// varying vec4 diffuse, ambient;
// varying vec3 vertex_normal, eyeSpaceVertexPos;

// void main()
// {
//     vec4 outputColor;
//     vec3 normal_n, lightDir;

//     lightDir = normalize(gl_LightSource[0].position.xyz); // already in eye space
//     /* The ambient term will always be present */
//     outputColor = ambient;
//     /* a fragment shader can't write a varying variable
//     hence we need a new variable to normalize them */
//     normal_n = normalize(vertex_normal);
//     /* compute light intensity
//      * (the dot product between normal and light dir)
//      */
//     float intensity = max(dot(normal_n, lightDir), 0.0);
//     if (intensity > 0.0) {
//        vec3 reflection;
//        vec4 specular = vec4(0.0);
//        vec3 eyeSpaceVertexPos_n = normalize(eyeSpaceVertexPos);
//        vec3 eyeVector = normalize(-eyeSpaceVertexPos_n); // in eye space, eye is at (0,0,0)

// 	outputColor += diffuse * intensity;
// 	// compute Phong specular component
// 	reflection = normalize((2.0 * dot(lightDir, normal_n) * normal_n) - lightDir);
//      	specular = pow(max(dot(reflection, eyeVector), 0.0), gl_FrontMaterial.shininess) * gl_FrontMaterial.specular * gl_LightSource[0].specular;
//         outputColor += specular;
//     }
//     gl_FragColor = outputColor;
// }


varying vec4 diffuse, ambient;
varying vec3 vertex_normal, eyeSpaceVertexPos;

// void main()
// {
//   vec4 outputColor, globalAmbient = vec4(0.0);
//   vec3 normal_n, lightDir;
//   float intensity;

//   globalAmbient = gl_LightModel.ambient * gl_FrontMaterial.ambient + gl_FrontMaterial.emission;
//   lightDir = gl_LightSource[0].position.xyz - eyeSpaceVertexPos;
//   /* The global ambient term will always be present */
//   outputColor = globalAmbient;
//   /* a fragment shader can't write a varying variable
//      hence we need a new variable to normalize them */
//   normal_n = normalize(vertex_normal);
//   /* compute light intensity
//    * (the dot product between normal and light dir)
//    */
//   intensity = max(dot(normal_n, normalize(lightDir)), 0.0);
//   if (intensity > 0.0) {
//     vec3 reflection;
//     vec4 specular = vec4(0.0);
//     vec3 eyeSpaceVertexPos_n = normalize(eyeSpaceVertexPos);
//     vec3 eyeVector = normalize(-eyeSpaceVertexPos_n); // in eye space, eye is at (0,0,0)
//     float att, dist;

//     dist = length(lightDir);
//     att = 1.0 / (gl_LightSource[0].constantAttenuation +
// 		 gl_LightSource[0].linearAttenuation * dist +
// 		 gl_LightSource[0].quadraticAttenuation * dist * dist);
//     outputColor += att * (diffuse * intensity + ambient);
//     // compute Phong specular component
//     reflection = normalize((2.0 * dot(lightDir, vertex_normal) * vertex_normal) - lightDir);
//     specular = pow(max(dot(reflection, eyeVector), 0.0), gl_FrontMaterial.shininess) *
//       gl_FrontMaterial.specular *
//       gl_LightSource[0].specular;
//     outputColor += att * specular;
//   }
//   outputColor.w = 1.0;
//   gl_FragColor = outputColor;
// }

void main()
{
  vec4 outputColor, globalAmbient = vec4(0.0);
  vec3 normal_n, lightDir;
  float intensity;

  globalAmbient = gl_LightModel.ambient * gl_FrontMaterial.ambient + gl_FrontMaterial.emission;
  lightDir = gl_LightSource[0].position.xyz - eyeSpaceVertexPos;
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
    float spotEffect;

    spotEffect = dot(normalize(gl_LightSource[0].spotDirection), normalize(-lightDir));
    if (spotEffect > gl_LightSource[0].spotCosCutoff) {
      vec3 reflection;
      vec4 specular = vec4(0.0);
      vec3 eyeSpaceVertexPos_n = normalize(eyeSpaceVertexPos);
      vec3 eyeVector = normalize(-eyeSpaceVertexPos_n); // in eye space, eye is at (0,0,0)
      float att, dist;

      dist = length(lightDir);
      att = spotEffect / (gl_LightSource[0].constantAttenuation +
			  gl_LightSource[0].linearAttenuation * dist +
			  gl_LightSource[0].quadraticAttenuation * dist * dist);

      outputColor += att * (diffuse * intensity + ambient);
      // compute Phong specular component
      reflection = normalize((2.0 * dot(lightDir, vertex_normal) * vertex_normal) - lightDir);
      specular = pow(max(dot(reflection, eyeVector), 0.0), gl_FrontMaterial.shininess) *
	gl_FrontMaterial.specular *
      gl_LightSource[0].specular;
      outputColor += att * specular;
    }
  }
  outputColor.w = 1.0;
  gl_FragColor = outputColor;
}
