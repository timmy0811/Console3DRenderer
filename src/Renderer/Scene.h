#pragma once

#include "../config.h"
#include "../Display/ScreenRenderer.h"
#include "Object/Cube.h"

#include "glm/gtc/matrix_transform.hpp"

#include <vector>

class Scene
{
private:
	std::vector<Object*> m_Objects;

	glm::mat4 m_Projection;
	glm::mat4 m_View;
	glm::vec3 m_Translation;

	glm::vec2 RenderPoint(glm::vec3& position, glm::mat4& model, ScreenRenderer* canvas) const;
	void UpdateVertex(float dt, glm::mat4& model); // Equivaltent to vertex shader

public:
	Scene();
	~Scene();

	template<class T>
	void Add(const float size, const glm::vec3& position);

	void Render(ScreenRenderer* canvas);
	void Update(float dt);
};

template<class T>
void Scene::Add(const float size, const glm::vec3& position)
{
	m_Objects.push_back(new T(size, position));
}
