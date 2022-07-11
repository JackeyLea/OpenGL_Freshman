#version 330 core

in vec2 pos;
in vec2 texCoord;
out vec4 texc;

void main(void)
{
    gl_Position = vec4(pos,0.0,1.0);
    texc = vec4(texCoord,0.0,1.0);
}
