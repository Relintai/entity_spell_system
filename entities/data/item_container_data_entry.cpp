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

#include "item_container_data_entry.h"

#include "../../data/items/item_template.h"

Ref<ItemTemplate> ItemContainerDataEntry::get_item() {
	return _item;
}
void ItemContainerDataEntry::set_item(Ref<ItemTemplate> item) {
	_item = item;
}

int ItemContainerDataEntry::get_item_count() const {
	return _item_count;
}
void ItemContainerDataEntry::set_item_count(int value) {
	_item_count = value;
}

ItemContainerDataEntry::ItemContainerDataEntry() {
	_item_count = 0;
}
ItemContainerDataEntry::~ItemContainerDataEntry() {
}

void ItemContainerDataEntry::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_item"), &ItemContainerDataEntry::get_item);
	ClassDB::bind_method(D_METHOD("set_item", "item"), &ItemContainerDataEntry::set_item);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemTemplate"), "set_item", "get_item");

	ClassDB::bind_method(D_METHOD("get_item_count"), &ItemContainerDataEntry::get_item_count);
	ClassDB::bind_method(D_METHOD("set_item_count", "value"), &ItemContainerDataEntry::set_item_count);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "item_count"), "set_item_count", "get_item_count");
}
