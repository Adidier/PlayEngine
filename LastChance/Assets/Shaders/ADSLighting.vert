#version 330
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 uvIn;
layout (location = 2) in vec3 nom;

out vec2 uv;
out vec4 light;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

vec4 ADSLighting(in vec3 normal,in vec3 position)
{
	const vec3 lightAmbient = vec3(0.7,0.7,0.7);
	const vec3 materialAmbient = vec3(0.7,0.7,0.7);

	const vec3 lightDiffuse = vec3(0.7,0.7,0.7);
	const vec3 materialDiffuse = vec3(0.7,0.7,0.7);

	vec3 light = vec3(2.5,2.5,2);
	vec3 view = vec3(1,1,1);

	const vec3 lightSpecular = vec3(0.7,0.7,0.7);
	const vec3 materialSpecular = vec3(0.7,0.7,0.7);
	const float shininess = 0.03;

	vec3 ambient = lightAmbient * materialAmbient;
	vec3 diffuse = lightDiffuse * materialDiffuse * max(0.0, dot(normal,light));
	vec3 specular = lightSpecular * materialSpecular *pow(max(0.0, dot(view,reflect(normal,light))),shininess);

	return vec4(ambient+diffuse+specular,1.0);
}
void main()
{
	gl_Position = projection * view 
	* model * vec4(pos,1.0);
	uv = uvIn;
	light = ADSLighting(nom, pos);
}