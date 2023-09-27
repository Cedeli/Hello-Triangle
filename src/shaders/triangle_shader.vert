#version 460 core

layout (location = 0) in vec3 triPos;

void main()
{
   gl_Position = vec4(triPos.x, triPos.y, triPos.z, 1.0);
}
