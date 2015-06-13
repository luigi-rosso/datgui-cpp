#ifdef GL_ES
precision highp float;
#endif

uniform vec4 Color;
uniform float Opacity;

void main(void)
{
	gl_FragColor = vec4(Color.rgb, Color.a*Opacity);
}