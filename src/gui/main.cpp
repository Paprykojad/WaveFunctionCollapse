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

    u32 width = 600;
    u32 height = 600;

    // Container root(0, 0, width, height, margin, margin);
    // GroupBoxObject rootObject(&root, title);

    RootObject root(width, height, margin, margin);
    GroupBoxObject* gr = new GroupBoxObject(Horizontal, title);
    GroupBoxObject* gr2 = new GroupBoxObject(Horizontal, title);
    GroupBoxObject* gr3 = new GroupBoxObject(Horizontal, title);
    root.addChild(gr);
    gr->addChild(gr2);
    gr->addChild(gr3);

	InitWindow(width, height, title.c_str());
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        root.children[0]->draw();
        for range(i, root.children[0]->children.size()) {
        	root.children[0]->children[i]->draw();
        }

        // GuiGroupBox(rect, title.c_str());

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
