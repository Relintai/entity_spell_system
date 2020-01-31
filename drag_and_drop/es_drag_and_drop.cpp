/*
Copyright (c) 2019-2020 Péter Magyar

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
	_origin = NULL;
}

void ESDragAndDrop::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_origin"), &ESDragAndDrop::get_origin);
	ClassDB::bind_method(D_METHOD("set_origin", "id"), &ESDragAndDrop::set_origin);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "origin", PROPERTY_HINT_RESOURCE_TYPE, "Node"), "set_origin", "get_origin");

	ClassDB::bind_method(D_METHOD("get_type"), &ESDragAndDrop::get_type);
	ClassDB::bind_method(D_METHOD("set_type", "type"), &ESDragAndDrop::set_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "type", PROPERTY_HINT_ENUM, BINDING_STRING_ES_DRAG_AND_DROP_TYPE), "set_type", "get_type");

	ClassDB::bind_method(D_METHOD("get_item_id"), &ESDragAndDrop::get_item_id);
	ClassDB::bind_method(D_METHOD("set_item_id", "id"), &ESDragAndDrop::set_item_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "item_id"), "set_item_id", "get_item_id");

	BIND_ENUM_CONSTANT(ES_DRAG_AND_DROP_TYPE_NONE);
	BIND_ENUM_CONSTANT(ES_DRAG_AND_DROP_TYPE_SPELL);
	BIND_ENUM_CONSTANT(ES_DRAG_AND_DROP_TYPE_ITEM);
	BIND_ENUM_CONSTANT(ES_DRAG_AND_DROP_TYPE_INVENTORY_ITEM);
	BIND_ENUM_CONSTANT(ES_DRAG_AND_DROP_TYPE_EQUIPPED_ITEM);
}
