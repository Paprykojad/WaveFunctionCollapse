#include <aliases.hpp>
#include "external/raylib.h"
#include <string>
#include <iostream>

using std::cout;
using std::endl;

#include <gui/UiObject.hpp>
#include <gui/RootObject.hpp>
#include <gui/GroupBoxObject.hpp>

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
    GroupBoxObject* gr = new GroupBoxObject(Horizontal, "gr1");
    GroupBoxObject* gr2 = new GroupBoxObject(Horizontal, "gr2");
    GroupBoxObject* gr3 = new GroupBoxObject(Vertical, "gr3");
    GroupBoxObject* gr4 = new GroupBoxObject(Horizontal, "gr4");
    GroupBoxObject* gr5 = new GroupBoxObject(Vertical, "gr5");
    GroupBoxObject* gr6 = new GroupBoxObject(Vertical, "gr6");
    GroupBoxObject* gr7 = new GroupBoxObject(Horizontal, "gr7");
    GroupBoxObject* gr8 = new GroupBoxObject(Vertical, "gr8");
    GroupBoxObject* gr9 = new GroupBoxObject(Vertical, "gr9");
    GroupBoxObject* gr10 = new GroupBoxObject(Vertical, "gr10");
    GroupBoxObject* gr11 = new GroupBoxObject(Vertical, "gr11");
    root.addChild(gr);
    gr->addChild(gr2);
    gr->addChild(gr3);
    gr3->addChild(gr4);
    gr3->addChild(gr5);
    gr5->addChild(gr6);
    gr5->addChild(gr7);
    gr7->addChild(gr8);
    gr7->addChild(gr9);
    gr9->addChild(gr10);
    gr9->addChild(gr11);

	InitWindow(width, height, title.c_str());
	SetTargetFPS(60);

	f32 dir = 1.0f;
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

		root.drawAll();
		f32 speed = 0.001;
		if (gr->splitRatio <=0 || gr->splitRatio >= 1) {
			dir *= -1.0f;
		}
		gr->resizeAll(gr->splitRatio += speed*dir);
		cout << gr->splitRatio << endl;

		// GuiGroupBox((Rectangle){}, "karaluch");

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
