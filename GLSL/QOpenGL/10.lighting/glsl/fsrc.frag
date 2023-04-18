#version 330 core

uniform sampler2D texture;
uniform bool enableLight;

in vec4 frontColor;
in vec2 texc;

void main(void)
{
    if(enableLight){
        vec3 ct,cf;
        vec4 texel;
        float at,af;

        cf = frontColor.rgb;
        af = frontColor.a;

        texel = texture2D(texture,texc);
        ct = texel.rgb;
        at = texel.a;

        gl_FragColor = vec4(ct * cf, at*af);
    }else{
        gl_FragColor = texture2D(texture,texc);
    }
}

