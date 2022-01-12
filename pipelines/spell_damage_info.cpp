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

#include "spell_damage_info.h"

#include "core/version.h"

#include "../data/spells/spell.h"
#include "../database/ess_resource_db.h"
#include "../entities/entity.h"
#include "../singletons/ess.h"

#include "../defines.h"

bool SpellDamageInfo::get_immune() const {
	return _crit;
}
void SpellDamageInfo::set_immune(const bool value) {
	_crit = value;
}

int SpellDamageInfo::damage_get() const {
	return _damage;
}
void SpellDamageInfo::damage_set(const int value) {
	_damage = value;
}

bool SpellDamageInfo::crit_get() const {
	return _crit;
}
void SpellDamageInfo::crit_set(const bool value) {
	_crit = value;
}

int SpellDamageInfo::amount_absorbed_get() const {
	return _amount_absorbed;
}
void SpellDamageInfo::amount_absorbed_set(const int value) {
	_amount_absorbed = value;
}

int SpellDamageInfo::damage_type_get() const {
	return _damage_type;
}
void SpellDamageInfo::damage_type_set(const int value) {
	_damage_type = value;
}

Entity *SpellDamageInfo::dealer_get() {
	return _dealer;
}
void SpellDamageInfo::dealer_set(Entity *value) {
	_dealer = value;
}
void SpellDamageInfo::dealer_set_bind(Node *value) {
	if (!value) {
		return;
	}

	Entity *e = cast_to<Entity>(value);

	if (!e) {
		return;
	}

	_dealer = e;
}

Entity *SpellDamageInfo::receiver_get() {
	return _receiver;
}
void SpellDamageInfo::receiver_set(Entity *value) {
	_receiver = value;
}
void SpellDamageInfo::receiver_set_bind(Node *value) {
	if (!value) {
		return;
	}

	Entity *e = cast_to<Entity>(value);

	if (!e) {
		return;
	}

	_receiver = e;
}

Ref<Reference> SpellDamageInfo::source_get() {
	return _damage_source;
}
void SpellDamageInfo::source_set(Ref<Reference> value) {
	_damage_source_type = DAMAGE_SOURCE_UNKNOWN;
	_damage_source = value;
	_damage_source_id = 0;

	if (value->has_method("get_id")) {
		_damage_source_id = value->call("get_id");
	}
}

Ref<Spell> SpellDamageInfo::spell_source_get() {
	return Ref<Spell>(_damage_source);
}

void SpellDamageInfo::spell_source_set(const Ref<Spell> &value) {
	_damage_source_type = DAMAGE_SOURCE_SPELL;
	_damage_source = value;

	if (value.is_valid())
		_damage_source_id = value->get_id();
}

Ref<Spell> SpellDamageInfo::aura_source_get() {
	return Ref<Spell>(_damage_source);
}

void SpellDamageInfo::aura_source_set(const Ref<Spell> &value) {
	_damage_source_type = DAMAGE_SOURCE_AURA;
	_damage_source = value;

	if (value.is_valid())
		_damage_source_id = value->get_id();
}

int SpellDamageInfo::source_get_id() const {
	return _damage_source_id;
}

void SpellDamageInfo::source_set_id(const int value) {
	_damage_source_id = value;
}

int SpellDamageInfo::source_get_type() const {
	return _damage_source_type;
}

void SpellDamageInfo::source_set_type(const int value) {
	_damage_source_type = value;
}

void SpellDamageInfo::reset() {
	_original_damage = -1;
}

void SpellDamageInfo::resolve_references(Node *owner) {
	ERR_FAIL_COND(!INSTANCE_VALIDATE(owner));
	ERR_FAIL_COND(!owner->is_inside_tree());

	_dealer = Object::cast_to<Entity>(owner->get_node_or_null(_dealer_path));
	_receiver = Object::cast_to<Entity>(owner->get_node_or_null(_receiver_path));

	if (_damage_source_type == DAMAGE_SOURCE_SPELL) {
		_damage_source = ESS::get_singleton()->get_resource_db()->get_spell(_damage_source_id);
	} else if (_damage_source_type == DAMAGE_SOURCE_AURA) {
		_damage_source = ESS::get_singleton()->get_resource_db()->get_spell(_damage_source_id);
	}
}

Dictionary SpellDamageInfo::to_dict() {
	Dictionary dict;

	if (INSTANCE_VALIDATE(_dealer))
		dict["dealer_path"] = _dealer->get_path();

	if (INSTANCE_VALIDATE(_receiver))
		dict["receiver_path"] = _receiver->get_path();

	dict["immune"] = _immune;
	dict["damage"] = _damage;

	dict["original_damage"] = _original_damage;
	dict["amount_absorbed"] = _amount_absorbed;
	dict["crit"] = _crit;

	dict["damage_type"] = _damage_type;

	dict["damage_source_type"] = _damage_source_type;
	dict["damage_source_id"] = _damage_source_id;

	return dict;
}
void SpellDamageInfo::from_dict(const Dictionary &dict) {
#if VERSION_MAJOR > 3
	ERR_FAIL_COND(dict.is_empty());
#else
	ERR_FAIL_COND(dict.empty());
#endif

	_immune = dict.get("immune", true);
	_damage = dict.get("damage", 0);

	_original_damage = dict.get("original_damage", 0);
	_amount_absorbed = dict.get("amount_absorbed", 0);
	_crit = dict.get("crit", false);

	_damage_type = dict.get("spell_type", 0);
	_damage_source_type = dict.get("damage_source_type", DAMAGE_SOURCE_UNKNOWN);
	_damage_source_id = dict.get("damage_source_id", 0);
}

SpellDamageInfo::SpellDamageInfo() {
	_immune = false;
	_damage = 0;
	_original_damage = 0;
	_crit = false;
	_damage_type = 0;
	_dealer = NULL;
	_receiver = NULL;
	_damage_source_type = DAMAGE_SOURCE_UNKNOWN;
	_damage_source_id = 0;
}

SpellDamageInfo::~SpellDamageInfo() {
	_damage_source.unref();
}

void SpellDamageInfo::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_immune"), &SpellDamageInfo::get_immune);
	ClassDB::bind_method(D_METHOD("set_immune", "value"), &SpellDamageInfo::set_immune);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "immune"), "set_immune", "get_immune");

	ClassDB::bind_method(D_METHOD("damage_get"), &SpellDamageInfo::damage_get);
	ClassDB::bind_method(D_METHOD("damage_set", "value"), &SpellDamageInfo::damage_set);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "damage"), "damage_set", "damage_get");

	ClassDB::bind_method(D_METHOD("crit_get"), &SpellDamageInfo::crit_get);
	ClassDB::bind_method(D_METHOD("crit_set", "value"), &SpellDamageInfo::crit_set);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "crit"), "crit_set", "crit_get");

	ClassDB::bind_method(D_METHOD("amount_absorbed_get"), &SpellDamageInfo::amount_absorbed_get);
	ClassDB::bind_method(D_METHOD("amount_absorbed_set", "value"), &SpellDamageInfo::amount_absorbed_set);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "amount_absorbed"), "amount_absorbed_set", "amount_absorbed_get");

	ClassDB::bind_method(D_METHOD("damage_type_get"), &SpellDamageInfo::damage_type_get);
	ClassDB::bind_method(D_METHOD("damage_type_set", "value"), &SpellDamageInfo::damage_type_set);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "damage_type_get"), "damage_type_set", "damage_type_get");

	ClassDB::bind_method(D_METHOD("dealer_get"), &SpellDamageInfo::dealer_get);
	ClassDB::bind_method(D_METHOD("dealer_set", "value"), &SpellDamageInfo::dealer_set_bind);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "dealer", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), "dealer_set", "dealer_get");

	ClassDB::bind_method(D_METHOD("receiver_get"), &SpellDamageInfo::receiver_get);
	ClassDB::bind_method(D_METHOD("receiver_set", "value"), &SpellDamageInfo::receiver_set_bind);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "receiver", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), "receiver_set", "receiver_get");

	ClassDB::bind_method(D_METHOD("source_get"), &SpellDamageInfo::source_get);
	ClassDB::bind_method(D_METHOD("source_set", "value"), &SpellDamageInfo::source_set);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "source", PROPERTY_HINT_RESOURCE_TYPE, "Resource"), "source_set", "source_get");

	ClassDB::bind_method(D_METHOD("spell_source_get"), &SpellDamageInfo::spell_source_get);
	ClassDB::bind_method(D_METHOD("spell_source_set", "value"), &SpellDamageInfo::spell_source_set);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "spell_source", PROPERTY_HINT_RESOURCE_TYPE, "Spell"), "spell_source_set", "spell_source_get");

	ClassDB::bind_method(D_METHOD("aura_source_get"), &SpellDamageInfo::aura_source_get);
	ClassDB::bind_method(D_METHOD("aura_source_set", "value"), &SpellDamageInfo::aura_source_set);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "aura_source", PROPERTY_HINT_RESOURCE_TYPE, "Aura"), "aura_source_set", "aura_source_get");

	ClassDB::bind_method(D_METHOD("source_get_id"), &SpellDamageInfo::source_get_id);
	ClassDB::bind_method(D_METHOD("source_set_id", "value"), &SpellDamageInfo::source_set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "source_id"), "source_set_id", "source_get_id");

	ClassDB::bind_method(D_METHOD("source_get_type"), &SpellDamageInfo::source_get_type);
	ClassDB::bind_method(D_METHOD("source_set_type", "value"), &SpellDamageInfo::source_set_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "source_type"), "source_set_type", "source_get_type");

	ClassDB::bind_method(D_METHOD("reset"), &SpellDamageInfo::reset);

	BIND_CONSTANT(DAMAGE_SOURCE_UNKNOWN);
	BIND_CONSTANT(DAMAGE_SOURCE_SPELL);
	BIND_CONSTANT(DAMAGE_SOURCE_AURA);
}
