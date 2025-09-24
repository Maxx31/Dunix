#include "dxpch.h"

#include "GLFW/glfw3.h"
#include "imgui.h"
#include "ImGuiLayer.h"

#include "Dunix/Core/Application.h"
#include "Dunix/Window/Window.h"
#include "Dunix/Renderer/ImGuiOpenGLRenderer.h"

#include <Dunix/Events/EventDispatcher.h>
#include <Dunix/Events/MouseEvent.h>
#include <Dunix/Events/KeyEvent.h>

namespace Dunix
{
	ImGuiLayer::ImGuiLayer()
		:Layer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

		io.SetKeyEventNativeData(ImGuiKey_Tab, GLFW_KEY_TAB, GLFW_KEY_TAB);
		io.SetKeyEventNativeData(ImGuiKey_LeftArrow, GLFW_KEY_LEFT, GLFW_KEY_LEFT);
		io.SetKeyEventNativeData(ImGuiKey_RightArrow, GLFW_KEY_RIGHT, GLFW_KEY_RIGHT);
		io.SetKeyEventNativeData(ImGuiKey_UpArrow, GLFW_KEY_UP, GLFW_KEY_UP);
		io.SetKeyEventNativeData(ImGuiKey_DownArrow, GLFW_KEY_DOWN, GLFW_KEY_DOWN);
		io.SetKeyEventNativeData(ImGuiKey_PageUp, GLFW_KEY_PAGE_UP, GLFW_KEY_PAGE_UP);
		io.SetKeyEventNativeData(ImGuiKey_PageDown, GLFW_KEY_PAGE_DOWN, GLFW_KEY_PAGE_DOWN);
		io.SetKeyEventNativeData(ImGuiKey_Home, GLFW_KEY_HOME, GLFW_KEY_HOME);
		io.SetKeyEventNativeData(ImGuiKey_End, GLFW_KEY_END, GLFW_KEY_END);
		io.SetKeyEventNativeData(ImGuiKey_Insert, GLFW_KEY_INSERT, GLFW_KEY_INSERT);
		io.SetKeyEventNativeData(ImGuiKey_Delete, GLFW_KEY_DELETE, GLFW_KEY_DELETE);
		io.SetKeyEventNativeData(ImGuiKey_Backspace, GLFW_KEY_BACKSPACE, GLFW_KEY_BACKSPACE);
		io.SetKeyEventNativeData(ImGuiKey_Space, GLFW_KEY_SPACE, GLFW_KEY_SPACE);
		io.SetKeyEventNativeData(ImGuiKey_Enter, GLFW_KEY_ENTER, GLFW_KEY_ENTER);
		io.SetKeyEventNativeData(ImGuiKey_Escape, GLFW_KEY_ESCAPE, GLFW_KEY_ESCAPE);
		io.SetKeyEventNativeData(ImGuiKey_A, GLFW_KEY_A, GLFW_KEY_A);
		io.SetKeyEventNativeData(ImGuiKey_C, GLFW_KEY_C, GLFW_KEY_C);
		io.SetKeyEventNativeData(ImGuiKey_V, GLFW_KEY_V, GLFW_KEY_V);
		io.SetKeyEventNativeData(ImGuiKey_X, GLFW_KEY_X, GLFW_KEY_X);
		io.SetKeyEventNativeData(ImGuiKey_Y, GLFW_KEY_Y, GLFW_KEY_Y);
		io.SetKeyEventNativeData(ImGuiKey_Z, GLFW_KEY_Z, GLFW_KEY_Z);

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{

	}

	void ImGuiLayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();

		Application& app = Application::GetApplication();
		io.DisplaySize = ImVec2(app.GetWindow()->GetWidth(), app.GetWindow()->GetHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f); //Calculate time between frames
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<MouseMovedEvent>(std::bind(&ImGuiLayer::OnMouseMovedEvent, this, std::placeholders::_1));
		dispatcher.Dispatch<MouseButtonPressedEvent>(std::bind(&ImGuiLayer::OnMouseButtonPressedEvent, this, std::placeholders::_1));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(std::bind(&ImGuiLayer::OnMouseButtonReleasedEvent, this, std::placeholders::_1));

		dispatcher.Dispatch<KeyPressedEvent>(std::bind(&ImGuiLayer::OnKeyPressedEvent, this, std::placeholders::_1));
		dispatcher.Dispatch<KeyReleasedEvent>(std::bind(&ImGuiLayer::OnKeyReleasedEvent, this, std::placeholders::_1));
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		return true;
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		return true;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		return true;
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		return true;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
		return true;
	}
}