#version 330 core

uniform sampler2D texture;
in vec4 texc;
out vec4 fragColor;
void main(){
    gl_FragColor = texture2D(texture,texc.st);
}
