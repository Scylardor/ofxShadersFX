#version 120

// varying vec4 outputColor;
varying vec4 color;

void main (void)
{
  gl_FragColor = /*outputColor*/ color;
}
