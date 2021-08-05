#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;
layout (location = 2) in vec3 norm;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

out vec3 vNormal;
out vec3 vECpos;
out vec2 TexCoord;

void main( )
{
	vNormal = normalize( norm );
	vECpos = ( model *  vec4(pos, 1.0) ).xyz;
	TexCoord = tex;
	gl_Position = projection * view * model * vec4(pos, 1.0);
}
