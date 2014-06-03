#version 120

varying vec4 diffuse, ambient;
varying vec3 vertex_normal, halfVector;
 
void main()
{
    vec4 outputColor;
    vec3 normal_n, lightDir;

    lightDir = normalize(gl_LightSource[0].position.xyz); // already in eye space
    /* The ambient term will always be present */
    outputColor = ambient;
    /* a fragment shader can't write a varying variable
    hence we need a new variable to normalize them */
    normal_n = normalize(vertex_normal);
    /* compute light intensity
     * (the dot product between normal and light dir)
     */
    float intensity = max(dot(normal_n, lightDir), 0.0);
    if (intensity > 0.0) {
       vec3 halfVector_n = normalize(halfVector); // can't write a varying variable
       float NdotHV;
       vec4 specular = vec4(0.0);

        outputColor += diffuse * intensity;
	// compute Blinn-Phong specular component
        NdotHV = max(dot(normal_n, halfVector_n), 0.0);
	specular = pow(NdotHV, gl_FrontMaterial.shininess) *
		   gl_FrontMaterial.specular *
                   gl_LightSource[0].specular;
        outputColor += specular;
    }
    gl_FragColor = outputColor;
}