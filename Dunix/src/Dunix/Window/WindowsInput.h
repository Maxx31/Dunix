#pragma once

#include "../Core/Core.h"
#include "../Core/Input.h"

namespace Dunix
{
	class DUNIX_API WindowsInput : public Input
	{
	protected:
		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual bool IsKeyPressedImpl(int keycode) override;

		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMousePosXImpl() override;
		virtual float GetMousePosYImpl() override;
	};
}