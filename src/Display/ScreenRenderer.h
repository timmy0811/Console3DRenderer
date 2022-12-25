#pragma once

#include "../config.h"

#include "glm/glm.hpp"
#include <iostream>

class ScreenRenderer
{
private:
	char m_Buffer[c_Display_X * c_Display_Y];
	char m_Background;

	inline unsigned int CoordToIndex(glm::vec2& coord);

public:
	ScreenRenderer() = default;
	ScreenRenderer(const char symbol);

	void Blit() const;
	void Clear();

	void DrawPoint(glm::vec2&& position);
	void DrawLine(glm::vec2& p1, glm::vec2& p2, const bool drawEndpoints = true);
};

