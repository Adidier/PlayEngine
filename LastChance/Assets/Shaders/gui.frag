#version 330

in vec2 TexCoords;

out vec4 colour;

uniform sampler2D skybox;

void main()
{
	vec4 color;
	color = vec4(1.0,1.0,1.0,1.0);
	colour = texture(skybox, TexCoords)*color;
}