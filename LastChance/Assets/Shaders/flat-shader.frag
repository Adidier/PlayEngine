#version 330
out vec4 colour;

in vec3 vNormal;
in vec3 vECpos;
in vec2 TexCoord;

uniform sampler2D blendTexture;

vec3 ADSLightModel( in vec3 myNormal, in vec3 myPosition )
{
	const vec3 myLightPosition = vec3( 0.0 , 0.0 , 0.0 );
	const vec3 myLightAmbient = vec3( 0.3, 0.3, 0.3 );
	const vec3 myLightDiffuse = vec3( 1.0 , 1.0 , 1.0 );
	const vec3 myLightSpecular = vec3( 1.0 , 1.0 , 1.0 );
	const vec3 myMaterialAmbient = vec3( 0.3 , 0.3, 0.3 );
	const vec3 myMaterialDiffuse = vec3( 1.0 , 0.5, 0.0 );
	const vec3 myMaterialSpecular = vec3( 0.6, 0.6, 0.6 );
	const float myMaterialShininess = 0.6;
	//normal, light, view, and light reflection vectors
	vec3 norm = normalize( myNormal );
	vec3 lightv = normalize( myLightPosition - myPosition);
	vec3 viewv = normalize( vec3(0.,0.,0.) - myPosition );
	vec3 refl = reflect( vec3(0.,0.,0.) - lightv, norm );
	//ambient light computation
	vec3 ambient = myMaterialAmbient*myLightAmbient;
	//diffuse light computation
	vec3 diffuse = max(0.0, dot(lightv, norm)) * myMaterialDiffuse *myLightDiffuse;
	//Optionally you can add a diffuse attenuation term at this
	//point
	//specular light computation
	vec3 specular = vec3( 0.0, 0.0, 0.0 );
	if( dot(lightv, viewv) > 0.0)
	{
	 specular = pow(max(0.0, dot(viewv,refl)), myMaterialShininess)*myMaterialSpecular*	myLightSpecular;
	}
	return clamp( ambient + diffuse + specular, 0.0, 1.0);
}

vec4 DeleteGrenColor(in vec4 color)
{
	
	color = vec4(0,color.gb,0.0);
	return color;
}


void main()
{
	vec4 color = vec4(ADSLightModel( vNormal, vECpos), 1);
	vec4 blendColor =  texture(blendTexture, TexCoord);
	colour =  blendColor*color;
}
