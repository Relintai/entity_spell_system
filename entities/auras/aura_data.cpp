#include "aura_data.h"

#include "../../data/aura.h"
#include "../entity.h"

AuraData::AuraData() {
	_owner = NULL;
	_aura_id = 0;
	_remaining_time = 0;
	_caster = NULL;
	_caster_guid = 0;
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
}

void AuraData::set_caster_bind(Node *value) {
	if (!value) {
		return;
	}

	Entity *e = cast_to<Entity>(value);

	if (!e) {
		return;
	}

	_caster = e;
}

int AuraData::get_caster_guid() {
	return _caster_guid;
}

void AuraData::set_caster_guid(int value) {
	_caster_guid = value;
}

float AuraData::get_spell_scale() {
	return _spell_scale;
}

void AuraData::set_spell_scale(float value) {
	_spell_scale = value;
}

Ref<Aura> AuraData::get_aura() {
	if (_aura == NULL) {
		//TODO fix!
		//_aura = Auras::getInstance()->GetData(get_aura_id());
	}

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

	ClassDB::bind_method(D_METHOD("get_caster_guid"), &AuraData::get_caster_guid);
	ClassDB::bind_method(D_METHOD("set_caster_guid", "value"), &AuraData::set_caster_guid);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "caster_guid"), "set_caster_guid", "get_caster_guid");

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
}
