#version 330

out vec4 color;

in vec2 uv;
in vec4 light;

uniform sampler2D blendTexture;

void main()
{
color = texture(blendTexture,uv)*light;
}