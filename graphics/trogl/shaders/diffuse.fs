#version 120


uniform vec4 meshPosition;

uniform int lampType;
uniform vec4 lampPosition;
uniform float lampPower;
uniform vec4 lampDirection;
uniform vec4 lampColor;
uniform float lampIA;
uniform float lampOA;


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
    color = clamp(color, 0.0, 1.0);
}


void directionLight(
        in vec4 vpos,
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
    color = clamp(color, 0.0, 1.0);
}


void spotLight()
{
}


void ambientLight()
{
}


void main()
{
    vec4 lampPos = gl_ModelViewMatrix * lampPosition;
    vec3 lampDir = -normalize(gl_ModelViewMatrix * lampDirection).xyz;

    switch (lampType)
    {
        // Point lamp light drawing.
	case 1:
	    pointLight(
	            vertexPosition, vertexNormal, vertexColor,
		    lampPos, lampColor, lampPower,
		    gl_FragColor
	    );
	    break;

        // Directional lamp light drawing.
	case 2:
	    directionLight(
	            vertexPosition, vertexNormal, vertexColor,
		    lampDir, lampColor, lampPower,
		    gl_FragColor
	    );
	    break;

        // Spot lamp light drawing.
	case 3:
	    spotLight();
	    break;

        // Ambient (scene background) light drawing.
	case 4:
	    ambientLight();
	    break;

        default:
	    gl_FragColor = vertexColor;
	    break;
    }
}
