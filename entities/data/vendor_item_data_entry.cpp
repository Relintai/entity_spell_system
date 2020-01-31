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

#include "vendor_item_data.h"

#include "../../data/item_template.h"

Ref<ItemTemplate> VendorItemDataEntry::get_item() {
	return _item;
}
void VendorItemDataEntry::set_item(Ref<ItemTemplate> item) {
	_item = item;
}

int VendorItemDataEntry::get_item_price() const {
	return _item_price;
}
void VendorItemDataEntry::set_item_price(int value) {
	_item_price = value;
}

int VendorItemDataEntry::get_item_count() const {
	return _item_count;
}
void VendorItemDataEntry::set_item_count(int value) {
	_item_count = value;
}

int VendorItemDataEntry::get_item_spawn_time() const {
	return _item_spawn_time;
}
void VendorItemDataEntry::set_item_spawn_time(int value) {
	_item_spawn_time = value;
}

VendorItemDataEntry::VendorItemDataEntry() {
	_item_price = 0;
	_item_count = 0;
	_item_spawn_time = 0;
}
VendorItemDataEntry::~VendorItemDataEntry() {
}

void VendorItemDataEntry::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_item"), &VendorItemDataEntry::get_item);
	ClassDB::bind_method(D_METHOD("set_item", "item"), &VendorItemDataEntry::set_item);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemTemplate"), "set_item", "get_item");

	ClassDB::bind_method(D_METHOD("get_item_price"), &VendorItemDataEntry::get_item_price);
	ClassDB::bind_method(D_METHOD("set_item_price", "value"), &VendorItemDataEntry::set_item_price);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "item_price"), "set_item_price", "get_item_price");

	ClassDB::bind_method(D_METHOD("get_item_count"), &VendorItemDataEntry::get_item_count);
	ClassDB::bind_method(D_METHOD("set_item_count", "value"), &VendorItemDataEntry::set_item_count);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "item_count"), "set_item_count", "get_item_count");

	ClassDB::bind_method(D_METHOD("get_item_spawn_time"), &VendorItemDataEntry::get_item_spawn_time);
	ClassDB::bind_method(D_METHOD("set_item_spawn_time", "value"), &VendorItemDataEntry::set_item_spawn_time);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "item_spawn_time"), "set_item_spawn_time", "get_item_spawn_time");
}
