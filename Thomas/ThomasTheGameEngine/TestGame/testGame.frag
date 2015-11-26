#version 430 core

out vec4 fColor;
in vec2 texCoord;
uniform sampler2D texture;

in vec3 vMaterial;
in vec4 vNormal;
in vec4 fPosition;

in vec4 vAmbientColor;
in vec4[1] vLightColor_Directional;
in vec4[1] vLightDirection_Directional;

in vec4[2]  vLightColor_Point;
in vec4[2]  vLightPosition_Point;

in vec4[2]	vLightColor_Spot;
in vec4[2]  vLightPosition_Spot;
in vec4[2]  vLightDirection_Spot;
in float[2] vLightAngle_Spot;

void main()
{
	/* AMBIENT LIGHTING */
	vec4 ambientLight = (vMaterial.x * vAmbientColor);

	/* DIFFUSE LIGHTING */
	vec4 diffuse = vec4(0, 0, 0, 0);

	//Directional
	for (int i = 0; i < vLightDirection_Directional.length(); i++)
	{
		//vec4 directionalDiffuse = (vLightColor_Directional[i] * vMaterial.y * dot(vLightDirection_Directional[i], vNormal));

		float brightness = dot(vNormal, vLightDirection_Directional[i]) / (length(vLightDirection_Directional[i]) * length(vNormal));
		brightness = clamp(brightness, 0, 1);
		vec4 directionalDiffuse = brightness * vLightColor_Directional[i] * vMaterial.y;

		directionalDiffuse.x = directionalDiffuse.x < 0 ? 0 : directionalDiffuse.x;
		directionalDiffuse.y = directionalDiffuse.y < 0 ? 0 : directionalDiffuse.y;
		directionalDiffuse.z = directionalDiffuse.z < 0 ? 0 : directionalDiffuse.z;
		directionalDiffuse.w = directionalDiffuse.w < 0 ? 0 : directionalDiffuse.w;

		diffuse += directionalDiffuse;
	}

	//Point
	for (int i = 0; i < vLightPosition_Point.length(); i++)
	{
		vec4 distanceToPoint =  fPosition - vLightPosition_Point[i];

		{
			float brightness = dot(vNormal, distanceToPoint) / (length(distanceToPoint) * length(distanceToPoint) * length(vNormal));
			brightness = clamp(brightness, 0, 1);
			vec4 pointDiffuse = brightness * vLightColor_Point[i] * vMaterial.y;

			pointDiffuse.x = pointDiffuse.x < 0 ? 0 : pointDiffuse.x;
			pointDiffuse.y = pointDiffuse.y < 0 ? 0 : pointDiffuse.y;
			pointDiffuse.z = pointDiffuse.z < 0 ? 0 : pointDiffuse.z;
			pointDiffuse.w = pointDiffuse.w < 0 ? 0 : pointDiffuse.w;

			diffuse += pointDiffuse;
		}
	}

	//Spot
	for (int i = 0; i < vLightPosition_Spot.length(); i++)
	{
		vec4 distanceToFrag =  fPosition - vLightPosition_Spot[i];

		{
			//Check if within cone
			if ( dot(distanceToFrag, vLightDirection_Spot[i]) / (length(distanceToFrag) * length(vLightDirection_Spot[i])) > cos(vLightAngle_Spot[i]/2.0f) )
			{
				float brightness = dot(vNormal, distanceToFrag) / (length(distanceToFrag) * length(distanceToFrag) * length(vNormal));
				brightness = clamp(brightness, 0, 1);
				vec4 spotDiffuse = brightness * vLightColor_Spot[i] * vMaterial.y;

				spotDiffuse.x = spotDiffuse.x < 0 ? 0 : spotDiffuse.x;
				spotDiffuse.y = spotDiffuse.y < 0 ? 0 : spotDiffuse.y;
				spotDiffuse.z = spotDiffuse.z < 0 ? 0 : spotDiffuse.z;
				spotDiffuse.w = spotDiffuse.w < 0 ? 0 : spotDiffuse.w;

				diffuse += spotDiffuse;
			}
		}
	}

	fColor = texture2D(texture, texCoord) * (ambientLight + diffuse);
		
	//if Alpha == 0, don't draw
	if (fColor.w == 0)
		discard;	

}