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
#include <gui/PixelDisplayerObject.hpp>

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

	u32 pxAmount = 40;
	ColorTable ctb(pxAmount, pxAmount);
	for range(y, pxAmount) {
		for range(x, pxAmount) {
			 Color col = (Color){
			 	.r = (unsigned char)(y*10),
				 .g = (unsigned char)(x*10),
				 .b = (unsigned char)((x+y)*10 % 255),
				 .a = (unsigned char)((x*y)*10 % 255),
			 };
			 ctb.Set(y, x, col);
		}
    }
    PixelDisplayerObject *pixel_displayer_object = new PixelDisplayerObject(&ctb, true);

    GroupBoxObject *gr4 = new GroupBoxObject(Horizontal, "gr4");

    ColorPickerObject *cp1 = new ColorPickerObject("cp1", &(pixel_displayer_object->drawColor));

    root.addChild(gr1);
    gr1->addChild(gr2);
    gr1->addChild(slider);
    gr1->resizeAll(0.1f);
    gr2->addChild(pixel_displayer_object);
    gr2->addChild(gr4);
    gr4->addChild(cp1);


    SetConfigFlags(FLAG_WINDOW_RESIZABLE); // Window configuration flags
    InitWindow(width, height, title.c_str());
    // SetExitKey(KEY_NULL);
    SetTargetFPS(144);

	for range(y, pxAmount) {
		for range(x, pxAmount) {
			ctb.data[y][x].r +=40;
			ctb.data[y][x].g +=40;
			ctb.data[y][x].b +=40;
			ctb.data[y][x].a +=40;
		}
	}

	while (!WindowShouldClose()) {
	    BeginDrawing();
	    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

	    root.updateSize();
	    root.drawAll();

	    EndDrawing();
    }

    CloseWindow();
    return 0;
}
