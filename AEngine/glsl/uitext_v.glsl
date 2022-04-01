#version 330 core

layout(location = 0) in vec2 a_VertexPosition;
layout(location = 1) in vec2 a_TexCoords;

uniform mat4 u_ViewProjMatrix;

out vec2 v_TexCoords;

void main(void)
{
    gl_Position = u_ViewProjMatrix * vec4(a_VertexPosition, 0.0, 1.0);
    v_TexCoords = a_TexCoords;
}