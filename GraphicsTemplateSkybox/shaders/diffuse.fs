#version 450 core

layout(binding = 0) uniform sampler2D ColTexture;
// passed on from the diffuse.vs  
in float Intensity;
in vec2 TexCoord;

out vec4 FragColor; // Color that will be used for the fragment

//////////////////////////////////////////////////////////////////
// main()
//////////////////////////////////////////////////////////////////
void main()
{
    //gets the textures colour
    vec4 colour = texture(ColTexture, TexCoord.xy); 
    
    //sets frag colour and intensity  
    FragColor = vec4(vec3(colour.xyz * Intensity), 1.0);
}