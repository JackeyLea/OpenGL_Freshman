#version 330 core

in vec4 aPos;
in vec4 aColor;
out vec4 outColor;
uniform mat4 mvpMatrix;
void main(){
    gl_Position = mvpMatrix * aPos;
    outColor=aColor;
}
