#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 norm;
layout (location = 3) in vec3 tangent;

out vec2 TexUV;
out vec3 VertexPos;
out vec3 Normal1;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main()
{
	TexUV = uv;
	Normal1 = norm;
	gl_Position =  projection * view * model * vec4(pos,1.0);
}
