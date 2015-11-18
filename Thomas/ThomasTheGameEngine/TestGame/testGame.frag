#version 430 core

layout(location = 1) in float colour;
out vec4 fColor;
in vec2 texCoord;
uniform sampler2D texture;

in vec4 vAmbientColor;
in vec4[2] vLightColor_Directional;
in vec4[2] vLightDirection_Directional;
in vec3 vMaterial;
in vec4 vNormal;
in vec4 fPosition;

void main()
{	

	{
		float avgV = abs(colour);

		float MEDIUM_LOW_SPEED = 250, 
			MEDIUM_HIGH_SPEED = 500,
				HIGH_SPEED = 750,
					MAX_SPEED = 1000;
    
		if (colour > 0)
		{
			float r = 0, g = 0, b = 0;

			avgV = avgV < 0 ? 0 : avgV;
			avgV = avgV > MAX_SPEED ? MAX_SPEED : avgV;

			//Low speed (blue @ 255; Green++)
			if (avgV <= MEDIUM_LOW_SPEED) // > 0
			{
				r = 21;
				b = 255;
				g = 21 + (avgV / (MEDIUM_LOW_SPEED - 0)) * 234;
			}
			//Medium-Low speed (Green @ 255; Blue--)
			else if (avgV <= MEDIUM_HIGH_SPEED)
			{
				r = 21;
				b = 255 - ((avgV - MEDIUM_LOW_SPEED) / (MEDIUM_HIGH_SPEED - MEDIUM_LOW_SPEED)) * 234;
				g = 255;
			}
			//Medium-High speed (Green @ 255; Red++)
			else if (avgV <= HIGH_SPEED)
			{
				r = 21 + ((avgV - MEDIUM_HIGH_SPEED) / (HIGH_SPEED - MEDIUM_HIGH_SPEED)) * 234;
				b = 21;
				g = 255;
			}
			//High speed (Red @ 255; Green--)
			else if (avgV <= MAX_SPEED)
			{
				r = 255;
				b = 21;
				g = 255 - ((avgV - HIGH_SPEED) / (MAX_SPEED - HIGH_SPEED)) * 234;
			}

			fColor = vec4(r/255.0f, g/255.0f, b/255.0f, 1.0f);
		}
		else if (colour == -1)
		{
			fColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
		}
		else
		{
			//Ambient
			vec4 ambientLight = (vMaterial.x * vAmbientColor * texture2D(texture, texCoord));

			//Direction
			vec4 diffuse = vec4(0, 0, 0, 0);

			for (int i = 0; i < vLightDirection_Directional.length(); i++)
			{
				vec4 directionalDiffuse = (vLightColor_Directional[i] * vMaterial.y * dot(vLightDirection_Directional[i], vNormal));

				directionalDiffuse.x = directionalDiffuse.x < 0 ? 0 : directionalDiffuse.x;
				directionalDiffuse.y = directionalDiffuse.y < 0 ? 0 : directionalDiffuse.y;
				directionalDiffuse.z = directionalDiffuse.z < 0 ? 0 : directionalDiffuse.z;
				directionalDiffuse.w = directionalDiffuse.w < 0 ? 0 : directionalDiffuse.w;

				diffuse += directionalDiffuse;
			}


			fColor = ambientLight + diffuse;
		}
		
	}
	
}