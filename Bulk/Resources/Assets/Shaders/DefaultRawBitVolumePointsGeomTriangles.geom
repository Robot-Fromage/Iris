// Version du GLSL
#version 330 core

// Geometry layout
layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

// In
in vec3 gNormal[];

// Uniform
uniform mat4 uModel;
uniform mat4 uProjectionView;
uniform int uSide;

// Out
out vec4 fWorldPos;
out vec3 fColor;
out vec3 fNormal;

// Functions
void GenerateFaceLeft()
{
    fWorldPos = uModel * gl_in[0].gl_Position;
    gl_Position = uProjectionView * fWorldPos;
    EmitVertex();
    fWorldPos = uModel * ( gl_in[0].gl_Position + vec4( 0.0, 0.0, 1.0, 0.0 ) );
    gl_Position = uProjectionView * fWorldPos;
    EmitVertex();
    fWorldPos = uModel * ( gl_in[0].gl_Position + vec4( 0.0, 1.0, 0.0, 0.0 ) );
    gl_Position = uProjectionView * fWorldPos;
    EmitVertex();
    fWorldPos = uModel * ( gl_in[0].gl_Position + vec4( 0.0, 1.0, 1.0, 0.0 ) );
    gl_Position = uProjectionView * fWorldPos;
    EmitVertex();
    EndPrimitive();
}

void GenerateFaceRight()
{
    fWorldPos = uModel * ( gl_in[0].gl_Position + vec4( 1.0, 0.0, 0.0, 0.0 ) );
    gl_Position = uProjectionView * fWorldPos;
    EmitVertex();
    fWorldPos = uModel * ( gl_in[0].gl_Position + vec4( 1.0, 1.0, 0.0, 0.0 ) );
    gl_Position = uProjectionView * fWorldPos;
    EmitVertex();
    fWorldPos = uModel * ( gl_in[0].gl_Position + vec4( 1.0, 0.0, 1.0, 0.0 ) );
    gl_Position = uProjectionView * fWorldPos;
    EmitVertex();
    fWorldPos = uModel * ( gl_in[0].gl_Position + vec4( 1.0, 1.0, 1.0, 0.0 ) );
    gl_Position = uProjectionView * fWorldPos;
    EmitVertex();
    EndPrimitive();
}

void GenerateFaceUp()
{
    fWorldPos = uModel * ( gl_in[0].gl_Position + vec4( 0.0, 1.0, 0.0, 0.0 ) );
    gl_Position = uProjectionView * fWorldPos;
    EmitVertex();
    fWorldPos = uModel * ( gl_in[0].gl_Position + vec4( 0.0, 1.0, 1.0, 0.0 ) );
    gl_Position = uProjectionView * fWorldPos;
    EmitVertex();
    fWorldPos = uModel * ( gl_in[0].gl_Position + vec4( 1.0, 1.0, 0.0, 0.0 ) );
    gl_Position = uProjectionView * fWorldPos;
    EmitVertex();
    fWorldPos = uModel * ( gl_in[0].gl_Position + vec4( 1.0, 1.0, 1.0, 0.0 ) );
    gl_Position = uProjectionView * fWorldPos;
    EmitVertex();
    EndPrimitive();
}

void GenerateFaceDown()
{
    fWorldPos = uModel * gl_in[0].gl_Position;
    gl_Position = uProjectionView * fWorldPos;
    EmitVertex();
    fWorldPos = uModel * ( gl_in[0].gl_Position + vec4( 1.0, 0.0, 0.0, 0.0 ) );
    gl_Position = uProjectionView * fWorldPos;
    EmitVertex();
    fWorldPos = uModel * ( gl_in[0].gl_Position + vec4( 0.0, 0.0, 1.0, 0.0 ) );
    gl_Position = uProjectionView * fWorldPos;
    EmitVertex();
    fWorldPos = uModel * ( gl_in[0].gl_Position + vec4( 1.0, 0.0, 1.0, 0.0 ) );
    gl_Position = uProjectionView * fWorldPos;
    EmitVertex();
    EndPrimitive();
}

void GenerateFaceFront()
{
    fWorldPos = uModel * gl_in[0].gl_Position;
    gl_Position = uProjectionView * fWorldPos;
    EmitVertex();
    fWorldPos = uModel * ( gl_in[0].gl_Position + vec4( 0.0, 1.0, 0.0, 0.0 ) );
    gl_Position = uProjectionView * fWorldPos;
    EmitVertex();
    fWorldPos = uModel * ( gl_in[0].gl_Position + vec4( 1.0, 0.0, 0.0, 0.0 ) );
    gl_Position = uProjectionView * fWorldPos;
    EmitVertex();
    fWorldPos = uModel * ( gl_in[0].gl_Position + vec4( 1.0, 1.0, 0.0, 0.0 ) );
    gl_Position = uProjectionView * fWorldPos;
    EmitVertex();
    EndPrimitive();
}

void GenerateFaceBack()
{
    fWorldPos = uModel * ( gl_in[0].gl_Position + vec4( 0.0, 0.0, 1.0, 0.0 ) );
    gl_Position = uProjectionView * fWorldPos;
    EmitVertex();
    fWorldPos = uModel * ( gl_in[0].gl_Position + vec4( 1.0, 0.0, 1.0, 0.0 ) );
    gl_Position = uProjectionView * fWorldPos;
    EmitVertex();
    fWorldPos = uModel * ( gl_in[0].gl_Position + vec4( 0.0, 1.0, 1.0, 0.0 ) );
    gl_Position = uProjectionView * fWorldPos;
    EmitVertex();
    fWorldPos = uModel * ( gl_in[0].gl_Position + vec4( 1.0, 1.0, 1.0, 0.0 ) );
    gl_Position = uProjectionView * fWorldPos;
    EmitVertex();
    EndPrimitive();
}


// main function
void main()
{
    fNormal = normalize( ( uModel * vec4( gNormal[0], 0.0 ) ).xyz );
    float grey = 0.8;
    vec3 gamma_color0 = vec3( 0.75686, 0.44705, 0.29411 );
    vec3 gamma_color1 = vec3( 0.75686, 0.75686, 0.75686 );
    vec3 gamma_color2 = vec3( 0.29411, 0.44705, 0.75686 );
    fColor = pow( gamma_color2, vec3(2.2));

    switch( uSide )
    {
        case 0: GenerateFaceLeft(); break;
        case 1: GenerateFaceRight(); break;
        case 2: GenerateFaceUp(); break;
        case 3: GenerateFaceDown(); break;
        case 4: GenerateFaceFront(); break;
        case 5: GenerateFaceBack(); break;
    }
}
