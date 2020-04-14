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

#include "item_instance.h"

#include "item_template.h"

#include "../../database/ess_resource_db.h"
#include "../../singletons/ess.h"

Ref<ItemTemplate> ItemInstance::get_item_template() {
	return _item_template;
}
void ItemInstance::set_item_template(const Ref<ItemTemplate> &value) {
	_item_template = value;

	_item_template_id = 0;

	if (value.is_valid())
		_item_template_id = value->get_id();
}

Ref<ItemStatModifier> ItemInstance::get_item_stat_modifier(const int index) {
	ERR_FAIL_INDEX_V(index, _modifiers.size(), Ref<ItemStatModifier>());

	return _modifiers.get(index);
}
void ItemInstance::add_item_stat_modifier(const Ref<ItemStatModifier> &modifier) {
	_modifiers.push_back(modifier);
}
void ItemInstance::remove_item_stat_modifier(const int index) {
	ERR_FAIL_INDEX(index, _modifiers.size());

	_modifiers.remove(index);
}
void ItemInstance::clear_item_stat_modifiers() {
	_modifiers.clear();
}
int ItemInstance::get_item_stat_modifier_count() const {
	return _modifiers.size();
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

	dict["item_id"] = _item_template->get_id();

	dict["stack_size"] = _stack_size;

	Array mods;

	for (int i = 0; i < _modifiers.size(); ++i) {
		mods.append(_modifiers.get(i)->to_dict());
	}

	dict["modifiers"] = mods;

	return dict;
}
void ItemInstance::_from_dict(const Dictionary &dict) {
	ERR_FAIL_COND(dict.empty());

	_item_template_id = dict.get("item_id", 0);

	if (ESS::get_instance() != NULL) {
		_item_template = ESS::get_instance()->get_resource_db()->get_item_template(_item_template_id);
	}

	_stack_size = dict.get("stack_size", 0);

	Array mods = dict.get("modifiers", Array());

	for (int i = 0; i < mods.size(); ++i) {
		Ref<ItemStatModifier> mod;
		mod.instance();

		mod->from_dict(mods.get(i));

		_modifiers.push_back(mod);
	}
}

ItemInstance::ItemInstance() {
	_stack_size = 1;
	_item_template_id = 0;
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

	ClassDB::bind_method(D_METHOD("get_item_stat_modifier", "index"), &ItemInstance::get_item_stat_modifier);
	ClassDB::bind_method(D_METHOD("add_item_stat_modifier", "modifier"), &ItemInstance::add_item_stat_modifier);
	ClassDB::bind_method(D_METHOD("remove_item_stat_modifier", "index"), &ItemInstance::remove_item_stat_modifier);
	ClassDB::bind_method(D_METHOD("clear_item_stat_modifiers"), &ItemInstance::clear_item_stat_modifiers);
	ClassDB::bind_method(D_METHOD("get_item_stat_modifier_count"), &ItemInstance::get_item_stat_modifier_count);

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
