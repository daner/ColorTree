#version 440 core

layout (binding = 0) uniform sampler2D texture;

out vec4 out_Color;
in vec2 UV;

void main(void)
{
	out_Color = texture2D(texture, UV);
}