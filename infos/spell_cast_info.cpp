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

#include "spell_cast_info.h"

#include "../data/spells/spell.h"
#include "../entities/entity.h"
#include "../world_spells/world_spell.h"
#include "../singletons/entity_data_manager.h"

////    SpellCastInfo    ////

Entity *SpellCastInfo::get_caster() {
	if (_caster && !ObjectDB::instance_validate(_caster)) {
		_caster = NULL;
	}

	return _caster;
}
void SpellCastInfo::set_caster(Entity *value) {
	_caster = value;
}
void SpellCastInfo::set_caster_bind(Node *caster) {
	if (!caster) {
		return;
	}

	Entity *e = cast_to<Entity>(caster);

	if (!e) {
		return;
	}

	_caster = e;
}

Entity *SpellCastInfo::get_target() {
	if (_target && !ObjectDB::instance_validate(_target)) {
		_target = NULL;
	}

	return _target;
}
void SpellCastInfo::set_target(Entity *value) {
	_target = value;
}
void SpellCastInfo::set_target_bind(Node *target) {
	if (!target) {
		return;
	}

	Entity *e = cast_to<Entity>(target);

	if (!e) {
		return;
	}

	_target = e;
}

WorldSpell *SpellCastInfo::get_world_spell() {
	if (_world_spell && !ObjectDB::instance_validate(_world_spell)) {
		_world_spell = NULL;
	}

	return _world_spell;
}
void SpellCastInfo::set_world_spell(WorldSpell *world_spell) {
	_world_spell = world_spell;
}
void SpellCastInfo::set_world_spell_bind(Node *world_spell) {
	if (!world_spell) {
		return;
	}

	WorldSpell *w = cast_to<WorldSpell>(world_spell);

	if (!ObjectDB::instance_validate(w)) {
		return;
	}

	_world_spell = w;
}

bool SpellCastInfo::get_has_cast_time() const {
	return _has_cast_time;
}
void SpellCastInfo::set_has_cast_time(bool value) {
	_has_cast_time = value;
}

float SpellCastInfo::get_cast_time() const {
	return _cast_time;
}
void SpellCastInfo::set_cast_time(float value) {
	_cast_time = value;
}

float SpellCastInfo::get_current_cast_time() const {
	return _current_cast_time;
}
void SpellCastInfo::set_current_cast_time(float value) {
	_current_cast_time = value;
}

bool SpellCastInfo::get_is_casting() const {
	return _is_casting;
}
void SpellCastInfo::set_is_casting(bool value) {
	_is_casting = value;
}

int SpellCastInfo::get_num_pushbacks() const {
	return _num_pushbacks;
}
void SpellCastInfo::set_num_pushbacks(int value) {
	_num_pushbacks = value;
}

float SpellCastInfo::get_spell_scale() const {
	return _spell_scale;
}
void SpellCastInfo::set_spell_scale(float value) {
	_spell_scale = value;
}

Ref<Spell> SpellCastInfo::get_spell() const {
	return _spell;
}
void SpellCastInfo::set_spell(Ref<Spell> spell) {
	_spell = spell;
}

bool SpellCastInfo::update_cast_time(float delta) {
	_current_cast_time += delta;

	if (_current_cast_time >= _cast_time) {
		_current_cast_time = _cast_time;

		return true;
	}

	return false;
}

void SpellCastInfo::physics_process(float delta) {
	ERR_FAIL_COND(!_spell.is_valid());

	_spell->son_physics_process(Ref<SpellCastInfo>(this), delta);
}

void SpellCastInfo::resolve_references(Node *owner) {
	ERR_FAIL_COND(!ObjectDB::instance_validate(owner));
	ERR_FAIL_COND(!owner->is_inside_tree());

	_caster = Object::cast_to<Entity>(owner);

	if (owner->is_inside_tree()) {
		_target = Object::cast_to<Entity>(owner->get_node_or_null(_target_path));
	}

	Ref<Spell> spell = EntityDataManager::get_instance()->get_spell(_spell_id);

	if (spell.is_valid()) {
		_spell = spell;
	}
}

Dictionary SpellCastInfo::to_dict() {
	Dictionary dict;

	if (ObjectDB::instance_validate(_caster))
		dict["caster"] = _caster->get_path();

	if (ObjectDB::instance_validate(_target))
		dict["target"] = _target->get_path();

	dict["has_cast_time"] = _has_cast_time;
	dict["cast_time"] = _cast_time;

	dict["current_cast_time"] = _current_cast_time;
	dict["num_pushbacks"] = _num_pushbacks;
	dict["is_casting"] = _is_casting;

	dict["spell_id"] = _spell->get_id();

	return dict;
}
void SpellCastInfo::from_dict(const Dictionary &dict) {
	ERR_FAIL_COND(dict.empty());

	_has_cast_time = dict.get("has_cast_time", true);
	_cast_time = dict.get("cast_time", 0);

	_current_cast_time = dict.get("current_cast_time", 0);
	_num_pushbacks = dict.get("num_pushbacks", 0);
	_is_casting = dict.get("is_casting", true);

	_spell_id = dict.get("spell_id", 0);
}

SpellCastInfo::SpellCastInfo() {
	_caster = NULL;
	_target = NULL;
	_world_spell = NULL;

	_has_cast_time = false;
	_cast_time = 0;
	_spell_scale = 0;

	_current_cast_time = 0;
	_num_pushbacks = 0;

	_is_casting = false;

	_spell_id = 0;
}

SpellCastInfo::~SpellCastInfo() {
	_caster = NULL;
	_target = NULL;
	//_spell = Ref<Spell>(NULL);
}

void SpellCastInfo::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_caster"), &SpellCastInfo::get_caster);
	ClassDB::bind_method(D_METHOD("set_caster", "caster"), &SpellCastInfo::set_caster_bind);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "caster", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), "set_caster", "get_caster");

	ClassDB::bind_method(D_METHOD("get_target"), &SpellCastInfo::get_target);
	ClassDB::bind_method(D_METHOD("set_target", "caster"), &SpellCastInfo::set_target_bind);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "target", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), "set_target", "get_target");

	ClassDB::bind_method(D_METHOD("get_world_spell"), &SpellCastInfo::get_world_spell);
	ClassDB::bind_method(D_METHOD("set_world_spell", "world_spell"), &SpellCastInfo::set_world_spell_bind);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "world_spell", PROPERTY_HINT_RESOURCE_TYPE, "WorldSpell"), "set_world_spell", "get_world_spell");

	ClassDB::bind_method(D_METHOD("get_has_cast_time"), &SpellCastInfo::get_has_cast_time);
	ClassDB::bind_method(D_METHOD("set_has_cast_time", "value"), &SpellCastInfo::set_has_cast_time);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "has_cast_time"), "set_has_cast_time", "get_has_cast_time");

	ClassDB::bind_method(D_METHOD("get_cast_time"), &SpellCastInfo::get_cast_time);
	ClassDB::bind_method(D_METHOD("set_cast_time", "value"), &SpellCastInfo::set_cast_time);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "cast_time"), "set_cast_time", "get_cast_time");

	ClassDB::bind_method(D_METHOD("get_current_cast_time"), &SpellCastInfo::get_current_cast_time);
	ClassDB::bind_method(D_METHOD("set_current_cast_time", "value"), &SpellCastInfo::set_current_cast_time);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "current_cast_time"), "set_current_cast_time", "get_current_cast_time");

	ClassDB::bind_method(D_METHOD("get_is_casting"), &SpellCastInfo::get_is_casting);
	ClassDB::bind_method(D_METHOD("set_is_casting", "value"), &SpellCastInfo::set_is_casting);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_casting"), "set_is_casting", "get_is_casting");

	ClassDB::bind_method(D_METHOD("get_num_pushbacks"), &SpellCastInfo::get_num_pushbacks);
	ClassDB::bind_method(D_METHOD("set_num_pushbacks", "value"), &SpellCastInfo::set_num_pushbacks);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "num_pushbacks"), "set_num_pushbacks", "get_num_pushbacks");

	ClassDB::bind_method(D_METHOD("get_spell_scale"), &SpellCastInfo::get_spell_scale);
	ClassDB::bind_method(D_METHOD("set_spell_scale", "value"), &SpellCastInfo::set_spell_scale);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "spell_scale"), "set_spell_scale", "get_spell_scale");

	ClassDB::bind_method(D_METHOD("get_spell"), &SpellCastInfo::get_spell);
	ClassDB::bind_method(D_METHOD("set_spell", "spell"), &SpellCastInfo::set_spell);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "spell", PROPERTY_HINT_RESOURCE_TYPE, "Spell"), "set_spell", "get_spell");

	ClassDB::bind_method(D_METHOD("update_cast_time", "delta"), &SpellCastInfo::update_cast_time);

	ClassDB::bind_method(D_METHOD("from_dict", "dict"), &SpellCastInfo::from_dict);
	ClassDB::bind_method(D_METHOD("to_dict"), &SpellCastInfo::to_dict);
}
