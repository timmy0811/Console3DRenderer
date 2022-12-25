#include <cwchar>
#include <Windows.h>

#include "glm/glm.hpp"

#include "config.h"
#include "Display/ScreenRenderer.h"
#include "Renderer/Scene.h"

#include "Renderer/Object/Cube.h"

int main() {
	// Setting up console
	CONSOLE_FONT_INFOEX cfi;

	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 10;
	cfi.dwFontSize.Y = 10;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	// Generating Scene
	ScreenRenderer Display = ScreenRenderer(' ');
	bool isRunning = true;

	Scene SceneExample = Scene();
	//SceneExample.Add<Cube>(1.f, { 0.f, 0.f, 0.f });

	// Main Render-Loop
	int i = 0;
	while (isRunning) {
		if (i > 60) isRunning = false;
		i++;

		Display.Clear();

		SceneExample.Update(1.f);
		SceneExample.Render(&Display);


		Display.Blit();
	}

	return 0;
}