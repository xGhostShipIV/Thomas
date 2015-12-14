#version 430 core

layout(location = 0) in vec4 vPosition;
layout(location = 2) in vec4 Normal;

in vec2 vTexCoord;
out vec2 texCoord;

out vec3 vMaterial;
out vec4 vNormal;
out vec4 fPosition;

out vec4 vAmbientColor;
out vec4[1] vLightColor_Directional;
out vec4[1] vLightDirection_Directional;

out vec4[2] vLightColor_Point;
out vec4[2] vLightPosition_Point;

out vec4[2]	 vLightColor_Spot;
out vec4[2]  vLightPosition_Spot;
out vec4[2]  vLightDirection_Spot;
out float[2] vLightAngle_Spot;

out vec3 fIsEffectedByLight;
out float fUiDraw;

out vec3 vCamPosition;
uniform vec3 CamPosition;


uniform float uiDraw;

//uniform vec4 Normal;

uniform mat4 view;
uniform mat4 projection;

uniform mat4 Transform; //model
uniform mat4 Rotation; //for normals
uniform vec3 Material;

uniform vec4 AmbientColor;
uniform vec4[1] LightColor_Directional;
uniform vec4[1] LightDirection_Directional;

uniform vec4[2] LightColor_Point;
uniform vec4[2] LightPosition_Point;

uniform vec4[2] LightColor_Spot;
uniform vec4[2] LightPosition_Spot;
uniform vec4[2] LightDirection_Spot;
uniform float[2] LightAngle_Spot;

uniform vec3 isEffectedByLight;

void main()
{
	if (uiDraw > 0)
	{
		gl_Position = (Transform * vPosition);
	}
	else
	{
		//				Projection	View	Model
		gl_Position = projection * view * (Transform * vPosition);
	}

	//World Position
	fPosition = Transform * vPosition;

	/* Textures -- FLIP THEM TO FIX WIERDNESS */
	texCoord = vTexCoord * vec2(1.0, -1.0);

	/* Light */
	vAmbientColor = AmbientColor;
	vLightColor_Directional = LightColor_Directional;
	vLightDirection_Directional = LightDirection_Directional;	

	vLightColor_Point = LightColor_Point;

	vLightPosition_Point = LightPosition_Point;
	vLightColor_Spot = LightColor_Spot;
	
	vLightPosition_Spot = LightPosition_Spot;
	vLightDirection_Spot = LightDirection_Spot;
	vLightAngle_Spot = LightAngle_Spot;

	vCamPosition = CamPosition;

	vMaterial = Material;

	//Need to rotate normals
	vNormal =  normalize(Rotation * Normal);

	fIsEffectedByLight = isEffectedByLight;

	fUiDraw = uiDraw;
}