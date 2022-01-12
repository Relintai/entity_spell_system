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

#include "aura_data.h"

#include "core/version.h"

#include "../../data/spells/spell.h"
#include "../../database/ess_resource_db.h"
#include "../../singletons/ess.h"
#include "../entity.h"

#include "../../defines.h"

float AuraData::damage_get_count() {
	return _damage_already_taken;
}

void AuraData::damage_set_count(int damageTaken) {
	_damage_already_taken = damageTaken;
}

int AuraData::get_aura_id() {
	return _aura_id;
}

void AuraData::set_aura_id(int value) {
	_aura_id = value;
}

bool AuraData::get_is_timed() {
	return _is_timed;
}
void AuraData::set_is_timed(bool value) {
	_is_timed = value;
}

float AuraData::get_remaining_time() {
	return _remaining_time;
}

void AuraData::set_remaining_time(float value) {
	_remaining_time = value;
}

bool AuraData::update(float delta) {
	if (_tick > 0.01) {
		_time_since_last_tick += delta;

		while (_time_since_last_tick >= _tick) {
			_time_since_last_tick -= _tick;
			++_unhandled_ticks;
		}
	}

	if (_is_timed) {
		_remaining_time -= delta;

		if (_remaining_time <= 0) {
			_remaining_time = 0;
			return true;
		}
	}

	return false;
}

Entity *AuraData::get_owner() {
	return _owner;
}
void AuraData::set_owner(Entity *value) {
	_owner = value;
}
void AuraData::set_owner_bind(Node *value) {
	if (!value) {
		return;
	}

	Entity *e = cast_to<Entity>(value);

	if (!e) {
		return;
	}

	_owner = e;
}

Entity *AuraData::caster_get() {
	return _caster;
}

void AuraData::caster_set(Entity *value) {
	_caster = value;

	if (_caster == _owner) {
		_caster_path = NodePath(".");
		return;
	}

	if (!value) {
		_caster_path = NodePath();
		return;
	}

	if (_caster->is_inside_tree()) {
		_caster_path = _caster->get_path();
	}
}

void AuraData::caster_set_bind(Node *value) {
	if (!value) {
		caster_set(NULL);
		return;
	}

	Entity *e = cast_to<Entity>(value);

	if (!e) {
		return;
	}

	caster_set(e);
}

NodePath AuraData::caster_get_path() {
	return _caster_path;
}
void AuraData::caster_set_path(NodePath value) {
	_caster_path = value;
}

float AuraData::spell_scale_get() {
	return _spell_scale;
}

void AuraData::spell_scale_set(float value) {
	_spell_scale = value;
}

Ref<Spell> AuraData::get_aura() {
	//if (_aura == NULL) {
	//TODO fix!
	//_aura = Auras::getInstance()->GetData(get_aura_id());
	//}

	return _aura;
}

void AuraData::set_aura(Ref<Spell> aura) {
	_aura = aura;

	if (aura.is_valid())
		_aura_path = aura->get_path();
	else
		_aura_path = "";
}

int AuraData::damage_get() {
	return _damage;
}

void AuraData::damage_set(int value) {
	_damage = value;
}

float AuraData::get_tick() {
	return _tick;
}

void AuraData::set_tick(float value) {
	_tick = value;
}

float AuraData::get_time_since_last_tick() {
	return _time_since_last_tick;
}

void AuraData::set_time_since_last_tick(float value) {
	_time_since_last_tick = value;
}

int AuraData::get_unhandled_ticks() {
	return _unhandled_ticks;
}

void AuraData::set_unhandled_ticks(int value) {
	_unhandled_ticks = value;
}

int AuraData::damage_get_taken() {
	return _damage_already_taken;
}

void AuraData::damage_set_taken(int value) {
	_damage_already_taken = value;
}

void AuraData::refresh(float remaining_time) {
	_remaining_time = remaining_time;
	_damage_already_taken = 0;
	_time_since_last_tick = (float)0;

	//_diminishing_level_count += 1;
}

/*
void AuraData::refresh(float remaining_time) {
	_diminishing_level_count += 1;
}


void AuraData::refresh(float remaining_time) {
	_damage_already_taken = 0;
}

void AuraData::refresh(float remaining_time) {
	_remaining_time = _remaining_time;
	_time_since_last_tick = (float)0;
}


void AuraData::refresh(float remaining_time) {
	_time_since_last_tick = (float)0;
}*/

int AuraData::heal_get() {
	return _heal;
}

void AuraData::heal_set(int value) {
	_heal = value;
}

int AuraData::get_remaining_absorb() {
	return _remaining_absorb;
}

void AuraData::set_remaining_absorb(int value) {
	_remaining_absorb = value;
}

float AuraData::get_slow() {
	return _slow;
}

void AuraData::set_slow(float value) {
	_slow = value;
}

void AuraData::resolve_references(Node *owner) {
	ERR_FAIL_COND(!INSTANCE_VALIDATE(owner));

	ERR_FAIL_COND(!owner->is_inside_tree());

	_owner = Object::cast_to<Entity>(owner);

	if (owner->is_inside_tree()) {
		_caster = Object::cast_to<Entity>(owner->get_node_or_null(_caster_path));
	}
}
Dictionary AuraData::to_dict() {
	return call("_to_dict");
}
void AuraData::from_dict(const Dictionary &dict) {
	call("_from_dict", dict);
}
Dictionary AuraData::_to_dict() {
	Dictionary dict;

	dict["aura_id"] = _aura_id;
	dict["aura_path"] = _aura_path;
	dict["remaining_time"] = _remaining_time;
	dict["caster_path"] = _caster_path;

	dict["spell_scale"] = _spell_scale;
	dict["aura_group"] = _aura_group;
	dict["aura_id"] = _aura->get_id();

	dict["is_timed"] = _is_timed;
	dict["damage"] = _damage;
	dict["heal"] = _heal;
	dict["slow"] = _slow;
	dict["remaining_absorb"] = _remaining_absorb;
	dict["tick"] = _tick;
	dict["time_since_last_tick"] = _time_since_last_tick;
	dict["damage_already_taken"] = _damage_already_taken;
	dict["unhandled_ticks"] = _unhandled_ticks;

	return dict;
}
void AuraData::_from_dict(const Dictionary &dict) {
#if VERSION_MAJOR > 3
	ERR_FAIL_COND(dict.is_empty());
#else
	ERR_FAIL_COND(dict.empty());
#endif
	ERR_FAIL_COND(!ESS::get_singleton()->get_resource_db().is_valid());

	_aura_id = dict.get("aura_id", 0);
	_aura_path = dict.get("aura_path", "");
	_remaining_time = dict.get("remaining_time", 0);
	_caster_path = dict.get("caster_path", NodePath());

	_spell_scale = dict.get("spell_scale", 0);

	_aura_group = dict.get("aura_group", 0);
	//int aura_id = dict.get("aura_id", 0);

	_aura = ESS::get_singleton()->get_resource_db()->get_spell_path(_aura_path);

	_is_timed = dict.get("is_timed", true);
	_damage = dict.get("damage", 0);
	_heal = dict.get("heal", 0);
	_slow = dict.get("slow", 0);
	_remaining_absorb = dict.get("remaining_absorb", 0);

	_tick = dict.get("tick", 0);
	_time_since_last_tick = dict.get("time_since_last_tick", 0);
	_damage_already_taken = dict.get("damage_already_taken", 0);
	_unhandled_ticks = dict.get("unhandled_ticks", 0);
}

Array AuraData::to_send_array() {
	return call("_to_send_array");
}
void AuraData::from_send_array(const Array &arr) {
	call("_from_send_array", arr);
}
Array AuraData::_to_send_array() {
	Array arr;

	arr.append(_aura_id);
	arr.append(_remaining_time);

	return arr;
}
void AuraData::_from_send_array(const Array &arr) {
	ERR_FAIL_COND(arr.size() < 2);

	_aura_id = arr.get(0);
	_remaining_time = arr.get(1);
}

AuraData::AuraData() {
	_owner = NULL;
	_aura_id = 0;
	_remaining_time = 0;
	_caster = NULL;
	_spell_scale = 0;
	_aura_group = 0;

	_is_timed = false;
	_damage = 0;
	_heal = 0;
	_slow = 0;
	_remaining_absorb = 0;
	_tick = 0;
	_time_since_last_tick = 0;
	_damage_already_taken = 0;
	_unhandled_ticks = 0;
}

void AuraData::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_aura_id"), &AuraData::get_aura_id);
	ClassDB::bind_method(D_METHOD("set_aura_id", "value"), &AuraData::set_aura_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "aura_id"), "set_aura_id", "get_aura_id");

	ClassDB::bind_method(D_METHOD("get_is_timed"), &AuraData::get_is_timed);
	ClassDB::bind_method(D_METHOD("set_is_timed", "value"), &AuraData::set_is_timed);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_timed"), "set_is_timed", "get_is_timed");

	ClassDB::bind_method(D_METHOD("get_remaining_time"), &AuraData::get_remaining_time);
	ClassDB::bind_method(D_METHOD("set_remaining_time", "value"), &AuraData::set_remaining_time);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "remaining_time"), "set_remaining_time", "get_remaining_time");

	ClassDB::bind_method(D_METHOD("get_owner"), &AuraData::get_owner);
	ClassDB::bind_method(D_METHOD("set_owner", "value"), &AuraData::set_owner_bind);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "owner", PROPERTY_HINT_RESOURCE_TYPE, "Entity", 0), "set_owner", "get_owner");

	ClassDB::bind_method(D_METHOD("caster_get"), &AuraData::caster_get);
	ClassDB::bind_method(D_METHOD("caster_set", "value"), &AuraData::caster_set_bind);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "caster", PROPERTY_HINT_RESOURCE_TYPE, "Entity", 0), "caster_set", "caster_get");

	ClassDB::bind_method(D_METHOD("caster_get_path"), &AuraData::caster_get_path);
	ClassDB::bind_method(D_METHOD("caster_set_path", "value"), &AuraData::caster_set_path);
	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "caster_path"), "caster_set_path", "caster_get_path");

	ClassDB::bind_method(D_METHOD("get_aura"), &AuraData::get_aura);
	ClassDB::bind_method(D_METHOD("set_aura", "value"), &AuraData::set_aura);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "aura", PROPERTY_HINT_RESOURCE_TYPE, "Aura"), "set_aura", "get_aura");

	ClassDB::bind_method(D_METHOD("refresh", "remaining"), &AuraData::refresh);

	ClassDB::bind_method(D_METHOD("damage_get"), &AuraData::damage_get);
	ClassDB::bind_method(D_METHOD("damage_set", "value"), &AuraData::damage_set);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "damage"), "damage_set", "damage_get");

	ClassDB::bind_method(D_METHOD("damage_get_count"), &AuraData::damage_get_count);
	ClassDB::bind_method(D_METHOD("damage_set_count", "value"), &AuraData::damage_set_count);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "damage_count"), "damage_set_count", "damage_get_count");

	ClassDB::bind_method(D_METHOD("get_tick"), &AuraData::get_tick);
	ClassDB::bind_method(D_METHOD("set_tick", "value"), &AuraData::set_tick);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "tick"), "set_tick", "get_tick");

	ClassDB::bind_method(D_METHOD("get_time_since_last_tick"), &AuraData::get_time_since_last_tick);
	ClassDB::bind_method(D_METHOD("set_time_since_last_tick", "value"), &AuraData::set_time_since_last_tick);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "time_since_last_tick"), "set_time_since_last_tick", "get_time_since_last_tick");

	ClassDB::bind_method(D_METHOD("get_unhandled_ticks"), &AuraData::get_unhandled_ticks);
	ClassDB::bind_method(D_METHOD("set_unhandled_ticks", "value"), &AuraData::set_unhandled_ticks);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "unhandled_ticks"), "set_unhandled_ticks", "get_unhandled_ticks");

	ClassDB::bind_method(D_METHOD("damage_get_taken"), &AuraData::damage_get_taken);
	ClassDB::bind_method(D_METHOD("damage_set_taken", "value"), &AuraData::damage_set_taken);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "damage_taken"), "damage_set_taken", "damage_get_taken");

	ClassDB::bind_method(D_METHOD("heal_get"), &AuraData::heal_get);
	ClassDB::bind_method(D_METHOD("heal_set", "value"), &AuraData::heal_set);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "heal"), "heal_set", "heal_get");

	ClassDB::bind_method(D_METHOD("get_remaining_absorb"), &AuraData::get_remaining_absorb);
	ClassDB::bind_method(D_METHOD("set_remaining_absorb", "value"), &AuraData::set_remaining_absorb);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "remaining_absorb"), "heal_set", "get_remaining_absorb");

	ClassDB::bind_method(D_METHOD("get_slow"), &AuraData::get_slow);
	ClassDB::bind_method(D_METHOD("set_slow", "value"), &AuraData::set_slow);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "slow"), "set_slow", "get_slow");

	//Serialization
	BIND_VMETHOD(MethodInfo("_from_dict", PropertyInfo(Variant::DICTIONARY, "dict")));
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::DICTIONARY, "dict"), "_to_dict"));

	ClassDB::bind_method(D_METHOD("from_dict", "dict"), &AuraData::from_dict);
	ClassDB::bind_method(D_METHOD("to_dict"), &AuraData::to_dict);
	ClassDB::bind_method(D_METHOD("_from_dict", "dict"), &AuraData::_from_dict);
	ClassDB::bind_method(D_METHOD("_to_dict"), &AuraData::_to_dict);

	//Networking
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::ARRAY, "arr"), "_to_send_array"));
	BIND_VMETHOD(MethodInfo("_from_send_array", PropertyInfo(Variant::ARRAY, "arr")));

	ClassDB::bind_method(D_METHOD("to_send_array"), &AuraData::to_send_array);
	ClassDB::bind_method(D_METHOD("from_send_array", "arr"), &AuraData::from_send_array);

	ClassDB::bind_method(D_METHOD("_to_send_array"), &AuraData::_to_send_array);
	ClassDB::bind_method(D_METHOD("_from_send_array", "arr"), &AuraData::_from_send_array);
}
