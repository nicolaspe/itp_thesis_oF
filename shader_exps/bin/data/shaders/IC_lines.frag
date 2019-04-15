#version 330

#ifdef GL_ES
precision mediump float;
#endif

uniform float u_time;
uniform vec2 u_resolution;

out vec4 fragColor;

float line(vec2 _st, float val){
    return smoothstep(val-0.01, val, _st.y) -
           smoothstep(val, val+0.01, _st.y);
}

void main() {
    vec2 st = gl_FragCoord.xy / u_resolution -0.5;

    float bri = line(st, 0);
    
    vec3 col = vec3(bri);
    fragColor = vec4(col, 1.0);
}