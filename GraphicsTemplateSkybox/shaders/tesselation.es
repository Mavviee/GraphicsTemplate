#version 460

uniform mat4 mvpMatrix;

layout (triangles, equal_spacing, ccw) in;

in packet_CS
{
	vec3 vertexPos;
	vec3 vertexNormal;
	vec2 uv;
	float intensity;
}inData[];

out packet_ES
{
	vec3 vertexPos;
	vec3 vertexNormal;
	vec2 uv;
	float intensity;
}outData;

vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2)
{
    return vec2(gl_TessCoord.x) * v0 + vec2(gl_TessCoord.y) * v1 + vec2(gl_TessCoord.z) * v2;
}

vec3 interpolate3D(vec3 v0, vec3 v1, vec3 v2)
{
    return vec3(gl_TessCoord.x) * v0 + vec3(gl_TessCoord.y) * v1 + vec3(gl_TessCoord.z) * v2;
}

void main(void) {
	
	gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position) +
				  (gl_TessCoord.y * gl_in[1].gl_Position) +
				  (gl_TessCoord.z * gl_in[2].gl_Position);
	
	// sending data out,  interpolate texture data so the texture looks normal on the tesselated object 
	outData.uv = interpolate2D(inData[0].uv, inData[1].uv, inData[2].uv);
	outData.vertexNormal = interpolate3D(inData[0].vertexNormal, inData[1].vertexNormal, inData[2].vertexNormal);
	outData.vertexNormal = normalize(outData.vertexNormal);
	outData.vertexPos = interpolate3D(inData[0].vertexPos, inData[1].vertexPos, inData[2].vertexPos);
	outData.intensity = inData[0].intensity;
	
}
