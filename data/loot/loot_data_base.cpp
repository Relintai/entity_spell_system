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

#include "loot_data_base.h"

#include "../../defines.h"

int LootDataBase::get_loot_db_size() const {
	return _loot_dbs.size();
}
void LootDataBase::set_loot_db_size(const float value) {
	_loot_dbs.resize(value);
}

int LootDataBase::get_items_size() const {
	return _items.size();
}
void LootDataBase::set_items_size(const int value) {
	_items.resize(value);
}

float LootDataBase::get_loot_db_chance(const int index) const {
	ERR_FAIL_INDEX_V(index, _loot_dbs.size(), 0);

	return _loot_dbs.get(index).chance;
}
void LootDataBase::set_loot_db_chance(const int index, const float value) {
	ERR_FAIL_INDEX(index, _loot_dbs.size());

	LootDBLDF l = _loot_dbs.get(index);
	l.chance = value;
	_loot_dbs.set(index, l);
}

Ref<LootDataBase> LootDataBase::get_loot_db(const int index) const {
	ERR_FAIL_INDEX_V(index, _loot_dbs.size(), 0);

	return _loot_dbs.get(index).loot_db;
}
void LootDataBase::set_loot_db(const int index, const Ref<LootDataBase> &value) {
	ERR_FAIL_INDEX(index, _loot_dbs.size());

	LootDBLDF l = _loot_dbs.get(index);
	l.loot_db = value;
	_loot_dbs.set(index, l);
}

float LootDataBase::get_item_chance(const int index) const {
	ERR_FAIL_INDEX_V(index, _items.size(), 0);

	return _items.get(index).chance;
}
void LootDataBase::set_item_chance(const int index, const float value) {
	ERR_FAIL_INDEX(index, _items.size());

	LootDBItem l = _items.get(index);
	l.chance = value;
	_items.set(index, l);
}

Ref<ItemTemplate> LootDataBase::get_item(const int index) const {
	ERR_FAIL_INDEX_V(index, _items.size(), 0);

	return _items.get(index).item;
}
void LootDataBase::set_item(const int index, const Ref<ItemTemplate> &value) {
	ERR_FAIL_INDEX(index, _items.size());

	LootDBItem l = _items.get(index);
	l.item = value;
	_items.set(index, l);
}

Array LootDataBase::get_loot() {
	return call("_get_loot");
}

Array LootDataBase::_get_loot() {
	Array arr;

	for (int i = 0; i < _loot_dbs.size(); ++i) {
		LootDBLDF l = _loot_dbs.get(i);

		if (!l.loot_db.is_valid())
			continue;

		Math::randomize();

		float val = Math::randf() * 100.0;

		if (val < l.chance) {
			arr.append(l.loot_db->get_loot());
		}
	}

	for (int i = 0; i < _items.size(); ++i) {
		LootDBItem l = _items.get(i);

		if (!l.item.is_valid())
			continue;

		Math::randomize();

		float val = Math::randf() * 100.0;

		if (val < l.chance) {
			arr.append(l.item);
		}
	}

	return arr;
}

LootDataBase::LootDataBase() {
}

LootDataBase::~LootDataBase() {
	_loot_dbs.clear();
	_items.clear();
}

bool LootDataBase::_set(const StringName &p_name, const Variant &p_value) {
	String name = p_name;

	if (name.begins_with("loot_dbs/")) {
		int index = name.get_slicec('/', 1).to_int();
		String what = name.get_slicec('/', 2);

		if (_loot_dbs.size() <= index) {
			set_loot_db_size(index);
		}

		LootDBLDF ldb = _loot_dbs.get(index);

		if (what == "chance") {
			ldb.chance = p_value;
			_loot_dbs.set(index, ldb);

			return true;
		} else if (what == "loot_db") {
			ldb.loot_db = p_value;
			_loot_dbs.set(index, ldb);

			return true;
		}

		return false;

	} else if (name.begins_with("items/")) {
		int index = name.get_slicec('/', 1).to_int();
		String what = name.get_slicec('/', 2);

		if (_items.size() <= index) {
			set_items_size(index);
		}

		LootDBItem ldb = _items.get(index);

		if (what == "chance") {
			ldb.chance = p_value;
			_items.set(index, ldb);

			return true;
		} else if (what == "item_template") {
			ldb.item = p_value;
			_items.set(index, ldb);

			return true;
		}

		return false;
	}

	return true;
}

bool LootDataBase::_get(const StringName &p_name, Variant &r_ret) const {
	String name = p_name;

	if (name.begins_with("loot_dbs/")) {
		int index = name.get_slicec('/', 1).to_int();
		String what = name.get_slicec('/', 2);

		if (_loot_dbs.size() <= index) {
			return false;
		}

		LootDBLDF ldb = _loot_dbs.get(index);

		if (what == "chance") {
			r_ret = ldb.chance;

			return true;
		} else if (what == "loot_db") {
			r_ret = ldb.loot_db;

			return true;
		}

		return false;
	} else if (name.begins_with("items/")) {
		int index = name.get_slicec('/', 1).to_int();
		String what = name.get_slicec('/', 2);

		if (_items.size() <= index) {
			return false;
		}

		LootDBItem ldb = _items.get(index);

		if (what == "chance") {
			r_ret = ldb.chance;

			return true;
		} else if (what == "item_template") {
			r_ret = ldb.item;

			return true;
		}

		return false;
	}

	return true;
}

void LootDataBase::_get_property_list(List<PropertyInfo> *p_list) const {
	int property_usange = PROPERTY_USAGE_DEFAULT;

	for (int i = 0; i < _loot_dbs.size(); ++i) {
		p_list->push_back(PropertyInfo(Variant::REAL, "loot_dbs/" + itos(i) + "/chance", PROPERTY_HINT_NONE, "", property_usange));
		p_list->push_back(PropertyInfo(Variant::OBJECT, "loot_dbs/" + itos(i) + "/loot_db", PROPERTY_HINT_RESOURCE_TYPE, "LootDataBase", property_usange));
	}

	for (int i = 0; i < _items.size(); ++i) {
		p_list->push_back(PropertyInfo(Variant::REAL, "items/" + itos(i) + "/chance", PROPERTY_HINT_NONE, "", property_usange));
		p_list->push_back(PropertyInfo(Variant::OBJECT, "items/" + itos(i) + "/item_template", PROPERTY_HINT_RESOURCE_TYPE, "ItemTemplate", property_usange));
	}
}

void LootDataBase::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_loot_db_size"), &LootDataBase::get_loot_db_size);
	ClassDB::bind_method(D_METHOD("set_loot_db_size", "value"), &LootDataBase::set_loot_db_size);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "loot_db_size", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED), "set_loot_db_size", "get_loot_db_size");

	ClassDB::bind_method(D_METHOD("get_items_size"), &LootDataBase::get_items_size);
	ClassDB::bind_method(D_METHOD("set_items_size", "value"), &LootDataBase::set_items_size);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "items_size", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED), "set_items_size", "get_items_size");

	ClassDB::bind_method(D_METHOD("get_loot_db_chance", "index"), &LootDataBase::get_loot_db_chance);
	ClassDB::bind_method(D_METHOD("set_loot_db_chance", "index", "value"), &LootDataBase::set_loot_db_chance);

	ClassDB::bind_method(D_METHOD("get_loot_db", "index"), &LootDataBase::get_loot_db);
	ClassDB::bind_method(D_METHOD("set_loot_db", "index", "value"), &LootDataBase::set_loot_db);

	ClassDB::bind_method(D_METHOD("get_item_chance", "index"), &LootDataBase::get_item_chance);
	ClassDB::bind_method(D_METHOD("set_item_chance", "index", "value"), &LootDataBase::set_item_chance);

	ClassDB::bind_method(D_METHOD("get_item", "index"), &LootDataBase::get_item);
	ClassDB::bind_method(D_METHOD("set_item", "index", "value"), &LootDataBase::set_item);

	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::ARRAY, "arr"), "_get_loot"));

	ClassDB::bind_method(D_METHOD("get_loot"), &LootDataBase::get_loot);
	ClassDB::bind_method(D_METHOD("_get_loot"), &LootDataBase::_get_loot);
}
