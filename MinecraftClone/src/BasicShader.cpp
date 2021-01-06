#include "BasicShader.h"
#include "FileIO.h"

BasicShader::BasicShader()
{
	std::vector<ShaderFile> shaderFiles = {
		{ ShaderType::Vertex, FileIO::readFile("resources/shaders/BasicShader_vertex.glsl") },
		{ ShaderType::Fragment, FileIO::readFile("resources/shaders/BasicShader_fragment.glsl") }
	};
	program = new ShaderProgram(shaderFiles);
}

BasicShader::~BasicShader()
{
	delete program;
}

void BasicShader::bind() const
{
	program->bind();
	program->setUniform("mvp", mvp);
	program->setUniform("sampler", textureIndex);
}

void BasicShader::unbind() const
{
	program->unbind();
}
