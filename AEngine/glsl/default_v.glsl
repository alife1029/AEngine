#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in float aTexIndex;

out vec4 vColor;
out vec2 vTexCoord;
out float vTexIndex;

uniform mat4 uViewProj;

void main() 
{
    vColor = aColor;
    vTexCoord = aTexCoord;
    vTexIndex = aTexIndex;
    gl_Position = uViewProj * vec4(aPos, 1.0);
}
