#version 130


struct CameraStruct
{
	vec4 position;
	vec4 direction;
};


struct MaterialStruct
{
	vec4 color;
	float diffuse;
	float specular;
	float hardness;
};


struct LampStruct
{
	int type;
	vec4 position;
	float power;
	vec4 direction;
	vec4 color;
	float ia;
	float oa;
};


float lampIntensity(
		in float lpow,
		in vec4 lpos,
		in vec4 vpos,
		in vec3 vnor)
{
	vec3 dir = lpos.xyz - vpos.xyz;
	float dis = length(dir);
	dir = normalize(dir);
	
	return max(dot(vnor, dir), 0.0) * lpow / pow(dis, 2);	
}


float sunIntensity(
		in float lpow,
		in vec3 ldir,
		in vec3 vnor)
{
	return max(dot(vnor, ldir), 0.0) * lpow;
}


float spotRatio(
		in vec3 vdir,
		in vec3 ldir,
		in float lia,
		in float loa)
{
	return clamp((dot(vdir, ldir) - cos(loa)) / (cos(lia) - cos(loa)), 0.0, 1.0);
}


float specularIntensity(
		in vec4 cpos,
		in vec4 vpos,
		in vec3 vnor,
		in vec3 ldir,
		in float mhar)
{
	vec3 cdir = normalize(vpos - cpos).xyz;
	vec3 _ldir = reflect(ldir, vnor).xyz;
	return pow(max(dot(cdir, _ldir), 0.0), mhar);
}


vec4 mixLighting(
		in MaterialStruct mat,
		in vec4 lcol,
		in float lint,
		in float sint)
{
	vec3 color = lcol.rgb * lint * (mat.color.rgb * mat.diffuse + sint * mat.specular);
	return vec4(color, mat.color.a);
}



uniform CameraStruct camera;
uniform MaterialStruct material;
uniform LampStruct lamp;

varying vec4 vertexPosition;
varying vec3 vertexNormal;


void main()
{
	vec4 cameraPos = -gl_ModelViewMatrix * camera.position;
	vec4 lampPos = gl_ModelViewMatrix * lamp.position;
	vec3 lampDir = -normalize(gl_ModelViewMatrix * lamp.direction).xyz;
	float lampInt;
	float specularInt;
	vec4 color;

	switch (lamp.type)
	{
		// Point lamp light drawing.
		case 1:
			lampDir = normalize(lampPos.xyz - vertexPosition.xyz);
			lampInt = lampIntensity(lamp.power, lampPos, vertexPosition, vertexNormal);
			specularInt = specularIntensity(cameraPos, vertexPosition, vertexNormal, lampDir, material.hardness);
			color = mixLighting(material, lamp.color, lampInt, specularInt);
			break;

		// Directional lamp light drawing.
		case 2:
			lampInt = sunIntensity(lamp.power, lampDir, vertexNormal);
			specularInt = specularIntensity(cameraPos, vertexPosition, vertexNormal, lampDir, material.hardness);
			color = mixLighting(material, lamp.color, lampInt, specularInt);
			break;

		// Spot lamp light drawing.
		case 3:
			vec3 dir = normalize(lampPos.xyz - vertexPosition.xyz);
			lampInt = spotRatio(dir, lampDir, lamp.ia, lamp.oa) * lampIntensity(lamp.power, lampPos, vertexPosition, vertexNormal);
			specularInt = specularIntensity(cameraPos, vertexPosition, vertexNormal, dir, material.hardness);
			color = mixLighting(material, lamp.color, lampInt, specularInt);
			break;

		// Ambient (scene background) light drawing.
		case 4:
			color = material.color * lamp.color * clamp(lamp.power, 0.0, 1.0);
			color.a = material.color.a;
			break;

		default:
			color = material.color;
			break;
	}

		gl_FragColor = clamp(color, 0.0, 1.0);
}

