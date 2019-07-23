#include "spell_cast_info.h"

#include "../data/spell.h"

////    SpellCastInfo    ////

Entity *SpellCastInfo::get_caster() const {
	return _caster;
}

void SpellCastInfo::set_caster(Node *caster) {
	if (!caster) {
		return;
	}

	Entity *e = cast_to<Entity>(caster);

	if (!e) {
		return;
	}

	_caster = e;
}

Entity *SpellCastInfo::get_target() const {
	return _target;
}

void SpellCastInfo::set_target(Node *target) {
	if (!target) {
		return;
	}

	Entity *e = cast_to<Entity>(target);

	if (!e) {
		return;
	}

	_target = e;
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

SpellCastInfo::SpellCastInfo() {
	_caster = NULL;
	_target = NULL;

	_has_cast_time = false;
	_cast_time = 0;
	_spell_scale = 0;

	_current_cast_time = 0;
	_num_pushbacks = 0;

	_is_casting = false;
}

SpellCastInfo::~SpellCastInfo() {
	_caster = NULL;
	_target = NULL;
	//_spell = Ref<Spell>(NULL);
}

void SpellCastInfo::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_caster"), &SpellCastInfo::get_caster);
	ClassDB::bind_method(D_METHOD("set_caster", "caster"), &SpellCastInfo::set_caster);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "caster", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), "set_caster", "get_caster");

	ClassDB::bind_method(D_METHOD("get_target"), &SpellCastInfo::get_target);
	ClassDB::bind_method(D_METHOD("set_target", "caster"), &SpellCastInfo::set_target);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "target", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), "set_target", "get_target");

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
}
