//
// Created by fg on 7/17/25.
//
#pragma once

#include <aliases.hpp>
#include <aliases.hpp>
#include <vector>

enum Mode {
    Vertical,
    Horizontal,
    NoChildren
};

struct ObjectData {
	u32 posX, posY;
	u32 width, height;
	u32 marginX, marginY;
};

class UiObject {
	private:
	Mode mode;

	ObjectData createObjectData(u32 amountOfChildren, u32 childNumber);

	protected:
	u32 posX, posY;
	u32 width, height;
	u32 marginX, marginY;
	u32 inheritableMarginX, inheritableMarginY;
	u32 childrenMax = 2;


	public:
	std::vector<UiObject*> children; // Changed to store unique_ptrs
	f32 splitRatio = 0.5f;
	void resize(u32 idx);
	void resizeAll(f32 ratio);

    void setValues(ObjectData data);
	UiObject(ObjectData data, Mode mode);
	ObjectData getObjectData();

    void addChild(UiObject* object); // Changed signature to accept unique_ptr
    void drawAll();

	virtual ~UiObject();
	virtual void draw();

};
