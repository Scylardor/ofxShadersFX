#version 120

varying vec4 diffuse,ambient;
varying vec3 vertex_normal, halfVector;

void main()
{
    /* first transform the normal into eye space and
    normalize the result */
    vertex_normal = normalize(gl_NormalMatrix * gl_Normal);
    /* pass the halfVector to the fragment shader */
    halfVector = gl_LightSource[0].halfVector.xyz;
    /* Compute the diffuse, ambient and globalAmbient terms */
    diffuse = gl_LightSource[0].diffuse * gl_FrontMaterial.diffuse;
    ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient + gl_FrontMaterial.emission;
    // ambient += gl_LightModel.ambient * gl_FrontMaterial.ambient;
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
