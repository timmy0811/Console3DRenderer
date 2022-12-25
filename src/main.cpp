#include <cwchar>
#include <Windows.h>
#include <conio.h>

#include "glm/glm.hpp"

#include "config.h"
#include "Display/ScreenRenderer.h"
#include "Renderer/Scene.h"

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

	// Creating Display and Scene
	ScreenRenderer Display = ScreenRenderer(' ');
	bool isRunning = true;

	Scene SceneExample = Scene();
	SceneExample.Add<Cube>(0.5f, { 0, 0, 0 });

	// Main Render-Loop
	int i = 0;
	while (true) {
		if (i > 60) isRunning = false;
		i++;

		Display.Clear();

		SceneExample.Update(1.f);
		SceneExample.Render(&Display);

		Display.Blit();
	}

	return 0;
}