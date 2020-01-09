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

Ref<ItemVisualEntry> SkeletonModelEntry::get_entry() {
	return _entry;
}
void SkeletonModelEntry::set_entry(Ref<ItemVisualEntry> entry) {
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
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "entry", PROPERTY_HINT_RESOURCE_TYPE, "ItemVisualEntry"), "set_entry", "get_entry");
}
