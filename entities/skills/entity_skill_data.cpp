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

#include "entity_skill_data.h"

int EntitySkillData::get_id() const {
	return _id;
}
void EntitySkillData::set_id(const int value) {
	_id = value;
}

int EntitySkillData::get_default_value() const {
	return _default_value;
}
void EntitySkillData::set_default_value(const int value) {
	_default_value = value;
}

int EntitySkillData::get_max_value() const {
	return _max_value;
}
void EntitySkillData::set_max_value(const int value) {
	_max_value = value;
}

String EntitySkillData::get_text_description() const {
	return _text_description;
}
void EntitySkillData::set_text_description(const String value) {
	_text_description = value;
}

EntitySkillData::EntitySkillData() {
	_id = 0;
	_default_value = 0;
	_max_value = 0;
}

EntitySkillData::~EntitySkillData() {
}

void EntitySkillData::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_id"), &EntitySkillData::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "value"), &EntitySkillData::set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");

	ClassDB::bind_method(D_METHOD("get_default_value"), &EntitySkillData::get_default_value);
	ClassDB::bind_method(D_METHOD("set_default_value", "value"), &EntitySkillData::set_default_value);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "default_value"), "set_default_value", "get_default_value");

	ClassDB::bind_method(D_METHOD("get_max_value"), &EntitySkillData::get_max_value);
	ClassDB::bind_method(D_METHOD("set_max_value", "value"), &EntitySkillData::set_max_value);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "max_value"), "set_max_value", "get_max_value");

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text_name"), "set_name", "get_name");

	ClassDB::bind_method(D_METHOD("get_text_description"), &EntitySkillData::get_text_description);
	ClassDB::bind_method(D_METHOD("set_text_description", "value"), &EntitySkillData::set_text_description);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text_description", PROPERTY_HINT_MULTILINE_TEXT), "set_text_description", "get_text_description");
}
