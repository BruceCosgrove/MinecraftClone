#pragma once

#include "Texture.h"

class OpenGLTexture
{
public:
	OpenGLTexture(const Texture& texture);
	~OpenGLTexture();

	void bind(unsigned int slot = 0) const;
	void unbind(unsigned int slot = 0) const;

	inline const Texture& getTexture() const { return texture; }

	// Call this when you want to update the internal
	// texture after the the local texture has updated.
	void update();
private:
	// TODO: when a reference counting system is in place, change this to that
	const Texture& texture;

	unsigned int rendererID = 0;
	int internalFormat = 0; // how opengl will store the texture data
	int localFormat = 0; // how the local copy of the texture data is stored
};
