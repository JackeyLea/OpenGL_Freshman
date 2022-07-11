#version 330 core

uniform mat4 mvpMatrix;

in vec4 pos;
in vec2 texCoord;
out vec4 texc;

void main(void)
{
    gl_Position = mvpMatrix * pos;
    texc = vec4(texCoord,0.0,1.0);
}
