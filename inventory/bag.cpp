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
	ERR_FAIL_COND_V(!item.is_valid(), false);

	if (has_method("_add_item")) {
		return call("_add_item", item);
	}

	int max_stack = item->get_item_template()->get_stack_size();

	if (max_stack > 1) {
		for (int i = 0; i < _items.size(); ++i) {
			Ref<ItemInstance> ii = _items.get(i);

			if (!ii.is_valid())
				continue;

			if (ii->get_stack_size() < max_stack) {
				int fs = max_stack - ii->get_stack_size();

				if (fs > item->get_stack_size()) {
					ii->set_stack_size(ii->get_stack_size() + item->get_stack_size());

					item->set_stack_size(0);

					emit_signal("item_count_changed", Ref<Bag>(this), ii, i);

					return true;
				} else {
					ii->set_stack_size(max_stack);
					item->set_stack_size(item->get_stack_size() - fs);

					emit_signal("item_count_changed", Ref<Bag>(this), ii, i);
				}
			}
		}
	}

	for (int i = 0; i < _items.size(); ++i) {
		Ref<ItemInstance> ii = _items.get(i);

		if (!ii.is_valid()) {
			_items.set(i, item);

			emit_signal("item_added", Ref<Bag>(this), item, i);

			if (get_valid_item_count() == _bag_size) {
				emit_signal("overburdened", Ref<Bag>(this));
			}

			return true;
		}
	}

	_items.push_back(item);

	emit_signal("item_added", Ref<Bag>(this), item, _items.size() - 1);

	if (get_valid_item_count() == _bag_size) {
		emit_signal("overburdened", Ref<Bag>(this));
	}

	return true;
}

void Bag::add_item_at(int index, Ref<ItemInstance> item, bool signal) {
	if (has_method("_add_item_at")) {
		call("_add_item_at", index, item, signal);
		return;
	}

	if (_items.size() <= index) {
		_items.resize(index + 1);
	}

	_items.set(index, item);

	if (signal)
		emit_signal("item_added", Ref<Bag>(this), item, index);
}

Ref<ItemInstance> Bag::get_item(const int index) {
	if (has_method("_get_item")) {
		return call("_get_item", index);
	}

	if (index >= _items.size()) {
		return Ref<ItemInstance>();
	}

	return _items.get(index);
}

Ref<ItemInstance> Bag::remove_item(const int index) {
	if (has_method("_remove_item")) {
		return call("_remove_item", index);
	}

	ERR_FAIL_INDEX_V(index, _items.size(), Ref<ItemInstance>());

	Ref<ItemInstance> ii = _items.get(index);

	if (!ii.is_valid())
		return ii;

	_items.set(index, Ref<ItemInstance>());

	emit_signal("item_removed", Ref<Bag>(this), ii, index);

	if (get_valid_item_count() + 1 == _bag_size) {
		emit_signal("overburden_removed", Ref<Bag>(this));
	}

	return ii;
}

void Bag::swap_items(const int item1_index, const int item2_index) {
	if (has_method("_swap_items")) {
		call("_swap_items", item1_index, item2_index);
		return;
	}

	ERR_FAIL_INDEX(item1_index, _items.size());
	ERR_FAIL_INDEX(item2_index, _items.size());

	Ref<ItemInstance> ii = _items.get(item1_index);

	_items.set(item1_index, _items.get(item2_index));

	_items.set(item2_index, ii);

	emit_signal("item_swapped", Ref<Bag>(this), item1_index, item2_index);
}

void Bag::change_item_equip(int slot_id, Ref<ItemInstance> item) {
	if (has_method("_change_item_equip")) {
		call("_change_item_equip", slot_id, item);
		return;
	}

	ERR_FAIL_INDEX(slot_id, _items.size());

	_items.set(slot_id, item);

	emit_signal("change_item_equip", Ref<Bag>(this), slot_id, item);
}

void Bag::set_item_count(int slot_id, int new_count) {
	ERR_FAIL_INDEX(slot_id, _items.size());

	Ref<ItemInstance> ii = _items.get(slot_id);

	ERR_FAIL_COND(!ii.is_valid());

	ii->set_stack_size(new_count);

	emit_signal("item_count_changed", Ref<Bag>(this), ii, slot_id);
}

bool Bag::can_add_item(const Ref<ItemInstance> item) {
	if (has_method("_can_add_item")) {
		return call("_can_add_item", item);
	}

	return true;
}

int Bag::get_item_count() {
	if (has_method("_get_item_count")) {
		return call("_get_item_count");
	}

	return _items.size();
}

int Bag::get_valid_item_count() {
	if (has_method("_get_valid_item_count")) {
		return call("_get_valid_item_count");
	}

	int ii = 0;

	for (int i = 0; i < _items.size(); ++i) {
		if (_items.get(i).is_valid())
			++ii;
	}

	return ii;
}

int Bag::get_size() {
	if (has_method("_get_size")) {
		return call("_get_size");
	}

	return _bag_size;
}

void Bag::set_size(const int size) {
	if (has_method("_set_size")) {
		call("_set_size", size);
		return;
	}

	int item_count = get_valid_item_count();

	if (_bag_size > size && _bag_size > item_count && size <= item_count) {
		_bag_size = size;

		emit_signal("overburdened", Ref<Bag>(this));

		return;
	}

	_bag_size = size;

	if (_items.size() < _bag_size) {
		_items.resize(_bag_size);
	}

	emit_signal("size_changed", Ref<Bag>(this));
}

bool Bag::is_full() {
	if (has_method("_is_full")) {
		return call("_is_full");
	}

	return false;
}

bool Bag::is_overburdened() {
	if (has_method("_is_overburdened")) {
		return call("_is_overburdened");
	}

	return _bag_size < get_valid_item_count();
}

bool Bag::has_item(Ref<ItemTemplate> item, int count) {
	return call("_has_item", item, count);
}
bool Bag::_has_item(Ref<ItemTemplate> item, int count) {
	int c = 0;

	for (int i = 0; i < _items.size(); ++i) {
		Ref<ItemInstance> ii = _items.get(i);

		if (ii.is_valid()) {
			if (ii->get_item_template() == item) {
				c += ii->get_stack_size();

				if (c >= count) {
					return true;
				}
			}
		}
	}

	return false;
}

void Bag::remove_items(Ref<ItemTemplate> item, int count) {
	call("_remove_items", item, count);
}
void Bag::_remove_items(Ref<ItemTemplate> item, int count) {
	int c = count;

	for (int i = 0; i < _items.size(); ++i) {
		Ref<ItemInstance> ii = _items.get(i);

		if (ii.is_valid()) {
			if (ii->get_item_template() == item) {
				int ss = ii->get_stack_size();

				if (ss > c) {
					ii->set_stack_size(ss - c);

					emit_signal("item_count_changed", Ref<Bag>(this), ii, i);
					return;
				} else if (ss < c) {
					c -= ii->get_stack_size();

					remove_item(i);
				} else if (ss == c) {
					remove_item(i);
					return;
				}
			}
		}
	}
}

Dictionary Bag::to_dict() {
	return call("_to_dict");
}
void Bag::from_dict(const Dictionary &dict) {
	call("_from_dict", dict);
}

Dictionary Bag::_to_dict() {
	Dictionary dict;

	dict["allowed_item_types"] = _allowed_item_types;
	dict["bag_size"] = _bag_size;

	Dictionary items;

	for (int i = 0; i < _items.size(); ++i) {
		Ref<ItemInstance> ii = _items[i];

		if (ii.is_valid())
			items[i] = ii->to_dict();
	}

	dict["items"] = items;

	return dict;
}
void Bag::_from_dict(const Dictionary &dict) {
	_items.clear();

	set_size(dict.get("bag_size", 0));

	Dictionary items = dict.get("items", Dictionary());

	Array keys = items.keys();

	for (int i = 0; i < keys.size(); ++i) {
		Ref<ItemInstance> ii;
		ii.instance();

		ii->from_dict(items[keys.get(i)]);

		int key = keys.get(i);

		if (key >= _items.size()) {
			_items.resize(key + 1);
		}

		_items.set(key, ii);
	}

	_allowed_item_types = dict.get("allowed_item_types", 0xFFFFFF);
}

Bag::Bag() {
	_allowed_item_types = 0xFFFFFF;
	_bag_size = 0;
}

Bag::~Bag() {
	_items.clear();
}

void Bag::_bind_methods() {
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::BOOL, "could_add"), "_add_item", PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance")));
	BIND_VMETHOD(MethodInfo("_add_item_at", PropertyInfo(Variant::INT, "index"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::BOOL, "signal")));
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), "_get_item", PropertyInfo(Variant::INT, "index")));
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), "_remove_item", PropertyInfo(Variant::INT, "index")));
	BIND_VMETHOD(MethodInfo("_swap_items", PropertyInfo(Variant::INT, "item1_index"), PropertyInfo(Variant::INT, "item2_index")));
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::BOOL, "can"), "_can_add_item", PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance")));
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::INT, "count"), "_get_item_count"));
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::INT, "count"), "_get_valid_item_count"));
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::INT, "size"), "_get_size"));
	BIND_VMETHOD(MethodInfo("_set_size", PropertyInfo(Variant::INT, "size")));
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::BOOL, "full"), "_is_full"));
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::BOOL, "overburdened"), "_is_overburdened"));
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::BOOL, "has"), "_has_item", PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemTemplate"), PropertyInfo(Variant::INT, "count")));
	BIND_VMETHOD(MethodInfo("_remove_items", PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemTemplate"), PropertyInfo(Variant::INT, "count")));
	BIND_VMETHOD(MethodInfo("_change_item_equip", PropertyInfo(Variant::INT, "slot_id"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance")));

	ADD_SIGNAL(MethodInfo("item_added", PropertyInfo(Variant::OBJECT, "bag", PROPERTY_HINT_RESOURCE_TYPE, "Bag"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::INT, "slot_id")));
	ADD_SIGNAL(MethodInfo("item_removed", PropertyInfo(Variant::OBJECT, "bag", PROPERTY_HINT_RESOURCE_TYPE, "Bag"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::INT, "slot_id")));
	ADD_SIGNAL(MethodInfo("item_swapped", PropertyInfo(Variant::OBJECT, "bag", PROPERTY_HINT_RESOURCE_TYPE, "Bag"), PropertyInfo(Variant::INT, "slot_id_1"), PropertyInfo(Variant::INT, "slot_id_2")));
	ADD_SIGNAL(MethodInfo("item_count_changed", PropertyInfo(Variant::OBJECT, "bag", PROPERTY_HINT_RESOURCE_TYPE, "Bag"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance"), PropertyInfo(Variant::INT, "slot_id")));
	ADD_SIGNAL(MethodInfo("overburdened", PropertyInfo(Variant::OBJECT, "bag", PROPERTY_HINT_RESOURCE_TYPE, "Bag")));
	ADD_SIGNAL(MethodInfo("overburden_removed", PropertyInfo(Variant::OBJECT, "bag", PROPERTY_HINT_RESOURCE_TYPE, "Bag")));
	ADD_SIGNAL(MethodInfo("size_changed", PropertyInfo(Variant::OBJECT, "bag", PROPERTY_HINT_RESOURCE_TYPE, "Bag")));
	ADD_SIGNAL(MethodInfo("change_item_equip", PropertyInfo(Variant::OBJECT, "bag", PROPERTY_HINT_RESOURCE_TYPE, "Bag"), PropertyInfo(Variant::INT, "slot_id"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance")));

	ClassDB::bind_method(D_METHOD("get_allowed_item_types"), &Bag::get_allowed_item_types);
	ClassDB::bind_method(D_METHOD("set_allowed_item_types", "count"), &Bag::set_allowed_item_types);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "allowed_item_types", PROPERTY_HINT_FLAGS, ItemEnums::BINDING_STRING_ITEM_TYPE_FLAGS), "set_allowed_item_types", "get_allowed_item_types");

	ClassDB::bind_method(D_METHOD("add_item", "item"), &Bag::add_item);
	ClassDB::bind_method(D_METHOD("add_item_at", "index", "item", "signal"), &Bag::add_item_at, DEFVAL(true));
	ClassDB::bind_method(D_METHOD("get_item", "index"), &Bag::get_item);
	ClassDB::bind_method(D_METHOD("remove_item", "index"), &Bag::remove_item);
	ClassDB::bind_method(D_METHOD("swap_items", "item1_index", "item2_index"), &Bag::swap_items);
	ClassDB::bind_method(D_METHOD("change_item_equip", "index", "item"), &Bag::change_item_equip);

	ClassDB::bind_method(D_METHOD("can_add_item", "item"), &Bag::can_add_item);

	ClassDB::bind_method(D_METHOD("get_item_count"), &Bag::get_item_count);

	ClassDB::bind_method(D_METHOD("get_size"), &Bag::get_size);
	ClassDB::bind_method(D_METHOD("set_size", "size"), &Bag::set_size);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "size"), "set_size", "get_size");

	ClassDB::bind_method(D_METHOD("is_full"), &Bag::is_full);
	ClassDB::bind_method(D_METHOD("is_overburdened"), &Bag::is_overburdened);

	ClassDB::bind_method(D_METHOD("has_item", "item", "count"), &Bag::has_item);
	ClassDB::bind_method(D_METHOD("_has_item", "item", "count"), &Bag::_has_item);

	ClassDB::bind_method(D_METHOD("remove_items", "item", "count"), &Bag::remove_items);
	ClassDB::bind_method(D_METHOD("_remove_items", "item", "count"), &Bag::_remove_items);

	//Serialization
	BIND_VMETHOD(MethodInfo("_from_dict", PropertyInfo(Variant::DICTIONARY, "dict")));
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::DICTIONARY, "dict"), "_to_dict"));

	ClassDB::bind_method(D_METHOD("from_dict", "dict"), &Bag::from_dict);
	ClassDB::bind_method(D_METHOD("to_dict"), &Bag::to_dict);

	ClassDB::bind_method(D_METHOD("_from_dict", "dict"), &Bag::_from_dict);
	ClassDB::bind_method(D_METHOD("_to_dict"), &Bag::_to_dict);
}
