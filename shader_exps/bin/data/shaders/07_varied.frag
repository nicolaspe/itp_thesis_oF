#version 330

#ifdef GL_ES
precision mediump float;
#endif

uniform float u_time;
uniform vec2 u_resolution;

out vec4 fragColor;

void main() {
    vec2 st = gl_FragCoord.xy / u_resolution; 

    vec2 tl = smoothstep(vec2(0.05), vec2(0.15), st);
    vec2 br = smoothstep(vec2(0.1), vec2(0.2), 1-st);
    float t = (sin(u_time));
    float circ = smoothstep(0.35+t/5., 0.45+t/5., pow(distance(st, vec2(0.5)),0.3));
    float pct = tl.x * tl.y * br.x * br.y * circ;
    vec3 col = vec3(pct, circ, abs(t));

    fragColor = vec4(col, 1.0);
}