#include "dxpch.h"
#include "Camera.h"

namespace Dunix
{
	Camera::Camera(float FOV, float aspect, float nearClip, float farClip) :
		m_FOV(FOV), m_Aspect(aspect), m_nearClip(nearClip), m_farClip(farClip)
	{

	}

	void Camera::SetPosition(const glm::vec3& pos)
	{
		m_Position = pos;
		RecalculateView();
	}

	void Camera::SetRotation(const glm::vec3& rotEuler)
	{
		m_Rotation = rotEuler;
		RecalculateView();
	}

	void Camera::RecalculateProjection()
	{
		m_Projection = glm::perspective(glm::radians(m_FOV), m_Aspect, m_nearClip, m_farClip);
	}

	void Camera::RecalculateView()
	{
		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::translate(transform, m_Position);

		transform = glm::rotate(transform, glm::radians(m_Rotation.x), { 1,0,0 });
		transform = glm::rotate(transform, glm::radians(m_Rotation.y), { 0,1,0 });
		transform = glm::rotate(transform, glm::radians(m_Rotation.z), { 0,0,1 });

		// camera matrix is inverse of its transform
		m_View = glm::inverse(transform);
	}
}
