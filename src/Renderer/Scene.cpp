#include "Scene.h"

glm::vec2 Scene::RenderPoint(glm::vec3& position, glm::mat4& model, ScreenRenderer* canvas) const
{
	// Projection to Clip Space
	glm::vec4 FragmentPos = m_View * model * glm::vec4(position, 1.f);

	// Clip when behind the camera
	if (FragmentPos.z < 0) return { -1, -1 };

	float x = (-1 / tan((45.f / 2.0) * 3.14159265 / 180.0));
	FragmentPos = FragmentPos * x / (x + FragmentPos.z);

	// Viewport transformation to Screen Space
	constexpr float halfX = c_Display_X / 2.f;
	constexpr float halfY = c_Display_Y / 2.f;

	FragmentPos.x = halfX + FragmentPos.x * halfX;
	FragmentPos.y = halfY + FragmentPos.y * halfY;

	// Render on Screen
	canvas->DrawPoint({ static_cast<int>(FragmentPos.x), static_cast<int>(FragmentPos.y) });

	return {FragmentPos.x, FragmentPos.y};
}

Scene::Scene()
	:m_View(1.f), m_Projection(glm::perspective(glm::radians(45.f), static_cast<float>(c_Display_X / c_Display_Y), 0.1f, 100.f))
{
	m_View = glm::translate(m_View, glm::vec3(0.f, 0.f, 4.f));

	m_Objects.push_back(new Cube(0.5f, { 0.f, 0.f, 0.f }));
}

Scene::~Scene()
{
	for (auto obj : m_Objects) {
		delete obj;
	}
}

void Scene::Render(ScreenRenderer* canvas)
{
	for (auto obj : m_Objects) {
		size_t points = obj->GetPointSize();
		glm::vec3* pointAlloc = obj->GetPointAllocator();

		for (int i = 0; i < points; i++) {
			UpdateVertex(1.f, obj->GetModel());
			obj->SetVertexPosition(RenderPoint(*(pointAlloc + i), obj->GetModel(), canvas), i);
		}

		// Call Render function on object
		obj->RenderEdges(canvas);
	}
}

void Scene::Update(float dt)
{
	//m_View = glm::translate(m_View, glm::vec3(0.f, 0.f, 0.5f));
}

#include <stdio.h>
#include <time.h>

void Scene::UpdateVertex(float dt, glm::mat4& model)
{
	model = glm::rotate(model, glm::radians(1.f), glm::vec3(1.0f, 1.0f, 0.0f));
}

template<class T>
void Scene::Add(const float size, glm::vec3&& position)
{
	m_Objects.push_back(new T(size, position));
}
