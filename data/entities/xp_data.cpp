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

int XPData::get_character_max_level() {
	return EntityEnums::MAX_CHARACTER_LEVEL;
}

int XPData::get_character_xp(int level) {
	ERR_FAIL_INDEX_V(level - 1, EntityEnums::MAX_CHARACTER_LEVEL, 9999999);

	return _character_xps.get(level - 1);
}

void XPData::set_character_xp(int level, int value) {
	ERR_FAIL_INDEX(level - 1, EntityEnums::MAX_CHARACTER_LEVEL);

	_character_xps.set(level - 1, value);
}

bool XPData::can_character_level_up(int level) {
	return level < EntityEnums::MAX_CHARACTER_LEVEL;
}

int XPData::get_class_max_level() {
	return EntityEnums::MAX_CLASS_LEVEL;
}

int XPData::get_class_xp(int level) {
	ERR_FAIL_INDEX_V(level - 1, EntityEnums::MAX_CLASS_LEVEL, 9999999);

	return _class_xps.get(level - 1);
}

void XPData::set_class_xp(int level, int value) {
	ERR_FAIL_INDEX(level - 1, EntityEnums::MAX_CLASS_LEVEL);

	_class_xps.set(level - 1, value);
}

bool XPData::can_class_level_up(int level) {
	return level < EntityEnums::MAX_CLASS_LEVEL;
}

XPData::XPData() {
	_character_xps.resize(EntityEnums::MAX_CHARACTER_LEVEL);

	for (int i = 0; i < _character_xps.size(); ++i) {
		_character_xps.set(i, 0);
	}

	_class_xps.resize(EntityEnums::MAX_CLASS_LEVEL);

	for (int i = 0; i < _class_xps.size(); ++i) {
		_class_xps.set(i, 0);
	}
}

XPData::~XPData() {
}

void XPData::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_character_max_level"), &XPData::get_character_max_level);
	ClassDB::bind_method(D_METHOD("get_character_xp", "level"), &XPData::get_character_xp);
	ClassDB::bind_method(D_METHOD("set_character_xp", "level", "value"), &XPData::set_character_xp);
	ClassDB::bind_method(D_METHOD("can_character_level_up", "level"), &XPData::can_character_level_up);

	ADD_GROUP("Character Level", "character_level_");
	for (int i = 1; i <= EntityEnums::MAX_CHARACTER_LEVEL; ++i) {
		ADD_PROPERTYI(PropertyInfo(Variant::INT, "character_level_" + String::num(i)), "set_character_xp", "get_character_xp", i);
	}

	ClassDB::bind_method(D_METHOD("get_class_max_level"), &XPData::get_class_max_level);
	ClassDB::bind_method(D_METHOD("get_class_xp", "level"), &XPData::get_class_xp);
	ClassDB::bind_method(D_METHOD("set_class_xp", "level", "value"), &XPData::set_class_xp);
	ClassDB::bind_method(D_METHOD("can_class_level_up", "level"), &XPData::can_class_level_up);

	ADD_GROUP("Class Level", "class_level_");
	for (int i = 1; i <= EntityEnums::MAX_CLASS_LEVEL; ++i) {
		ADD_PROPERTYI(PropertyInfo(Variant::INT, "class_level_" + String::num(i)), "set_class_xp", "get_class_xp", i);
	}
}
