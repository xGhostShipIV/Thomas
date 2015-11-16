#version 430 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) out float vColor;

in vec2 vTexCoord;
out vec2 texCoord;

out vec4 vAmbientColor;
out vec4 vLightColor;
out vec4 vLightDirection;
out vec3 vMaterial;
out vec4 vNormal;

uniform float fColor;
uniform vec4 Normal;

uniform mat4 cameraMatrix;
uniform mat4 Transform;
uniform vec3 Material;

uniform vec4 AmbientColor;
uniform vec4 LightColor;
uniform vec4 LightDirection;

void main()
{
	gl_Position = cameraMatrix * (Transform * vPosition);
	vColor = fColor;

	/* Textures */
	texCoord = vTexCoord;

	vAmbientColor = AmbientColor;
	vLightColor = LightColor;
	vLightDirection = LightDirection;
	vMaterial = Material;
	vNormal = Normal;
}