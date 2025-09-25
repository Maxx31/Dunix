#pragma once

#include "Dunix/Core/Layer.h"

namespace Dunix
{
	class DUNIX_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate() override;
		virtual void OnEvent(Event& e) override;

	private:

		bool OnMouseMovedEvent(class MouseMovedEvent& e);
		bool OnMouseButtonPressedEvent(class MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(class MouseButtonReleasedEvent& e);
		bool OnMouseScrolledEvent(class MouseScrolledEvent& e);

		bool OnKeyPressedEvent(class KeyPressedEvent& e);
		bool OnKeyReleasedEvent(class KeyReleasedEvent& e);
		bool OnKeyTypedEvent(class KeyTypedEvent& e);

	private:
		float m_Time = 0.0f;
	};
}