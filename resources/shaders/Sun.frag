#version 330 core
layout (location = 0) out vec4 color;
in vec2 uv;

uniform vec2  resolution;
uniform float sunIntensity;
uniform float sunTemperature;
uniform vec3  sunCol;
uniform float sunRadius;
uniform vec3  sunPos;
uniform vec3  camPos;
uniform mat4  invViewProj;

vec3 g_SunWorldPos;

float sphereSDF(vec3 p, float r) { return length(p) - r; }
float sceneSDF(vec3 p)           { return sphereSDF(p - g_SunWorldPos, sunRadius); }

float normTemp(float kelvin)
{
    return clamp((log(kelvin) - log(2500.0)) / (log(40000.0) - log(2500.0)), 0.0, 1.0);
}

vec3 blackbodyColor(float kelvin)
{
    float t = kelvin / 100.0;
    vec3 c;

    // Red
    if (t <= 66.0)
        c.r = 1.0;
    else
        c.r = clamp(329.698727 * pow(t - 60.0, -0.1332047) / 255.0, 0.0, 1.0);

    // Green
    if (t <= 66.0)
        c.g = clamp((99.4708025 * log(t) - 161.1195681) / 255.0, 0.0, 1.0);
    else
        c.g = clamp(288.1221695 * pow(t - 60.0, -0.0755148) / 255.0, 0.0, 1.0);

    // Blue
    if (t >= 66.0)
        c.b = 1.0;
    else if (t <= 19.0)
        c.b = 0.0;
    else
        c.b = clamp((138.5177312 * log(t - 10.0) - 305.0447927) / 255.0, 0.0, 1.0);

    return c;
}

vec3 limbColor(vec3 baseColor, float limbFactor, float kelvin)
{
    float edge = 1.0 - pow(clamp(limbFactor, 0.0, 1.0), 0.6);
    float coolKelvin = clamp(kelvin * (1.0 - 0.25 * edge), 2000.0, 40000.0);
    vec3  coolColor  = blackbodyColor(coolKelvin);
    return mix(baseColor, coolColor, edge * 0.6);
}

vec3 coronaTint(float kelvin)
{
    float t = normTemp(kelvin);
    vec3 cool = vec3(1.0, 0.30, 0.04);
    vec3 mid  = vec3(1.0, 0.85, 0.55);
    vec3 hot  = vec3(0.70, 0.88, 1.00);
    if (t < 0.5)
        return mix(cool, mid, t * 2.0);
    else
        return mix(mid, hot, (t - 0.5) * 2.0);
}

void main()
{
    vec4 clipPos  = vec4(uv * 2.0 - 1.0, -1.0, 1.0);
    vec4 worldPos = invViewProj * clipPos;
    vec3 rd       = normalize(worldPos.xyz / worldPos.w - camPos);
    vec3 ro       = camPos;

    g_SunWorldPos = sunPos;

    float t01      = normTemp(sunTemperature);
    vec3  starColor = blackbodyColor(sunTemperature);

    vec3  sunDir        = normalize(g_SunWorldPos - ro);
    float sunDist       = length(g_SunWorldPos - ro);
    float cosAngle      = dot(rd, sunDir);
    float angle         = acos(clamp(cosAngle, -1.0, 1.0));
    float angularRadius = atan(sunRadius, sunDist);

    // ── Corona ────────────────────────────────────────────────────────────
    float inner     = mix( 50.0, 140.0, t01);
    float mid_      = mix( 10.0,  35.0, t01);
    float outer     = mix(  2.0,   7.0, t01);
    float haloWidth = mix(  1.2,   0.4, t01);
    float halo      = exp(-max(angle - angularRadius, 0.0) * haloWidth);

    float excess = max(angle - angularRadius, 0.0);
    float glow1  = exp(-excess * inner);
    float glow2  = exp(-excess * mid_);
    float glow3  = exp(-excess * outer);

    float totalGlow =
        glow1 * mix(0.8,  1.2, t01) +
        glow2 * mix(0.3,  0.6, t01) +
        glow3 * mix(0.12, 0.2, t01) +
        halo  * mix(0.35, 0.0, t01);

    vec3 cTint     = coronaTint(sunTemperature);
    vec3 glowColor = mix(starColor * cTint, starColor, t01 * 0.6) * totalGlow;

    // ── Raymarching — start just outside the sphere, march only 2*diameter ─
    // Project camera onto the ray toward sun, start just before the sphere
    float tCenter = dot(g_SunWorldPos - ro, rd);     // distance along ray to closest point
    float rayT    = max(tCenter - sunRadius * 1.1, 0.0); // start just before sphere
    float rayFar  = tCenter + sunRadius * 1.1;            // stop just after sphere

    bool hit = false;
    for (int i = 0; i < 64; i++)
    {
        if (rayT > rayFar) break;
        vec3  pos = ro + rd * rayT;
        float d   = sceneSDF(pos);
        if (d < sunRadius * 0.001) { hit = true; break; }  // relative epsilon
        rayT += max(d, sunRadius * 0.001);                  // minimum step to avoid stalling
    }

    if (hit)
    {
        vec3 pos = ro + rd * rayT;
        vec2 e   = vec2(sunRadius * 0.001, 0.0);            // relative epsilon for normal
        vec3 normal = normalize(vec3(
            sceneSDF(pos + e.xyy) - sceneSDF(pos - e.xyy),
            sceneSDF(pos + e.yxy) - sceneSDF(pos - e.yxy),
            sceneSDF(pos + e.yyx) - sceneSDF(pos - e.yyx)
        ));

        float limb         = max(dot(normal, -rd), 0.0);
        float darkeningExp = mix(0.3, 0.9, t01);
        float darkening    = 0.25 + 0.75 * pow(limb, darkeningExp);

        vec3 diskColor = limbColor(starColor, limb, sunTemperature) * sunIntensity * darkening;
        vec3 bloom     = glowColor * mix(0.25, 0.55, t01);

        color = vec4(diskColor + bloom, 1.0);
    }
    else if (totalGlow > 0.001)
    {
        color = vec4(glowColor, totalGlow * mix(0.5, 1.0, t01));
    }
    else
    {
        discard;
    }
}