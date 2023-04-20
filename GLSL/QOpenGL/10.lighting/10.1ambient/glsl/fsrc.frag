#version 330 core

uniform sampler2D texture;
uniform vec3 lightColor;

in vec2 texc;

void main(void)
{
    //环境光
    float ambientStrength = 0.3f;//环境光强度
    vec3 ambient = ambientStrength * lightColor;

    //纹理
    vec4 objectColor = texture2D(texture,texc);
    gl_FragColor = vec4(ambient , 1.0) * objectColor;
}

