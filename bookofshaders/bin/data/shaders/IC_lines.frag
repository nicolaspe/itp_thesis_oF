#version 330

#ifdef GL_ES
precision mediump float;
#endif

uniform float u_time;
uniform vec2 u_resolution;
uniform vec2 u_position;

out vec4 fragColor;

float line(vec2 _st, float val){
    return smoothstep(val-0.01, val, _st.y) -
           smoothstep(val, val+0.01, _st.y);
}

void main() {
    // vec2 st = gl_FragCoord.xy / u_resolution -0.5;
    vec2 st = gl_FragCoord.xy / u_resolution;
    vec2 mid = vec2(0.5);

    vec2 uv = u_position / u_resolution;

    float l = 0.;
    if(uv.x < 0.5){
        l = max(st, -st +2*uv).x;
    } else { 
        l = min(st, -st +2*uv).x;
    }

    float bri = line(st, l);
    
    vec3 col = vec3(bri);
    fragColor = vec4(col, 1.0);
}