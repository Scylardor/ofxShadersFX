#version 120

varying vec4 ambientGlobal, diffuse, ambient, specular;

void main (void)
{
  gl_FragColor = (ambientGlobal + diffuse + ambient) + specular;
}
