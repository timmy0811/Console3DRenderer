#pragma once

#include "glm/glm.hpp"
#include "../../Display/ScreenRenderer.h"

class Object
{
protected:
	glm::mat4 m_Model;
	glm::vec3 m_Position;

public:
	Object();

	inline glm::mat4& GetModel() { return m_Model; };

	virtual inline glm::vec3* GetPointAllocator() = 0;
	virtual inline size_t GetPointSize() const = 0;

	virtual void rotate() {};

	virtual void RenderEdges(ScreenRenderer* Renderer) = 0;
	virtual void SetVertexPosition(glm::vec2 position, unsigned int index) = 0;
};

