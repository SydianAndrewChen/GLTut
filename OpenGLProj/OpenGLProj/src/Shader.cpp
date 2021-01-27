#include "Shader.h"
#include "Renderer.h"



Shader::Shader(const char* vertexPath, const char* fragmentPath) : vPath(vertexPath), fPath(fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e) 
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	unsigned int vertex, fragment;
	int success;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) 
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		ASSERT(false);
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);	
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		ASSERT(false);
	}

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) 
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		ASSERT(false);
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use() const
{
	GLCall(glUseProgram(ID));
}

int Shader::getLocation(const std::string& name) const
{
	int location = glGetUniformLocation(ID, name.c_str());
	if (location == -1) {
		ASSERT(false);
		return -1;
	}
	return location;
}

void Shader::setBool(const std::string& name, bool value) const
{
	GLCall(glUniform1i(getLocation(name), (int)value));
}

void Shader::setInt(const std::string& name, int value) const
{
	GLCall(glUniform1i(getLocation(name), value));
}

void Shader::setFloat(const std::string& name, float value) const
{
	GLCall(glUniform1f(getLocation(name), value));
}

void Shader::setFloat4_4(const std::string& name, glm::mat4 value) const
{
	GLCall(glUniformMatrix4fv(getLocation(name),1, GL_FALSE, glm::value_ptr(value)));
}


void Shader::setFloatv3(const std::string& name, glm::vec3 val) const
{
	setFloatv3(name, val.x, val.y, val.z);
}

void Shader::setFloatv3(const std::string& name, float x, float y, float z) const
{
	GLCall(glUniform3f(getLocation(name), x, y, z));
}