varying vec4 vColor;
varying vec2 vTexCoord;

uniform sampler2D u_texture;   //diffuse map
uniform sampler2D u_normals;   //normal map

uniform vec2 Resolution;      //resolution of screen
uniform vec3 LightPos;        //light position, normalized
uniform vec4 LightColor;      //light RGBA -- alpha is intensity
uniform vec4 AmbientColor;    //ambient RGBA -- alpha is intensity 
uniform vec3 Falloff;         //attenuation coefficients

void main() {
    vec4 DiffuseColor = texture2D(u_texture, vTexCoord);

    vec3 NormalMap = texture2D(u_normals, vTexCoord).rgb;

    vec3 LightDir = vec3(LightPos.xy - (gl_FragCoord.xy / Resolution.xy), LightPos.z);

    LightDir.x *= Resolution.x / Resolution.y;

    float D = length(LightDir);

    vec3 N = normalize(NormalMap * 2.0 - 1.0);
    vec3 L = normalize(LightDir);

    vec3 Diffuse = (LightColor.rgb * LightColor.a) * max(dot(N, L), 0.0);

    vec3 Ambient = AmbientColor.rgb * AmbientColor.a;

    float Attenuation = 1.0 / ( Falloff.x + (Falloff.y*D) + (Falloff.z*D*D) );

    vec3 Intensity = Ambient + Diffuse * Attenuation;
    vec3 FinalColor = DiffuseColor.rgb * Intensity;
    gl_FragColor = vColor * vec4(FinalColor, DiffuseColor.a);
}