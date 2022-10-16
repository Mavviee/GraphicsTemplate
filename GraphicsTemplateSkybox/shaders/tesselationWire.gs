#version 460 core

layout (triangles) in;
layout (line_strip, max_vertices = 6) out; 


in packet_ES
{
	vec3 vertexPos;
	vec3 vertexNormal;
	vec2 uv;
	float intensity;
}inData[];

out packet_GS
{
	vec3 vertexPos;
	vec3 vertexNormal;
	vec2 uv;
	float intensity;
}outData;





void main()
{
	gl_Position = gl_in[0].gl_Position;
	outData.intensity = 1.0;
	outData.uv = inData[0].uv;
	EmitVertex();

	gl_Position = gl_in[1].gl_Position;
	outData.intensity = 1.0;
	outData.uv = inData[1].uv;
	EmitVertex();
	
	EndPrimitive();

	gl_Position = gl_in[1].gl_Position;
	outData.intensity = 1.0;
	outData.uv = inData[1].uv;
	EmitVertex();

	gl_Position = gl_in[2].gl_Position;
	outData.intensity = 1.0;
	outData.uv = inData[2].uv;
	EmitVertex();
	
	EndPrimitive();

	gl_Position = gl_in[2].gl_Position;
	outData.intensity = 1.0;
	outData.uv = inData[2].uv;
	EmitVertex();

	gl_Position = gl_in[0].gl_Position;
	outData.intensity = 1.0;
	outData.uv = inData[0].uv;
	EmitVertex();
	
	EndPrimitive();	
	
}


