#version 450 core

layout(binding = 0) uniform sampler2D ColTexture;

in FSPacket
{
    float intensity;
    vec2  uv;
}inVertex;

out vec4 FragColor; // Color that will be used for the fragment

//////////////////////////////////////////////////////////////////
// main()
//////////////////////////////////////////////////////////////////
void main()
{
//    vec4 colour = texture(ColTexture, inVertex.uv); 

//    FragColor = vec4(vec3(colour.xyz * inVertex.intensity), 1.0);

    FragColor = vec4(vec3(inVertex.intensity), 1.0);
}