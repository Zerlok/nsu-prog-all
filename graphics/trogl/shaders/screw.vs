#version 120

attribute vec4 position;
attribute vec4 normal;
attribute vec4 color;

uniform float alpha;
uniform vec4 trogl_objPosition;


mat3 rotationMatrix(vec3 axis, float angle)
{
	axis = normalize(axis);
	float s = sin(angle);
	float c = cos(angle);
	float nc = 1.0 - c;
	return mat3(nc * axis.x * axis.x + c,           nc * axis.x * axis.y - axis.z * s,  nc * axis.z * axis.x + axis.y * s,
				nc * axis.x * axis.y + axis.z * s,  nc * axis.y * axis.y + c,           nc * axis.y * axis.z - axis.x * s,
				nc * axis.z * axis.x - axis.y * s,  nc * axis.y * axis.z + axis.x * s,  nc * axis.z * axis.z + c);
}


void main()
{
	vec3 pos = position.xyz;
	pos -= trogl_objPosition.xyz;
	pos *= rotationMatrix(vec3(0.0, 1.0, 0.0), alpha * sin(pos.y));
	pos += trogl_objPosition.xyz;
	gl_Position = gl_ModelViewProjectionMatrix * vec4(pos, 1.0);
	gl_FrontColor = color;
}
