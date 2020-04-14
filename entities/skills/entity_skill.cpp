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

#include "entity_skill.h"

#include "../../database/ess_resource_db.h"
#include "../../singletons/entity_data_manager.h"

Ref<EntitySkillData> EntitySkill::get_skill() {
	return _skill;
}
void EntitySkill::set_skill(Ref<EntitySkillData> value) {
	_skill = value;

	if (_skill.is_valid())
		_skill_id = _skill->get_id();
	else
		_skill_id = 0;

	emit_signal("skill_changed", Ref<EntitySkill>(this));
}

int EntitySkill::get_skill_id() {
	return _skill_id;
}
void EntitySkill::set_skill_id(int value) {
	_skill_id = value;

	if (EntityDataManager::get_instance() != NULL) {
		_skill = EntityDataManager::get_instance()->get_resource_db()->get_entity_skill(_skill_id);
	}

	emit_signal("skill_changed", Ref<EntitySkill>(this));
}

int EntitySkill::get_current() {
	return _current;
}
void EntitySkill::set_current(int value) {
	_current = value;

	emit_signal("current_changed", Ref<EntitySkill>(this));
}

int EntitySkill::get_max() {
	return _max;
}
void EntitySkill::set_max(int value) {
	_max = value;

	emit_signal("max_changed", Ref<EntitySkill>(this));
}

bool EntitySkill::get_disabled() {
	return _disabled;
}
void EntitySkill::set_disabled(bool value) {
	_disabled = value;

	emit_signal("skill_changed", Ref<EntitySkill>(this));
}

Dictionary EntitySkill::to_dict() {
	return call("_to_dict");
}
void EntitySkill::from_dict(const Dictionary &dict) {
	call("_from_dict", dict);
}

Dictionary EntitySkill::_to_dict() {
	Dictionary dict;

	dict["skill_id"] = _skill_id;
	dict["current"] = _current;
	dict["max"] = _max;
	dict["disabled"] = _disabled;

	return dict;
}
void EntitySkill::_from_dict(const Dictionary &dict) {
	ERR_FAIL_COND(dict.empty());

	_skill_id = dict.get("skill_id", 0);
	_current = dict.get("current", 0);
	_max = dict.get("max", 0);
	_disabled = dict.get("disabled", true);
}

EntitySkill::EntitySkill() {
	_skill_id = 0;
	_current = 0;
	_max = 0;
	_disabled = false;
}

EntitySkill::~EntitySkill() {
	_skill.unref();
}

void EntitySkill::_bind_methods() {
	ADD_SIGNAL(MethodInfo("skill_changed", PropertyInfo(Variant::OBJECT, "skill", PROPERTY_HINT_RESOURCE_TYPE, "EntitySkill")));
	ADD_SIGNAL(MethodInfo("current_changed", PropertyInfo(Variant::OBJECT, "skill", PROPERTY_HINT_RESOURCE_TYPE, "EntitySkill")));
	ADD_SIGNAL(MethodInfo("max_changed", PropertyInfo(Variant::OBJECT, "skill", PROPERTY_HINT_RESOURCE_TYPE, "EntitySkill")));

	ClassDB::bind_method(D_METHOD("get_skill"), &EntitySkill::get_skill);
	ClassDB::bind_method(D_METHOD("set_skill", "value"), &EntitySkill::set_skill);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "skill", PROPERTY_HINT_RESOURCE_TYPE, "EntitySkillData"), "set_skill", "get_skill");

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

	//Serialization
	BIND_VMETHOD(MethodInfo("_from_dict", PropertyInfo(Variant::DICTIONARY, "dict")));
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::DICTIONARY, "dict"), "_to_dict"));

	ClassDB::bind_method(D_METHOD("from_dict", "dict"), &EntitySkill::from_dict);
	ClassDB::bind_method(D_METHOD("to_dict"), &EntitySkill::to_dict);

	ClassDB::bind_method(D_METHOD("_from_dict", "dict"), &EntitySkill::_from_dict);
	ClassDB::bind_method(D_METHOD("_to_dict"), &EntitySkill::_to_dict);
}
