#include <aliases.hpp>
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

int main()
{
	u32 BoxesW = 10;
	u32 BoxesH = 10;

	u32 pixelsPerBox = 100;

	u32 paddingW = 50;
	u32 paddingH = 50;

	InitWindow(pixelsPerBox*BoxesW+paddingW, pixelsPerBox*BoxesH+paddingH, "raygui - controls test suite");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();
		ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));


		Rectangle rect(paddingW/2,paddingH/2, pixelsPerBox*BoxesW, pixelsPerBox*BoxesH);
		GuiGroupBox(rect, "Draw Pixels");

		EndDrawing();
	}

	CloseWindow();
	return 0;
}