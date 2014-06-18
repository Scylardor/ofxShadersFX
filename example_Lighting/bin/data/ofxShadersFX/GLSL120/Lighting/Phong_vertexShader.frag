#version 120

uniform sampler2D tex;

varying vec4 ambientGlobal, diffuse, ambient, specular;

void main (void)
{
  gl_FragColor = (texture2D(tex, gl_TexCoord[0].st) * (ambientGlobal + diffuse + ambient)) + specular;
}
