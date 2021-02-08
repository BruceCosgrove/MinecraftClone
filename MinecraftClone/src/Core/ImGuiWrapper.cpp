#include "ImGuiWrapper.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <glfw/glfw3.h>

#include <iostream>

ImGuiWrapper::ImGuiWrapper(const Window& window)
	: window(window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	init();
	ImGui_ImplGlfw_InitForOpenGL(window.getNativeWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 460"); // TODO: this version should be gotten from the window
}

ImGuiWrapper::~ImGuiWrapper()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiWrapper::begin()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void ImGuiWrapper::end()
{
	ImGuiIO& io = ImGui::GetIO();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(context);
	}
}

void ImGuiWrapper::init()
{
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_ViewportsEnable;

	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowRounding = 0.0f;

	// Colors
	ImGui::StyleColorsDark();

	auto& colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_WindowBg] = { 0.1f, 0.105f, 0.11f, 1.0f };

	// Headers
	colors[ImGuiCol_Header] = { 0.2f, 0.205f, 0.21f, 1.0f };
	colors[ImGuiCol_HeaderHovered] = { 0.3f, 0.305f, 0.31f, 1.0f };
	colors[ImGuiCol_HeaderActive] = { 0.15f, 0.155f, 0.16f, 1.0f };

	// Buttons
	colors[ImGuiCol_Button] = { 0.2f, 0.205f, 0.21f, 1.0f };
	colors[ImGuiCol_ButtonHovered] = { 0.3f, 0.305f, 0.31f, 1.0f };
	colors[ImGuiCol_ButtonActive] = { 0.15f, 0.155f, 0.16f, 1.0f };

	// Frame Background
	colors[ImGuiCol_FrameBg] = { 0.2f, 0.205f, 0.21f, 1.0f };
	colors[ImGuiCol_FrameBgHovered] = { 0.3f, 0.305f, 0.31f, 1.0f };
	colors[ImGuiCol_FrameBgActive] = { 0.15f, 0.155f, 0.16f, 1.0f };

	// Tabs
	colors[ImGuiCol_Tab] = { 0.15f, 0.155f, 0.16f, 1.0f };
	colors[ImGuiCol_TabHovered] = { 0.38f, 0.385f, 0.39f, 1.0f };
	colors[ImGuiCol_TabActive] = { 0.28f, 0.285f, 0.29f, 1.0f };
	colors[ImGuiCol_TabUnfocused] = { 0.15f, 0.155f, 0.16f, 1.0f };
	colors[ImGuiCol_TabUnfocusedActive] = { 0.2f, 0.205f, 0.21f, 1.0f };

	// Title Background
	colors[ImGuiCol_TitleBg] = { 0.15f, 0.155f, 0.16f, 1.0f };
	colors[ImGuiCol_TitleBgActive] = { 0.15f, 0.155f, 0.16f, 1.0f };
	colors[ImGuiCol_TitleBgCollapsed] = { 0.15f, 0.155f, 0.16f, 1.0f };
}
