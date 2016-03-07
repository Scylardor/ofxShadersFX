#version 120
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect tex;

varying vec4 ambientGlobal, diffuse, ambient, specular;

void main(void) {
    gl_FragColor = (texture2DRect(tex, gl_TexCoord[0].st) * (ambientGlobal + diffuse + ambient)) + specular;
}
