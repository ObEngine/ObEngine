uniform vec2 frag_LightOrigin;
uniform vec3 frag_LightColor;
uniform float frag_LightAttenuation;
uniform vec2 frag_ScreenResolution;
uniform float frag_LightAlpha;

void main()
{
    vec2 baseDistance =  gl_FragCoord.xy;

    baseDistance.y = frag_ScreenResolution.y-baseDistance.y;

    vec2 distance=frag_LightOrigin - baseDistance;

    float linear_distance = length(distance);
    float attenuation=1.0/( frag_LightAttenuation*linear_distance + frag_LightAttenuation*linear_distance);

    vec4 lightColor = vec4(frag_LightColor, 1.0);
    vec4 color = vec4(attenuation, attenuation, attenuation, frag_LightAlpha) * lightColor;

    gl_FragColor=color;
}
