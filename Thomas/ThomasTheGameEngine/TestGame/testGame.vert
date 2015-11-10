#version 430 core
layout(location = 0) in vec4 vPosition;
layout(location = 1) out float vColor;

in vec2 vTexCoord;
out vec2 texCoord;

uniform float fColor;
uniform mat4 cameraMatrix;
uniform mat4 Transform;

void main()
{
	gl_Position = cameraMatrix * (Transform * vPosition);
	vColor = fColor;

	/* Textures */
	texCoord = vTexCoord;
}