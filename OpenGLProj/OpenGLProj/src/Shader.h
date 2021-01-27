#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
private:
	char infoLog[512];
	int getLocation(const std::string & name) const;
public:
	unsigned int ID;
	const char* vPath, * fPath;
	Shader(const char* vertexPath, const char* fragmentPath);

	void use() const;
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setFloat4_4(const std::string& name, glm::mat4 value) const;
	void setFloatv3(const std::string& name, glm::vec3 val) const;
	void setFloatv3(const std::string& name, float x, float y, float z) const;

};

#endif

