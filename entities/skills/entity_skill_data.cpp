#include "entity_skill_data.h"

int EntitySkillData::get_id() {
	return _id;
}
void EntitySkillData::set_id(int value) {
	_id = value;
}

int EntitySkillData::get_default_value() {
	return _default_value;
}
void EntitySkillData::set_default_value(int value) {
	_default_value = value;
}

int EntitySkillData::get_max_value() {
	return _max_value;
}
void EntitySkillData::set_max_value(int value) {
	_max_value = value;
}

String EntitySkillData::get_text_description() {
	return _text_description;
}
void EntitySkillData::set_text_description(String value) {
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
