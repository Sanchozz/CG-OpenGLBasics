#version 330 core

out vec4 color;
in vec3 outColor;
in vec2 outTex;

uniform sampler2D outTexture;

void main()
{
    vec4 ricardo = texture(outTexture, outTex);
    color = vec4(mix(outColor,ricardo.rgb, ricardo.a), 1.0);
}