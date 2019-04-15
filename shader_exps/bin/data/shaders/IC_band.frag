#version 330

#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2DRect inTex;
uniform sampler2DRect prevTex;
uniform float u_time;
uniform vec2 u_resolution;
uniform vec2 u_position;
uniform float u_angle;
uniform float u_speed;
uniform float u_fade;

out vec4 fragColor;

float circle(in vec2 _st, in vec2 _pos, in float _rad) {
    vec2 dist = _st - _pos;
    return 1. - smoothstep(_rad-0.1, _rad+0.1, dot(dist, dist)*4.);
}
float ellipse(in vec2 _st, in vec2 _pos, in float _rad){
    vec2 dist = _st - _pos;
    float A = 0.1; 
    float B = 0.3;
    float ell = dot(dist/vec2(A,B), dist/vec2(A,B));
    return 1.- smoothstep((_rad*0.5), (_rad*1.5), ell*1.);
}

float bar (in vec2 _st, in vec2 _pos){
    vec2 barR = vec2(1) - smoothstep(vec2(_pos.x+0.1, 0), vec2(_pos.x+0.25, 0), _st);
    vec2 barL = smoothstep(vec2(_pos.x-0.25, 0), vec2(_pos.x-0.1, 0), _st);
    return barR.x * barL.x;
}
float wave(in vec2 _st){
    vec2 rot = vec2(cos(0), sin(0));
    return cos(dot(_st, rot))+0.5;
}


void main() {
    vec2 uv = vec2(gl_FragCoord.x, u_resolution.y -gl_FragCoord.y);
    vec2 st = gl_FragCoord.xy / u_resolution;
    vec2 focus = u_position / u_resolution;
    float aspect = u_resolution.x / u_resolution.y;

    // float mask = bar(st, focus);
    // float mask = wave(st*80+u_time*40, u_angle);
    // float mask = circle(st, focus, 0.1);
    // float mask = ellipse(st, focus, 0.2);
    float mask = ellipse(st, focus, 0.3) * wave(st*80+u_time*40);

    vec3 col = texture(inTex, uv).rgb * vec3(180./255, 0., 1.);
    fragColor = vec4(col, mask);
}