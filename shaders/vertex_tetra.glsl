#version 330

layout(location = 0) in vec3 coord;

uniform mat4 g_model;
uniform mat4 g_view;
uniform mat4 g_projection;
uniform vec3 g_color;

out vec3 outColor;

void main(void)
{
    gl_Position  = g_projection * g_view * g_model * vec4(coord,1.0);
    outColor = g_color;
}
