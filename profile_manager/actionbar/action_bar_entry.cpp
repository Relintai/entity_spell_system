#include "action_bar_entry.h"

float ActionBarEntry::get_size() {
	return _size;
}

void ActionBarEntry::set_size(float value) {
	_size = value;

	emit_signal("changed");
}

int ActionBarEntry::get_action_bar_id() {
	return _action_bar_id;
}

void ActionBarEntry::set_action_bar_id(int value) {
	_action_bar_id = value;

	emit_signal("changed");
}

int ActionBarEntry::get_slot_num() {
	return _slot_num;
}

void ActionBarEntry::set_slot_num(int value) {
	_slot_num = value;

	emit_signal("changed");
}

int ActionBarEntry::get_action_bar_entry_count() {
	return _button_entries.size();
}

Ref<ActionBarButtonEntry> ActionBarEntry::get_button_for_slotid(int slotId) {
	for (int i = 0; i < _button_entries.size(); ++i) {
		if (_button_entries.get(i)->get_slot_id() == slotId) {
			return _button_entries.get(i);
		}
	}

	Ref<ActionBarButtonEntry> abe = Ref<ActionBarButtonEntry>(memnew(ActionBarButtonEntry(_action_bar_id, slotId, ActionBarButtonEntry::ACTION_BAR_BUTTON_ENTRY_TYPE_NONE, 0)));
	_button_entries.push_back(abe);
	return Ref<ActionBarButtonEntry>(abe);
}

Ref<ActionBarButtonEntry> ActionBarEntry::get_button(int index) {
	ERR_FAIL_INDEX_V(index, _button_entries.size(), Ref<ActionBarButtonEntry>(NULL));

	return _button_entries.get(index);
}

Dictionary ActionBarEntry::to_dict() const  {
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
	ERR_FAIL_COND(dict.empty());

	_button_entries.clear();

	_action_bar_id = dict.get("action_bar_id", 0);
	_slot_num = dict.get("slot_num", 0);
	
	Array arr = dict.get("button_entries", Array());

	for (int i = 0; i < arr.size(); ++i) {
		Ref<ActionBarButtonEntry> e;
		e.instance();
		
		e->from_dict(arr.get(i));

		_button_entries.push_back(e);
	}
}

ActionBarEntry::ActionBarEntry() {
	_size = 45;
	_slot_num = 12;
}

ActionBarEntry::~ActionBarEntry() {
	_button_entries.clear();
}

void ActionBarEntry::_bind_methods() {
	ADD_SIGNAL(MethodInfo("changed"));

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
}
