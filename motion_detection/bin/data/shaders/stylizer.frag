#version 330

#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2DRect img;
uniform vec2 u_resolution;
uniform vec3 color1;
uniform vec3 color2;
uniform vec3 color3;
uniform vec4 limit;

out vec4 fragColor;


float luma(vec3 col){
    float light = 0.2126*col.r + 0.7152*col.g + 0.0722*col.b;
    return light;
}
float lightness(vec3 col){
    float M = max(col.r, max(col.g, col.b));
    float m = min(col.r, min(col.g, col.b));
    return 0.5*(M+m);
}
float brightness(vec3 col){
    float M = max(col.r, max(col.g, col.b));
    return M;
}


void main() {
    vec3 color0 = vec3(0);
    vec3 color4 = vec3(1);
    vec2 st = gl_FragCoord.xy;
    st.x = u_resolution.x-st.x;
    int mode = 2;

    vec4 texColor = texture(img, st);
    float value = 0.;
    if(mode == 0){
        value = brightness(texColor.rgb);
    } else if (mode == 1){
        value = lightness(texColor.rgb);
    } else if (mode == 2){
        value = luma(texColor.rgb);
    }

    vec3 col;
    if(value < limit.r){
        col = color0;
    } else if(value < limit.g){
        col = color1;
    } else if(value < limit.b){
        col = color2;
    } else if(value < limit.a){
        col = color3;
    } else{
        col = color4;
    }

    fragColor = vec4(col, 1.0);
}