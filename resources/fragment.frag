#version 330 core
layout (location = 0) out vec4 color;

in vec2 uv;
in vec3 normal;
in vec3 fragPos;

uniform sampler2D diffuseTex;
uniform sampler2D specularTex;

uniform vec3 camPos;

uniform vec3 sunPos;
uniform vec3 lightColor;

float ambientStrength = .6f;
float lightStrength = 2.0f;

void main()
{
    // Ambient
    vec3 ambient = ambientStrength * vec3(1.0);

    // Diffuse
    float diff = max(dot(normal, normalize(sunPos-fragPos)), 0.0);

    // Specular
    vec3 viewDir    = normalize(camPos - fragPos);
    vec3 reflectDir = reflect(normalize(sunPos-fragPos), normal);
    float spec      = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);

    // Sample textures
    vec4 diffuseSample  = texture(diffuseTex,  uv);
    float specularSample = texture(specularTex, uv).r;

    // Combine — ambient is unaffected by lightStrength
    vec3 diffuse  = diff * lightColor * lightStrength;
    vec3 specular = 0.5 * spec * specularSample * lightColor * lightStrength;

    color = vec4(
        (ambient + diffuse + specular) * diffuseSample.rgb,
        diffuseSample.a
    );
}