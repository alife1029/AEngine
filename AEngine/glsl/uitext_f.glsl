#version 400 core

in vec2 v_TexCoords;

uniform sampler2D u_Text;
uniform vec4 textColor;

out vec4 fragColor;

void main(void) 
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(u_Text, v_TexCoords).r);
    fragColor = textColor * sampled;
}
