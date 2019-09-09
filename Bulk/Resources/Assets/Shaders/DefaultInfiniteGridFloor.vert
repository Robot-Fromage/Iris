// Version du GLSL
#version 330 core

// In
layout (location = 0) in vec3 iVertex;

// Uniform
uniform mat4 uMVP;

// Out
out vec2 fTexCoord;
out vec3 fVertex;

// main function
void main()
{
    float size = 50;
    gl_Position = uMVP * vec4( iVertex, 1.0 );
    fTexCoord = vec2( iVertex.x / size, iVertex.z / size );
    fVertex = iVertex;
}
