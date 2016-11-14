#version 130


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


uniform vec4 meshPosition;
uniform LampStruct lamp;


varying vec4 vertexPosition;
varying vec3 vertexNormal;
varying vec4 vertexColor;


void pointLight(
		in vec4 vpos,
		in vec3 vnor,
		in vec4 vcol,
		in vec4 lpos,
		in vec4 lcol,
		in float lpow,
		out vec4 color)
{
	vec3 dir = lpos.xyz - vpos.xyz;
	float dis = length(dir);
	dir = normalize(dir);

	vec4 dcol = lcol * max(dot(vnor, dir), 0.0) * lpow / pow(dis, 2);

	color.r = vcol.r * dcol.r;
	color.g = vcol.g * dcol.g;
	color.b = vcol.b * dcol.b;
	color.a = vcol.a;
}


void directionLight(
		in vec3 vnor,
		in vec4 vcol,
		in vec3 ldir,
		in vec4 lcol,
		in float lpow,
		out vec4 color)
{
	vec4 dcol = lcol * max(dot(vnor, ldir), 0.0) * lpow;

	color.r = vcol.r * dcol.r;
	color.g = vcol.g * dcol.g;
	color.b = vcol.b * dcol.b;
	color.a = vcol.a;
}


void spotLight(
		in vec4 vpos,
		in vec3 vnor,
		in vec4 vcol,
		in vec4 lpos,
		in vec3 ldir,
		in vec4 lcol,
		in float lpow,
		in float lia,
		in float loa,
		out vec4 color)
{
	vec3 dir = lpos.xyz - vpos.xyz;
	float dis = length(dir);
	dir = normalize(dir);
	float cosA = (dot(dir, ldir)-cos(loa)) / (cos(lia) - cos(loa));

	vec4 dcol = clamp(cosA, 0.0, 1.0) * lcol * max(dot(vnor, dir), 0.0) * lpow / pow(dis, 2);

	color.r = vcol.r * dcol.r;
	color.g = vcol.g * dcol.g;
	color.b = vcol.b * dcol.b;
	color.a = vcol.a;
}


void ambientLight(
		in vec4 vcol,
		in vec4 acol,
		in float apow,
		out vec4 color)
{
	float power = clamp(apow, 0.0, 1.0);
	color.r = vcol.r * acol.r * power;
	color.g = vcol.g * acol.g * power;
	color.b = vcol.b * acol.b * power;
	color.a = vcol.a;
}


void main()
{
	vec4 color;
	vec4 lampPos = gl_ModelViewMatrix * lamp.position;
	vec3 lampDir = -normalize(gl_ModelViewMatrix * lamp.direction).xyz;

	switch (lamp.type)
	{
		// Point lamp light drawing.
		case 1:
			pointLight(
					vertexPosition, vertexNormal, vertexColor,
					lampPos, lamp.color, lamp.power,
					color
			);
			break;

		// Directional lamp light drawing.
		case 2:
			directionLight(
					vertexNormal, vertexColor,
					lampDir, lamp.color, lamp.power,
					color
			);
			break;

		// Spot lamp light drawing.
		case 3:
			spotLight(
					vertexPosition, vertexNormal, vertexColor,
					lampPos, lampDir, lamp.color, lamp.power, lamp.ia, lamp.oa,
					color
			);
			break;

		// Ambient (scene background) light drawing.
		case 4:
			ambientLight(
					vertexColor,
					lamp.color, lamp.power,
					color
			);
			break;

		default:
			color = vertexColor;
			break;
	}

	gl_FragColor = clamp(color, 0.0, 1.0);
}
