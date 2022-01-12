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

#include "bag.h"

#include "../data/items/item_instance.h"
#include "../data/items/item_template.h"

int Bag::get_allowed_item_types() const {
	return _allowed_item_types;
}

void Bag::set_allowed_item_types(const int value) {
	_allowed_item_types = value;
}

bool Bag::add_item(Ref<ItemInstance> item) {
}

Ref<ItemInstance> Bag::get_item(const int index) const {
	ERR_FAIL_INDEX_V(index, _items.size(), Ref<ItemInstance>(NULL));

	return (_items.get(index));
}

Ref<ItemInstance> Bag::remove_item(const int index) {
	ERR_FAIL_INDEX_V(index, _items.size(), Ref<ItemInstance>(NULL));

	Ref<ItemInstance> item = _items.get(index);

	_items.remove(index);

	//Go over everything, to make sure item site changes won't cause bugs.
	for (int x = 0; x < _size_x; ++x) {
		for (int y = 0; y < _size_y; ++y) {
			int indx = x * _size_x + y;

			if (_space_map[indx] == index) {
				_space_map.set(indx, 0);
			}
		}
	}

	return item;
}

bool Bag::can_add_item(const Ref<ItemInstance> item) const {
}

int Bag::get_item_count() const {
	return _items.size();
}

int Bag::get_size() const {
	return _items.size();
}

void Bag::set_size(const int x, const int y) {
	ERR_FAIL_COND(x == 0 || y == 0);
	ERR_FAIL_COND(_size_x != 0 || _size_y != 0);

	_size_x = x;
	_size_y = y;

	_space_map.resize(x * y);

	for (int i = 0; i < _space_map.size(); ++i) {
		_space_map.set(i, 0);
	}
}

Bag::Bag() {
	_allowed_item_types = 0x1FFF;

	_size = 0;
}

Bag::~Bag() {
	_items.clear();
}

void Bag::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_allowed_item_types"), &Bag::get_allowed_item_types);
	ClassDB::bind_method(D_METHOD("set_allowed_item_types", "count"), &Bag::set_allowed_item_types);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "allowed_item_types", PROPERTY_HINT_FLAGS, ItemEnums::BINDING_STRING_ITEM_TYPE_FLAGS), "set_allowed_item_types", "get_allowed_item_types");

	ClassDB::bind_method(D_METHOD("add_item", "item"), &Bag::add_item);
	ClassDB::bind_method(D_METHOD("add_item_to_position", "x", "y", "item"), &Bag::add_item_to_position);

	ClassDB::bind_method(D_METHOD("can_add_item_at", "x", "y", "item"), &Bag::can_add_item_at);
	ClassDB::bind_method(D_METHOD("item_count_under_area", "x", "y", "item"), &Bag::item_count_under_area);

	ClassDB::bind_method(D_METHOD("get_item", "index"), &Bag::get_item);
	ClassDB::bind_method(D_METHOD("get_and_remove_item", "index"), &Bag::get_and_remove_item);
	ClassDB::bind_method(D_METHOD("remove_item", "index"), &Bag::remove_item);

	ClassDB::bind_method(D_METHOD("basic_add_item", "item"), &Bag::basic_add_item);
	ClassDB::bind_method(D_METHOD("basic_remove_item", "index"), &Bag::basic_remove_item);

	ClassDB::bind_method(D_METHOD("get_item_count"), &Bag::get_item_count);

	ClassDB::bind_method(D_METHOD("get_space_map_entry", "index"), &Bag::get_space_map_entry);
	ClassDB::bind_method(D_METHOD("set_space_map_entry", "index", "value"), &Bag::set_space_map_entry);

	ClassDB::bind_method(D_METHOD("get_size_x"), &Bag::get_size_x);
	ClassDB::bind_method(D_METHOD("get_size_y"), &Bag::get_size_y);

	ClassDB::bind_method(D_METHOD("set_size", "x", "y"), &Bag::set_size);
}
