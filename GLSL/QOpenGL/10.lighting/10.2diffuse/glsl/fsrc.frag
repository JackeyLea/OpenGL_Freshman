#version 330 core

uniform sampler2D texture;
uniform vec3 lightPos;
uniform vec3 lightColor;

in vec2 texc;
in vec3 fragPos;
in vec3 normal;

void main(void)
{
    //环境光
    float ambientStrength = 0.3f;//环境光强度
    vec3 ambient = ambientStrength * lightColor;

    //漫反射
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm,lightDir),0.0);
    vec3 diffuse = diff * lightColor;

    //纹理
    vec4 objectColor = texture2D(texture,texc);
    gl_FragColor = vec4(ambient + diffuse, 1.0) * objectColor;
}

