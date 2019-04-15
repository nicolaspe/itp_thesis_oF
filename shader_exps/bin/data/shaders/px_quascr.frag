#version 330

#ifdef GL_ES
precision mediump float;
#endif

#define PI 3.1415926535897932384626433832795

uniform float u_time;
uniform vec2 u_resolution;
uniform vec2 u_position;

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
    vec2 uv = u_position / u_resolution;
    vec2 center = -vec2(uv.x, 0.05);
    st += center; 

    float bri_wave = 0.;
    if(uv.x > 0.5){
        for(float i=4.; i<=8.; i++){
            bri_wave += wave_c(st*50., u_time / i);
            bri_wave += wave_c(st*50., i);
        }
        bri_wave += wave_s(st*80.,-u_time/2.);
    } else {
        for(float i=4.; i<=8.; i++){
            bri_wave += wave_c(st*50., -u_time / i);
            bri_wave += wave_c(st*50., -i);
        }
        bri_wave += wave_s(st*80.,u_time/2.);
    }
    bri_wave = wrap(bri_wave);

    vec3 col = vec3(bri_wave);
    fragColor = vec4(col, 1.0);
}