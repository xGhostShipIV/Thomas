#version 430 core

layout(location = 0) in vec4 vPosition;
layout(location = 2) in vec4 Normal;
in vec2 vTexCoord;
out vec2 texCoord;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 Transform; //model
uniform mat4 Rotation; //for normals
uniform vec3 CamPosition;

out vec4 vNormal;
out vec4 worldPosition;

out vec4 toCameraVector;
out float distanceToVertex;

void main()
{
	//				Projection	View	Model
	gl_Position = projection * view * (Transform * vPosition);

	//World Position
	worldPosition = Transform * vPosition;

	//Need to rotate normals
	vNormal =  normalize(Rotation * Normal);

	texCoord = vTexCoord;

	toCameraVector = normalize(vec4(CamPosition, 0.0) - worldPosition);

	distanceToVertex = length(vec4(CamPosition, 0.0) - worldPosition);
}