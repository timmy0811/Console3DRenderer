#pragma once

#include "Object.h"

class Cube :
    public Object
{
private:
    glm::vec3 m_Points[8];
    glm::vec2 m_PointsProjected[8];

public:
    Cube(const float size, const glm::vec3& position);

    inline glm::vec3* GetPointAllocator() override { return m_Points; };
    inline size_t GetPointSize() const override { return sizeof(m_Points) / (sizeof(float) * 3); };

    void SetVertexPosition(glm::vec2 position, unsigned int index) override;

    void RenderEdges(ScreenRenderer* Renderer) override;
};

