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

#include "grid_bag.h"

#include "../data/items/item_instance.h"
#include "../data/items/item_template.h"

int GridBag::get_allowed_item_types() const {
	return _allowed_item_types;
}

void GridBag::set_allowed_item_types(const int value) {
	_allowed_item_types = value;
}

bool GridBag::add_item(Ref<ItemInstance> item) {
	ERR_FAIL_COND_V(!item.is_valid(), true);

	Ref<ItemTemplate> item_template = item->get_item_template();

	ERR_FAIL_COND_V(!item_template.is_valid(), true);

	int _item_size_x = item_template->get_inventory_size_x();
	int _item_size_y = item_template->get_inventory_size_y();

	for (int x = 0; x < _size_x - _item_size_x; ++x) {
		for (int y = 0; y < _size_y - _item_size_y; ++y) {
			if (_space_map[x * _size_x + y] == 0) {

				bool found = true;
				for (int xx = x; xx < _item_size_x; ++xx) {
					for (int yy = y; yy < _item_size_y; ++yy) {
						if (_space_map[xx * _size_x + yy] != 0) {
							found = false;
							break;
						}
					}

					if (!found)
						break;
				}

				if (found) {
					item->set_inventory_position_x(x);
					item->set_inventory_position_y(y);

					_items.push_back(item);

					int index = _items.size() - 1;

					for (int xx = x; xx < _item_size_x; ++xx) {
						for (int yy = y; yy < _item_size_y; ++yy) {
							_space_map.set(xx * _size_x + yy, index);
						}
					}
				}
			}
		}
	}

	return false;
}

bool GridBag::add_item_to_position(const int x, const int y, Ref<ItemInstance> item) {
	ERR_FAIL_COND_V(!item.is_valid(), false);
	ERR_FAIL_COND_V(x < 0 || y < 0, false);
	ERR_FAIL_COND_V(x > _size_x || y > _size_y, false);

	Ref<ItemTemplate> item_template = item->get_item_template();

	ERR_FAIL_COND_V(!item_template.is_valid(), true);

	int _item_size_x = item_template->get_inventory_size_x();
	int _item_size_y = item_template->get_inventory_size_y();

	ERR_FAIL_COND_V(x + _item_size_x > _size_x || y + _item_size_y > _size_y, false);

	int sx = x + _item_size_x;
	int sy = y + _item_size_y;

	for (int xx = x; xx < sx; ++xx) {
		for (int yy = y; yy < sy; ++yy) {
			if (_space_map[xx * _size_x + yy] != 0) {
				return false;
			}
		}
	}

	item->set_inventory_position_x(x);
	item->set_inventory_position_y(y);

	_items.push_back(item);

	int index = _items.size() - 1;

	for (int xx = x; xx < sx; ++xx) {
		for (int yy = y; yy < sy; ++yy) {
			_space_map.set(xx * _size_x + yy, index);
		}
	}

	return true;
}

bool GridBag::can_add_item_at(const int x, const int y, const Ref<ItemInstance> item) const {
	ERR_FAIL_COND_V(!item.is_valid(), false);
	ERR_FAIL_COND_V(x < 0 || y < 0, false);
	ERR_FAIL_COND_V(x > _size_x || y > _size_y, false);

	int indx = _space_map[x * _size_x + y];

	if (indx != 0) {
		Ref<ItemInstance> it = _items[indx];

		if (it.is_valid()) {
			if (it->get_item_template() == item->get_item_template()) {
				//todo check stacks
				return false;
			}
		}
	}

	Ref<ItemTemplate> item_template = item->get_item_template();

	ERR_FAIL_COND_V(!item_template.is_valid(), true);

	int _item_size_x = item_template->get_inventory_size_x();
	int _item_size_y = item_template->get_inventory_size_y();

	ERR_FAIL_COND_V(x + _item_size_x > _size_x || y + _item_size_y > _size_y, false);

	int sx = x + _item_size_x;
	int sy = y + _item_size_y;

	for (int xx = x; xx < sx; ++xx) {
		for (int yy = y; yy < sy; ++yy) {
			if (_space_map[xx * _size_x + yy] != 0) {
				return false;
			}
		}
	}

	return true;
}
int GridBag::item_count_under_area(const int x, const int y, const int size_x, const int size_y) const {
	ERR_FAIL_COND_V(x < 0 || y < 0, false);
	ERR_FAIL_COND_V(x > _size_x || y > _size_y, false);

	ERR_FAIL_COND_V(x + size_x > _size_x || y + size_y > _size_y, false);

	int count = 0;
	int sx = x + size_x;
	int sy = y + size_y;

	for (int xx = x; xx < sx; ++xx) {
		for (int yy = y; yy < sy; ++yy) {
			if (_space_map[xx * _size_x + yy] != 0) {
			}
		}
	}

	return count;
}

Ref<ItemInstance> GridBag::get_item(const int index) const {
	ERR_FAIL_INDEX_V(index, _items.size(), Ref<ItemInstance>(NULL));

	return (_items.get(index));
}

Ref<ItemInstance> GridBag::get_and_remove_item(const int index) {
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

void GridBag::remove_item(const int index) {
	ERR_FAIL_INDEX(index, _items.size());

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
}

void GridBag::basic_add_item(const Ref<ItemInstance> item) {
	_items.push_back(item);
}
void GridBag::basic_remove_item(const int index) {
	_items.remove(index);
}

int GridBag::get_item_count() const {
	return _items.size();
}

int GridBag::get_space_map_entry(const int index) const {
	return _space_map[index];
}
void GridBag::set_space_map_entry(const int index, const int value) {
	_space_map.set(index, value);
}

int GridBag::get_size_x() const {
	return _size_x;
}
int GridBag::get_size_y() const {
	return _size_y;
}

void GridBag::set_size(const int x, const int y) {
	ERR_FAIL_COND(x == 0 || y == 0);
	ERR_FAIL_COND(_size_x != 0 || _size_y != 0);

	_size_x = x;
	_size_y = y;

	_space_map.resize(x * y);

	for (int i = 0; i < _space_map.size(); ++i) {
		_space_map.set(i, 0);
	}
}

GridBag::GridBag() {
	_allowed_item_types = 0x1FFF;

	_size_x = 0;
	_size_y = 0;
}

GridBag::~GridBag() {
	_items.clear();
	_space_map.clear();
}

void GridBag::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_allowed_item_types"), &GridBag::get_allowed_item_types);
	ClassDB::bind_method(D_METHOD("set_allowed_item_types", "count"), &GridBag::set_allowed_item_types);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "allowed_item_types", PROPERTY_HINT_FLAGS, ItemEnums::BINDING_STRING_ITEM_TYPE_FLAGS), "set_allowed_item_types", "get_allowed_item_types");

	ClassDB::bind_method(D_METHOD("add_item", "item"), &GridBag::add_item);
	ClassDB::bind_method(D_METHOD("add_item_to_position", "x", "y", "item"), &GridBag::add_item_to_position);

	ClassDB::bind_method(D_METHOD("can_add_item_at", "x", "y", "item"), &GridBag::can_add_item_at);
	ClassDB::bind_method(D_METHOD("item_count_under_area", "x", "y", "item"), &GridBag::item_count_under_area);

	ClassDB::bind_method(D_METHOD("get_item", "index"), &GridBag::get_item);
	ClassDB::bind_method(D_METHOD("get_and_remove_item", "index"), &GridBag::get_and_remove_item);
	ClassDB::bind_method(D_METHOD("remove_item", "index"), &GridBag::remove_item);

	ClassDB::bind_method(D_METHOD("basic_add_item", "item"), &GridBag::basic_add_item);
	ClassDB::bind_method(D_METHOD("basic_remove_item", "index"), &GridBag::basic_remove_item);

	ClassDB::bind_method(D_METHOD("get_item_count"), &GridBag::get_item_count);

	ClassDB::bind_method(D_METHOD("get_space_map_entry", "index"), &GridBag::get_space_map_entry);
	ClassDB::bind_method(D_METHOD("set_space_map_entry", "index", "value"), &GridBag::set_space_map_entry);

	ClassDB::bind_method(D_METHOD("get_size_x"), &GridBag::get_size_x);
	ClassDB::bind_method(D_METHOD("get_size_y"), &GridBag::get_size_y);

	ClassDB::bind_method(D_METHOD("set_size", "x", "y"), &GridBag::set_size);
}
