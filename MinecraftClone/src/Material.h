#pragma once

#include "Shader.h"
#include "OpenGLTexture.h"
#include <glm/glm.hpp>

class Material
{
public:
	Material(const Shader* shader = nullptr, const OpenGLTexture* texture = nullptr, unsigned int texSlot = 0, const glm::vec4& tint = glm::vec4(1.0f));

	void bind() const;
	void unbind() const;

	inline const Shader* getShader() const { return shader; }
	inline void setShader(const Shader* shader) { this->shader = shader; }

	inline const OpenGLTexture* getTexure() const { return texture; }
	inline void setTexture(const OpenGLTexture* texture) { this->texture = texture; }

	inline unsigned int getTexureSlot() const { return textureSlot; }
	inline void setTextureSlot(unsigned int textureSlot) { this->textureSlot = textureSlot; }

	inline const glm::vec4& getTint() const { return tint; }
	inline void setTint(const glm::vec4& tint) { this->tint = tint; }
protected:
	const Shader* shader;
	const OpenGLTexture* texture;
	unsigned int textureSlot;
	glm::vec4 tint;
};
