#include <aliases.hpp>
#include "external/raylib.h"
#include <string>

#include <gui/UiObject.hpp>
#include <gui/RootObject.hpp>
#include <gui/GroupBoxObject.hpp>

#define RAYGUI_IMPLEMENTATION
#include "external/raygui.h"


int main()
{
    std::string title = "Wave Function Collapse";
	u32 margin = 20;

    u32 width = 1200;
    u32 height = 1200;

    // Container root(0, 0, width, height, margin, margin);
    // GroupBoxObject rootObject(&root, title);

    RootObject root(width, height, margin, margin);
    GroupBoxObject* gr = new GroupBoxObject(Horizontal, title);
    GroupBoxObject* gr2 = new GroupBoxObject(Horizontal, title);
    GroupBoxObject* gr3 = new GroupBoxObject(Vertical, title);
    GroupBoxObject* gr4 = new GroupBoxObject(Horizontal, title);
    GroupBoxObject* gr5 = new GroupBoxObject(Horizontal, title);
    root.addChild(gr);
    gr->addChild(gr2);
    gr->addChild(gr3);
    gr3->addChild(gr4);
    gr3->addChild(gr5);

	InitWindow(width, height, title.c_str());
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

		root.drawAll();
		// GuiGroupBox((Rectangle){}, "karaluch");

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
