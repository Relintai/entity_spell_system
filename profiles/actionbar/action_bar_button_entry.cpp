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

#include "action_bar_button_entry.h"

#include "action_bar_entry.h"

const String ActionBarButtonEntry::BINDING_STRING_ACTIONBAR_BUTTON_ENTRY_TYPE = "None, Spell, Item";

Ref<ActionBarEntry> ActionBarButtonEntry::get_owner() {
	return Ref<ActionBarEntry>(_owner);
}
void ActionBarButtonEntry::set_owner(ActionBarEntry *owner) {
	_owner = owner;
}

int ActionBarButtonEntry::get_action_bar_id() {
	return _action_bar_id;
}

void ActionBarButtonEntry::set_action_bar_id(int value) {
	_action_bar_id = value;

	emit_change();
}

int ActionBarButtonEntry::get_slot_id() {
	return _slot_id;
}

void ActionBarButtonEntry::set_slot_id(int value) {
	_slot_id = value;

	emit_change();
}

ActionBarButtonEntry::ActionBarButtonEntryType ActionBarButtonEntry::get_type() {
	return _type;
}

void ActionBarButtonEntry::set_type(ActionBarButtonEntry::ActionBarButtonEntryType value) {
	_type = value;

	emit_change();
}

int ActionBarButtonEntry::get_item_id() {
	return _item_id;
}

void ActionBarButtonEntry::set_item_id(int value) {
	_item_id = value;

	emit_change();
}

void ActionBarButtonEntry::emit_change() {
	emit_signal("changed", Ref<ActionBarButtonEntry>(this));

	if (_owner != NULL)
		_owner->emit_change();
}

Dictionary ActionBarButtonEntry::to_dict() const {
	Dictionary dict;

	dict["action_bar_id"] = _action_bar_id;
	dict["slot_id"] = _slot_id;
	dict["type"] = _type;
	dict["item_id"] = _item_id;

	return dict;
}
void ActionBarButtonEntry::from_dict(const Dictionary &dict) {
	ERR_FAIL_COND(dict.empty());

	_action_bar_id = dict.get("action_bar_id", 0);
	_slot_id = dict.get("slot_id", 0);
	_type = VariantCaster<ActionBarButtonEntryType>().cast(dict.get("type", ACTION_BAR_BUTTON_ENTRY_TYPE_NONE));
	_item_id = dict.get("item_id", 0);

	emit_change();
}

ActionBarButtonEntry::ActionBarButtonEntry() {
	_owner = NULL;

	_action_bar_id = 0;
	_slot_id = 0;
	_type = ACTION_BAR_BUTTON_ENTRY_TYPE_NONE;
	_item_id = 0;
}

ActionBarButtonEntry::ActionBarButtonEntry(int actionBarId, int slotId) {
	_owner = NULL;

	_action_bar_id = actionBarId;
	_slot_id = slotId;

	_type = ACTION_BAR_BUTTON_ENTRY_TYPE_NONE;
	_item_id = 0;
}

ActionBarButtonEntry::ActionBarButtonEntry(int actionBarId, int slotId, ActionBarButtonEntryType type, int itemId) {
	_owner = NULL;

	_action_bar_id = actionBarId;
	_slot_id = slotId;
	_type = type;
	_item_id = itemId;
}

ActionBarButtonEntry::~ActionBarButtonEntry() {
}

void ActionBarButtonEntry::_bind_methods() {
	ADD_SIGNAL(MethodInfo("changed", PropertyInfo(Variant::OBJECT, "action_bar_button_entry", PROPERTY_HINT_RESOURCE_TYPE, "ActionBarButtonEntry")));

	ClassDB::bind_method(D_METHOD("get_owner"), &ActionBarButtonEntry::get_owner);

	ClassDB::bind_method(D_METHOD("get_action_bar_id"), &ActionBarButtonEntry::get_action_bar_id);
	ClassDB::bind_method(D_METHOD("set_action_bar_id", "value"), &ActionBarButtonEntry::set_action_bar_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "action_bar_id"), "set_action_bar_id", "get_action_bar_id");

	ClassDB::bind_method(D_METHOD("get_slot_id"), &ActionBarButtonEntry::get_slot_id);
	ClassDB::bind_method(D_METHOD("set_slot_id", "value"), &ActionBarButtonEntry::set_slot_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "slot_id"), "set_slot_id", "get_slot_id");

	ClassDB::bind_method(D_METHOD("get_type"), &ActionBarButtonEntry::get_type);
	ClassDB::bind_method(D_METHOD("set_type", "value"), &ActionBarButtonEntry::set_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "type", PROPERTY_HINT_ENUM, ActionBarButtonEntry::BINDING_STRING_ACTIONBAR_BUTTON_ENTRY_TYPE), "set_type", "get_type");

	ClassDB::bind_method(D_METHOD("get_item_id"), &ActionBarButtonEntry::get_item_id);
	ClassDB::bind_method(D_METHOD("set_item_id", "value"), &ActionBarButtonEntry::set_item_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "item_id"), "set_item_id", "get_item_id");

	ClassDB::bind_method(D_METHOD("from_dict", "dict"), &ActionBarButtonEntry::from_dict);
	ClassDB::bind_method(D_METHOD("to_dict"), &ActionBarButtonEntry::to_dict);

	ClassDB::bind_method(D_METHOD("emit_change"), &ActionBarButtonEntry::emit_change);

	BIND_ENUM_CONSTANT(ACTION_BAR_BUTTON_ENTRY_TYPE_NONE);
	BIND_ENUM_CONSTANT(ACTION_BAR_BUTTON_ENTRY_TYPE_SPELL);
	BIND_ENUM_CONSTANT(ACTION_BAR_BUTTON_ENTRY_TYPE_ITEM);
}
