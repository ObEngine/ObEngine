uniform vec3      iResolution;           // viewport resolution (in pixels)
uniform float     iGlobalTime;           // shader playback time (in seconds)
uniform float     iTimeDelta;            // render time (in seconds)
uniform sampler2D tex;                   // input channel. XX = 2D/Cube
uniform sampler2D noiseTex;                 // second input channel
uniform float     amplitude;
uniform float     speed;

vec4 rgbShift( in vec2 p , in vec4 shift) {
    shift *= 2.0*shift.w - 1.0;
    vec2 rs = vec2(shift.x,-shift.y);
    vec2 gs = vec2(shift.y,-shift.z);
    vec2 bs = vec2(shift.z,-shift.x);
    
    float r = texture2D(tex, p+rs, 0.0).x;
    float g = texture2D(tex, p+gs, 0.0).y;
    float b = texture2D(tex, p+bs, 0.0).z;
    
    return vec4(r,g,b,1.0);
}

vec4 noise( in vec2 p ) {
    return texture2D(noiseTex, p, 0.0);
}

vec4 vec4pow( in vec4 v, in float p ) {
    // Don't touch alpha (w), we use it to choose the direction of the shift
    // and we don't want it to go in one direction more often than the other
    return vec4(pow(v.x,p),pow(v.y,p),pow(v.z,p),v.w); 
}

void main()
{
	vec2 p = gl_TexCoord[0].xy / iResolution.xy;
    vec4 c = vec4(0.0,0.0,0.0,1.0);
    
    // Elevating shift values to some high power (between 8 and 16 looks good)
    // helps make the stuttering look more sudden
    vec4 shift = vec4pow(noise(vec2(speed*iGlobalTime,2.0*speed*iGlobalTime/25.0 )),8.0)
        		*vec4(amplitude,amplitude,amplitude,1.0);;
    
    c += rgbShift(p, shift);
    
	gl_FragColor = c;
}