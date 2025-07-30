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
#include <gui/ColorPickerObject.hpp>

#define RAYGUI_IMPLEMENTATION
#include "external/raygui.h"


int main()
{
    std::string title = "Wave Function Collapse";
	u32 margin = 20;

    u32 width = 600;
    u32 height = 600;

    RootObject root(width, height, margin, margin);
    GroupBoxObject* gr1 = new GroupBoxObject(Vertical, "gr1");
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

    // ColorPickerObject* cp1 = new ColorPickerObject("cp1");
    // ColorPickerObject* cp2 = new ColorPickerObject("cp2");
    GroupBoxObject* gr5 = new GroupBoxObject(Horizontal, "gr5");

    root.addChild(gr1);
    gr1->addChild(gr2);
    gr1->addChild(slider);
    gr1->resizeAll(0.1f);
    gr2->addChild(gr3);
    gr2->addChild(gr4);
    // gr4->addChild(cp1);
    gr4->addChild(gr5);
    // gr4->addChild(cp2);


    SetConfigFlags(FLAG_WINDOW_RESIZABLE);    // Window configuration flags
    InitWindow(width, height, title.c_str());
	SetTargetFPS(144);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        root.updateSize();
        root.drawAll();

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
