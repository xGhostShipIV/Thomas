#include "Shader.h"
#include "OpenGLUtilities.h"

#define BUFFER_OFFSET(i) ((void*)(i))

/*********************************************************/
/*                       BASE                            */
/*********************************************************/
Shader::Shader(GLuint program_) : program(program_){}

Shader::~Shader(){}

GLuint Shader::GetProgram() const
{
	return program;
}

/*********************************************************/
/*                     CHILDREN                          */
/*********************************************************/
#pragma region GENERIC_SHADER
Generic_Shader* Generic_Shader::instance;

Generic_Shader* Generic_Shader::_GetInstance()
{
	if (!instance)
		instance = new Generic_Shader();

	return instance;
}
Generic_Shader::Generic_Shader() : Shader(GLU::CreateShaders("Generic.vert", "Generic.frag"))
{
	glUseProgram(program);

	//glBindAttribLocation(program, VERTEX_ATTRIBUTE, "vPosition");
	glBindAttribLocation(program, TEXTURE_ATTRIBUTE, "vTexCoord");
	glBindAttribLocation(program, NORMAL_ATTRIBUTE, "Normal");

	transform_Location = glGetUniformLocation(program, "Transform");
	rotate_Location = glGetUniformLocation(program, "Rotation");
	cameraPosition_Location = glGetUniformLocation(program, "CamPosition");
	ambient_Location = glGetUniformLocation(program, "AmbientColor");
	lightColor_Directional_Location = glGetUniformLocation(program, "LightColor_Directional");
	lightDirection_Directional_Location = glGetUniformLocation(program, "LightDirection_Directional");
	lightColor_Point_Location = glGetUniformLocation(program, "LightColor_Point");
	lightPosition_Point_Location = glGetUniformLocation(program, "LightPosition_Point");
	lightColor_Spot_Location = glGetUniformLocation(program, "LightColor_Spot");
	lightPosition_Spot_Location = glGetUniformLocation(program, "LightPosition_Spot");
	lightDirection_Spot_Location = glGetUniformLocation(program, "LightDirection_Spot");
	lightAngle_Spot_Location = glGetUniformLocation(program, "LightAngle_Spot");
	isEffectedByLight_Location = glGetUniformLocation(program, "IsEffectedByLight");
	material_Location = glGetUniformLocation(program, "Material");
	numberOfLights_Location = glGetUniformLocation(program, "NumberOfLights");
	view_Location = glGetUniformLocation(program, "view");
	projection_Location = glGetUniformLocation(program, "projection");
	opacity_Location = glGetUniformLocation(program, "Opacity");
}
Generic_Shader::~Generic_Shader(){}
#pragma endregion

#pragma region GUI_SHADER
GUI_Shader* GUI_Shader::instance;

GUI_Shader* GUI_Shader::_GetInstance()
{
	if (!instance)
		instance = new GUI_Shader();

	return instance;
}

GUI_Shader::GUI_Shader() : Shader(GLU::CreateShaders("GUI.vert", "GUI.frag"))
{
	glUseProgram(program);

	//glBindAttribLocation(program, VERTEX_ATTRIBUTE, "vPosition");
	glBindAttribLocation(program, TEXTURE_ATTRIBUTE, "vTexCoord");

	transform_Location = glGetUniformLocation(program, "Transform");
	drawPercent_Location = glGetUniformLocation(program, "drawPercent");
	opacity_Location = glGetUniformLocation(program, "Opacity");
}
GUI_Shader::~GUI_Shader(){}
#pragma endregion

#pragma region SUN_SHADER
Sun_Shader* Sun_Shader::instance;

Sun_Shader* Sun_Shader::_GetInstance()
{
	if (!instance)
		instance = new Sun_Shader();

	return instance;
}

Sun_Shader::Sun_Shader() : Shader(GLU::CreateShaders("Sun.vert", "Sun.frag"))
{
	glUseProgram(program);

	glBindAttribLocation(program, TEXTURE_ATTRIBUTE, "vTexCoord");

	transform_Location = glGetUniformLocation(program, "Transform");
	
	view_Location = glGetUniformLocation(program, "view");
	projection_Location = glGetUniformLocation(program, "projection");

	lightIntensity_Location = glGetUniformLocation(program, "lightIntensity");
	Offset_Location = glGetUniformLocation(program, "Offset");
}
Sun_Shader::~Sun_Shader(){}
#pragma endregion

#pragma region RAINBOW_GUI_SHADER
Rainbow_GUI_Shader* Rainbow_GUI_Shader::instance;

Rainbow_GUI_Shader* Rainbow_GUI_Shader::_GetInstance()
{
	if (!instance)
		instance = new Rainbow_GUI_Shader();

	return instance;
}

Rainbow_GUI_Shader::Rainbow_GUI_Shader() : Shader(GLU::CreateShaders("Rainbow_GUI.vert", "Rainbow_GUI.frag"))
{
	glUseProgram(program);
	glBindAttribLocation(program, TEXTURE_ATTRIBUTE, "vTexCoord");

	transform_Location = glGetUniformLocation(program, "Transform");
	drawPercent_Location = glGetUniformLocation(program, "drawPercent");
}
Rainbow_GUI_Shader::~Rainbow_GUI_Shader(){}
#pragma endregion