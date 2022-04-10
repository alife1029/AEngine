#version 400 core

in vec2 v_TexCoords;
in vec4 v_Color;
in float v_TexIndex;

uniform sampler2D u_Text[32];

out vec4 fragColor;

void main(void) 
{
    int texIndex = int(v_TexIndex);
    fragColor = vec4(v_Color.rgb, texture(u_Text[texIndex], v_TexCoords).r * v_Color.a);
}
