#version 120

uniform int lightsNumber;
uniform int lightsIDs[8];

varying vec4 ambientGlobal, diffuse, ambient, specular;

vec4 eyeSpaceVertexPos;


void directional_light(in int lightIndex, in vec3 normal) {
  vec3 lightDir;
  float intensity;

  lightDir = normalize(gl_LightSource[lightIndex].position.xyz); // that's already in eye space
  /* The ambient term of a directional light will always be present */
  ambient += gl_FrontMaterial.ambient * gl_LightSource[lightIndex].ambient;
  /* compute light intensity
   * (the dot product between normal and light dir)
   */
  intensity = max(dot(normal, lightDir), 0.0);
  if (intensity > 0.0) {
       vec3 reflection;
       vec3 eyeSpaceVertexPos_n = normalize(vec3(eyeSpaceVertexPos));
       vec3 eyeVector = normalize(-eyeSpaceVertexPos_n); // in eye space, eye is at (0,0,0)

       diffuse += gl_FrontMaterial.diffuse * gl_LightSource[lightIndex].diffuse * intensity;
       // compute Phong specular component
       reflection = normalize((2.0 * dot(lightDir, normal) * normal) - lightDir);
       specular += pow(max(dot(reflection, eyeVector), 0.0), gl_FrontMaterial.shininess) *
	 gl_FrontMaterial.specular * gl_LightSource[lightIndex].specular;
  }
}

void point_light(in int lightIndex, in vec3 normal) {
  vec3 lightDir;
  float intensity, dist;

  // Compute the light direction
  lightDir = vec3(gl_LightSource[lightIndex].position - eyeSpaceVertexPos);
  /* compute the distance to the light source */
  dist = length(lightDir);
  intensity = max(dot(normal, normalize(lightDir)), 0.0);
  if (intensity > 0.0) {
    vec3 reflection;
    vec3 eyeSpaceVertexPos_n = normalize(vec3(eyeSpaceVertexPos));
    vec3 eyeVector = normalize(-eyeSpaceVertexPos_n);
    float att, dist;

    dist = length(lightDir);
    att = 1.0 / (gl_LightSource[lightIndex].constantAttenuation +
		 gl_LightSource[lightIndex].linearAttenuation * dist +
		 gl_LightSource[lightIndex].quadraticAttenuation * dist * dist);
    diffuse += att * gl_FrontMaterial.diffuse * gl_LightSource[lightIndex].diffuse * intensity;
    ambient += att * gl_FrontMaterial.ambient * gl_LightSource[lightIndex].ambient;
    // compute Phong specular component
    reflection = normalize((2.0 * dot(lightDir, normal) * normal) - lightDir);
    specular += att * pow(max(dot(reflection, eyeVector), 0.0), gl_FrontMaterial.shininess) *
      gl_FrontMaterial.specular *
      gl_LightSource[lightIndex].specular;
  }
}


void spot_light(in int lightIndex, in vec3 normal) {
  vec3 lightDir;
  float intensity, dist;

  // Compute the light direction
  lightDir = vec3(gl_LightSource[lightIndex].position - eyeSpaceVertexPos);
  /* compute the distance to the light source */
  dist = length(lightDir);
  intensity = max(dot(normal, normalize(lightDir)), 0.0);
  if (intensity > 0.0) {
    float spotEffect;

    spotEffect = dot(normalize(gl_LightSource[lightIndex].spotDirection), normalize(-lightDir));
    if (spotEffect > gl_LightSource[lightIndex].spotCosCutoff) {
      vec3 reflection;
      vec3 eyeSpaceVertexPos_n = normalize(vec3(eyeSpaceVertexPos));
      vec3 eyeVector = normalize(-eyeSpaceVertexPos_n);
      float att, dist;

      spotEffect = pow(spotEffect, gl_LightSource[lightIndex].spotExponent);
      dist = length(lightDir);
      att = spotEffect / (gl_LightSource[lightIndex].constantAttenuation +
			  gl_LightSource[lightIndex].linearAttenuation * dist +
			  gl_LightSource[lightIndex].quadraticAttenuation * dist * dist);
      diffuse += att * gl_FrontMaterial.diffuse * gl_LightSource[lightIndex].diffuse * intensity;
      ambient += att * gl_FrontMaterial.ambient * gl_LightSource[lightIndex].ambient;
      // compute Phong specular component
      reflection = normalize((2.0 * dot(lightDir, normal) * normal) - lightDir);
      specular += att * pow(max(dot(reflection, eyeVector), 0.0), gl_FrontMaterial.shininess) *
	gl_FrontMaterial.specular * gl_LightSource[lightIndex].specular;
    }
  }
}


bool light_is_enabled(in int lightIndex) {
  bool enabled = false;

  for (int i = 0; i < lightsNumber; i++) {
    if (lightsIDs[i] == lightIndex) {
      enabled = true;
      break;
    }
  }
  return enabled;
}


void calc_lighting_color(in vec3 normal) {
  for (int i = 0; i < 8; i++) {
    if (light_is_enabled(i)) {
      if (gl_LightSource[i].position.w == 0.0) {
	directional_light(i, normal);
      }
      else {
	if (gl_LightSource[i].spotCutoff <= 90.0) {
	  spot_light(i, normal);
	}
	else {
	  point_light(i, normal);
	}
      }
    }
  }
}


void main()
{
  vec3 vertex_normal;
  vec4 color;

  diffuse = vec4(0.0);
  ambient = vec4(0.0);
  specular = vec4(0.0);
  /* first transform the normal into eye space and normalize the result */
  vertex_normal = normalize(gl_NormalMatrix * gl_Normal);
  /* compute the vertex position  in eye space. */
  eyeSpaceVertexPos = gl_ModelViewMatrix * gl_Vertex;
  // Global ambient lighting is computed in any case
  ambientGlobal = gl_LightModel.ambient * gl_FrontMaterial.ambient + gl_FrontMaterial.emission;
  calc_lighting_color(vertex_normal);
  gl_Position = ftransform();
}
