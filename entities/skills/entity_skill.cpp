#include "entity_skill.h"

int EntitySkill::get_skill_id() {
	return _skill_id;
}
void EntitySkill::set_skill_id(int value) {
	_skill_id = value;
}

int EntitySkill::get_current() {
	return _current;
}
void EntitySkill::set_current(int value) {
	_current = value;
}

int EntitySkill::get_max() {
	return _max;
}
void EntitySkill::set_max(int value) {
	_max = value;
}

bool EntitySkill::get_disabled() {
	return _disabled;
}
void EntitySkill::set_disabled(bool value) {
	_disabled = value;
}

EntitySkill::EntitySkill() {
	_skill_id = 0;
	_current = 0;
	_max = 0;
	_disabled = false;
}

void EntitySkill::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_skill_id"), &EntitySkill::get_skill_id);
	ClassDB::bind_method(D_METHOD("set_skill_id", "value"), &EntitySkill::set_skill_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "skill_id"), "set_skill_id", "get_skill_id");

	ClassDB::bind_method(D_METHOD("get_current"), &EntitySkill::get_current);
	ClassDB::bind_method(D_METHOD("set_current", "value"), &EntitySkill::set_current);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "current"), "set_current", "get_current");

	ClassDB::bind_method(D_METHOD("get_max"), &EntitySkill::get_max);
	ClassDB::bind_method(D_METHOD("set_max", "value"), &EntitySkill::set_max);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "max"), "set_max", "get_max");

	ClassDB::bind_method(D_METHOD("get_disabled"), &EntitySkill::get_disabled);
	ClassDB::bind_method(D_METHOD("set_disabled", "value"), &EntitySkill::set_disabled);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "disabled"), "set_disabled", "get_disabled");
}
