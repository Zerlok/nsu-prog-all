#version 330


struct CameraStruct
{
	vec4 position;
	vec4 direction;
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


struct TextureStruct
{
    vec2 offset;
	vec2 scale;
	float color;
	float normal;
};
const int TEXLIM = 16;


struct MaterialStruct
{
    vec4 color;
	float diffuse;
	float specular;
	float hardness;
	float textureMixing;
};


in vec4 vertexPosition;
in vec3 vertexNormal;
in vec2 vertexUV;

uniform mat4 MW;
uniform mat4 MV;
uniform mat4 MP;

uniform CameraStruct camera;
uniform LampStruct lamp;
uniform MaterialStruct material;

uniform sampler2D samples[TEXLIM];
uniform TextureStruct textures[TEXLIM];
uniform int texturesLen;
uniform float texturesMixing;

uniform float shadows;
uniform sampler2D shadowMap;
uniform float screenW;
uniform float screenH;


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


void mixTextures(
		in vec2 uv,
		in vec3 n,
		out vec4 color,
		out vec3 normal)
{
    const vec4 e = vec4(0.0, 0.0, 0.0, 0.0);
	const vec3 q = vec3(1.0, 1.0, 1.0);

    color = e;
	normal = n;

    vec3 t, b, nloc, nglob;
	vec4 texel;
	for (int i = 0; i < texturesLen; ++i)
	{
	    texel = texture2D(samples[i], uv / textures[i].scale + textures[i].offset);
		color += mix(e, texel, textures[i].color) / texturesLen;

        nloc = texel.rgb * 2.0 - 1.0;
		t = cross(n, q);
		b = cross(n, t);
		nglob = nloc.x * t + nloc.y * b + nloc.z * n;
		normal += nglob * textures[i].normal;
	}

    normal = normalize(normal);
}


out vec4 color;


void main()
{
    if (material.diffuse == 0.0f)
	{
	    color = material.color;
		return;
	}

    vec4 cameraPos = -MV * camera.position;
	vec4 lampPos = MV * lamp.position;
	vec3 lampDir = -normalize(MV * lamp.direction).xyz;

    vec4 textureColor;
	vec3 normal;
	mixTextures(vertexUV, vertexNormal, textureColor, normal);

    float lampInt;
	float specularInt;

	switch (lamp.type)
	{
	    case 1: // Point lamp light drawing.
			lampDir = normalize(lampPos.xyz - vertexPosition.xyz);
			lampInt = lampIntensity(lamp.power, lampPos, vertexPosition, normal);
			specularInt = specularIntensity(cameraPos, vertexPosition, normal, lampDir, material.hardness);
			break;

        case 2: // Directional lamp light drawing.
		    lampInt = sunIntensity(lamp.power, lampDir, normal);
			specularInt = specularIntensity(cameraPos, vertexPosition, normal, lampDir, material.hardness);
			break;

        case 3: // Spot lamp light drawing.
			vec3 dir = normalize(lampPos.xyz - vertexPosition.xyz);
			lampInt = spotRatio(dir, lampDir, lamp.ia, lamp.oa) * lampIntensity(lamp.power, lampPos, vertexPosition, normal);
			specularInt = specularIntensity(cameraPos, vertexPosition, normal, dir, material.hardness);
			break;

        case 4: // Ambient (scene background) light drawing.
		    lampInt = clamp(lamp.power, 0.0, 1.0);
			specularInt = 0.0;
			break;

        default: // Unkown lamp type.
		    lampInt = 1.0;
			specularInt = 0.0;
			textureColor = material.color;
			break;
	}

    lampInt *= material.specular;
	specularInt *= material.specular;

    color = mix(material.color, textureColor, texturesMixing) * lamp.color * (lampInt + specularInt);
	color = clamp(color, 0.0, 1.0);
}
