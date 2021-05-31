#version 330

layout (location = 0) in vec3 pos;

out vec4 vCol;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

uniform vec3 color1;
uniform vec3 color2;

void main()
{

	gl_Position = projection * view * model * vec4(pos, 1.0);

	if (gl_Position.z > 0.5f)
	{
		vCol = vec4(color1, 1.0f);
	}
	else 
	{
		vCol = vec4(color2, 1.0f);
	}
}