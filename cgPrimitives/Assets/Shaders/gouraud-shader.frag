#version 330
out vec4 colour;

in vec4 vCol;
in vec2 TexCoord;

uniform sampler2D mainTex;
uniform sampler2D rTex;
uniform sampler2D gTex;
uniform sampler2D bTex;
uniform sampler2D blendTexture;

void main()
{
	vec4 blendColor =  texture(blendTexture, TexCoord);
	float mainTexture = 1-(blendColor.r+blendColor.g+blendColor.b);
	vec4 mainTextureColor = texture(mainTex,TexCoord)*mainTexture;
	vec4 rTexColor = texture(rTex,TexCoord)*blendColor.r;
	vec4 gTexColor = texture(gTex,TexCoord)*blendColor.g;
	vec4 bTexColor = texture(bTex,TexCoord)*blendColor.b;
	vec4 finalColor = mainTextureColor+rTexColor+gTexColor+bTexColor;
	colour =  finalColor*vCol;
}
