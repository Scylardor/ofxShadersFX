#version 120

uniform sampler2D tex;
uniform int lightsNumber;
uniform int lightsIDs[8];

varying vec4 ambientGlobal, eyeSpaceVertexPos;
varying vec3 vertex_normal;


vec4 directional_light(in int lightIndex, in vec3 normal) {
  vec3 lightDir;
  vec4 dirLightColor, diffuse, specular, ambient = vec4(0.0);;
  float intensity;

  lightDir = normalize(gl_LightSource[lightIndex].position.xyz); // that's already in eye space
  ambient = gl_FrontMaterial.ambient * gl_LightSource[lightIndex].ambient * texture2D(tex, gl_TexCoord[0].st);
  /* The ambient term of a directional light will always be present */
  dirLightColor = ambient;
  /* compute light intensity
   * (the dot product between normal and light dir)
   */
  intensity = max(dot(normal, lightDir), 0.0);
  if (intensity > 0.0) {
    vec3 halfVector_n = normalize(gl_LightSource[lightIndex].halfVector.xyz);
    float NdotHV;

    diffuse = gl_FrontMaterial.diffuse * gl_LightSource[lightIndex].diffuse;
    dirLightColor += diffuse * intensity * texture2D(tex, gl_TexCoord[0].st);
    // compute Blinn-Phong specular component
    NdotHV = max(dot(normal, halfVector_n), 0.0);
    specular = pow(NdotHV, gl_FrontMaterial.shininess) *
      gl_FrontMaterial.specular *
      gl_LightSource[lightIndex].specular;
    dirLightColor += specular;
  }
  return dirLightColor;
}


vec4 point_light(in int lightIndex, in vec3 normal) {
  vec3 lightDir;
  vec4 pointLightColor;
  float intensity, dist;

  pointLightColor = vec4(0.0);
  // Compute the light direction
  lightDir = vec3(gl_LightSource[lightIndex].position - eyeSpaceVertexPos);
  /* compute the distance to the light source */
  dist = length(lightDir);
  intensity = max(dot(normal, normalize(lightDir)), 0.0);
  if (intensity > 0.0) {
    float att, NdotHV;
    vec4 diffuse, specular, ambient = vec4(0.0);
    vec3 halfVector;

    att = 1.0 / (gl_LightSource[lightIndex].constantAttenuation +
		 gl_LightSource[lightIndex].linearAttenuation * dist +
		 gl_LightSource[lightIndex].quadraticAttenuation * dist * dist);
    diffuse = gl_FrontMaterial.diffuse * gl_LightSource[lightIndex].diffuse * texture2D(tex, gl_TexCoord[0].st);
    ambient = gl_FrontMaterial.ambient * gl_LightSource[lightIndex].ambient * texture2D(tex, gl_TexCoord[0].st);
    pointLightColor += att * (diffuse * intensity + ambient);
    // compute Blinn-Phong specular component
    halfVector = normalize(lightDir - vec3(eyeSpaceVertexPos));
    NdotHV = max(dot(normal, halfVector), 0.0);
    specular = pow(NdotHV,gl_FrontMaterial.shininess) * gl_FrontMaterial.specular *
      gl_LightSource[lightIndex].specular;
    pointLightColor += att * specular;
  }
  return pointLightColor;
}


vec4 spot_light(in int lightIndex, in vec3 normal) {
  vec3 lightDir;
  vec4 spotLightColor;
  float intensity, dist;

  spotLightColor = vec4(0.0);
  // Compute the light direction
  lightDir = vec3(gl_LightSource[lightIndex].position - eyeSpaceVertexPos);
  /* compute the distance to the light source */
  dist = length(lightDir);
  intensity = max(dot(normal, normalize(lightDir)), 0.0);
  if (intensity > 0.0) {
    float spotEffect, att, NdotHV;
    vec4 diffuse, specular, ambient = vec4(0.0);
    vec3 halfVector;

    spotEffect = dot(normalize(gl_LightSource[lightIndex].spotDirection), normalize(-lightDir));
    if (spotEffect > gl_LightSource[lightIndex].spotCosCutoff) {
      spotEffect = pow(spotEffect, gl_LightSource[lightIndex].spotExponent);
      att = spotEffect / (gl_LightSource[lightIndex].constantAttenuation +
			  gl_LightSource[lightIndex].linearAttenuation * dist +
			  gl_LightSource[lightIndex].quadraticAttenuation * dist * dist);
      diffuse = gl_FrontMaterial.diffuse * gl_LightSource[lightIndex].diffuse * texture2D(tex, gl_TexCoord[0].st);
      ambient = gl_FrontMaterial.ambient * gl_LightSource[lightIndex].ambient * texture2D(tex, gl_TexCoord[0].st);
      spotLightColor += att * (diffuse * intensity + ambient);
      // compute Blinn-Phong specular component
      halfVector = normalize(lightDir - vec3(eyeSpaceVertexPos));
      NdotHV = max(dot(normal, halfVector), 0.0);
      specular = pow(NdotHV,gl_FrontMaterial.shininess) * gl_FrontMaterial.specular *
	gl_LightSource[lightIndex].specular;
      spotLightColor += att * specular;
    }
  }
  return spotLightColor;
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


vec4 calc_lighting_color(in vec3 normal) {
  vec4 lightingColor = vec4(0.0);

  for (int i = 0; i < 8; i++) {
    if (light_is_enabled(i)) {
      if (gl_LightSource[i].position.w == 0.0) {
	lightingColor += directional_light(i, normal);
      }
      else {
	if (gl_LightSource[i].spotCutoff <= 90.0) {
	  lightingColor +=spot_light(i, normal);
	}
	else {
	  lightingColor += point_light(i, normal);
	}
      }
    }
  }
  return lightingColor;
}


void main()
{
  vec3 n;
  vec4 color = ambientGlobal;

  /* a fragment shader can't write a verying variable, hence we need
     a new variable to store the normalized interpolated normal */
  n = normalize(vertex_normal);
  color += calc_lighting_color(n);
  color.w = 1.0;
  gl_FragColor = color;
}
