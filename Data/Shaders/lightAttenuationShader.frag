uniform vec2 lightPos;

uniform vec3 lightColor;

uniform float radius;

uniform float bleed;

uniform float linearizeFactor;

void main()
{
	float dist = length(lightPos - gl_FragCoord.xy);

	float distFromFalloff = radius - dist;

	// Still has absolute falloff point
	float attenuation = distFromFalloff * (bleed / pow(dist, 2.0) + linearizeFactor / radius);

	// Optional, clamp it to prevent overcoloring
	attenuation = clamp(attenuation, 0.0, 1.0);

	vec4 color = vec4(attenuation, attenuation, attenuation, 1.0) * vec4(lightColor.r, lightColor.g, lightColor.b, 1.0);

	gl_FragColor = color;
}