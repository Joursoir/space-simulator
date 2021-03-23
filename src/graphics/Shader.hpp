#ifndef ENGINE_SHADER_H
#define ENGINE_SHADER_H

class Shader {
	GLuint shader_id;
	GLchar *error_log;

public:
	Shader() : shader_id(0), error_log(0) { }
	~Shader();

	int Compile(const char *source, GLenum shaderType);
	char *GetError() { return error_log; }
	GLuint GetID() { return shader_id; }
};

class ShaderManager {
	GLuint program_id;
	GLchar *error_log;

public:
	ShaderManager() : program_id(0), error_log(0) { }
	~ShaderManager();

	int Link(Shader *arr, int nsize);
	char *GetError() { return error_log; }
	GLuint GetID() { return program_id; }
	void Use();
};

#endif /* ENGINE_SHADER_H */
