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

#include "action_bar_entry.h"

#include "core/version.h"

#include "action_bar_profile.h"

#include "../../defines.h"

Ref<ActionBarProfile> ActionBarEntry::get_owner() {
	return Ref<ActionBarProfile>(_owner);
}
void ActionBarEntry::set_owner(ActionBarProfile *owner) {
	_owner = owner;
}

float ActionBarEntry::get_size() const {
	return _size;
}

void ActionBarEntry::set_size(const float value) {
	_size = value;

	emit_change();
}

int ActionBarEntry::get_action_bar_id() const {
	return _action_bar_id;
}

void ActionBarEntry::set_action_bar_id(const int value) {
	_action_bar_id = value;

	emit_change();
}

int ActionBarEntry::get_slot_num() const {
	return _slot_num;
}

void ActionBarEntry::set_slot_num(const int value) {
	_slot_num = value;

	emit_change();
}

int ActionBarEntry::get_action_bar_entry_count() const {
	return _button_entries.size();
}

void ActionBarEntry::emit_change() {
	emit_signal("changed");

	if (_owner != NULL)
		_owner->emit_change();
}

Ref<ActionBarButtonEntry> ActionBarEntry::get_button_for_slotid(const int slotId) {
	for (int i = 0; i < _button_entries.size(); ++i) {
		if (_button_entries.get(i)->get_slot_id() == slotId) {
			return _button_entries.get(i);
		}
	}

	Ref<ActionBarButtonEntry> abe = Ref<ActionBarButtonEntry>(memnew(ActionBarButtonEntry(_action_bar_id, slotId, ActionBarButtonEntry::ACTION_BAR_BUTTON_ENTRY_TYPE_NONE, StringName())));
	abe->set_owner(this);
	_button_entries.push_back(abe);

	emit_change();

	return Ref<ActionBarButtonEntry>(abe);
}

Ref<ActionBarButtonEntry> ActionBarEntry::get_button(const int index) {
	ERR_FAIL_INDEX_V(index, _button_entries.size(), Ref<ActionBarButtonEntry>(NULL));

	return _button_entries.get(index);
}

Dictionary ActionBarEntry::to_dict() const {
	Dictionary dict;

	dict["action_bar_id"] = _action_bar_id;
	dict["slot_num"] = _slot_num;

	Array arr;

	for (int i = 0; i < _button_entries.size(); ++i) {
		Dictionary d = _button_entries[i]->to_dict();

		arr.append(d);
	}

	dict["button_entries"] = arr;

	return dict;
}
void ActionBarEntry::from_dict(const Dictionary &dict) {
#if VERSION_MAJOR > 3
	ERR_FAIL_COND(dict.is_empty());
#else
	ERR_FAIL_COND(dict.empty());
#endif

	for (int i = 0; i < _button_entries.size(); ++i) {
		_button_entries.get(i)->set_owner(NULL);
	}

	_button_entries.clear();

	_action_bar_id = dict.get("action_bar_id", 0);
	_slot_num = dict.get("slot_num", 0);

	Array arr = dict.get("button_entries", Array());

	for (int i = 0; i < arr.size(); ++i) {
		Ref<ActionBarButtonEntry> e;
		e.instance();

		e->from_dict(arr.get(i));
		e->set_owner(this);

		_button_entries.push_back(e);
	}

	emit_change();
}

ActionBarEntry::ActionBarEntry() {
	_owner = NULL;

	_action_bar_id = 0;
	_size = 45;
	_slot_num = 12;
}

ActionBarEntry::~ActionBarEntry() {
	_button_entries.clear();
}

void ActionBarEntry::_bind_methods() {
	ADD_SIGNAL(MethodInfo("changed"));

	ClassDB::bind_method(D_METHOD("get_owner"), &ActionBarEntry::get_owner);

	ClassDB::bind_method(D_METHOD("get_size"), &ActionBarEntry::get_size);
	ClassDB::bind_method(D_METHOD("set_size", "value"), &ActionBarEntry::set_size);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "size"), "set_size", "get_size");

	ClassDB::bind_method(D_METHOD("get_action_bar_id"), &ActionBarEntry::get_action_bar_id);
	ClassDB::bind_method(D_METHOD("set_action_bar_id", "value"), &ActionBarEntry::set_action_bar_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "action_bar_id"), "set_action_bar_id", "get_action_bar_id");

	ClassDB::bind_method(D_METHOD("get_slot_num"), &ActionBarEntry::get_slot_num);
	ClassDB::bind_method(D_METHOD("set_slot_num", "value"), &ActionBarEntry::set_slot_num);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "slot_num"), "set_slot_num", "get_slot_num");

	ClassDB::bind_method(D_METHOD("get_action_bar_entry_count"), &ActionBarEntry::get_action_bar_entry_count);

	ClassDB::bind_method(D_METHOD("get_button_for_slotid", "slot_id"), &ActionBarEntry::get_button_for_slotid);
	ClassDB::bind_method(D_METHOD("get_button", "index"), &ActionBarEntry::get_button);

	ClassDB::bind_method(D_METHOD("from_dict", "dict"), &ActionBarEntry::from_dict);
	ClassDB::bind_method(D_METHOD("to_dict"), &ActionBarEntry::to_dict);

	ClassDB::bind_method(D_METHOD("emit_change"), &ActionBarEntry::emit_change);
}
