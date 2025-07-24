//
// Created by fg on 7/17/25.
//
#pragma once

#include <aliases.hpp>
#include <vector>
#include <memory> // Required for std::unique_ptr

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
	u32 childrenMax = 2;

	ObjectData createObjectData(u32 amountOfChildren, u32 childNumber);

	protected:
	u32 posX, posY;
	u32 width, height;
	u32 marginX, marginY;


	public:
	std::vector<UiObject*> children; // Changed to store unique_ptrs
    void setValues(ObjectData data);
	UiObject(ObjectData data, Mode mode);
	ObjectData getObjectData();

    void addChild(UiObject* object); // Changed signature to accept unique_ptr

	virtual ~UiObject();
	virtual void draw();

};
