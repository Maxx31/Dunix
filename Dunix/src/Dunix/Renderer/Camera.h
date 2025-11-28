#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Dunix
{
	class Camera
	{
	public:
		Camera(float FOV, float aspect, float nearClip, float farClip);

		void SetPosition(const glm::vec3& pos);
		void SetRotation(const glm::vec3& rotEuler);

		void RecalculateProjection();
		void RecalculateView();

		const glm::mat4& GetView() const { return m_View; }
		const glm::mat4& GetProjection() const { return m_Projection; }
		glm::mat4 GetViewProjection() const { return m_Projection * m_View; }

	private:
		float m_FOV, m_Aspect, m_nearClip, m_farClip;

		glm::vec3 m_Position;
		glm::vec3 m_Rotation; // pitch, yaw, roll

		glm::mat4 m_View{ 1.0f };
		glm::mat4 m_Projection{ 1.0f };

	};
}

