#include "es_drag_and_drop.h"

const String ESDragAndDrop::BINDING_STRING_ES_DRAG_AND_DROP_TYPE = "None, Spell, Item";

ESDragAndDrop::ESDragAndDropType ESDragAndDrop::get_type() {
	return _type;
}

void ESDragAndDrop::set_type(ESDragAndDrop::ESDragAndDropType type) {
	_type = type;
}

int ESDragAndDrop::get_item_id() {
	return _item_id;
}

void ESDragAndDrop::set_item_id(int item_id) {
	_item_id = item_id;
}

ESDragAndDrop::ESDragAndDrop() {
	_item_id = 0;
	_type = ES_DRAG_AND_DROP_TYPE_NONE;
}

void ESDragAndDrop::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_type"), &ESDragAndDrop::get_type);
	ClassDB::bind_method(D_METHOD("set_type", "type"), &ESDragAndDrop::set_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "type", PROPERTY_HINT_ENUM, BINDING_STRING_ES_DRAG_AND_DROP_TYPE), "set_type", "get_type");

	ClassDB::bind_method(D_METHOD("get_item_id"), &ESDragAndDrop::get_item_id);
	ClassDB::bind_method(D_METHOD("set_item_id", "id"), &ESDragAndDrop::set_item_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "item_id"), "set_item_id", "get_item_id");

	BIND_ENUM_CONSTANT(ES_DRAG_AND_DROP_TYPE_NONE);
	BIND_ENUM_CONSTANT(ES_DRAG_AND_DROP_TYPE_SPELL);
	BIND_ENUM_CONSTANT(ES_DRAG_AND_DROP_TYPE_ITEM);
}

