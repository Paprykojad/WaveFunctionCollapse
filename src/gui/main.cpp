#include <aliases.hpp>
#include "external/raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "external/raygui.h"

#include "Container.hpp"
#include "GroupBoxObject.hpp"

int main()
{
    std::string title = "Wave Function Collapse";
	u32 margin = 20;

    // u32 width = 1000;
    // u32 height = 1000;
    u32 width = 600;
    u32 height = 600;

    Container root(0, 0, width, height, margin, margin);
    GroupBoxObject rootObject(&root, title);

    // Rectangle rect = (Rectangle){
    //     .x = (f32)50,
    //     .y = (f32)50,
    //     .width = (f32)width-100,
    //     .height = (f32)height-100
    // };

	InitWindow(width, height, title.c_str());
	// InitWindow(pixelsPerBox*BoxesW+padding, pixelsPerBox*BoxesH+padding, "external/raygui - controls test suite");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        rootObject.draw();

        // GuiGroupBox(rect, title.c_str());

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
