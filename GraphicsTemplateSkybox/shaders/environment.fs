#version 450 core

layout(binding = 0) uniform sampler2D ColTexture;
layout(binding = 2) uniform samplerCube SkyboxTexture;


in float Intensity;
in vec2 TexCoord;
in vec3 rv;

out vec4 FragColor; // Color that will be used for the fragment

//////////////////////////////////////////////////////////////////
// main()
//////////////////////////////////////////////////////////////////
void main()
{
// gets reflection from the skybox texture
    vec4 colour = texture(ColTexture, TexCoord.xy); 
    vec4 reflect = texture(SkyboxTexture, rv); 
     
	// add the reflection onto the texture colour
	FragColor = vec4(vec3(colour.xyz + reflect.xyz *  Intensity), 1.0);
	
	
	
 
}