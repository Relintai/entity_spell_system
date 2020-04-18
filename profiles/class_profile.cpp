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

#include "class_profile.h"

int ClassProfile::get_class_id() {
	return _class_id;
}

void ClassProfile::set_class_id(int value) {
	_class_id = value;
}

String ClassProfile::get_character_class_name() {
	return _character_class_name;
}

void ClassProfile::set_character_class_name(String value) {
	_character_class_name = value;
}

int ClassProfile::get_level() {
	return _level;
}

void ClassProfile::set_level(int value) {
	_level = value;

	emit_change();
}

int ClassProfile::get_xp() {
	return _xp;
}

void ClassProfile::set_xp(int value) {
	_xp = value;

	emit_change();
}

bool ClassProfile::get_actionbar_locked() {
	return _actionbar_locked;
}
void ClassProfile::set_actionbar_locked(bool value) {
	_actionbar_locked = value;

	emit_change();
}

Ref<InputProfile> ClassProfile::get_input_profile() {
	return _input_profile;
}
Ref<ActionBarProfile> ClassProfile::get_action_bar_profile() {
	return _action_bar_profile;
}

void ClassProfile::emit_change() {
	emit_signal("changed");
}

bool ClassProfile::has_custom_data(const String &p_name) const {
	return _custom_data.has(p_name);
}

void ClassProfile::set_custom_data(const String &p_name, const Variant &p_value) {
	if (p_value.get_type() == Variant::NIL) {
		_custom_data.erase(p_name);

		emit_change();

		return;
	};

	_custom_data[p_name] = p_value;

	emit_change();
}

Variant ClassProfile::get_custom_data(const String &p_name) const {
	ERR_FAIL_COND_V(!_custom_data.has(p_name), Variant());

	return _custom_data[p_name];
}

void ClassProfile::remove_custom_data(const String &p_name) {
	_custom_data.erase(p_name);

	emit_change();
}

Dictionary ClassProfile::to_dict() const {
	Dictionary dict;

	dict["character_class_name"] = _character_class_name;
	dict["class_id"] = _class_id;
	dict["level"] = _level;
	dict["xp"] = _xp;
	dict["actionbar_locked"] = _actionbar_locked;
	dict["actionbar_profile"] = _action_bar_profile->to_dict();

	dict["custom_data"] = _custom_data;

	return dict;
}
void ClassProfile::from_dict(const Dictionary &dict) {
	ERR_FAIL_COND(dict.empty());

	_character_class_name = dict.get("character_class_name", "");
	_class_id = dict.get("class_id", 0);
	_level = dict.get("level", 1);
	_xp = dict.get("xp", 0);
	_actionbar_locked = dict.get("actionbar_locked", false);

	_action_bar_profile->from_dict(dict.get("actionbar_profile", Dictionary()));

	_custom_data = dict.get("custom_data", Dictionary());

	emit_change();
}

ClassProfile::ClassProfile() {
	_action_bar_profile.instance();
	_action_bar_profile->set_owner(this);
	_input_profile.instance();

	_class_id = 0;
	_level = 1;
	_xp = 0;
	_actionbar_locked = false;
}

ClassProfile::ClassProfile(int class_id) {
	_action_bar_profile.instance();
	_action_bar_profile->set_owner(this);
	_input_profile.instance();

	_class_id = class_id;
	_level = 1;
	_xp = 0;
	_actionbar_locked = false;
}

ClassProfile::ClassProfile(String class_name, int class_id, int level, int xp, bool locked) {
	_action_bar_profile.instance();
	_action_bar_profile->set_owner(this);

	_input_profile.instance();

	_character_class_name = class_name;
	_class_id = class_id;
	_level = level;
	_xp = xp;
	_actionbar_locked = true;
}

ClassProfile::~ClassProfile() {
	_input_profile.unref();
	_action_bar_profile.unref();

	_custom_data.clear();
}

void ClassProfile::load_defaults() {
	_action_bar_profile->load_defaults();

	emit_change();
}

void ClassProfile::_bind_methods() {
	ADD_SIGNAL(MethodInfo("changed"));

	ClassDB::bind_method(D_METHOD("get_class_id"), &ClassProfile::get_class_id);
	ClassDB::bind_method(D_METHOD("set_class_id", "value"), &ClassProfile::set_class_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "class_id"), "set_class_id", "get_class_id");

	ClassDB::bind_method(D_METHOD("get_character_class_name"), &ClassProfile::get_character_class_name);
	ClassDB::bind_method(D_METHOD("set_character_class_name", "value"), &ClassProfile::set_character_class_name);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "character_class_name"), "set_character_class_name", "get_character_class_name");

	ClassDB::bind_method(D_METHOD("get_level"), &ClassProfile::get_level);
	ClassDB::bind_method(D_METHOD("set_level", "value"), &ClassProfile::set_level);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "level"), "set_level", "get_level");

	ClassDB::bind_method(D_METHOD("get_xp"), &ClassProfile::get_xp);
	ClassDB::bind_method(D_METHOD("set_xp", "value"), &ClassProfile::set_xp);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "xp"), "set_xp", "get_xp");

	ClassDB::bind_method(D_METHOD("get_actionbar_locked"), &ClassProfile::get_actionbar_locked);
	ClassDB::bind_method(D_METHOD("set_actionbar_locked", "value"), &ClassProfile::set_actionbar_locked);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "actionbar_locked"), "set_actionbar_locked", "get_actionbar_locked");

	ClassDB::bind_method(D_METHOD("has_custom_data", "name"), &ClassProfile::has_custom_data);
	ClassDB::bind_method(D_METHOD("set_custom_data", "name", "value"), &ClassProfile::set_custom_data);
	ClassDB::bind_method(D_METHOD("remove_custom_data", "name"), &ClassProfile::remove_custom_data);
	ClassDB::bind_method(D_METHOD("get_custom_data", "name"), &ClassProfile::get_custom_data);

	ClassDB::bind_method(D_METHOD("get_input_profile"), &ClassProfile::get_input_profile);
	ClassDB::bind_method(D_METHOD("get_action_bar_profile"), &ClassProfile::get_action_bar_profile);

	ClassDB::bind_method(D_METHOD("from_dict", "dict"), &ClassProfile::from_dict);
	ClassDB::bind_method(D_METHOD("to_dict"), &ClassProfile::to_dict);
}
