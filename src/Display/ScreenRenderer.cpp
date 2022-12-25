#include "ScreenRenderer.h"

inline unsigned int ScreenRenderer::CoordToIndex(const glm::vec2& coord)
{
	return coord.y * c_Display_X + coord.x;
}

ScreenRenderer::ScreenRenderer(const char symbol)
{
	m_Background = symbol;
	std::fill_n(m_Buffer, std::size(m_Buffer), symbol);
}

void ScreenRenderer::Blit() const
{
	system("cls");

	unsigned int bufferOffset = 0;
	for (int y = 0; y < c_Display_Y; y++) {
		std::fwrite(m_Buffer + bufferOffset, c_Display_X, 1, stderr);
		std::cout << "\n";

		bufferOffset += c_Display_X;
	}

}

void ScreenRenderer::Clear()
{
	std::fill_n(m_Buffer, std::size(m_Buffer), m_Background);
}

void ScreenRenderer::DrawPoint(const glm::vec2& position)
{
	unsigned int i = CoordToIndex(position);
	if (i < 0 || i > c_Display_X * c_Display_Y - 1) return;
	m_Buffer[i] = 'X';
}

void ScreenRenderer::DrawLine(const glm::vec2& p1, const glm::vec2& p2, const bool drawEndpoints)
{
	// Using Bresenham rasterisation algorithm
	const int dx = p2.x - p1.x;
	const int dy = p2.y - p1.y;

	const int dFast = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	const int dSlow = abs(dx) > abs(dy) ? abs(dy) : abs(dx);

	int mX, mY;

	// Getting magnitude for X
	if (dx < 0) mX = -1;
	else if (dx == 0) mX = 0;
	else mX = 1;

	// Getting magnitude for Y
	if (dy < 0) mY = -1;
	else if (dy == 0) mY = 0;
	else mY = 1;

	// 0 = x, 1 = y
	const unsigned int fastDir = abs(dx) > abs(dy) ? 0 : 1;

	const float error = abs(fastDir == 0 ? dx : dy) / 2.f;
	float dynamicError = error;

	// Main Bresenham loop
	glm::vec2 tile = p1;
	for (int i = 0; i < dFast - 1; i++) {
		fastDir == 0 ? tile.x += mX : tile.y += mY;
		dynamicError = dynamicError - dSlow;

		// Decide if line goes in slow direction
		if (dynamicError < 0) {
			fastDir == 0 ? tile.y += mY : tile.x += mX;
			dynamicError += dFast;
		}

		// Error checking
		if (tile.x < 0 || tile.x >= c_Display_X || tile.y < 0 || tile.y >= c_Display_Y) continue;
		unsigned int c = CoordToIndex(tile);
		m_Buffer[c] = '.';
	}

	// Draw Endpoints
	if (drawEndpoints) {
		if (p1.x < 0 || p1.x >= c_Display_X || p1.y < 0 || p1.y >= c_Display_Y) return;
		if (p2.x < 0 || p2.x >= c_Display_X || p2.y < 0 || p2.y >= c_Display_Y) return;
		m_Buffer[CoordToIndex(p1)] = '.';
		m_Buffer[CoordToIndex(p2)] = '.';
	}
}
