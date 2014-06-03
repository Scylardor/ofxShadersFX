#version 330

uniform mat4 modelViewProjectionMatrix; // automatically imported by OF
uniform mat4 modelViewMatrix; // automatically imported by OF
uniform mat4 normalMatrix; // the normal matrix (the inversed-then-transposed modelView matrix)
uniform vec3 cameraSpaceLightPos; // already in eye space

in vec3 interp_normal, interp_eyeVector, eyeSpaceVertexPos;
out vec4 fragColor;

const vec4 lightDiffuse = vec4(0.,0., 1., 1.);
const vec4 lightSpecular = vec4(1., 1., 1., 1.);
const vec4 lightAmbient = vec4(0.,0., 0., 1.);
const vec4 materialDiffuse = vec4(0.8, 0.8, 0.8, 1.);
const vec4 materialSpecular = vec4(1., 1., 1., 1.);
const vec4 materialAmbient = vec4(0.2, 0.2, 0.2, 1.);
const vec4 materialEmission = vec4(0., 0., 0., 1.);
const float materialShininess = 50.0;
 
void main()
{
    vec4 outputColor = vec4(0.0);
    vec3 normal, eyeVector, lightDir;
    vec4 diffuse, ambient, globalAmbient, specular = vec4(0.0);
    float intensity;
    
    /* normalize both input vectors
     * a fragment shader can't write a varying variable
     * hence we need a new variable to normalize them
     */
    normal = normalize(interp_normal);
    eyeVector = normalize(interp_eyeVector);
    lightDir = normalize(eyeSpaceVertexPos - cameraSpaceLightPos);
    /* The ambient term will always be present */
    ambient = materialAmbient * lightAmbient + materialEmission;
    outputColor += ambient;
    /* compute light intensity
     * (the dot product between normal and light dir)
     */
    intensity = max(dot(normal, lightDir), 0.0);
    if (intensity > 0.0) {
       vec3 halfVector;
       float NdotHV;

       diffuse = lightDiffuse * materialDiffuse;
       outputColor += diffuse * intensity;
       // compute Blinn-Phong specular component
       halfVector = normalize(lightDir + eyeVector);
       NdotHV = max(dot(normal, halfVector), 0.0);
       specular = pow(NdotHV, materialShininess) *
		  materialSpecular * lightSpecular;
        outputColor += specular;
    }
    outputColor.w = 1.0;
    fragColor = outputColor;
}