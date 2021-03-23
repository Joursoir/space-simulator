#include <GL/glew.h>

#include "Shader.hpp"

Shader::~Shader()
{
	if(shader_id)
		glDeleteShader(shader_id);
	if(error_log)
		delete[] error_log;
}

int Shader::Compile(const char *source, GLenum shaderType)
{
	GLint success;

	shader_id = glCreateShader(shaderType);
	glShaderSource(shader_id, 1, &source, NULL);
	glCompileShader(shader_id);
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
	if(success == 0) {
		error_log = new char[GL_INFO_LOG_LENGTH];
		glGetShaderInfoLog(shader_id, GL_INFO_LOG_LENGTH, NULL, error_log);
		return 1;
	}
	return 0;
}

////////////////////////////////////////////////////////////////////

ShaderManager::~ShaderManager()
{
	if(program_id)
		glDeleteProgram(program_id);
	if(error_log)
		delete[] error_log;
}

int ShaderManager::Link(Shader *arr, int nsize)
{
	GLint success;
	int i;

	program_id = glCreateProgram();
	for(i = 0; i < nsize; i++)
		glAttachShader(program_id, arr[i].GetID());
	glLinkProgram(program_id);
	glGetProgramiv(program_id, GL_LINK_STATUS, &success);
	if(success == 0) {
		error_log = new char[GL_INFO_LOG_LENGTH];
		glGetProgramInfoLog(program_id, GL_INFO_LOG_LENGTH, NULL, error_log);
		return 1;
	}
	return 0;
}

void ShaderManager::Use()
{
	glUseProgram(program_id);
}
