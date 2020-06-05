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

#include "spell_damage_info.h"

#include "../data/auras/aura.h"
#include "../data/spells/spell.h"
#include "../database/ess_resource_db.h"
#include "../entities/entity.h"
#include "../singletons/ess.h"

#include "../defines.h"

bool SpellDamageInfo::get_immune() {
	return _crit;
}
void SpellDamageInfo::set_immune(bool value) {
	_crit = value;
}

int SpellDamageInfo::damage_get() {
	return _damage;
}
void SpellDamageInfo::damage_set(int value) {
	_damage = value;
}

bool SpellDamageInfo::crit_get() {
	return _crit;
}
void SpellDamageInfo::crit_set(bool value) {
	_crit = value;
}

int SpellDamageInfo::amount_absorbed_get() {
	return _amount_absorbed;
}
void SpellDamageInfo::amount_absorbed_set(int value) {
	_amount_absorbed = value;
}

SpellEnums::SpellType SpellDamageInfo::spell_type_get() {
	return _spell_type;
}
void SpellDamageInfo::spell_type_set(SpellEnums::SpellType value) {
	_spell_type = value;
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

void SpellDamageInfo::spell_source_set(Ref<Spell> value) {
	_damage_source_type = DAMAGE_SOURCE_SPELL;
	_damage_source = value;

	ERR_FAIL_COND(!value.is_valid());

	_damage_source_id = value->get_id();
}

Ref<Aura> SpellDamageInfo::aura_source_get() {
	return Ref<Aura>(_damage_source);
}

void SpellDamageInfo::aura_source_set(Ref<Aura> value) {
	_damage_source_type = DAMAGE_SOURCE_AURA;
	_damage_source = value;

	ERR_FAIL_COND(!value.is_valid());

	_damage_source_id = value->get_id();
}

int SpellDamageInfo::source_get_id() {
	return _damage_source_id;
}

void SpellDamageInfo::source_set_id(int value) {
	_damage_source_id = value;
}

SpellDamageInfo::DamageSourceType SpellDamageInfo::source_get_type() {
	return _damage_source_type;
}

void SpellDamageInfo::source_set_type(DamageSourceType value) {
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
		_damage_source = ESS::get_singleton()->get_resource_db()->get_aura(_damage_source_id);
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

	dict["spell_type"] = _spell_type;
	dict["damage_source_type"] = _damage_source_type;
	dict["damage_source_id"] = _damage_source_id;

	return dict;
}
void SpellDamageInfo::from_dict(const Dictionary &dict) {
	ERR_FAIL_COND(dict.empty());

	_immune = dict.get("immune", true);
	_damage = dict.get("damage", 0);

	_original_damage = dict.get("original_damage", 0);
	_amount_absorbed = dict.get("amount_absorbed", 0);
	_crit = dict.get("crit", false);

	_spell_type = static_cast<SpellEnums::SpellType>(static_cast<int>(dict.get("spell_type", SpellEnums::SPELL_TYPE_NONE)));
	_damage_source_type = static_cast<DamageSourceType>(static_cast<int>(dict.get("damage_source_type", DAMAGE_SOURCE_UNKNOWN)));
	_damage_source_id = dict.get("damage_source_id", 0);
}

SpellDamageInfo::SpellDamageInfo() {
	_damage = 0;
	_original_damage = 0;
	_crit = false;
	_spell_type = SpellEnums::SPELL_TYPE_NONE;
	_dealer = NULL;
	_receiver = NULL;
	_damage_source_type = DAMAGE_SOURCE_UNKNOWN;
	//Ref<Reference> _damage_source = Ref<;
	_damage_source_id = 0;
}

SpellDamageInfo::~SpellDamageInfo() {
	//_dealer = NULL;
	//_receiver = NULL;
	//_damage_source = Ref<Reference>(NULL);
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

	ClassDB::bind_method(D_METHOD("spell_type_get"), &SpellDamageInfo::spell_type_get);
	ClassDB::bind_method(D_METHOD("spell_type_set", "value"), &SpellDamageInfo::spell_type_set);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "spell_type", PROPERTY_HINT_ENUM, "None, Melee, Magic"), "spell_type_set", "spell_type_get");

	ClassDB::bind_method(D_METHOD("dealer_get"), &SpellDamageInfo::dealer_get);
	ClassDB::bind_method(D_METHOD("dealer_set", "value"), &SpellDamageInfo::dealer_set_bind);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "dealer", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), "dealer_set", "dealer_get");

	ClassDB::bind_method(D_METHOD("receiver_get"), &SpellDamageInfo::receiver_get);
	ClassDB::bind_method(D_METHOD("receiver_set", "value"), &SpellDamageInfo::receiver_set_bind);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "receiver", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), "receiver_set", "receiver_get");

	ClassDB::bind_method(D_METHOD("source_get"), &SpellDamageInfo::source_get);
	ClassDB::bind_method(D_METHOD("source_set", "value"), &SpellDamageInfo::source_set);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "damage_source", PROPERTY_HINT_RESOURCE_TYPE, "Resource"), "source_set", "source_get");

	ClassDB::bind_method(D_METHOD("source_get_id"), &SpellDamageInfo::source_get_id);
	ClassDB::bind_method(D_METHOD("source_set_id", "value"), &SpellDamageInfo::source_set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "damage_source_id"), "source_set_id", "source_get_id");

	ClassDB::bind_method(D_METHOD("source_get_type"), &SpellDamageInfo::source_get_type);
	ClassDB::bind_method(D_METHOD("source_set_type", "value"), &SpellDamageInfo::source_set_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "damage_source_type", PROPERTY_HINT_ENUM, "Unknown,Spell,Aura"), "source_set_type", "source_get_type");

	ClassDB::bind_method(D_METHOD("reset"), &SpellDamageInfo::reset);

	BIND_ENUM_CONSTANT(DAMAGE_SOURCE_UNKNOWN);
	BIND_ENUM_CONSTANT(DAMAGE_SOURCE_SPELL);
	BIND_ENUM_CONSTANT(DAMAGE_SOURCE_AURA);
}
