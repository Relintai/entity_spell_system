#include "input_profile_modifier_entry.h"

String InputProfileModifierEntry::get_action() {
	return _action;
}

void InputProfileModifierEntry::set_action(String value) {
	_action = value;
}

String InputProfileModifierEntry::get_translate_to() {
	return _translate_to;
}

void InputProfileModifierEntry::set_translate_to(String value) {
	_action = _translate_to;
}

InputProfileModifierEntry::InputProfileModifierEntry() {

}

void InputProfileModifierEntry::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_action"), &InputProfileModifierEntry::get_action);
	ClassDB::bind_method(D_METHOD("set_action", "value"), &InputProfileModifierEntry::set_action);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "action"), "set_action", "get_action");

	ClassDB::bind_method(D_METHOD("get_translate_to"), &InputProfileModifierEntry::get_translate_to);
	ClassDB::bind_method(D_METHOD("set_translate_to", "value"), &InputProfileModifierEntry::set_translate_to);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "translate_to"), "set_translate_to", "get_translate_to");
}

