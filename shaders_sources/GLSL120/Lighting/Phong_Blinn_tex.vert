#version 120

varying vec4 ambientGlobal, eyeSpaceVertexPos;
varying vec3 vertex_normal;

void main() {
    vertex_normal = normalize(gl_NormalMatrix * gl_Normal);
    eyeSpaceVertexPos = gl_ModelViewMatrix * gl_Vertex;
    ambientGlobal = gl_LightModel.ambient * gl_FrontMaterial.ambient + gl_FrontMaterial.emission;
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    gl_Position = ftransform();
}
