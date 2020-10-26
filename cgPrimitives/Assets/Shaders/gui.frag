#version 330

in vec2 TexCoords;

out vec4 colour;

uniform sampler2D overlay;

void main()
{
	vec4 color;
	color = vec4(1.0,1.0,1.0,1.0);
	vec2 flipped_texcoord = vec2(1.0 - TexCoords.x, TexCoords.y);
	colour = texture(overlay, flipped_texcoord)*color;
}