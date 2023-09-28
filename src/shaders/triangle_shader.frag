#version 460 core

out vec4 FragColor;

in vec3 vertexColor;
in vec2 TexCoord;

uniform sampler2D triTexture; 
  
void main()
{
    FragColor = texture(triTexture, TexCoord);
}
