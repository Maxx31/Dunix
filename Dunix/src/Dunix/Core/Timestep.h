#pragma once

namespace Dunix
{
	class Timestep
	{
	public:
		Timestep(float time = 0.0)
			:m_time(time) {}

		float GetSeconds() const { return m_time; }
		float GetMilliseconds() const { return m_time * 1000.0f; }

		operator float() const {return m_time;}

	private:
		float m_time;

	};
}

