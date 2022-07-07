#version 330 core

in vec4 pos;
in vec4 color;

out vec4 outColor;

uniform mat4 mvpMatrix;

void main(void)
{
    gl_Position = mvpMatrix * pos;
    outColor = color;
}
