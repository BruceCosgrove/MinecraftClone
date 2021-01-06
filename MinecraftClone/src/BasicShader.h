#pragma once

#include "Shader.h"
#include <glm/glm.hpp>

class BasicShader : public Shader
{
public:
	BasicShader();
	virtual ~BasicShader();

	virtual void bind() const override;
	virtual void unbind() const override;

	inline const glm::mat4& getMVP() const { return mvp; }
	inline void setMVP(const glm::mat4& mvp) { this->mvp = mvp; }
	inline unsigned int getTextureIndex() const { return textureIndex; }
	inline void setTextureIndex(unsigned int textureIndex) { this->textureIndex = textureIndex; }
private:
	glm::mat4 mvp{ 1.0f };
	unsigned int textureIndex = 0;
};
