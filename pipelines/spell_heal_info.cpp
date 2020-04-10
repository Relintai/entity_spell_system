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
#include "../entities/entity.h"
#include "../singletons/entity_data_manager.h"

#include "core/version.h"

bool SpellHealInfo::get_immune() {
	return _immune;
}
void SpellHealInfo::set_immune(bool value) {
	_immune = value;
}

int SpellHealInfo::get_heal() {
	return _heal;
}

void SpellHealInfo::set_heal(int value) {
	_heal = value;
}

bool SpellHealInfo::get_crit() {
	return _crit;
}

void SpellHealInfo::set_crit(bool value) {
	_crit = value;
}

int SpellHealInfo::get_amount_absorbed() {
	return _amount_absorbed;
}

void SpellHealInfo::set_amount_absorbed(int value) {
	_amount_absorbed = value;
}

SpellEnums::SpellType SpellHealInfo::get_spell_type() {
	return _spell_type;
}

void SpellHealInfo::set_spell_type(SpellEnums::SpellType value) {
	_spell_type = value;
}

Entity *SpellHealInfo::get_dealer() {
	return _dealer;
}

void SpellHealInfo::set_dealer(Node *value) {
	if (!value) {
		return;
	}

	Entity *e = cast_to<Entity>(value);

	if (!e) {
		return;
	}

	_dealer = e;
}

Entity *SpellHealInfo::get_receiver() {
	return _receiver;
}

void SpellHealInfo::set_receiver(Node *value) {
	if (!value) {
		return;
	}

	Entity *e = cast_to<Entity>(value);

	if (!e) {
		return;
	}

	_receiver = e;
}

Ref<Reference> SpellHealInfo::get_heal_source() {
	return _heal_source;
}

void SpellHealInfo::set_heal_source(Ref<Reference> value) {
	_heal_source_type = HEAL_SOURCE_UNKNOWN;
	_heal_source = value;
}

Ref<Spell> SpellHealInfo::get_spell_heal_source() {
	return Ref<Spell>(_heal_source);
}

void SpellHealInfo::set_spell_heal_source(Ref<Spell> value) {
	_heal_source_type = HEAL_SOURCE_SPELL;
	_heal_source = value;

	ERR_FAIL_COND(!value.is_valid());

	_heal_source_id = value->get_id();
}

Ref<Aura> SpellHealInfo::get_aura_heal_source() {
	return Ref<Aura>(_heal_source);
}

void SpellHealInfo::set_aura_heal_source(Ref<Aura> value) {
	_heal_source_type = HEAL_SOURCE_AURA;
	_heal_source = value;

	ERR_FAIL_COND(!value.is_valid());

	_heal_source_id = value->get_id();
}

int SpellHealInfo::get_heal_source_id() {
	return _heal_source_id;
}

void SpellHealInfo::set_heal_source_id(int value) {
	_heal_source_id = value;
}

SpellHealInfo::HealSourceType SpellHealInfo::get_heal_source_type() {
	return _heal_source_type;
}

void SpellHealInfo::set_heal_source_type(HealSourceType value) {
	_heal_source_type = value;
}

void SpellHealInfo::reset() {
	_original_heal = -1;
}

void SpellHealInfo::resolve_references(Node *owner) {
#if VERSION_MAJOR < 4
	ERR_FAIL_COND(!ObjectDB::instance_validate(owner));
#else
	ERR_FAIL_COND(owner == NULL);
#endif
	ERR_FAIL_COND(!owner->is_inside_tree());

	_dealer = Object::cast_to<Entity>(owner->get_node_or_null(_dealer_path));
	_receiver = Object::cast_to<Entity>(owner->get_node_or_null(_receiver_path));

	if (_heal_source_type == HEAL_SOURCE_SPELL) {
		_heal_source = EntityDataManager::get_instance()->get_spell(_heal_source_id);
	} else if (_heal_source_type == HEAL_SOURCE_AURA) {
		_heal_source = EntityDataManager::get_instance()->get_aura(_heal_source_id);
	}
}

Dictionary SpellHealInfo::to_dict() {
	Dictionary dict;

#if VERSION_MAJOR < 4
	if (ObjectDB::instance_validate(_dealer))
		dict["dealer_path"] = _dealer->get_path();

	if (ObjectDB::instance_validate(_receiver))
		dict["receiver_path"] = _receiver->get_path();
#else
	if (_dealer == NULL)
		dict["dealer_path"] = _dealer->get_path();

	if (_receiver == NULL)
		dict["receiver_path"] = _receiver->get_path();
#endif

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

	ClassDB::bind_method(D_METHOD("get_heal"), &SpellHealInfo::get_heal);
	ClassDB::bind_method(D_METHOD("set_heal", "value"), &SpellHealInfo::set_heal);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "heal"), "set_heal", "get_heal");

	ClassDB::bind_method(D_METHOD("get_crit"), &SpellHealInfo::get_crit);
	ClassDB::bind_method(D_METHOD("set_crit", "value"), &SpellHealInfo::set_crit);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "crit"), "set_crit", "get_crit");

	ClassDB::bind_method(D_METHOD("get_amount_absorbed"), &SpellHealInfo::get_amount_absorbed);
	ClassDB::bind_method(D_METHOD("set_amount_absorbed", "value"), &SpellHealInfo::set_amount_absorbed);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "amount_absorbed"), "set_amount_absorbed", "get_amount_absorbed");

	ClassDB::bind_method(D_METHOD("get_spell_type"), &SpellHealInfo::get_spell_type);
	ClassDB::bind_method(D_METHOD("set_spell_type", "value"), &SpellHealInfo::set_spell_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "spell_type", PROPERTY_HINT_ENUM, "None, Melee, Magic"), "set_spell_type", "get_spell_type");

	ClassDB::bind_method(D_METHOD("get_dealer"), &SpellHealInfo::get_dealer);
	ClassDB::bind_method(D_METHOD("set_dealer", "value"), &SpellHealInfo::set_dealer);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "dealer", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), "set_dealer", "get_dealer");

	ClassDB::bind_method(D_METHOD("get_receiver"), &SpellHealInfo::get_receiver);
	ClassDB::bind_method(D_METHOD("set_receiver", "value"), &SpellHealInfo::set_receiver);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "receiver", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), "set_receiver", "get_receiver");

	ClassDB::bind_method(D_METHOD("get_heal_source"), &SpellHealInfo::get_heal_source);
	ClassDB::bind_method(D_METHOD("set_heal_source", "value"), &SpellHealInfo::set_heal_source);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "heal_source", PROPERTY_HINT_RESOURCE_TYPE, "Resource"), "set_heal_source", "get_heal_source");

	ClassDB::bind_method(D_METHOD("get_heal_source_id"), &SpellHealInfo::get_heal_source_id);
	ClassDB::bind_method(D_METHOD("set_heal_source_id", "value"), &SpellHealInfo::set_heal_source_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "heal_source_id"), "set_heal_source_id", "get_heal_source_id");

	ClassDB::bind_method(D_METHOD("get_heal_source_type"), &SpellHealInfo::get_heal_source_type);
	ClassDB::bind_method(D_METHOD("set_heal_source_type", "value"), &SpellHealInfo::set_heal_source_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "heal_source_type", PROPERTY_HINT_ENUM, "Unknown, Spell, Aura"), "set_heal_source_type", "get_heal_source_type");

	ClassDB::bind_method(D_METHOD("reset"), &SpellHealInfo::reset);

	BIND_ENUM_CONSTANT(HEAL_SOURCE_UNKNOWN);
	BIND_ENUM_CONSTANT(HEAL_SOURCE_SPELL);
	BIND_ENUM_CONSTANT(HEAL_SOURCE_AURA);
}
