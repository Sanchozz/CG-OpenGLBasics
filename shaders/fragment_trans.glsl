#version 330 core

out vec4 color;
in vec3 outColor;
in float trans;

void main()
{
    color = vec4(outColor, trans);
}