// simple vertex shader

varying vec4 V;
varying vec3 N;

void main()
{
	gl_Position    = gl_ModelViewProjectionMatrix * gl_Vertex;
	V = gl_ModelViewMatrix * gl_Vertex;
	N = gl_NormalMatrix * gl_Normal;
}
