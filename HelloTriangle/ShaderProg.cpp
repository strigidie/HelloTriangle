#include "App.hpp"

ShaderProg::ShaderProg(void) : _shaderProgram(glCreateProgram())
{
	// Init Shader Program
	M_GL_LASTERROR;
}

ShaderProg::~ShaderProg(void)
{
	// Delete Shader Program
	glDeleteProgram(_shaderProgram); M_GL_LASTERROR;
}

void ShaderProg::attach(const std::string& path, const unsigned int type)
{
	// Create shader
	const unsigned int shader = glCreateShader(type); M_GL_LASTERROR;
	
	// Read source file of the shader
	std::string shaderSourceStr = readShaderFile(path);
	const char* shaderSource = shaderSourceStr.c_str();
	glShaderSource(shader, 1, &shaderSource, NULL); M_GL_LASTERROR;

	// Compile shader
	glCompileShader(shader);

	// Check compilation status
	int status;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status); M_GL_LASTERROR;
	if (!status)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog); M_GL_LASTERROR;
		std::cout << infoLog;
	}
	else
	{
		// Attach the shader if status is ok
		glAttachShader(_shaderProgram, shader); M_GL_LASTERROR;
		glDeleteShader(shader); M_GL_LASTERROR;
	}
}

void ShaderProg::link(void)
{
	// Link all loaded shaders
	glLinkProgram(_shaderProgram);

	// Check linkage status
	int status;
	char infoLog[512];
	glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &status); M_GL_LASTERROR;
	if (!status)
	{
		glGetProgramInfoLog(_shaderProgram, 512, NULL, infoLog); M_GL_LASTERROR;
		std::cout << infoLog;
	}
}

void ShaderProg::use(void)
{
	// Use Shader Program
	glUseProgram(_shaderProgram);
}

void ShaderProg::addUniform(const std::string& varName)
{
	_uniformVars[varName] = glGetUniformLocation(_shaderProgram, varName.c_str()); M_GL_LASTERROR;
}

void ShaderProg::setUniform(const std::string& varName, const float value)
{
	glUniform1f(_uniformVars[varName], value); M_GL_LASTERROR;
}

std::string ShaderProg::readShaderFile(const std::string& path)
{
	std::ifstream file(path);

	if (!file.is_open())
		return "";

	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();

	return buffer.str();
}