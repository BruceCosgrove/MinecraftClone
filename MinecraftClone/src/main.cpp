#include <iostream>
#include <vector>

#include "Window.h"
#include "Renderer.h"
#include "ImGuiWrapper.h"
#include "Scene.h"
#include "MinecraftScene.h"

int main()
{
	// 11:44 https://www.youtube.com/watch?v=7D8lLbp9_rQ&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&index=23
	
	{
		// GLFW must be destroyed after all buffers and some other stuff
		Window window;
		{
			ImGuiWrapper imguiWrapper(window);

			BasicRenderer basicRenderer;
			Renderer& renderer = basicRenderer.getRenderer();
			renderer.setClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });

			Scene* scene = new MinecraftScene();

			while (!window.shouldClose())
			{
				renderer.clear();

				scene->onUpdate(0.0f);
				scene->onRender(basicRenderer);

				imguiWrapper.begin();
				scene->onImGuiRender();
				imguiWrapper.end();

				window.swapBuffers();
				window.pollEvents();
			}

			delete scene;
		}
	}

	return 0;
}
