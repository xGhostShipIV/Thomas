#version 430 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) out float vColor;

in vec2 vTexCoord;
out vec2 texCoord;

out vec4 vAmbientColor;
out vec4[2] vLightColor_Directional;
out vec4[2] vLightDirection_Directional;

out vec4[4] vLightColor_Point;
out vec4[4] vLightPosition_Point;
out float[4] vLightRadius_Point;

out vec4[4]	 vLightColor_Spot;
out vec4[4]  vLightPosition_Spot;
out vec4[4]  vLightDirection_Spot;
out float[4] vLightRadius_Spot;
out float[4] vLightAngle_Spot;

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

uniform vec4[4] LightColor_Point;
uniform vec4[4] LightPosition_Point;
uniform float[4] LightRadius_Point;

uniform vec4[4] LightColor_Spot;
uniform vec4[4] LightPosition_Spot;
uniform vec4[4] LightDirection_Spot;
uniform float[4] LightRadius_Spot;
uniform float[4] LightAngle_Spot;

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

	vLightColor_Spot = LightColor_Spot;
	vLightPosition_Spot = vLightPosition_Spot;
	vLightDirection_Spot = LightDirection_Spot;
	vLightRadius_Spot = LightRadius_Spot;
	vLightAngle_Spot = LightAngle_Spot;

	vMaterial = Material;
	vNormal = Normal;
}