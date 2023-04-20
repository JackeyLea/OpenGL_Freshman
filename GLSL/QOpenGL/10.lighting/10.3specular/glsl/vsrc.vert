#version 330 core

uniform mat4 mvpMatrix;
uniform mat4 modelMatrix;

in vec3 pos;
in vec2 texCoord;
in vec3 a_normal;//法线向量

out vec2 texc;
out vec3 fragPos;
out vec3 normal;

void main(void)
{
    fragPos = vec3(modelMatrix * vec4(pos,1.0));
    normal = mat3(transpose(inverse(modelMatrix))) * a_normal;
    texc = texCoord;
    gl_Position = mvpMatrix * vec4(pos,1);
}
