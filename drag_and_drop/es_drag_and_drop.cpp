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

#include "es_drag_and_drop.h"

const String ESDragAndDrop::BINDING_STRING_ES_DRAG_AND_DROP_TYPE = "None,Spell,Item,Inventory Item,Equipped Item";

Node *ESDragAndDrop::get_origin() const {
	return _origin;
}
void ESDragAndDrop::set_origin(Node *origin) {
	_origin = origin;
}

ESDragAndDrop::ESDragAndDropType ESDragAndDrop::get_type() const {
	return _type;
}
void ESDragAndDrop::set_type(const ESDragAndDrop::ESDragAndDropType type) {
	_type = type;
}

StringName ESDragAndDrop::get_item_path() const {
	return _item_path;
}
void ESDragAndDrop::set_item_path(const StringName &item_path) {
	_item_path = item_path;
}

ESDragAndDrop::ESDragAndDrop() {
	_type = ES_DRAG_AND_DROP_TYPE_NONE;
	_origin = NULL;
}

void ESDragAndDrop::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_origin"), &ESDragAndDrop::get_origin);
	ClassDB::bind_method(D_METHOD("set_origin", "id"), &ESDragAndDrop::set_origin);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "origin", PROPERTY_HINT_RESOURCE_TYPE, "Node"), "set_origin", "get_origin");

	ClassDB::bind_method(D_METHOD("get_type"), &ESDragAndDrop::get_type);
	ClassDB::bind_method(D_METHOD("set_type", "type"), &ESDragAndDrop::set_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "type", PROPERTY_HINT_ENUM, BINDING_STRING_ES_DRAG_AND_DROP_TYPE), "set_type", "get_type");

	ClassDB::bind_method(D_METHOD("get_item_path"), &ESDragAndDrop::get_item_path);
	ClassDB::bind_method(D_METHOD("set_item_path", "id"), &ESDragAndDrop::set_item_path);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "item_path"), "set_item_path", "get_item_path");

	BIND_ENUM_CONSTANT(ES_DRAG_AND_DROP_TYPE_NONE);
	BIND_ENUM_CONSTANT(ES_DRAG_AND_DROP_TYPE_SPELL);
	BIND_ENUM_CONSTANT(ES_DRAG_AND_DROP_TYPE_ITEM);
	BIND_ENUM_CONSTANT(ES_DRAG_AND_DROP_TYPE_INVENTORY_ITEM);
	BIND_ENUM_CONSTANT(ES_DRAG_AND_DROP_TYPE_EQUIPPED_ITEM);
}
