#version 330 core

uniform mat4 mvpMatrix;

in vec3 pos;
in vec2 texCoord;

out vec2 texc;

void main(void)
{
    texc = texCoord;
    gl_Position = mvpMatrix * vec4(pos,1);
}
