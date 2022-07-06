#ifdef GL_ES
precision mediump int;
precision mediump float;
#endif

uniform mat4 mvpMatrix;
attribute vec4 aPos;
attribute vec2 inTexCoord;
varying vec2 texCoord;
void main()
{
    gl_Position = mvpMatrix * aPos;
    texCoord = inTexCoord;
}
