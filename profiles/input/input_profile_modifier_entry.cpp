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
