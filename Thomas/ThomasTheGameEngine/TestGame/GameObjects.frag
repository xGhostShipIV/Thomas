#version 430 core

out vec4 fColor;
in vec2 texCoord;
uniform sampler2D texture;

in vec3 vMaterial;
in vec4 vNormal;
in vec4 fPosition;

in vec3 vCamPosition;

in vec4 vAmbientColor;
in vec4[1] vLightColor_Directional;
in vec4[1] vLightDirection_Directional;

in vec4[2]  vLightColor_Point;
in vec4[2]  vLightPosition_Point;

in vec4[2]	vLightColor_Spot;
in vec4[2]  vLightPosition_Spot;
in vec4[2]  vLightDirection_Spot;
in float[2] vLightAngle_Spot;

in vec3 fIsEffectedByLight;
in float fUiDraw;

void main()
{

	//Normals Debug View
	bool normalsDebug = false;
	if (normalsDebug)
	{
		if (fUiDraw > 0)
			discard;
		fColor = 0.5 * vNormal + 0.5;
	}
	else if (fUiDraw > 0)
		fColor = texture2D(texture, texCoord);
	else
	{
		/* AMBIENT LIGHTING */
		vec4 ambientLight = (vMaterial.x * vAmbientColor);

		if (length(fIsEffectedByLight) == 0)
			ambientLight = vec4(1, 1, 1, 1);

		/* DIFFUSE LIGHTING */
		vec4 diffuse = vec4(0, 0, 0, 0);

		/* SPECULAR LIGHTING */
		vec4 specular = vec4(0, 0, 0, 0);


		vec4 toCameraVector = normalize(vec4(vCamPosition, 0.0) - fPosition);

		if (fIsEffectedByLight.x > 0)
		{
			/* DIRECTIONAL */
			for (int i = 0; i < vLightDirection_Directional.length(); i++)
			{
				//vec4 directionalDiffuse = (vLightColor_Directional[i] * vMaterial.y * dot(vLightDirection_Directional[i], vNormal));

				float brightness = dot(vNormal, -vLightDirection_Directional[i]) / ( length(vLightDirection_Directional[i]) * length(vNormal) );
				brightness = clamp(brightness, 0, 1);
				vec4 directionalDiffuse = brightness * vLightColor_Directional[i] * vMaterial.y;

				/*directionalDiffuse.x = directionalDiffuse.x < 0 ? 0 : directionalDiffuse.x;
				directionalDiffuse.y = directionalDiffuse.y < 0 ? 0 : directionalDiffuse.y;
				directionalDiffuse.z = directionalDiffuse.z < 0 ? 0 : directionalDiffuse.z;
				directionalDiffuse.w = directionalDiffuse.w < 0 ? 0 : directionalDiffuse.w;*/

				diffuse += directionalDiffuse;
			}
		}

		if (fIsEffectedByLight.y > 0)
		{
			/* POINT */
			for (int i = 0; i < vLightPosition_Point.length(); i++)
			{
				vec4 distanceToPoint =  fPosition - vLightPosition_Point[i];
				vec4 toPointLight =  normalize(vLightPosition_Point[i] - fPosition);

				{
					float brightness = dot(vNormal, toPointLight);
					brightness = clamp(brightness, 0.0f, 1.0f) / ( length(toPointLight) * length(vNormal) * pow(length(distanceToPoint), 2) );
					vec4 pointDiffuse = brightness * vLightColor_Point[i] * vMaterial.y;
					diffuse += pointDiffuse;
				}

				vec4 lightDirection = fPosition - vLightPosition_Point[i];
				vec4 reflection =  reflect(normalize(lightDirection), vNormal);
				float sp_brightness = max(dot(reflection, toCameraVector), 0.0);
				vec4 pointSpecular = (pow(sp_brightness, 5) / (length(distanceToPoint) * length(distanceToPoint))) * vMaterial.z * vLightColor_Point[i];
				specular += pointSpecular;
			}
		}

		if (fIsEffectedByLight.z > 0)
		{
			/* SPOT */
			for (int i = 0; i < vLightPosition_Spot.length(); i++)
			{
				vec4 distanceToFrag =  fPosition - vLightPosition_Spot[i];
				vec4 toSpotLight =  normalize(vLightPosition_Spot[i] - fPosition);

				{
					//Check if within cone
					if ( dot(distanceToFrag, vLightDirection_Spot[i]) / (length(distanceToFrag) * length(vLightDirection_Spot[i])) > cos(vLightAngle_Spot[i]/2.0f) )
					{
						float distanceOfAngle = (vLightAngle_Spot[i]/2.0f) - acos(dot(distanceToFrag, vLightDirection_Spot[i]) / (length(distanceToFrag) * length(vLightDirection_Spot[i])));

						float brightness = dot(vNormal, toSpotLight) / (pow(length(distanceToFrag),2) * length(toSpotLight) * length(vNormal)) * (distanceOfAngle / (vLightAngle_Spot[i]/2.0f));
						brightness = clamp(brightness, 0, 1);
						vec4 spotDiffuse = brightness * vLightColor_Spot[i] * vMaterial.y;
						diffuse += spotDiffuse;

						vec4 reflection =  reflect(normalize(vLightDirection_Spot[i]), vNormal);
						float sp_brightness = max(dot(toCameraVector, reflection), 0.0);
						vec4 spotSpecular = (pow(sp_brightness, 5) / (pow(length(distanceToFrag), 2) )) * vMaterial.z * (distanceOfAngle / (vLightAngle_Spot[i]/2.0f)) * vLightColor_Spot[i];
						specular += spotSpecular;
					}
				}
			}
		}

		diffuse.x = diffuse.x > 1 ? 1 : diffuse.x;
		diffuse.y = diffuse.y > 1 ? 1 : diffuse.y;
		diffuse.z = diffuse.z > 1 ? 1 : diffuse.z;
		diffuse.w = diffuse.w > 1 ? 1 : diffuse.w;

		specular.x = specular.x > 1 ? 1 : specular.x;
		specular.y = specular.y > 1 ? 1 : specular.y;
		specular.z = specular.z > 1 ? 1 : specular.z;
		specular.w = specular.w > 0 ? 0 : specular.w;


		fColor = specular + texture2D(texture, texCoord) * (ambientLight + diffuse);
	}


	//if Alpha == 0, don't draw
	if (fColor.w == 0)
		discard;	

}