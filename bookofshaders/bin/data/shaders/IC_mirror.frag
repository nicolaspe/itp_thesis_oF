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
    st -= vec2((u_position/u_resolution).x, 0);
    st = abs(st);

    float bri = max(st.x, st.y);
    
    vec3 col = vec3(bri);
    fragColor = vec4(col, 1.0);
}