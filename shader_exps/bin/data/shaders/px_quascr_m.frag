#version 330

#ifdef GL_ES
precision mediump float;
#endif

#define PI 3.1415926535897932384626433832795

uniform float u_time;
uniform float u_angle;
uniform vec2 u_resolution;
uniform vec2 u_position;

out vec4 fragColor;

mat2 rotate(float _a){
    return mat2(cos(_a), -sin(_a),
                sin(_a),  cos(_a));
}

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
    vec2 center = -vec2(uv.x, uv.y);
    st += center; 
    st = rotate(u_angle) * st;
    st.x = abs(st.x);

    float bri_wave = 0.;
    for(float i=4.; i<=8.; i++){
        bri_wave += wave_c(st*50., -u_time / i);
        bri_wave += wave_c(st*50., -i);
    }
    bri_wave += wave_s(st*80.,u_time/2.);
    bri_wave = wrap(bri_wave);

    vec3 col = vec3(bri_wave);
    fragColor = vec4(col, 1.0);
}