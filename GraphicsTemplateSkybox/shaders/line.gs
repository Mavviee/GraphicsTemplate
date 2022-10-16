#version 450 core

layout (triangles) in;
layout (line_strip, max_vertices = 3) out; // use line_strip rendering instead of trianlges to get a wireframe 
in GSPacket
{
	float intensity;
	vec2  uv;
	vec3  n;
}inputVertex[];

out FSPacket
{
	float intensity;
	vec2  uv;
}outVertex;



void main() // draws line between the points to get wireframed look
{
	gl_Position = gl_in[0].gl_Position; // draw first line - start point
	outVertex.intensity = 1.0;
	EmitVertex();

	gl_Position = gl_in[1].gl_Position; // draw first line -  end point 
	outVertex.intensity = 1.0;
	EmitVertex();
	
	EndPrimitive();

	gl_Position = gl_in[1].gl_Position; // draw second line
	outVertex.intensity = 1.0;
	EmitVertex();

	gl_Position = gl_in[2].gl_Position;
	outVertex.intensity = 1.0;
	EmitVertex();
	
	EndPrimitive();

	gl_Position = gl_in[2].gl_Position; // draw third line
	outVertex.intensity = 1.0;
	EmitVertex();

	gl_Position = gl_in[0].gl_Position;
	outVertex.intensity = 1.0;
	EmitVertex();
	
	EndPrimitive();	
}


