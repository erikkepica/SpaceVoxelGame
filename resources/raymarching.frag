#version 330 core

layout (location = 0) out vec4 color;

in vec2 uv;

uniform vec2 resolution;

float sphereSDF(vec3 p, float r)
{
    return length(p) - r;
}

vec3 repeat(vec3 p, float s)
{
    return mod(p + 0.5 * s, s) - 0.5 * s;
}

float sceneSDF(vec3 p)
{
    p = repeat(p, 3.0);   // repeat space every 3 units
    return sphereSDF(p, 0.8);
}

vec3 getNormal(vec3 p)
{
    float e = 0.001;
    vec2 h = vec2(e, 0);

    return normalize(vec3(
        sceneSDF(p + h.xyy) - sceneSDF(p - h.xyy),
        sceneSDF(p + h.yxy) - sceneSDF(p - h.yxy),
        sceneSDF(p + h.yyx) - sceneSDF(p - h.yyx)
    ));
}

void main()
{
    vec2 p = uv * 2.0 - 1.0;
    p.x *= resolution.x / resolution.y;

    vec3 ro = vec3(0.0, 0.0, 5.0);
    vec3 rd = normalize(vec3(p, -1.5));

    float t = 0.0;
    float d;

    for(int i = 0; i < 128; i++)
    {
        vec3 pos = ro + rd * t;
        d = sceneSDF(pos);

        if(d < 0.001) break;

        t += d;

        if(t > 200.0) break;
    }

    if(t < 200.0)
    {
        vec3 pos = ro + rd * t;
        vec3 normal = getNormal(pos);

        vec3 lightDir = normalize(vec3(1,1,1));
        float diff = max(dot(normal, lightDir), 0.0);

        color = vec4(vec3(diff), 1.0);
    }
    else
    {
        color = vec4(0.0);
    }
}