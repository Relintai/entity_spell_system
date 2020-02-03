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

#include "loot_data_item.h"

Ref<ItemTemplate> LootDataItem::get_item() const {
	return _item;
}
void LootDataItem::set_item(const Ref<ItemTemplate> item) {
	_item = item;
}

void LootDataItem::_get_loot(Array into) {
	if (_item.is_valid()) {
		Math::randomize();

		float val = Math::randf() * 100.0;

		if (val < get_chance()) {
			into.append(_item);
		}
	}
}

LootDataItem::LootDataItem() {
}

void LootDataItem::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_get_loot", "into"), &LootDataItem::_get_loot);

	ClassDB::bind_method(D_METHOD("get_item"), &LootDataItem::get_item);
	ClassDB::bind_method(D_METHOD("set_item", "value"), &LootDataItem::set_item);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemTemplate"), "set_item", "get_item");
}
