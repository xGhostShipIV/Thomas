#version 430 core

layout(location = 0) in vec4 vPosition;
in vec2 vTexCoord;
out vec2 texCoord;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 Transform; //model
uniform mat4 Rotation; //for normals

out vec3  worldPosition;

void main()
{
	//				Projection	View	Model
	gl_Position = projection * view * (Transform * vPosition);

	vec4 vertex =  vPosition;
	worldPosition = vertex.xyz;

	texCoord = vTexCoord;
}