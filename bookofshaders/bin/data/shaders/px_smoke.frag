#version 330

// from pixelshaders.com

#ifdef GL_ES
precision mediump float;
#endif

uniform float u_time;
uniform vec2 u_resolution;

out vec4 fragColor;

float random(in float x){
    return fract(sin(x)*10000.);
}
float noise(in vec2 pos){
    return random(pos.x + pos.y*10000.);
}
float stepNoise(in vec2 pos){
    return noise(floor(pos));
}

vec2 sw(in vec2 pos){ return vec2(floor(pos.x), floor(pos.y)); }
vec2 se(in vec2 pos){ return vec2(ceil(pos.x),  floor(pos.y)); }
vec2 nw(in vec2 pos){ return vec2(floor(pos.x), ceil(pos.y)); }
vec2 ne(in vec2 pos){ return vec2(ceil(pos.x),  ceil(pos.y)); }

float smoothNoise(in vec2 pos){
    vec2 inter = smoothstep(0., 1., fract(pos));
    float s = mix( noise(sw(pos)), noise(se(pos)), inter.x );
    float n = mix( noise(nw(pos)), noise(ne(pos)), inter.x );
    return mix(s, n, inter.y);
}
float fractalNoise(in vec2 pos){
    float result = 0.;
    float divs = 0.;
    for(float i=0.; i<=4.; i++){
        result += smoothNoise(pos * pow(-2., i)) / pow(2.,i);
        divs  += 1./ pow(2, i);
    }
    return result/divs;
}
float movingNoise(in vec2 pos){
    float result = 0.;
    float divs = 0.;
    for(float i=0.; i<=4.; i++){
        result += smoothNoise(pos*pow(-2., i) - u_time*pow(-1., i)) / pow(2.,i);
        divs  += 1./ pow(2, i);
    }
    return result/divs;
}
float nestedNoise(in vec2 pos){
    float x = movingNoise(pos);
    float y = movingNoise(pos + 100.);
    return movingNoise(pos + vec2(x, y));
}


void main() {
    vec2 st = gl_FragCoord.xy / u_resolution;

    // float smoke = fractalNoise(st*6.);
    // float smoke = movingNoise(st*6.);
    float smoke = nestedNoise(st*6.);

    vec3 col = vec3(smoke);
    fragColor = vec4(col, 1.0);
}