#version 460 core

in vec2 _texCoord;

out vec4 outColor;

uniform sampler2D sampler;

void main()
{
	outColor = texture(sampler, _texCoord);
}
