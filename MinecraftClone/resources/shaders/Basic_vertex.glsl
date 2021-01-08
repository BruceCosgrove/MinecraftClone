#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 tintColor;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in float texIndex;

out vec2 _texCoord;

uniform mat4 projection;
uniform mat4 cameraTransform;

void main()
{
	mat4 view = inverse(cameraTransform);
	
	gl_Position = projection * view * vec4(position, 1.0);
	_texCoord = texCoord;
}
