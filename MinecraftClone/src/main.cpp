#include <iostream>

#include "Window.h"
#include "Renderer.h"

#include "VertexArray.h"
#include "BufferLayout.h"
#include "BasicShader.h"
#include "Material.h"
#include "ImGuiWrapper.h"
#include <glm/glm.hpp>

//#include <imgui/imgui.h>

int main()
{
	// 11:44 https://www.youtube.com/watch?v=7D8lLbp9_rQ&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&index=23

	// GLFW must be destroyed after all buffers and some other stuff
	Window window;
	{
		ImGuiWrapper imguiWrapper(window);

		Renderer renderer;
		renderer.setClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });

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
		vertexArray.addVertexBuffer(&vertexBuffer);

		BasicShader basicShader;
		Texture localTexture("resources/textures/sapling_oak.png", 4);
		OpenGLTexture texture(localTexture);
		Material material(&basicShader, &texture);

		while (!window.shouldClose())
		{
			renderer.clear();

			renderer.draw(vertexArray, indexBuffer, material);

			imguiWrapper.begin();
			// All ImGui rendering should go between these
			// When sufficient abstraction has been implemented,
			// Have each class that has imgui code have their own
			// onImGuiRender methods called here.
			//static bool show = true;
			//ImGui::ShowDemoWindow(&show);
			imguiWrapper.end();

			window.swapBuffers();
			window.pollEvents();
		}
	}

	return 0;
}
