// Version du GLSL
#version 330 core

// In
layout (location = 0) in vec3 iVertex;

// Uniform
uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

// Out
out vec3 fColor;

// main function
void main()
{
    fColor = vec3( 0.5, 0.5, 0.5 );
    gl_Position = uProjection * uView * uModel * vec4( iVertex, 1.0 );
}
