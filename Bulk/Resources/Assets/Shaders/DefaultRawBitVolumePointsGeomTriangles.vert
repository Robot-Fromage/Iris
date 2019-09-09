// Version du GLSL
#version 330 core

// In
layout (location = 0) in vec3 iVertex;
layout (location = 1) in vec3 iNormal;

// Out
out vec3 gNormal;

// main function
void main()
{
    gNormal = iNormal;
    gl_Position = vec4( iVertex, 1.0 );
}