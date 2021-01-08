#include "OpenGLTexture.h"

#include <gl/glew.h>

OpenGLTexture::OpenGLTexture(const Texture* texture)
	: texture(texture)
{
	// TODO: this should be from texture specifications
	switch (texture->getChannels())
	{
		case 1: internalFormat = GL_R8; localFormat = GL_R; break;
		case 2: internalFormat = GL_RG8; localFormat = GL_RG; break;
		case 3: internalFormat = GL_RGB8; localFormat = GL_RGB; break;
		case 4: internalFormat = GL_RGBA8; localFormat = GL_RGBA; break;
	}

	glCreateTextures(GL_TEXTURE_2D, 1, &rendererID);
	glTextureStorage2D(rendererID, 1, internalFormat, texture->getWidth(), texture->getHeight());

	// TODO: this should be from texture specifications
	glTextureParameteri(rendererID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTextureParameteri(rendererID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTextureParameteri(rendererID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// TODO: this should be from texture specifications ---------------------------------------------VVVVVVVVVVVVVVVV
	glTextureSubImage2D(rendererID, 0, 0, 0, texture->getWidth(), texture->getHeight(), localFormat, GL_UNSIGNED_BYTE, texture->getData());
}

OpenGLTexture::~OpenGLTexture()
{
	glDeleteTextures(1, &rendererID);
}

void OpenGLTexture::bind(unsigned int slot) const
{
	glBindTextureUnit(slot, rendererID);
}

void OpenGLTexture::unbind(unsigned int slot) const
{
	glBindTextureUnit(slot, 0);
}

void OpenGLTexture::update()
{
	// TODO: this should be from texture specifications ---------------------------------------------VVVVVVVVVVVVVVVV
	glTextureSubImage2D(rendererID, 0, 0, 0, texture->getWidth(), texture->getHeight(), localFormat, GL_UNSIGNED_BYTE, texture->getData());
}
