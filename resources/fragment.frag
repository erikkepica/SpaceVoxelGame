#version 330 core
layout (location = 0) out vec4 color;

in vec2 uv;
in vec3 normal;
in vec3 fragPos;

uniform sampler2D tex;
vec3 lightDir = vec3(-1.0f,1.0f, 0.0f);
vec3 lightColor = vec3(1.f,1.f,1.f);
float ambientStrength = .2f;

void main()
{
    // Ambient
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse
    vec3 norm = normalize(normal);
    float diff = max(dot(norm, normalize(lightDir)), 0.0);
    vec3 diffuse = diff * lightColor;

    vec4 texColor = texture(tex, uv);
    color = vec4((ambient + diffuse) * texColor.rgb, texColor.a);
}