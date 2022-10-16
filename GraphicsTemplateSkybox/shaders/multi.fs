#version 450 core

layout(binding = 0) uniform sampler2D ColTexture;
layout(binding = 1) uniform sampler2D ColTexture2;

in float Intensity;
in vec2 TexCoord;

out vec4 FragColor; // Color that will be used for the fragment

//////////////////////////////////////////////////////////////////
// main()
//////////////////////////////////////////////////////////////////
void main()
{
    vec4 colour = texture(ColTexture, TexCoord.xy); 
    vec4 stencil = texture(ColTexture2, TexCoord.xy); 

	// if the stencil colour is greater than 0.5 then it will keep the normal colour
	if(stencil.r > 0.5)
	{
	 FragColor = vec4(vec3(colour.xyz *  Intensity), 1.0);
	}
	else
	{
	FragColor = vec4(vec3((1.0, 1.0, 1.0) * Intensity), 1.0); // else turn fragment into white
	}
	
 
}