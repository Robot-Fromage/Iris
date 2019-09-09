// Version du GLSL
#version 330 core

// In
in vec4 fWorldPos;
in vec3 fColor;
in vec3 fNormal;

// Uniform
uniform vec3 uWorldNormal;
uniform vec3 uCameraEye;
uniform float uMetallic;
uniform float uRoughness;

// lights
uniform vec3 uLightPositions[4];
uniform vec3 uLightColors[4];

// Out
out vec4 oFragColor;

// Consts
const float PI = 3.14159265359;

// Functions
float DistributionGGX( vec3 N, vec3 H, float roughness )
{
    float a      = roughness*roughness;
    float a2     = a*a;
    float NdotH  = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float num   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return num / denom;
}


float GeometrySchlickGGX( float NdotV, float roughness )
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float num   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return num / denom;
}


float GeometrySmith( vec3 N, vec3 V, vec3 L, float roughness )
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2  = GeometrySchlickGGX(NdotV, roughness);
    float ggx1  = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}


vec3 fresnelSchlick( float cosTheta, vec3 F0 )
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}


// main function
void main()
{
    vec3 WorldPos = fWorldPos.xyz;
    vec3 N = fNormal;
    vec3 V = normalize( uCameraEye - WorldPos );

    vec3 F0 = vec3(0.04);
    F0 = mix(F0, fColor, uMetallic);

    // reflectance equation
    vec3 Lo = vec3(0.0);
    for( int i = 0; i < 4; ++i ) {
        // calculate per-light radiance
        vec3 L = normalize(uLightPositions[i] - WorldPos);
        vec3 H = normalize(V + L);
        float distance    = length(uLightPositions[i] - WorldPos);
        float attenuation = 1.0 / (distance * distance);
        vec3 radiance     = uLightColors[i] * attenuation;
        
        // cook-torrance brdf
        float NDF = DistributionGGX(N, H, uRoughness);
        float G   = GeometrySmith(N, V, L, uRoughness);
        vec3 F    = fresnelSchlick(max(dot(H, V), 0.0), F0);
        
        vec3 kS = F;
        vec3 kD = vec3(1.0) - kS;
        kD *= 1.0 - uMetallic;
        
        vec3 numerator    = NDF * G * F;
        float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0);
        vec3 specular     = numerator / max(denominator, 0.001);  
            
        // add to outgoing radiance Lo
        float NdotL = max(dot(N, L), 0.0);
        Lo += (kD * fColor / PI + specular) * radiance * NdotL;
    }

    vec3 ambient = vec3(0.03) * fColor;
    vec3 color = ambient + Lo;

    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.2));  

    oFragColor = vec4( color, 1.0);
    //oFragColor = vec4( ( fNormal + vec3( 1 ) ) / 2.0, 1.0);
}
