#version 460 core

layout (location = 0) in vec3               vertexPos_VS;	  	// Position in attribute location 0
layout (location = 1) in vec2               texCoord_VS;
layout (location = 2) in vec3               vertexNormal_VS;

layout (location = 3) uniform mat4          modelMatrix;
layout (location = 4) uniform mat4          gVP;

layout (location = 5) uniform vec3          gCP;
layout (location = 6) uniform vec3          lightPosition;


out packet_VS
{
	vec3 vertexPos;
	vec3 vertexNormal;
	vec2 uv;
	float intensity;
}outData;

//////////////////////////////////////////////////////////////////
// main()
//////////////////////////////////////////////////////////////////
void main()
{    
	vec3 mpos   = (modelMatrix * vec4(vertexPos_VS, 1.0)).xyz;
	
	outData.vertexPos = vertexPos_VS;
	outData.vertexNormal = vertexNormal_VS;
	outData.uv = texCoord_VS;
	outData.intensity = 1;

    gl_Position = gVP * vec4(mpos, 1.0);
}