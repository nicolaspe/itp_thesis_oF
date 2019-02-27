#version 330 

#ifdef GL_ES
precision mediump float;
#endif

uniform float u_time;
uniform vec2 u_resolution;

out vec4 fragColor;

void main() {
    float t = abs( sin(u_time) );
    vec2 st = gl_FragCoord.xy / u_resolution;
    vec3 col = vec3(st.x, st.y, t);
    fragColor = vec4(col.rgb, 1.0);
}