#version 330

#ifdef GL_ES
precision mediump float;
#endif

uniform float u_time;
uniform vec2 u_resolution;

out vec4 fragColor;

void main() {
    vec2 st = gl_FragCoord.xy / u_resolution;

    float t = sin(u_time);

    // float pct = pow(min(distance(st,vec2(0.4)),distance(st,vec2(0.6))), t+0.1);
    float pct = pow(distance(st,vec2(0.4+t/8.)),distance(st,vec2(0.6-t/8.)));

    vec3 col = vec3(pct);
    fragColor = vec4(col, 1.0);
}