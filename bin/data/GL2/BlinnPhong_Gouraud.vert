#version 120

// varying vec4 outputColor;

// void main (void)
// {
//   vec3 vertex_normal = normalize(gl_NormalMatrix * gl_Normal);
//   vec3 lightDir = normalize(gl_LightSource[0].position.xyz);//spotDirection
//   //  vec3 lightDir = gl_LightSource[0].position.xyz;//spotDirection
//   float intensity = max(dot(vertex_normal, lightDir), 0.0);
//   vec4 diffuse, ambient, globalAmbient, specular = vec4(0.0);

//   diffuse = gl_LightSource[0].diffuse *	gl_FrontMaterial.diffuse;
//   if (intensity > 0.0) {
//     // Blinn-Phong Specular Highlights : getting the half-vector, a vector with a direction half-way between
//     // the eye vector and the light vector. Fortunately OpenGL computes it for us
//     vec3 halfVector = gl_LightSource[0].halfVector.xyz;
//     float NdotHV = max(dot(vertex_normal, halfVector), 0.0);
//     // Calculating the Blinn-Phong specular component
//     specular = pow(NdotHV, gl_FrontMaterial.shininess) * gl_FrontMaterial.specular * gl_LightSource[0].specular;
//   }
//   ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient + gl_FrontMaterial.emission;
//   //ambient += gl_LightModel.ambient * gl_FrontMaterial.ambient;
//   globalAmbient = gl_LightModel.ambient * gl_FrontMaterial.ambient;
//   outputColor = intensity * diffuse + ambient + specular; // + globalAmbient ;
//   outputColor.w = 1.0;
//   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
// }

varying vec4 color;

// void main()
// {
//   vec4 diffuse,ambientGlobal,ambient, ecPos;
//   vec3 normal,halfVector;

//   /* first transform the normal into eye space and normalize the result */
//   normal = normalize(gl_NormalMatrix * gl_Normal);
//   /* compute the vertex position  in camera space. */
//   ecPos = gl_ModelViewMatrix * gl_Vertex;
//   /* Normalize the halfVector to pass it to the fragment shader */
//   halfVector = gl_LightSource[0].halfVector.xyz;

//   /* Compute the diffuse, ambient and globalAmbient terms */
//   ambientGlobal = gl_LightModel.ambient * gl_FrontMaterial.ambient;

//   vec3 n,halfV,viewV,lightDir;
//   float NdotL,NdotHV;
//   float att, dist;


//   color = ambientGlobal;
//   /* a fragment shader can't write a verying variable, hence we need
//      a new variable to store the normalized interpolated normal */
//   n = normalize(normal);

//   // Compute the ligt direction
//   lightDir = vec3(gl_LightSource[0].position-ecPos);

//   /* compute the distance to the light source to a varying variable*/
//   dist = length(lightDir);


//   /* compute the dot product between normal and ldir */
//   NdotL = max(dot(n,normalize(lightDir)),0.0);

//   if (NdotL > 0.0) {
//     diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;
//     ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;

//     att = 1.0 / (gl_LightSource[0].constantAttenuation +
// 		 gl_LightSource[0].linearAttenuation * dist +
// 		 gl_LightSource[0].quadraticAttenuation * dist * dist);
//     color += att * (diffuse * NdotL + ambient);
//     halfV = normalize(lightDir - vec3(ecPos));
//     NdotHV = max(dot(n,halfV),0.0);
//     color += att * gl_FrontMaterial.specular *
//       gl_LightSource[0].specular *
//       pow(NdotHV,gl_FrontMaterial.shininess);
//   }
//   gl_Position = ftransform();
// }


void main()
{
  vec4 diffuse,ambientGlobal,ambient, ecPos;
  vec3 normal,halfVector;

  /* first transform the normal into eye space and normalize the result */
  normal = normalize(gl_NormalMatrix * gl_Normal);
  /* compute the vertex position  in camera space. */
  ecPos = gl_ModelViewMatrix * gl_Vertex;
  /* Normalize the halfVector to pass it to the fragment shader */
  halfVector = gl_LightSource[0].halfVector.xyz;

  /* Compute the diffuse, ambient and globalAmbient terms */
  ambientGlobal = gl_LightModel.ambient * gl_FrontMaterial.ambient;

  vec3 n,halfV,viewV,lightDir;
  float NdotL,NdotHV;
  float att, dist;


  color = ambientGlobal;
  /* a fragment shader can't write a verying variable, hence we need
     a new variable to store the normalized interpolated normal */
  n = normalize(normal);

  // Compute the ligt direction
  lightDir = vec3(gl_LightSource[0].position-ecPos);

  /* compute the distance to the light source to a varying variable*/
  dist = length(lightDir);


  /* compute the dot product between normal and ldir */
  NdotL = max(dot(n,normalize(lightDir)),0.0);

  if (NdotL > 0.0) {
    diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;
    ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;

    float spotEffect;

    spotEffect = dot(normalize(gl_LightSource[0].spotDirection), normalize(-lightDir));
    if (spotEffect > gl_LightSource[0].spotCosCutoff) {
      spotEffect = pow(spotEffect, gl_LightSource[0].spotExponent);
      att = spotEffect / (gl_LightSource[0].constantAttenuation +
			  gl_LightSource[0].linearAttenuation * dist +
			  gl_LightSource[0].quadraticAttenuation * dist * dist);

      color += att * (diffuse * NdotL + ambient);
      halfV = normalize(lightDir - vec3(ecPos));
      NdotHV = max(dot(n,halfV),0.0);
      color += att * gl_FrontMaterial.specular * gl_LightSource[0].specular * pow(NdotHV,gl_FrontMaterial.shininess);
    }
  }
  gl_Position = ftransform();
}
