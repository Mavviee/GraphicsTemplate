#version 460 core


layout(binding = 0) uniform sampler2D ColTexture;


in packet_GS
{
	vec3 vertexPos;
	vec3 vertexNormal;
	vec2 uv;
	float intensity;
}inData;




out vec4 FragColor; // Color that will be used for the fragment

//////////////////////////////////////////////////////////////////
// main()
//////////////////////////////////////////////////////////////////
void main()
{
    vec4 colour = texture(ColTexture, inData.uv.xy); 

    FragColor = vec4(vec3(colour.xyz), 1.0);
}