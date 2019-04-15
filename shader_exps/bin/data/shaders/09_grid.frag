#version 330

#ifdef GL_ES
precision mediump float;
#endif

uniform float u_time;
uniform vec2 u_resolution;

out vec4 fragColor;

float circle(in vec2 _st, in float _rad) {
    vec2 dist = _st - vec2(0.5);
    return 1. - smoothstep(_rad-0.001, _rad+0.001, dot(dist, dist)*4.);
}

void main() {
    vec2 st = gl_FragCoord.xy / u_resolution;
    // grid (fixed by aspect ratio)
    float grid = 3.;
    float aspect = u_resolution.x / u_resolution.y;
    st *= vec2(aspect, 1.) * grid;
    st = fract(st);
    
    // vec3 col = vec3(st, 0.);
    vec3 col = vec3(circle(st, 0.2));

    fragColor = vec4(col, 1.0);
}