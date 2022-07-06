#version 330 core

in vec2 position;
in vec2 texCoord;
out vec4 texc;
void main(){
    gl_Position = vec4(position,0.0,1.0);
    texc = vec4(texCoord,0.0,1.0);
}
