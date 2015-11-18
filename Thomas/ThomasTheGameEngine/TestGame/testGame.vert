#version 430 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) out float vColor;

in vec2 vTexCoord;
out vec2 texCoord;

out vec4 vAmbientColor;
out vec4[2] vLightColor_Directional;
out vec4[2] vLightDirection_Directional;
out vec3 vMaterial;
out vec4 vNormal;
out vec4 fPosition;

uniform float fColor;
uniform vec4 Normal;

uniform mat4 cameraMatrix;
uniform mat4 Transform;
uniform vec3 Material;

uniform vec4 AmbientColor;
uniform vec4[2] LightColor_Directional;
uniform vec4[2] LightDirection_Directional;

void main()
{
	gl_Position = cameraMatrix * (Transform * vPosition);
	fPosition = gl_Position;

	vColor = fColor;

	/* Textures */
	texCoord = vTexCoord;

	vAmbientColor = AmbientColor;
	vLightColor_Directional = LightColor_Directional;
	vLightDirection_Directional = LightDirection_Directional;
	vMaterial = Material;
	vNormal = Normal;
}