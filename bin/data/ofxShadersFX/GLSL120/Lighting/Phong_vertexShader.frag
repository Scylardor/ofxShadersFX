#version 120

uniform sampler2D tex;

varying vec4 ambientGlobal, diffuse, ambient, specular;

//varying vec4 fragColor;

void main (void)
{
  gl_FragColor = (texture2D(tex, gl_TexCoord[0].st) * (ambientGlobal + diffuse + ambient)) + specular;
  //  gl_FragColor = fragColor;
}
