#version 440 core

layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec2 in_UV;

out vec2 UV;

void main(void)
{
     gl_Position = vec4(in_Position, 1.0);
	 UV = in_UV;
}