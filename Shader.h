#pragma once
#include <vector>

class Shader
{
public:
	Shader();

	// Variables
	unsigned int shader_program;

	int success;
	char info_log[512];

	std::vector<float> vertices;
	unsigned int VAO, VBO, EBO;

	unsigned int texture1, texture2;

	// Fucntions
	void Create(const char* vertex_path, const char* fragment_path);
	void Config(std::vector<float> vertices, std::vector<unsigned int> indices);
	void Load_Texture(std::string texture1_path, std::string texture2_path);
	void Use();
	void Unbind();
	void Clean_Up();

	// Utility Uniform
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;

private:
	

};

