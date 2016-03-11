#version 430 core

out vec4 fColor;
uniform sampler2D texture;
in vec2 texCoord;

uniform float drawPercent;

void main()
{
	fColor = texture2D(texture, texCoord);

	if (texCoord.x > drawPercent)
		discard;

	//if Alpha == 0, don't draw
	if (fColor.w == 0)
		discard;
}