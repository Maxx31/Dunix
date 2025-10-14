#include "dxpch.h"
#include "WindowsInput.h"

namespace Dunix
{
	Input* Input::m_instance = new WindowsInput();

	bool Dunix::WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		return false;
	}

	bool Dunix::WindowsInput::IsKeyPressedImpl(int keycode)
	{
		return false;
	}

	std::pair<float, float> Dunix::WindowsInput::GetMousePositionImpl()
	{
		return std::pair<float, float>();
	}

	float Dunix::WindowsInput::GetMousePosXImpl()
	{
		return 0.0f;
	}

	float Dunix::WindowsInput::GetMousePosYImpl()
	{
		return 0.0f;
	}
}
