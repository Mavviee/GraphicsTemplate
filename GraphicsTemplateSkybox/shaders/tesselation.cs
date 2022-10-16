#version 460 core

layout (vertices = 3) out;

in packet_VS
{
	vec3 vertexPos;
	vec3 vertexNormal;
	vec2 uv;
	float intensity;
}
inData[];

out packet_CS
{
	vec3 vertexPos;
	vec3 vertexNormal;
	vec2 uv;
	float intensity;
}
outData[];


void main()
{
	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
	
	// internal tesselation factors, the greater the number the more the object will be tesselated.
	gl_TessLevelInner[0] = 5.0f;
	
	// outer
	gl_TessLevelOuter[0] = 8.0f;
	gl_TessLevelOuter[1] = 8.0f;
	gl_TessLevelOuter[2] = 8.0f;
	
	
	
	
	//pass on the data to the next stage of the pipeline 
	outData[gl_InvocationID].vertexPos = inData[gl_InvocationID].vertexPos;
	outData[gl_InvocationID].vertexNormal = inData[gl_InvocationID].vertexNormal;
	outData[gl_InvocationID].uv = inData[gl_InvocationID].uv;
	outData[gl_InvocationID].intensity = inData[gl_InvocationID].intensity;

	
}