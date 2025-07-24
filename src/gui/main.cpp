#include <aliases.hpp>
#include "external/raylib.h"
#include <string>
#include <iostream>

using std::cout;
using std::endl;

#include <gui/UiObject.hpp>
#include <gui/RootObject.hpp>
#include <gui/GroupBoxObject.hpp>
#include <gui/SliderObject.hpp>

#define RAYGUI_IMPLEMENTATION
#include "external/raygui.h"


int main()
{
    std::string title = "Wave Function Collapse";
	u32 margin = 20;

    u32 width = 1000;
    u32 height = 1000;

    // Container root(0, 0, width, height, margin, margin);
    // GroupBoxObject rootObject(&root, title);

    RootObject root(width, height, margin, margin);
    GroupBoxObject* gr = new GroupBoxObject(Vertical, "gr1");
    GroupBoxObject* gr2 = new GroupBoxObject(Horizontal, "gr2");
    SliderObject* slider = new SliderObject(
    "Min", "Max",
    0.0f, 1.0f,
    &UiObject::resizeAll,
    gr2,
    true
    );

    GroupBoxObject* gr3 = new GroupBoxObject(Horizontal, "gr3");
    GroupBoxObject* gr4 = new GroupBoxObject(Horizontal, "gr4");

    root.addChild(gr);
    gr->addChild(gr2);
    gr->addChild(slider);
    gr->resizeAll(0.1f);
    gr2->addChild(gr3);
    gr2->addChild(gr4);

    InitWindow(width, height, title.c_str());
	SetTargetFPS(144);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

		root.drawAll();

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
