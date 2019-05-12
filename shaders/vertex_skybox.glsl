#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 g_model;
uniform mat4 g_view;
uniform mat4 g_projection;

void main()
{
    TexCoords = aPos;
    gl_Position = g_projection * g_view * g_model * vec4(aPos, 1.0);
}  