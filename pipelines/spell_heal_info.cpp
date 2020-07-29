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

#include "spell_heal_info.h"

#include "../data/auras/aura.h"
#include "../data/spells/spell.h"
#include "../database/ess_resource_db.h"
#include "../entities/entity.h"
#include "../singletons/ess.h"

#include "../defines.h"

bool SpellHealInfo::get_immune() {
	return _immune;
}
void SpellHealInfo::set_immune(bool value) {
	_immune = value;
}

int SpellHealInfo::heal_get() {
	return _heal;
}

void SpellHealInfo::heal_set(int value) {
	_heal = value;
}

bool SpellHealInfo::crit_get() {
	return _crit;
}

void SpellHealInfo::crit_set(bool value) {
	_crit = value;
}

int SpellHealInfo::amount_absorbed_get() {
	return _amount_absorbed;
}

void SpellHealInfo::amount_absorbed_set(int value) {
	_amount_absorbed = value;
}

SpellEnums::SpellType SpellHealInfo::spell_type_get() {
	return _spell_type;
}

void SpellHealInfo::spell_type_set(SpellEnums::SpellType value) {
	_spell_type = value;
}

Entity *SpellHealInfo::dealer_get() {
	return _dealer;
}

void SpellHealInfo::dealer_set(Node *value) {
	if (!value) {
		return;
	}

	Entity *e = cast_to<Entity>(value);

	if (!e) {
		return;
	}

	_dealer = e;
}

Entity *SpellHealInfo::receiver_get() {
	return _receiver;
}

void SpellHealInfo::receiver_set(Node *value) {
	if (!value) {
		return;
	}

	Entity *e = cast_to<Entity>(value);

	if (!e) {
		return;
	}

	_receiver = e;
}

Ref<Reference> SpellHealInfo::source_get() {
	return _heal_source;
}

void SpellHealInfo::source_set(Ref<Reference> value) {
	_heal_source_type = HEAL_SOURCE_UNKNOWN;
	_heal_source = value;
}

Ref<Spell> SpellHealInfo::spell_source_get() {
	return Ref<Spell>(_heal_source);
}

void SpellHealInfo::spell_source_set(Ref<Spell> value) {
	_heal_source_type = HEAL_SOURCE_SPELL;
	_heal_source = value;

	ERR_FAIL_COND(!value.is_valid());

	_heal_source_id = value->get_id();
}

Ref<Aura> SpellHealInfo::aura_source_get() {
	return Ref<Aura>(_heal_source);
}

void SpellHealInfo::aura_source_set(Ref<Aura> value) {
	_heal_source_type = HEAL_SOURCE_AURA;
	_heal_source = value;

	ERR_FAIL_COND(!value.is_valid());

	_heal_source_id = value->get_id();
}

int SpellHealInfo::source_get_id() {
	return _heal_source_id;
}

void SpellHealInfo::source_set_id(int value) {
	_heal_source_id = value;
}

SpellHealInfo::HealSourceType SpellHealInfo::source_get_type() {
	return _heal_source_type;
}

void SpellHealInfo::source_set_type(HealSourceType value) {
	_heal_source_type = value;
}

void SpellHealInfo::reset() {
	_original_heal = -1;
}

void SpellHealInfo::resolve_references(Node *owner) {
	ERR_FAIL_COND(!INSTANCE_VALIDATE(owner));
	ERR_FAIL_COND(!owner->is_inside_tree());

	_dealer = Object::cast_to<Entity>(owner->get_node_or_null(_dealer_path));
	_receiver = Object::cast_to<Entity>(owner->get_node_or_null(_receiver_path));

	if (_heal_source_type == HEAL_SOURCE_SPELL) {
		_heal_source = ESS::get_singleton()->get_resource_db()->get_spell(_heal_source_id);
	} else if (_heal_source_type == HEAL_SOURCE_AURA) {
		_heal_source = ESS::get_singleton()->get_resource_db()->get_aura(_heal_source_id);
	}
}

Dictionary SpellHealInfo::to_dict() {
	Dictionary dict;

	if (INSTANCE_VALIDATE(_dealer))
		dict["dealer_path"] = _dealer->get_path();

	if (INSTANCE_VALIDATE(_receiver))
		dict["receiver_path"] = _receiver->get_path();

	dict["immune"] = _immune;
	dict["heal"] = _heal;

	dict["original_heal"] = _original_heal;
	dict["amount_absorbed"] = _amount_absorbed;
	dict["crit"] = _crit;

	dict["spell_type"] = _spell_type;
	dict["heal_source_type"] = _heal_source_type;
	dict["heal_source_id"] = _heal_source_id;

	return dict;
}
void SpellHealInfo::from_dict(const Dictionary &dict) {
	ERR_FAIL_COND(dict.empty());

	_immune = dict.get("immune", true);
	_heal = dict.get("heal", 0);

	_original_heal = dict.get("original_heal", 0);
	_amount_absorbed = dict.get("amount_absorbed", 0);
	_crit = dict.get("crit", false);

	_spell_type = static_cast<SpellEnums::SpellType>(static_cast<int>(dict.get("spell_type", SpellEnums::SPELL_TYPE_NONE)));
	_heal_source_type = static_cast<HealSourceType>(static_cast<int>(dict.get("heal_source_type", HEAL_SOURCE_UNKNOWN)));
	_heal_source_id = dict.get("heal_source_id", 0);
}

SpellHealInfo::SpellHealInfo() {
	_heal = 0;
	_original_heal = 0;
	_crit = false;
	_spell_type = SpellEnums::SPELL_TYPE_NONE;
	_dealer = NULL;
	_receiver = NULL;
	_heal_source_type = HEAL_SOURCE_UNKNOWN;
	//Ref<Reference> _heal_source = Ref<;
	_heal_source_id = 0;
	_immune = false;
}

SpellHealInfo::~SpellHealInfo() {
	//_dealer = NULL;
	//_receiver = NULL;
	//_heal_source = Ref<Reference>(NULL);
}

void SpellHealInfo::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_immune"), &SpellHealInfo::get_immune);
	ClassDB::bind_method(D_METHOD("set_immune", "value"), &SpellHealInfo::set_immune);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "immune"), "set_immune", "get_immune");

	ClassDB::bind_method(D_METHOD("heal_get"), &SpellHealInfo::heal_get);
	ClassDB::bind_method(D_METHOD("heal_set", "value"), &SpellHealInfo::heal_set);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "heal"), "heal_set", "heal_get");

	ClassDB::bind_method(D_METHOD("crit_get"), &SpellHealInfo::crit_get);
	ClassDB::bind_method(D_METHOD("crit_set", "value"), &SpellHealInfo::crit_set);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "crit"), "crit_set", "crit_get");

	ClassDB::bind_method(D_METHOD("amount_absorbed_get"), &SpellHealInfo::amount_absorbed_get);
	ClassDB::bind_method(D_METHOD("amount_absorbed_set", "value"), &SpellHealInfo::amount_absorbed_set);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "amount_absorbed"), "amount_absorbed_set", "amount_absorbed_get");

	ClassDB::bind_method(D_METHOD("spell_type_get"), &SpellHealInfo::spell_type_get);
	ClassDB::bind_method(D_METHOD("spell_type_set", "value"), &SpellHealInfo::spell_type_set);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "spell_type", PROPERTY_HINT_ENUM, "None, Melee, Magic"), "spell_type_set", "spell_type_get");

	ClassDB::bind_method(D_METHOD("dealer_get"), &SpellHealInfo::dealer_get);
	ClassDB::bind_method(D_METHOD("dealer_set", "value"), &SpellHealInfo::dealer_set);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "dealer", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), "dealer_set", "dealer_get");

	ClassDB::bind_method(D_METHOD("receiver_get"), &SpellHealInfo::receiver_get);
	ClassDB::bind_method(D_METHOD("receiver_set", "value"), &SpellHealInfo::receiver_set);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "receiver", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), "receiver_set", "receiver_get");

	ClassDB::bind_method(D_METHOD("source_get"), &SpellHealInfo::source_get);
	ClassDB::bind_method(D_METHOD("source_set", "value"), &SpellHealInfo::source_set);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "heal_source", PROPERTY_HINT_RESOURCE_TYPE, "Resource"), "source_set", "source_get");

	ClassDB::bind_method(D_METHOD("source_get_id"), &SpellHealInfo::source_get_id);
	ClassDB::bind_method(D_METHOD("source_set_id", "value"), &SpellHealInfo::source_set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "heal_source_id"), "source_set_id", "source_get_id");

	ClassDB::bind_method(D_METHOD("source_get_type"), &SpellHealInfo::source_get_type);
	ClassDB::bind_method(D_METHOD("source_set_type", "value"), &SpellHealInfo::source_set_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "heal_source_type", PROPERTY_HINT_ENUM, "Unknown, Spell, Aura"), "source_set_type", "source_get_type");

	ClassDB::bind_method(D_METHOD("reset"), &SpellHealInfo::reset);

	BIND_ENUM_CONSTANT(HEAL_SOURCE_UNKNOWN);
	BIND_ENUM_CONSTANT(HEAL_SOURCE_SPELL);
	BIND_ENUM_CONSTANT(HEAL_SOURCE_AURA);
}
