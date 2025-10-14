#pragma once

#include "../../dxpch.h"

#include "Core.h"

namespace Dunix
{
	class DUNIX_API Input
	{
	public:
	    static bool IsMouseButtonPressed(int button) { return m_instance->IsMouseButtonPressedImpl(button); }
		static bool IsKeyPressed(int keycode) { return m_instance->IsKeyPressedImpl(keycode); }

		static std::pair<float, float> GetMousePosition() { return m_instance->GetMousePositionImpl(); }
		static float GetMousePosX() { return m_instance->GetMousePosXImpl(); }
		static float GetMousePosY() { return m_instance->GetMousePosYImpl(); }

	protected:
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual bool IsKeyPressedImpl(int keycode) = 0;

		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMousePosXImpl() = 0;
		virtual float GetMousePosYImpl() = 0;

	private:
		static Input* m_instance;
	};
}