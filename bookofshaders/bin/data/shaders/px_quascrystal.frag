#version 330

// from pixelshaders.com

#ifdef GL_ES
precision mediump float;
#endif

uniform float u_time;
uniform vec2 u_resolution;

out vec4 fragColor;

float wave_c(in vec2 _uv, in float _angle) {
    vec2 rotation = vec2(cos(_angle), sin(_angle));
    return cos(dot(_uv, rotation));
}

float wave_s(in vec2 _uv, in float _angle) {
    vec2 rotation = vec2(sin(_angle), cos(_angle));
    return cos(dot(_uv, rotation));
}

float wrap(in float x){ return abs(mod(x, 2.)-1.); }

void main() {
    vec2 st = gl_FragCoord.xy / u_resolution;
    st -= 0.5;
    vec2 center = 0.5 * vec2(0., 0.75);
    // vec2 center = 1.0 * vec2(cos(u_time/10.), sin(u_time/10.));
    st += center; 

    float bri_wave = 0.;
    for(float i=4.; i<=8.; i++){
        bri_wave += wave_c(st*50., u_time / i);
        bri_wave += wave_c(st*50., i);
    }
    bri_wave += wave_s(st*80.,-u_time/2.);
    bri_wave = wrap(bri_wave);

    vec3 col = vec3(bri_wave);
    fragColor = vec4(col, 1.0);
}