#version 430 core

layout(location = 1) in float colour;
out vec4 fColor;
in vec2 texCoord;
uniform sampler2D texture;

in vec4 vAmbientColor;
in vec4 vLightColor;
in vec4 vLightDirection;
in vec3 vMaterial;
in vec4 vNormal;

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
			fColor = texture2D(texture, texCoord);		
		}

		//lighting calculations
		vec4 ambientLight = (vMaterial.x * vAmbientColor * fColor);

		vec4 diffuse = (vLightColor * vMaterial.y * dot(vLightDirection, vNormal));

		diffuse.x = diffuse.x < 0 ? 0 : diffuse.x;
		diffuse.y = diffuse.y < 0 ? 0 : diffuse.y;
		diffuse.z = diffuse.z < 0 ? 0 : diffuse.z;
		diffuse.w = diffuse.w < 0 ? 0 : diffuse.w;

		fColor = ambientLight + diffuse;
	}
	
}