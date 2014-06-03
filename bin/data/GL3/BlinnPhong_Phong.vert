#version 330

uniform mat4 modelViewProjectionMatrix; // automatically imported by OF
uniform mat4 modelViewMatrix; // automatically imported by OF
uniform mat4 normalMatrix; // the normal matrix (the inversed-then-transposed modelView matrix)
uniform vec3 cameraSpaceLightPos; // already in eye space

in vec4 position; // in local space
in vec3 normal; // in local space

out vec3 interp_normal, interp_eyeVector, eyeSpaceVertexPos;

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
    /* The vertex shader is only going to prepare the data that needs to be
     * interpolated, and the fragment shader will perform the colour computation
     * based on per fragment values. To compute the colour the fragment shader
     * will need to receive the following per fragment data: normal and eye vector.
     */
    eyeSpaceVertexPos = vec3(modelViewMatrix * position);
    interp_eyeVector = normalize(-eyeSpaceVertexPos); // in eye space, eye is at (0,0,0)
    interp_normal = normalize((normalMatrix * vec4(normal, 0.0)).xyz);
    gl_Position = modelViewProjectionMatrix * position;
}
