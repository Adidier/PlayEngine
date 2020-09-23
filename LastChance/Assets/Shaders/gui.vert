#version 330

layout (location = 0) in vec3 pos;

out vec2 TexCoords;

uniform mat4 view;

void main()
{
	TexCoords = vec2(pos.x, pos.y);
	gl_Position = vec4(pos, 1.0);
}