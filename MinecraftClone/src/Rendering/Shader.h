#pragma once

#include <vector>
#include <string>
#include <unordered_map>

enum class ShaderType
{
	Vertex,
	TessolationControl,
	TessolationEvaluation,
	Geometry,
	Fragment,
	Compute
};

struct ShaderFile
{
	ShaderType type;
	std::string source;
};

class ShaderProgram
{
public:
	ShaderProgram(const std::vector<ShaderFile>& shaders);
	~ShaderProgram();

	void bind() const;
	void unbind() const;

	template<typename T>
	void setUniform(const std::string& name, const T& value) const;

	template<typename T>
	void setUniforms(const std::string& name, const T* values, int count) const;
private:
	bool linkAndValidate();
	unsigned int compile(const ShaderFile& shader);
	int getUniformLocation(const std::string& name) const;

	unsigned int rendererID = 0;
	mutable std::unordered_map<std::string, int> uniformLocations;
};

class Shader
{
public:
	virtual ~Shader() = default;

	virtual void bind() const = 0;
	virtual void unbind() const = 0;
protected:
	ShaderProgram* program = nullptr;
};
