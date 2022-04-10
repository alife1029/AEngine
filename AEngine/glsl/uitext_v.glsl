#version 330 core

layout(location = 0) in vec2 a_VertexPosition;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoords;
layout(location = 3) in float a_TexIndex;

uniform mat4 u_ViewProjMatrix;

out vec2 v_TexCoords;
out vec4 v_Color;
out float v_TexIndex;

void main(void)
{
    gl_Position = u_ViewProjMatrix * vec4(a_VertexPosition, 0.0, 1.0);
    v_Color = a_Color;
    v_TexCoords = a_TexCoords;
    v_TexIndex = a_TexIndex;
}
