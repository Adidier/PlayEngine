#version 330

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal1;
out vec4 colour;

uniform sampler2D tex;

void main()
{
	vec3 lightDir = vec3(1.0,0.95,0.95);
	float intensity;
	vec4 color;
	intensity = dot(lightDir,normalize(Normal1));

	if (intensity > 0.95)
		color = vec4(1.0,0.5,0.5,1.0);
	else if (intensity > 0.5)
		color = vec4(0.6,0.3,0.3,1.0);
	else if (intensity > 0.25)
		color = vec4(0.4,0.2,0.2,1.0);
	else
		color = vec4(0.2,0.1,0.1,1.0);
	colour = texture(tex, TexCoord)*color;
}