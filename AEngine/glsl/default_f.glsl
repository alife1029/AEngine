#version 400 core

#define MAX_TEXTURES 32

in vec4 vColor;
in vec2 vTexCoord;
in float vTexIndex;

out vec4 fragColor;

uniform sampler2D uSamplers[MAX_TEXTURES];

void main()
{
    int texIndex = int(vTexIndex);
    fragColor = texture(uSamplers[texIndex], vTexCoord) * vColor;
}
