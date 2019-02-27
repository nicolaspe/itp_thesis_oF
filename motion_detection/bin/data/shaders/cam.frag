#version 330

#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2DRect nowTex;
uniform vec2 u_resolution;

out vec4 fragColor;

void main() {
    vec2 st = gl_FragCoord.xy;
    vec4 texColor = texture(nowTex, st);
    fragColor = vec4(texColor.rgb, 1.0);
}