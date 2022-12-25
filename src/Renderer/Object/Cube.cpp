#include "Cube.h"

Cube::Cube(const float size, const glm::vec3& position)
{
	m_Points[0] = { position.x - size / 2.f, position.y - size / 2.f, position.z - size / 2.f };
	m_Points[1] = { position.x + size / 2.f, position.y - size / 2.f, position.z - size / 2.f };
	m_Points[2] = { position.x - size / 2.f, position.y + size / 2.f, position.z - size / 2.f };
	m_Points[3] = { position.x + size / 2.f, position.y + size / 2.f, position.z - size / 2.f };

	m_Points[4] = { position.x - size / 2.f, position.y - size / 2.f, position.z + size / 2.f };
	m_Points[5] = { position.x + size / 2.f, position.y - size / 2.f, position.z + size / 2.f };
	m_Points[6] = { position.x - size / 2.f, position.y + size / 2.f, position.z + size / 2.f };
	m_Points[7] = { position.x + size / 2.f, position.y + size / 2.f, position.z + size / 2.f };

	m_Position = position;
}

void Cube::SetVertexPosition(glm::vec2 position, unsigned int index)
{
	m_PointsProjected[index].x = (int)position.x;
	m_PointsProjected[index].y = (int)position.y;
}

void Cube::RenderEdges(ScreenRenderer* Renderer)
{
	Renderer->DrawLine(m_PointsProjected[0], m_PointsProjected[1], false);
	Renderer->DrawLine(m_PointsProjected[1], m_PointsProjected[3], false);
	Renderer->DrawLine(m_PointsProjected[2], m_PointsProjected[3], false);
	Renderer->DrawLine(m_PointsProjected[2], m_PointsProjected[0], false);

	Renderer->DrawLine(m_PointsProjected[0], m_PointsProjected[4], false);
	Renderer->DrawLine(m_PointsProjected[1], m_PointsProjected[5], false);
	Renderer->DrawLine(m_PointsProjected[2], m_PointsProjected[6], false);
	Renderer->DrawLine(m_PointsProjected[3], m_PointsProjected[7], false);

	Renderer->DrawLine(m_PointsProjected[4], m_PointsProjected[5], false);
	Renderer->DrawLine(m_PointsProjected[5], m_PointsProjected[7], false);
	Renderer->DrawLine(m_PointsProjected[6], m_PointsProjected[7], false);
	Renderer->DrawLine(m_PointsProjected[6], m_PointsProjected[4], false);
}
