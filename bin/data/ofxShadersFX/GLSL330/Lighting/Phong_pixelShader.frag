#version 330

struct Light
{
  vec4    position;
  vec4    ambient;
  vec4    diffuse;
  vec4    specular;
  float   constant_attenuation;
  float   linear_attenuation;
  float   quadratic_attenuation;
  vec3    spot_direction;
  float   spot_cutoff;
  float   spot_cos_cutoff;
  float   spot_exponent;
};

uniform Lights
{
  Light light[8];
} lights;

uniform Material
{
  vec4    ambient;
  vec4    diffuse;
  vec4    specular;
  vec4    emission;
  float   shininess;
} material;

uniform mat4 modelViewProjectionMatrix; // automatically imported by OF
uniform mat4 modelViewMatrix; // automatically imported by OF
uniform mat4 normalMatrix; // the normal matrix (the inversed-then-transposed modelView matrix)
uniform int lightsNumber;

in vec4 eyeSpaceVertexPos, ambientGlobal;
in vec3 vertex_normal;

out vec4 fragColor;


vec4 directional_light(in int lightIndex, in vec3 normal) {
  vec4 outputColor = vec4(0.0);
  vec3 lightDir;
  vec4 diffuse, ambient, specular = vec4(0.0);
  float intensity;

  lightDir = vec3(normalize(eyeSpaceVertexPos - lights.light[lightIndex].position));
  /* The ambient term will always be present */
  ambient = material.ambient * lights.light[lightIndex].ambient;
  outputColor = ambient;
  /* compute light intensity
   * (the dot product between normal and light dir)
   */
  intensity = max(dot(normal, lightDir), 0.0);
  if (intensity > 0.0) {
    vec3 reflection;
    vec3 eyeSpaceVertexPos_n = normalize(vec3(eyeSpaceVertexPos));
    vec3 eyeVector = normalize(-eyeSpaceVertexPos_n); // in eye space, eye is at (0,0,0)

    diffuse = lights.light[lightIndex].diffuse * material.diffuse;
    outputColor += diffuse * intensity;
    // compute Phong specular component
    reflection = normalize((2.0 * dot(lightDir, normal) * normal) - lightDir);
    specular = pow(max(dot(reflection, eyeVector), 0.0), material.shininess) * material.specular * lights.light[lightIndex].specular;
    outputColor += specular;
  }
  outputColor.w = 1.0;
  return outputColor;
}


vec4 point_light(in int lightIndex, in vec3 normal) {
  vec3 lightDir;
  vec4 pointLightColor;
  float intensity, dist;

  pointLightColor = vec4(0.0);
  // Compute the light direction
  lightDir = vec3(lights.light[lightIndex].position - eyeSpaceVertexPos);
  /* compute the distance to the light source */
  dist = length(lightDir);
  intensity = max(dot(normal, normalize(lightDir)), 0.0);
  if (intensity > 0.0) {
    float att;
    vec4 diffuse, specular, ambient = vec4(0.0);
    vec3 reflection;
    vec3 eyeSpaceVertexPos_n = normalize(vec3(eyeSpaceVertexPos));
    vec3 eyeVector = normalize(-eyeSpaceVertexPos_n); // in eye space, eye is at (0,0,0)

    att = 1.0 / (lights.light[lightIndex].constant_attenuation +
		 lights.light[lightIndex].linear_attenuation * dist +
		 lights.light[lightIndex].quadratic_attenuation * dist * dist);
    diffuse = material.diffuse * lights.light[lightIndex].diffuse;
    ambient = material.ambient * lights.light[lightIndex].ambient;
    pointLightColor += att * (diffuse * intensity + ambient);
    // compute Phong specular component
    reflection = normalize((2.0 * dot(lightDir, normal) * normal) - lightDir);
    specular = pow(max(dot(reflection, eyeVector), 0.0), material.shininess) *
      material.specular * lights.light[lightIndex].specular;
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
  lightDir = vec3(lights.light[lightIndex].position - eyeSpaceVertexPos);
  /* compute the distance to the light source */
  dist = length(lightDir);
  intensity = max(dot(normal, normalize(lightDir)), 0.0);
  if (intensity > 0.0) {
    float spotEffect, att;
    vec4 diffuse, specular, ambient = vec4(0.0);
    vec3 reflection;
    vec3 eyeSpaceVertexPos_n = normalize(vec3(eyeSpaceVertexPos));
    vec3 eyeVector = normalize(-eyeSpaceVertexPos_n); // in eye space, eye is at (0,0,0)

    spotEffect = dot(normalize(lights.light[lightIndex].spot_direction), normalize(-lightDir));
    if (spotEffect > lights.light[lightIndex].spot_cos_cutoff) {
      spotEffect = pow(spotEffect, lights.light[lightIndex].spot_exponent);
      att = spotEffect / (lights.light[lightIndex].constant_attenuation +
			  lights.light[lightIndex].linear_attenuation * dist +
			  lights.light[lightIndex].quadratic_attenuation * dist * dist);
      diffuse = material.diffuse * lights.light[lightIndex].diffuse;
      ambient = material.ambient * lights.light[lightIndex].ambient;
      spotLightColor += att * (diffuse * intensity + ambient);
      // compute Phong specular component
      reflection = normalize((2.0 * dot(lightDir, normal) * normal) - lightDir);
      specular = pow(max(dot(reflection, eyeVector), 0.0), material.shininess) *
	material.specular *
	lights.light[lightIndex].specular;
      spotLightColor += att * specular;
    }
  }
  return spotLightColor;
}


vec4 calc_lighting_color(in vec3 normal) {
  vec4 lightingColor = vec4(0.0);

  for (int i = 0; i < lightsNumber; i++) {
    // position is a vec4 because the fourth component (w) is important.
    // It is usual to deal with vec4's even for 3D position for convenience
    // for transformations with mat4. Hence, we set the w to 1.0 when it's
    // really a position for the transformations to work. Since a directional
    // light's position is more a direction (i.e. a vector) than a real position,
    // that's why it allows us to recognize them.
    if (lights.light[i].position.w == 0.0) {
      lightingColor += directional_light(i, normal);
    }
    else {
      if (lights.light[i].spot_cutoff <= 90.0) {
	lightingColor += spot_light(i, normal);
      }
      else {
	lightingColor += point_light(i, normal);
      }
    }
  }
  return lightingColor;
}

void main()
{
  vec3 n;

  fragColor = ambientGlobal;
  /* a fragment shader can't write an in variable, hence we need
     a new variable to store the normalized interpolated normal */
  n = normalize(vertex_normal);
  fragColor += calc_lighting_color(n);
  fragColor.w = 1.0;
}
