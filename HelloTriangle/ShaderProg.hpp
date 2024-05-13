#pragma once

#include "App.hpp"

class ShaderProg
{
private:
	unsigned int _shaderProgram;
	std::map<std::string, unsigned int> _uniformVars;

public:
	ShaderProg(void);
	~ShaderProg(void);

	void attach(const std::string& path, const unsigned int type);
	void link(void);
	void use(void);

	void addUniform(const std::string& varName);
	void setUniform(const std::string& varName, const float value);

private:
	static std::string readShaderFile(const std::string& path);
};