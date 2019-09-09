// Version du GLSL
#version 330 core

// In
in vec2 fTexCoord;
in vec3 fVertex;

// Uniform
uniform sampler2D iTexture;
uniform vec3 uCameraEye;

// Out
out vec4 oFragColor;


float getFogFactor(float d)
{
    const float FogMax = 10000.0;
    const float FogMin = 1000.0;

    if (d>=FogMax) return 1;
    if (d<=FogMin) return 0;

    return 1 - (FogMax - d) / (FogMax - FogMin);
}

// main function
void main()
{
    float d = distance( uCameraEye, fVertex );
    float alpha = getFogFactor(d);
	oFragColor = mix( texture( iTexture, fTexCoord ), vec4( 0.8, 0.8, 0.8, 1.0 ), alpha );
}
