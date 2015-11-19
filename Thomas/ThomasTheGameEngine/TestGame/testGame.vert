#version 430 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) out float vColor;

in vec2 vTexCoord;
out vec2 texCoord;

out vec4 vAmbientColor;
out vec4[2] vLightColor_Directional;
out vec4[2] vLightDirection_Directional;
out vec4[8] vLightColor_Point;
out vec4[8] vLightPosition_Point;
out float[8] vLightRadius_Point;
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

uniform vec4[8] LightColor_Point;
uniform vec4[8] LightPosition_Point;
uniform float[8] LightRadius_Point;

void main()
{
	gl_Position = cameraMatrix * (Transform * vPosition);
	fPosition = Transform * vPosition;

	vColor = fColor;

	/* Textures */
	texCoord = vTexCoord;

	/* Light */
	vAmbientColor = AmbientColor;
	vLightColor_Directional = LightColor_Directional;
	vLightDirection_Directional = LightDirection_Directional;
	vLightColor_Point = LightColor_Point;
	vLightPosition_Point = LightPosition_Point;
	vLightRadius_Point = LightRadius_Point;

	vMaterial = Material;
	vNormal = Normal;
}