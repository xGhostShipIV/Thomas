#version 430 core
layout(location = 0) in vec4 vPosition;
uniform float fColor;
layout(location = 1) out float vColor;

uniform mat4 cameraMatrix;


void main()
{
	gl_Position = cameraMatrix * vPosition;
	vColor = fColor;
}