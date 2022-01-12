/*
Copyright (c) 2019-2022 Péter Magyar

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "skeleton_model_entry.h"

int SkeletonModelEntry::get_count() const {
	return _count;
}
void SkeletonModelEntry::set_count(const int value) {
	_count = value;
}

int SkeletonModelEntry::get_priority() const {
	return _priority;
}
void SkeletonModelEntry::set_priority(const int value) {
	_priority = value;
}

Color SkeletonModelEntry::get_color() const {
	return _color;
}
void SkeletonModelEntry::set_color(const Color value) {
	_color = value;
}

Ref<ModelVisualEntry> SkeletonModelEntry::get_entry() {
	return _entry;
}
void SkeletonModelEntry::set_entry(Ref<ModelVisualEntry> entry) {
	_entry = entry;
}

SkeletonModelEntry::SkeletonModelEntry() {
	_count = 1;
	_priority = 0;
	_color = Color(1, 1, 1, 1);
}

SkeletonModelEntry::~SkeletonModelEntry() {
	_entry.unref();
}

void SkeletonModelEntry::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_count"), &SkeletonModelEntry::get_count);
	ClassDB::bind_method(D_METHOD("set_count", "value"), &SkeletonModelEntry::set_count);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "count"), "set_count", "get_count");

	ClassDB::bind_method(D_METHOD("get_priority"), &SkeletonModelEntry::get_priority);
	ClassDB::bind_method(D_METHOD("set_priority", "value"), &SkeletonModelEntry::set_priority);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "priority"), "set_priority", "get_priority");

	ClassDB::bind_method(D_METHOD("get_color"), &SkeletonModelEntry::get_color);
	ClassDB::bind_method(D_METHOD("set_color", "value"), &SkeletonModelEntry::set_color);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "color"), "set_color", "get_color");

	ClassDB::bind_method(D_METHOD("get_entry"), &SkeletonModelEntry::get_entry);
	ClassDB::bind_method(D_METHOD("set_entry", "path"), &SkeletonModelEntry::set_entry);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "entry", PROPERTY_HINT_RESOURCE_TYPE, "ModelVisualEntry"), "set_entry", "get_entry");
}
