#include <external/raylib.h>
#include <external/raygui.h>
#include <stdexcept>

#include "SliderObject.hpp"
#include "UiObject.hpp"

SliderObject::SliderObject(ObjectData object, std::string LeftText, std::string RightText, f32 min, f32 max,  void (UiObject::*func)(f32), UiObject* target, bool revert) : UiObject(object, NoChildren) {
	if (func == nullptr ) {
		throw std::invalid_argument("func is null");
	} else if (target == nullptr) {
		throw std::invalid_argument("target is null");
	}

	this->LeftText = LeftText;
	this->RightText = RightText;
	val = 0.5f;
	this->min = min;
	this->max = max;
	this->func = func;
	this->target = target;
	this->revert = revert;
}

SliderObject::SliderObject (std::string LeftText, std::string RightText, f32 min, f32 max,  void (UiObject::*func)(f32), UiObject* target, bool revert) : SliderObject((ObjectData){}, LeftText, RightText, min, max, func, target, revert) {}

void SliderObject::draw() {
	GuiSliderBar((Rectangle){
		.x = (f32)posX,
		.y = (f32)posY,
		.width = (f32)width,
		.height = (f32)height
	}
	, LeftText.c_str(), RightText.c_str(), &val, min, max);

	f32 v2 = 1 - val;

	revert ? (target->*func)(v2) : (target->*func)(val);
}
