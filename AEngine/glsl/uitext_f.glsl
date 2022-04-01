#version 400 core

in vec2 v_TexCoords;

uniform sampler2D u_Text;
uniform vec4 u_TextColor;

out vec4 fragColor;

void main(void) 
{
    fragColor = vec4(u_TextColor.rgb, texture(u_Text, v_TexCoords).r * u_TextColor.a);
}
