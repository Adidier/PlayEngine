#version 330
out vec4 colour;

in vec4 vCol;
in vec2 TexCoord;

uniform sampler2D blendTexture;

void main()
{
	vec4 blendColor =  texture(blendTexture, TexCoord);
	colour =  blendColor*vCol;
}
