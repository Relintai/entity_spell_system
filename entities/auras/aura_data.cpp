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

#include "aura_data.h"

#include "../../data/aura.h"
#include "../../singletons/entity_data_manager.h"
#include "../entity.h"

float AuraData::get_damage_count() {
	return _damage_already_taken;
}

void AuraData::set_damage_count(int damageTaken) {
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

Entity *AuraData::get_caster() {
	return _caster;
}

void AuraData::set_caster(Entity *value) {
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

void AuraData::set_caster_bind(Node *value) {
	if (!value) {
		set_caster(NULL);
		return;
	}

	Entity *e = cast_to<Entity>(value);

	if (!e) {
		return;
	}

	set_caster(e);
}

NodePath AuraData::get_caster_path() {
	return _caster_path;
}
void AuraData::set_caster_path(NodePath value) {
	_caster_path = value;
}

float AuraData::get_spell_scale() {
	return _spell_scale;
}

void AuraData::set_spell_scale(float value) {
	_spell_scale = value;
}

Ref<Aura> AuraData::get_aura() {
	//if (_aura == NULL) {
	//TODO fix!
	//_aura = Auras::getInstance()->GetData(get_aura_id());
	//}

	return _aura;
}

void AuraData::set_aura(Ref<Aura> aura) {
	_aura = aura;
}

int AuraData::get_damage() {
	return _damage;
}

void AuraData::set_damage(int value) {
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

int AuraData::get_damage_taken() {
	return _damage_already_taken;
}

void AuraData::set_damage_taken(int value) {
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

int AuraData::get_heal() {
	return _heal;
}

void AuraData::set_heal(int value) {
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
	ERR_FAIL_COND(!ObjectDB::instance_validate(owner));
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
	ERR_FAIL_COND(dict.empty());

	_aura_id = dict.get("aura_id", 0);
	_remaining_time = dict.get("remaining_time", 0);
	_caster_path = dict.get("caster_path", NodePath());

	_spell_scale = dict.get("spell_scale", 0);

	_aura_group = dict.get("aura_group", 0);
	int aura_id = dict.get("aura_id", 0);

	Ref<Aura> aura = EntityDataManager::get_instance()->get_aura(aura_id);

	if (aura.is_valid()) {
		_aura = aura;
	}

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
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "owner", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), "set_owner", "get_owner");

	ClassDB::bind_method(D_METHOD("get_caster"), &AuraData::get_caster);
	ClassDB::bind_method(D_METHOD("set_caster", "value"), &AuraData::set_caster_bind);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "caster", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), "set_caster", "get_caster");

	ClassDB::bind_method(D_METHOD("get_caster_path"), &AuraData::get_caster_path);
	ClassDB::bind_method(D_METHOD("set_caster_path", "value"), &AuraData::set_caster_path);
	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "caster_path"), "set_caster_path", "get_caster_path");

	ClassDB::bind_method(D_METHOD("get_aura"), &AuraData::get_aura);
	ClassDB::bind_method(D_METHOD("set_aura", "value"), &AuraData::set_aura);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "aura", PROPERTY_HINT_RESOURCE_TYPE, "Aura"), "set_aura", "get_aura");

	ClassDB::bind_method(D_METHOD("refresh", "remaining"), &AuraData::refresh);

	ClassDB::bind_method(D_METHOD("get_damage"), &AuraData::get_damage);
	ClassDB::bind_method(D_METHOD("set_damage", "value"), &AuraData::set_damage);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "damage"), "set_damage", "get_damage");

	ClassDB::bind_method(D_METHOD("get_damage_count"), &AuraData::get_damage_count);
	ClassDB::bind_method(D_METHOD("set_damage_count", "value"), &AuraData::set_damage_count);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "damage_count"), "set_damage_count", "get_damage_count");

	ClassDB::bind_method(D_METHOD("get_tick"), &AuraData::get_tick);
	ClassDB::bind_method(D_METHOD("set_tick", "value"), &AuraData::set_tick);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "tick"), "set_tick", "get_tick");

	ClassDB::bind_method(D_METHOD("get_time_since_last_tick"), &AuraData::get_time_since_last_tick);
	ClassDB::bind_method(D_METHOD("set_time_since_last_tick", "value"), &AuraData::set_time_since_last_tick);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "time_since_last_tick"), "set_time_since_last_tick", "get_time_since_last_tick");

	ClassDB::bind_method(D_METHOD("get_unhandled_ticks"), &AuraData::get_unhandled_ticks);
	ClassDB::bind_method(D_METHOD("set_unhandled_ticks", "value"), &AuraData::set_unhandled_ticks);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "unhandled_ticks"), "set_unhandled_ticks", "get_unhandled_ticks");

	ClassDB::bind_method(D_METHOD("get_damage_taken"), &AuraData::get_damage_taken);
	ClassDB::bind_method(D_METHOD("set_damage_taken", "value"), &AuraData::set_damage_taken);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "damage_taken"), "set_damage_taken", "get_damage_taken");

	ClassDB::bind_method(D_METHOD("get_heal"), &AuraData::get_heal);
	ClassDB::bind_method(D_METHOD("set_heal", "value"), &AuraData::set_heal);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "heal"), "set_heal", "get_heal");

	ClassDB::bind_method(D_METHOD("get_remaining_absorb"), &AuraData::get_remaining_absorb);
	ClassDB::bind_method(D_METHOD("set_remaining_absorb", "value"), &AuraData::set_remaining_absorb);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "remaining_absorb"), "set_heal", "get_remaining_absorb");

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
