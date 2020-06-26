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

#include "xp_data.h"

#include "../../entity_enums.h"

#include "../../singletons/ess.h"

int XPData::get_character_max_level() {
	return ESS::get_singleton()->get_max_character_level();
}

int XPData::get_character_xp(int level) {
	ERR_FAIL_INDEX_V(level - 1, ESS::get_singleton()->get_max_character_level(), 9999999);

	return _character_xps.get(level - 1);
}

void XPData::set_character_xp(int level, int value) {
	ERR_FAIL_INDEX(level - 1, ESS::get_singleton()->get_max_character_level());

	_character_xps.set(level - 1, value);
}

bool XPData::can_character_level_up(int level) {
	return level < ESS::get_singleton()->get_max_character_level();
}

int XPData::get_class_max_level() {
	return ESS::get_singleton()->get_max_class_level();
}

int XPData::get_class_xp(int level) {
	ERR_FAIL_INDEX_V(level - 1, ESS::get_singleton()->get_max_class_level(), 9999999);

	return _class_xps.get(level - 1);
}

void XPData::set_class_xp(int level, int value) {
	ERR_FAIL_INDEX(level - 1, ESS::get_singleton()->get_max_class_level());

	_class_xps.set(level - 1, value);
}

bool XPData::can_class_level_up(int level) {
	return level < ESS::get_singleton()->get_max_class_level();
}

XPData::XPData() {
	_character_xps.resize(ESS::get_singleton()->get_max_character_level());

	for (int i = 0; i < _character_xps.size(); ++i) {
		_character_xps.set(i, 0);
	}

	_class_xps.resize(ESS::get_singleton()->get_max_class_level());

	for (int i = 0; i < _class_xps.size(); ++i) {
		_class_xps.set(i, 0);
	}
}

XPData::~XPData() {
}

bool XPData::_set(const StringName &p_name, const Variant &p_value) {
	String prop_name = p_name;

	if (prop_name.begins_with("character_level")) {
		int level = prop_name.get_slice("/", 1).to_int();

		if (level >= ESS::get_singleton()->get_max_character_level())
			return false;

		_character_xps.write[level] = p_value;

		return true;
	} else if (prop_name.begins_with("class_level")) {
		int level = prop_name.get_slice("/", 1).to_int();

		if (level >= ESS::get_singleton()->get_max_class_level())
			return false;

		_class_xps.write[level] = p_value;

		return true;
	}

	return false;
}

bool XPData::_get(const StringName &p_name, Variant &r_ret) const {
	String prop_name = p_name;

	if (prop_name.begins_with("character_level")) {
		int level = prop_name.get_slice("/", 1).to_int();

		if (level >= ESS::get_singleton()->get_max_character_level())
			return false;

		r_ret = _character_xps[level];

		return true;
	} else if (prop_name.begins_with("class_level")) {
		int level = prop_name.get_slice("/", 1).to_int();

		if (level >= ESS::get_singleton()->get_max_class_level())
			return false;

		r_ret = _class_xps[level];

		return true;
	}

	return false;
}

void XPData::_get_property_list(List<PropertyInfo> *p_list) const {
	//int property_usange = PROPERTY_USAGE_STORAGE | PROPERTY_USAGE_INTERNAL;
	//int property_usange = PROPERTY_USAGE_DEFAULT;

	for (int i = 1; i <= ESS::get_singleton()->get_max_character_level(); ++i) {
		p_list->push_back(PropertyInfo(Variant::INT, "character_level/" + String::num(i)));
	}

	for (int i = 1; i <= ESS::get_singleton()->get_max_class_level(); ++i) {
		p_list->push_back(PropertyInfo(Variant::INT, "class_level/" + String::num(i)));
	}
}

void XPData::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_character_max_level"), &XPData::get_character_max_level);
	ClassDB::bind_method(D_METHOD("get_character_xp", "level"), &XPData::get_character_xp);
	ClassDB::bind_method(D_METHOD("set_character_xp", "level", "value"), &XPData::set_character_xp);
	ClassDB::bind_method(D_METHOD("can_character_level_up", "level"), &XPData::can_character_level_up);

	ClassDB::bind_method(D_METHOD("get_class_max_level"), &XPData::get_class_max_level);
	ClassDB::bind_method(D_METHOD("get_class_xp", "level"), &XPData::get_class_xp);
	ClassDB::bind_method(D_METHOD("set_class_xp", "level", "value"), &XPData::set_class_xp);
	ClassDB::bind_method(D_METHOD("can_class_level_up", "level"), &XPData::can_class_level_up);
}
