#version 330

uniform sampler2DRect tex;

in vec4 ambientGlobal, diffuse, ambient, specular;
in vec2 varyingtexcoord;
//in vec4 outputColor;
out vec4 fragColor;

// in vec4 outputColor;
// out vec4 fragColor;

void main (void)
{
  fragColor = (texture(tex0, varyingtexcoord) * (ambientGlobal + diffuse + ambient)) + specular;
  //  fragColor = outputColor;
}
