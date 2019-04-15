#version 330

#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2DRect inTex;
uniform float u_time;
uniform vec2 u_resolution;
uniform vec2 u_position;

out vec4 fragColor;


void main() {
    vec2 mid = u_resolution/2.;
    vec2 st = gl_FragCoord.xy;
    vec2 uv = u_position;

    vec2 uv2 = st;
    if(uv.x < mid.x){
        uv2.x = max(st, -st +2*uv).x;
    } else { 
        uv2.x = min(st, -st +2*uv).x;
    }
    
    vec3 col = texture(inTex, uv2).rgb;
    fragColor = vec4(col, 1.0);
}