#version 330 core

uniform mat4 mvpMatrix;
uniform vec4 lightPos;
uniform vec4 lightDiffuse;
uniform vec4 lightAmbient;
uniform vec4 lightModelAmbient;
uniform vec4 materialDiffuse;
uniform vec4 materialAmbient;

in vec4 pos;
in vec2 texCoord;

out vec2 texc;
out vec4 frontColor;

void main(void)
{
    vec3 lightDir;

    lightDir = normalize(vec3(lightPos));
    gl_Position = mvpMatrix * pos;
    texc = vec4(texCoord,0.0,1.0);
}
