#include <iostream>

#include "Window.h"
#include "Renderer.h"

#include "VertexArray.h"

int main()
{
	// Shaders: youtube.com/watch?v=71BLZwRGUJE&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&index=7

	// GLFW must be destroyed after all buffers and some other stuff
	Window window;
	{
		Renderer renderer;
		
		float vertices[] = {
			-0.5f, -0.5f, 0.0f,  0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f,  1.0f, 1.0f,
			 0.5f,  0.5f, 0.0f,  1.0f, 0.0f,
			-0.5f,  0.5f, 0.0f,  0.0f, 0.0f,
		};
		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		BufferLayout bufferLayout = {{
			{ ElementType::Float3 },
			{ ElementType::Float2 }
		}};
		VertexBuffer vertexBuffer(sizeof(vertices), vertices);
		vertexBuffer.setBufferLayout(&bufferLayout);

		IndexBuffer indexBuffer(sizeof(indices) / sizeof(unsigned int), indices);

		VertexArray vertexArray;
		vertexArray.setIndexBuffer(&indexBuffer);
		vertexArray.addVertexBuffer(&vertexBuffer);

		while (!window.shouldClose())
		{
			renderer.clear();
			renderer.draw(vertexArray);

			window.swapBuffers();
			window.pollEvents();
		}
	}

	return 0;
}
