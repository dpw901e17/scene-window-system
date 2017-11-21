#pragma once

class Camera
{
public:
	float FieldOfView() const { return m_FieldOfView; }
	float AspectRatio() const { return m_AspectRatio; }
	float Near() const { return m_Near; }
	float Far() const { return m_Far; }

	static Camera Default() { return Camera(); }
private:
	float m_FieldOfView = 45.0f;
	float m_AspectRatio = 3.0f / 4.0f;
	float m_Near = 0.1f;
	float m_Far = 10.0f;
};