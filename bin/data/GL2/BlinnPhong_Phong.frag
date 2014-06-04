#version 120

// varying vec4 diffuse, ambient;
// varying vec3 vertex_normal, halfVector;

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
//        vec3 halfVector_n = normalize(halfVector); // can't write a varying variable
//        float NdotHV;
//        vec4 specular = vec4(0.0);

//         outputColor += diffuse * intensity;
// 	// compute Blinn-Phong specular component
//         NdotHV = max(dot(normal_n, halfVector_n), 0.0);
// 	specular = pow(NdotHV, gl_FrontMaterial.shininess) *
// 		   gl_FrontMaterial.specular *
//                    gl_LightSource[0].specular;
//         outputColor += specular;
//     }
//     gl_FragColor = outputColor;
// }


varying vec4 diffuse,ambientGlobal, ambient, ecPos;
varying vec3 normal,halfVector;

void main()
{
  vec3 n,halfV,viewV,lightDir;
  float NdotL,NdotHV;
  vec4 color = ambientGlobal;
  float att, dist;

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

        att = 1.0 / (gl_LightSource[0].constantAttenuation +
                gl_LightSource[0].linearAttenuation * dist +
		     gl_LightSource[0].quadraticAttenuation * dist * dist);
        color += att * (diffuse * NdotL + ambient);


	//        halfV = normalize(halfVector);
	halfV = normalize(lightDir - vec3(ecPos));
	//	halfV = normalize(gl_LightSource[0].halfVector.xyz);
        NdotHV = max(dot(n,halfV),0.0);
        color += att * gl_FrontMaterial.specular * gl_LightSource[0].specular * pow(NdotHV,gl_FrontMaterial.shininess);
  }

  gl_FragColor = color;
}
