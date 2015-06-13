#ifdef GL_ES
precision highp float;
#endif

uniform vec4 Color;
uniform float Opacity;
uniform sampler2D TextureSampler;

varying vec2 TexCoord;

void main(void)
{
	vec4 color = vec4(Color.rgb, texture2D(TextureSampler, TexCoord).a*Color.a*Opacity);
	gl_FragColor = color;
}