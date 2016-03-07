#version 120

varying vec2 texCoord;

void main(void){
    texCoord = vec2(gl_MultiTexCoord0);
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
