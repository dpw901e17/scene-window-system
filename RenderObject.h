#pragma once

class RenderObject
{
public:
	explicit RenderObject(float x, float y, float z) : m_X(x), m_Y(y), m_Z(z) { }

	float x() const { return m_X; }
	float y() const { return m_Y; }
	float z() const { return m_Z; }
private:
	float m_X, m_Y, m_Z;
};