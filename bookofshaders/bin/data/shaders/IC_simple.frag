#version 330

#ifdef GL_ES
precision mediump float;
#endif

uniform float u_time;
uniform vec2 u_resolution;
uniform vec2 u_position;

out vec4 fragColor;

void main() {
    vec2 st = gl_FragCoord.xy / u_resolution;
    vec2 focus = u_position / u_resolution;

    vec2 barR = vec2(1) - smoothstep(vec2(focus.x+0.1, 0), vec2(focus.x+0.25, 0), st);
    vec2 barL = smoothstep(vec2(focus.x-0.25, 0), vec2(focus.x-0.1, 0), st);
    float bar = barR.x * barL.x;

    vec3 col = vec3(0.6, 0.2, 1.0);
    fragColor = vec4(col, bar);
}