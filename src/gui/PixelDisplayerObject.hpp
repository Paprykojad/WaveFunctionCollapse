#pragma once
#include "UiObject.hpp"
#include "algorithm/ColorTable.hpp"

class PixelDisplayerObject : public UiObject {
	private:
	ColorTable* colorTable;
	bool drawable;

	public:
	Color drawColor = (Color){
		.r = 255,
		.g = 0,
		.b = 0,
		.a = 255,
	};

	PixelDisplayerObject(ObjectData object, ColorTable* colorTable, bool drawable);
	PixelDisplayerObject(ColorTable* colorTable, bool drawable);

	void draw() override;
};
