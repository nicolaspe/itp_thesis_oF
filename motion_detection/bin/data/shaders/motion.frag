#version 330

#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2DRect nowTex;
uniform sampler2DRect preTex;
uniform sampler2DRect targetTex;
uniform float fade;
uniform float tolerance;

out vec4 fragColor;

float diff(in vec4 t0, in vec4 t1){
	vec3 d = abs(t0.rgb - t1.rgb);
	return (d.r + d.g + d.b)/3.;
}

float brightness(in vec4 tex){
	float bri = max(max(tex.r, tex.g), tex.b);
	return bri;
}

void main() {
    vec2 st = gl_FragCoord.xy;

	vec4 nowColor = texture(nowTex, st);
	vec4 preColor = texture(preTex, st);
	vec4 targetColor = texture(targetTex, st);
	float delta = diff(nowColor, preColor);

	float alpha = targetColor.a - 0.0005;
//	if(preColor.r > tolerance){
//	if(nowColor.r > tolerance){
	if(delta > tolerance){
		alpha = 1.;
	}
	
    fragColor = vec4(nowColor.rgb, alpha);
}