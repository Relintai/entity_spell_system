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

#include "vendor_item_data.h"

#include "../../data/items/item_template.h"
#include "../../data/spells/spell.h"

Ref<ItemTemplate> VendorItemDataEntry::get_item() {
	return _item;
}
void VendorItemDataEntry::set_item(const Ref<ItemTemplate> &item) {
	_item = item;
}

Ref<Spell> VendorItemDataEntry::get_spell() {
	return _spell;
}
void VendorItemDataEntry::set_spell(const Ref<Spell> &spell) {
	_spell = spell;
}

Ref<ItemTemplate> VendorItemDataEntry::get_cost_item() {
	return _cost_item;
}
void VendorItemDataEntry::set_cost_item(const Ref<ItemTemplate> &item) {
	_cost_item = item;
}

int VendorItemDataEntry::get_price() const {
	return _price;
}
void VendorItemDataEntry::set_price(const int value) {
	_price = value;
}

int VendorItemDataEntry::get_count() const {
	return _count;
}
void VendorItemDataEntry::set_count(const int value) {
	_count = value;
}

int VendorItemDataEntry::get_spawn_time() const {
	return _spawn_time;
}
void VendorItemDataEntry::set_spawn_time(const int value) {
	_spawn_time = value;
}

VendorItemDataEntry::VendorItemDataEntry() {
	_price = 0;
	_count = 0;
	_spawn_time = 0;
}
VendorItemDataEntry::~VendorItemDataEntry() {
	_item.unref();
	_spell.unref();
	_cost_item.unref();
}

void VendorItemDataEntry::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_item"), &VendorItemDataEntry::get_item);
	ClassDB::bind_method(D_METHOD("set_item", "item"), &VendorItemDataEntry::set_item);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemTemplate"), "set_item", "get_item");

	ClassDB::bind_method(D_METHOD("get_spell"), &VendorItemDataEntry::get_spell);
	ClassDB::bind_method(D_METHOD("set_spell", "item"), &VendorItemDataEntry::set_spell);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "spell", PROPERTY_HINT_RESOURCE_TYPE, "Spell"), "set_spell", "get_spell");

	ClassDB::bind_method(D_METHOD("get_cost_item"), &VendorItemDataEntry::get_cost_item);
	ClassDB::bind_method(D_METHOD("set_cost_item", "item"), &VendorItemDataEntry::set_cost_item);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "cost_item", PROPERTY_HINT_RESOURCE_TYPE, "ItemTemplate"), "set_cost_item", "get_cost_item");

	ClassDB::bind_method(D_METHOD("get_price"), &VendorItemDataEntry::get_price);
	ClassDB::bind_method(D_METHOD("set_price", "value"), &VendorItemDataEntry::set_price);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "price"), "set_price", "get_price");

	ClassDB::bind_method(D_METHOD("get_count"), &VendorItemDataEntry::get_count);
	ClassDB::bind_method(D_METHOD("set_count", "value"), &VendorItemDataEntry::set_count);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "count"), "set_count", "get_count");

	ClassDB::bind_method(D_METHOD("get_spawn_time"), &VendorItemDataEntry::get_spawn_time);
	ClassDB::bind_method(D_METHOD("set_spawn_time", "value"), &VendorItemDataEntry::set_spawn_time);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "spawn_time"), "set_spawn_time", "get_spawn_time");
}
