#include "BlankObject.hpp"

BlankObject::BlankObject(ObjectData data, Mode mode) : UiObject(data, mode) {
}

BlankObject::BlankObject(Mode mode) : UiObject((ObjectData){}, mode) {
}

void BlankObject::draw() {}
