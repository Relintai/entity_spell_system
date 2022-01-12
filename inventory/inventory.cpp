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

#include "inventory.h"

#include "../data/items/item_instance.h"
#include "../data/items/item_template.h"

#include "../entities/player.h"

int Inventory::get_allowed_item_types() const {
	return _allowed_item_types;
}

void Inventory::set_allowed_item_types(const int value) {
	_allowed_item_types = value;
}

Player *Inventory::target_get() const {
	return _target;
}

void Inventory::target_set(Player *value) {
	_target = value;
}

void Inventory::target_set_bind(Node *caster) {
	if (!caster) {
		return;
	}

	Player *e = Object::cast_to<Player>(caster);

	if (!e) {
		return;
	}

	_target = e;
}

Inventory::Inventory() {
	_allowed_item_types = 0xFFFFFF;
}

Inventory::~Inventory() {
}

void Inventory::_bind_methods() {
	ADD_SIGNAL(MethodInfo("changed", PropertyInfo(Variant::OBJECT, "inventory", PROPERTY_HINT_RESOURCE_TYPE, "Inventory")));

	ClassDB::bind_method(D_METHOD("get_allowed_item_types"), &Inventory::get_allowed_item_types);
	ClassDB::bind_method(D_METHOD("set_allowed_item_types", "count"), &Inventory::set_allowed_item_types);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "allowed_item_types", PROPERTY_HINT_FLAGS, ItemEnums::BINDING_STRING_ITEM_TYPE_FLAGS), "set_allowed_item_types", "get_allowed_item_types");

	ClassDB::bind_method(D_METHOD("get_target"), &Inventory::get_target);
	ClassDB::bind_method(D_METHOD("set_target", "target"), &Inventory::target_set_bind);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "target", PROPERTY_HINT_RESOURCE_TYPE, "Player"), "set_target", "get_target");
}
