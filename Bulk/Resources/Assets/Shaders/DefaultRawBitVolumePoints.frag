// Version du GLSL
#version 330 core

// In
in vec3 fColor;

// Out
out vec4 oFragColor;

// main function
void main()
{
	oFragColor = vec4( fColor, 1.0 );
}
