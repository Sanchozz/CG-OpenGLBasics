#version 330

layout(location = 0) in vec3 coord;
layout(location = 1) in vec3 color;

uniform mat4 g_model;
uniform mat4 g_view;
uniform mat4 g_projection;

out vec3 outColor;

void main(void)
{
    gl_Position  = g_projection * g_view * g_model * vec4(coord,1.0);
    outColor = color;
}
