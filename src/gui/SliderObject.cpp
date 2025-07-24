#include <external/raylib.h>
#include <external/raygui.h>

#include "SliderObject.hpp"
#include "UiObject.hpp"

SliderObject::SliderObject(ObjectData object, std::string LeftText, std::string RightText, f32 min, f32 max,  void (*func)(f32), Mode mode) : UiObject(object, mode) {
	this->LeftText = LeftText;
	this->RightText = RightText;
	val = 0.0f;
	this->min = min;
	this->max = max;
	this->func = func;
}

SliderObject::SliderObject (std::string LeftText, std::string RightText, f32 min, f32 max,  void (*func)(f32), Mode mode) : SliderObject((ObjectData){}, LeftText, RightText, min, max, func, mode) {}

void SliderObject::draw() {
	GuiSliderBar((Rectangle){
		.x = (f32)posX,
		.y = (f32)posY,
		.width = (f32)width,
		.height = (f32)height
	}
	, LeftText.c_str(), RightText.c_str(), &val, min, max);

	func(val);
}
