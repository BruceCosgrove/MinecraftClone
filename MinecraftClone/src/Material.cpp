#include "Material.h"

Material::Material(const Shader* shader, const OpenGLTexture* texture, unsigned int textureSlot, const glm::vec4& tint)
	: shader(shader), texture(texture), textureSlot(textureSlot), tint(tint)
{

}

void Material::bind() const
{
	if (shader != nullptr)
		shader->bind();
	if (texture != nullptr)
		texture->bind(textureSlot);
}

void Material::unbind() const
{
	if (shader != nullptr)
		shader->unbind();
	if (texture != nullptr)
		texture->unbind(textureSlot);
}
