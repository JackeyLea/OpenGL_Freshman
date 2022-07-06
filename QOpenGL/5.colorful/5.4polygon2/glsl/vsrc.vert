#version 330 core

in vec3 pos;
in vec4 color;
out vec4 outColor;

void main(void)
{
    gl_Position = vec4(pos,1.0);
    outColor = color;
}

