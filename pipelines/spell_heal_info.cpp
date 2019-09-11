#include "spell_heal_info.h"

#include "../data/aura.h"
#include "../data/spell.h"
#include "../entities/entity.h"

bool SpellHealInfo::get_immune() {
	return _crit;
}
void SpellHealInfo::set_immune(bool value) {
	_crit = value;
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
	//cast
	return NULL;
}

void SpellHealInfo::set_spell_heal_source(Ref<Spell> value) {
	_heal_source_type = HEAL_SOURCE_SPELL;
	_heal_source = value;
}

Ref<Aura> SpellHealInfo::get_aura_heal_source() {
	//cast
	return NULL;
}

void SpellHealInfo::set_aura_heal_source(Ref<Aura> value) {
	_heal_source_type = HEAL_SOURCE_AURA;
	_heal_source = value;
}

int SpellHealInfo::get_heal_source_id() {
	return _heal_source_id;
}

void SpellHealInfo::set_heal_source_id(int value) {
	_heal_source_id = value;
}

SpellHealInfo::HealSource SpellHealInfo::get_heal_source_type() {
	return _heal_source_type;
}

void SpellHealInfo::set_heal_source_type(HealSource value) {
	_heal_source_type = value;
}

void SpellHealInfo::reset() {
	_original_heal = -1;
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
