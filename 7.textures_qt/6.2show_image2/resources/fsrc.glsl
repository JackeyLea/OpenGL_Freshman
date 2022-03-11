#version 330 core

uniform sampler2D texture;
varying vec2 texc;
highp vec4 rgba;
void main(){
    rgba = texture2D(texture,texc.st);
    gl_FragColor = rgba;
}
