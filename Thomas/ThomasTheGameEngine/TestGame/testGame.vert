#version 430 core

layout(location = 0) in vec4 vPosition;

in vec2 vTexCoord;
out vec2 texCoord;

out float faceDot; /* Face Culling -- Dot Product */

uniform float fColor;
uniform mat4 cameraMatrix;
uniform mat4 Transform;

uniform vec4 vTranslate;
uniform vec4 vNormal;
uniform vec4 camView;

layout(location = 1) out float vColor;

void main()
{
	gl_Position = cameraMatrix * (Transform * vPosition);
	vColor = fColor;

	texCoord = vTexCoord;

	/* Face Culling */
	vec4 v4Normal = (Transform * vNormal) - vTranslate;
	vec4 v4Cam = ((Transform * vPosition) - vTranslate) - (camView - vTranslate);
	faceDot = dot(vec3(v4Normal.x, v4Normal.y, v4Normal.z),  vec3(v4Cam.x, v4Cam.y, v4Cam.z));
}