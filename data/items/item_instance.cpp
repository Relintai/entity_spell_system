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

#include "item_instance.h"

#include "item_template.h"

#include "../../database/ess_resource_db.h"
#include "../../singletons/ess.h"

#include "core/version.h"

Ref<ItemTemplate> ItemInstance::get_item_template() {
	return _item_template;
}
void ItemInstance::set_item_template(const Ref<ItemTemplate> &value) {
	_item_template = value;

	_item_template_path = "";

	if (value.is_valid())
		_item_template_path = value->get_path();
}

int ItemInstance::stat_modifier_get_stat_id(const int index) const {
	ERR_FAIL_INDEX_V(index, _modifiers.size(), 0);

	return _modifiers[index].stat_id;
}
void ItemInstance::stat_modifier_set_stat_id(const int index, const int value) {
	ERR_FAIL_INDEX(index, _modifiers.size());

	_modifiers.write[index].stat_id = value;
}

float ItemInstance::stat_modifier_get_base_mod(const int index) const {
	ERR_FAIL_INDEX_V(index, _modifiers.size(), 0);

	return _modifiers[index].base_mod;
}
void ItemInstance::stat_modifier_set_base_mod(const int index, const float value) {
	ERR_FAIL_INDEX(index, _modifiers.size());

	_modifiers.write[index].base_mod = value;
}

float ItemInstance::stat_modifier_get_bonus_mod(const int index) const {
	ERR_FAIL_INDEX_V(index, _modifiers.size(), 0);

	return _modifiers[index].bonus_mod;
}
void ItemInstance::stat_modifier_set_bonus_mod(const int index, const float value) {
	ERR_FAIL_INDEX(index, _modifiers.size());

	_modifiers.write[index].bonus_mod = value;
}

float ItemInstance::stat_modifier_get_percent_mod(const int index) const {
	ERR_FAIL_INDEX_V(index, _modifiers.size(), 0);

	return _modifiers[index].percent_mod;
}
void ItemInstance::stat_modifier_set_percent_mod(const int index, const float value) {
	ERR_FAIL_INDEX(index, _modifiers.size());

	_modifiers.write[index].percent_mod = value;
}

void ItemInstance::add_item_stat_modifier(const int stat_id, const int base_mod, const int bonus_mod, const int percent_mod) {
	ItemStatModifier mod;

	mod.stat_id = stat_id;
	mod.base_mod = base_mod;
	mod.bonus_mod = bonus_mod;
	mod.percent_mod = percent_mod;

	_modifiers.push_back(mod);
}
void ItemInstance::remove_item_stat_modifier(const int index) {
	ERR_FAIL_INDEX(index, _modifiers.size());

	_modifiers.remove(index);
}
void ItemInstance::clear_item_stat_modifiers() {
	_modifiers.clear();
}
int ItemInstance::stat_modifier_get_count() const {
	return _modifiers.size();
}

Vector<Variant> ItemInstance::stat_modifiers_get() {
	Vector<Variant> arr;
	arr.resize(_modifiers.size() * 4);

	for (int i = 0; i < _modifiers.size(); ++i) {
		int indx = i * 4;
		const ItemStatModifier &m = _modifiers[i];

		arr.write[indx] = m.stat_id;
		arr.write[indx + 1] = m.base_mod;
		arr.write[indx + 2] = m.bonus_mod;
		arr.write[indx + 3] = m.percent_mod;
	}

	return arr;
}
void ItemInstance::stat_modifiers_set(const Vector<Variant> &mods) {
	ERR_FAIL_COND((mods.size() % 4) != 0);

	_modifiers.resize(mods.size() / 4);

	for (int i = 0; i < _modifiers.size(); ++i) {
		int indx = i * 4;
		ItemStatModifier &m = _modifiers.write[i];

		m.stat_id = mods[indx];
		m.base_mod = mods[indx + 1];
		m.bonus_mod = mods[indx + 2];
		m.percent_mod = mods[indx + 3];
	}
}

int ItemInstance::get_stack_size() const {
	return _stack_size;
}
void ItemInstance::set_stack_size(const int value) {
	_stack_size = value;

	emit_signal("stack_size_changed", Ref<ItemInstance>(this));
}

int ItemInstance::get_charges() const {
	return _charges;
}
void ItemInstance::set_charges(const int value) {
	_charges = value;

	emit_signal("stack_charges_changed", Ref<ItemInstance>(this));
}

String ItemInstance::get_description() {
	if (!has_method("_get_description"))
		return "";

	return call("_get_description");
}

Dictionary ItemInstance::to_dict() {
	return call("_to_dict");
}
void ItemInstance::from_dict(const Dictionary &dict) {
	call("_from_dict", dict);
}

Dictionary ItemInstance::_to_dict() {
	Dictionary dict;

	dict["item_path"] = _item_template->get_path();

	dict["stack_size"] = _stack_size;

	Array mods;

	for (int i = 0; i < _modifiers.size(); ++i) {
		Dictionary mdict;

		mdict["stat_id"] = _modifiers[i].stat_id;

		mdict["base_mod"] = _modifiers[i].base_mod;
		mdict["bonus_mod"] = _modifiers[i].bonus_mod;
		mdict["percent_mod"] = _modifiers[i].percent_mod;

		mods.append(mdict);
	}

	dict["modifiers"] = mods;

	return dict;
}
void ItemInstance::_from_dict(const Dictionary &dict) {
#if VERSION_MAJOR > 3
	ERR_FAIL_COND(dict.is_empty());
#else
	ERR_FAIL_COND(dict.empty());
#endif

	_item_template_path = dict.get("item_path", 0);

	if (ESS::get_singleton() != NULL) {
		_item_template = ESS::get_singleton()->get_resource_db()->get_item_template_path(_item_template_path);
	}

	_stack_size = dict.get("stack_size", 0);

	Array mods = dict.get("modifiers", Array());

	for (int i = 0; i < mods.size(); ++i) {
		ItemStatModifier mod;
		Dictionary mdict = mods.get(i);

		mod.stat_id = dict.get("stat_id", 0);
		mod.base_mod = dict.get("base_mod", 0);
		mod.bonus_mod = dict.get("bonus_mod", 0);
		mod.percent_mod = dict.get("percent_mod", 0);

		_modifiers.push_back(mod);
	}
}

ItemInstance::ItemInstance() {
	_stack_size = 1;
	_charges = -1;
}
ItemInstance::~ItemInstance() {
	_modifiers.clear();
}

void ItemInstance::_bind_methods() {
	ADD_SIGNAL(MethodInfo("stack_size_changed", PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance")));
	ADD_SIGNAL(MethodInfo("stack_charges_changed", PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "ItemInstance")));

	ClassDB::bind_method(D_METHOD("get_item_template"), &ItemInstance::get_item_template);
	ClassDB::bind_method(D_METHOD("set_item_template", "value"), &ItemInstance::set_item_template);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "item_template", PROPERTY_HINT_RESOURCE_TYPE, "ItemTemplate"), "set_item_template", "get_item_template");

	ClassDB::bind_method(D_METHOD("get_stack_size"), &ItemInstance::get_stack_size);
	ClassDB::bind_method(D_METHOD("set_stack_size", "count"), &ItemInstance::set_stack_size);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "stack_size"), "set_stack_size", "get_stack_size");

	ClassDB::bind_method(D_METHOD("get_charges"), &ItemInstance::get_charges);
	ClassDB::bind_method(D_METHOD("set_charges", "size"), &ItemInstance::set_charges);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "charges"), "set_charges", "get_charges");

	ClassDB::bind_method(D_METHOD("stat_modifier_get_stat_id", "index"), &ItemInstance::stat_modifier_get_stat_id);
	ClassDB::bind_method(D_METHOD("stat_modifier_set_stat_id", "index", "value"), &ItemInstance::stat_modifier_set_stat_id);

	ClassDB::bind_method(D_METHOD("stat_modifier_get_base_mod", "index"), &ItemInstance::stat_modifier_get_base_mod);
	ClassDB::bind_method(D_METHOD("stat_modifier_set_base_mod", "index", "value"), &ItemInstance::stat_modifier_set_base_mod);

	ClassDB::bind_method(D_METHOD("stat_modifier_get_bonus_mod", "index"), &ItemInstance::stat_modifier_get_bonus_mod);
	ClassDB::bind_method(D_METHOD("stat_modifier_set_bonus_mod", "index", "value"), &ItemInstance::stat_modifier_set_bonus_mod);

	ClassDB::bind_method(D_METHOD("stat_modifier_get_percent_mod", "index"), &ItemInstance::stat_modifier_get_percent_mod);
	ClassDB::bind_method(D_METHOD("stat_modifier_set_percent_mod", "index", "value"), &ItemInstance::stat_modifier_set_percent_mod);

	ClassDB::bind_method(D_METHOD("add_item_stat_modifier", "stat_id", "base_mod", "bonus_mod", "percent_mod"), &ItemInstance::add_item_stat_modifier);
	ClassDB::bind_method(D_METHOD("remove_item_stat_modifier", "index"), &ItemInstance::remove_item_stat_modifier);
	ClassDB::bind_method(D_METHOD("clear_item_stat_modifiers"), &ItemInstance::clear_item_stat_modifiers);
	ClassDB::bind_method(D_METHOD("stat_modifier_get_count"), &ItemInstance::stat_modifier_get_count);

	ClassDB::bind_method(D_METHOD("stat_modifiers_get"), &ItemInstance::stat_modifiers_get);
	ClassDB::bind_method(D_METHOD("stat_modifiers_set", "mods"), &ItemInstance::stat_modifiers_set);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "stat_modifiers", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT, ""), "stat_modifiers_set", "stat_modifiers_get");

	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::STRING, "desc"), "_get_description"));
	ClassDB::bind_method(D_METHOD("get_description"), &ItemInstance::get_description);

	//Serialization
	BIND_VMETHOD(MethodInfo("_from_dict", PropertyInfo(Variant::DICTIONARY, "dict")));
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::DICTIONARY, "dict"), "_to_dict"));

	ClassDB::bind_method(D_METHOD("from_dict", "dict"), &ItemInstance::from_dict);
	ClassDB::bind_method(D_METHOD("to_dict"), &ItemInstance::to_dict);

	ClassDB::bind_method(D_METHOD("_from_dict", "dict"), &ItemInstance::_from_dict);
	ClassDB::bind_method(D_METHOD("_to_dict"), &ItemInstance::_to_dict);
}
