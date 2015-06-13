attribute vec2 VertexPosition;

uniform mat4 ProjectionMatrix;
uniform mat4 WorldMatrix;

void main(void)
{
	vec4 pos = WorldMatrix * vec4(VertexPosition.x, VertexPosition.y, 0.0, 1.0);
	gl_Position = ProjectionMatrix * vec4(pos.xyz, 1.0);
}