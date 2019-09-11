#include "spell_damage_info.h"

#include "../entities/entity.h"
#include "../data/spell.h"
#include "../data/aura.h"

bool SpellDamageInfo::get_immune() {
	return _crit;
}
void SpellDamageInfo::set_immune(bool value) {
	_crit = value;
}

int SpellDamageInfo::get_damage() {
	return _damage;
}
void SpellDamageInfo::set_damage(int value) {
	_damage = value;
}

bool SpellDamageInfo::get_crit() {
	return _crit;
}
void SpellDamageInfo::set_crit(bool value) {
	_crit = value;
}

int SpellDamageInfo::get_amount_absorbed() {
	return _amount_absorbed;
}
void SpellDamageInfo::set_amount_absorbed(int value) {
	_amount_absorbed = value;
}

SpellEnums::SpellType SpellDamageInfo::get_spell_type() {
	return _spell_type;
}
void SpellDamageInfo::set_spell_type(SpellEnums::SpellType value) {
	_spell_type = value;
}

Entity *SpellDamageInfo::get_dealer() {
	return _dealer;
}
void SpellDamageInfo::set_dealer(Entity *value) {
	_dealer = value;
}
void SpellDamageInfo::set_dealer_bind(Node *value) {
	if (!value) {
		return;
	}

	Entity *e = cast_to<Entity>(value);

	if (!e) {
		return;
	}

	_dealer = e;
}

Entity *SpellDamageInfo::get_receiver() {
	return _receiver;
}
void SpellDamageInfo::set_receiver(Entity *value) {
	_receiver = value;
}
void SpellDamageInfo::set_receiver_bind(Node *value) {
	if (!value) {
		return;
	}

	Entity *e = cast_to<Entity>(value);

	if (!e) {
		return;
	}

	_receiver = e;
}

Ref<Reference> SpellDamageInfo::get_damage_source() {
	return _damage_source;
}
void SpellDamageInfo::set_damage_source(Ref<Reference> value) {
	_damage_source_type = DAMAGE_SOURCE_UNKNOWN;
	_damage_source = value;
}


Ref<Spell> SpellDamageInfo::get_spell_damage_source() {
	//cast
	return NULL;
}

void SpellDamageInfo::set_spell_damage_source(Ref<Spell> value) {
	_damage_source_type = DAMAGE_SOURCE_SPELL;
	_damage_source = value;
}


Ref<Aura> SpellDamageInfo::get_aura_damage_source() {
	//cast
	return NULL;
}

void SpellDamageInfo::set_aura_damage_source(Ref<Aura> value) {
	_damage_source_type = DAMAGE_SOURCE_AURA;
	_damage_source = value;
}



int SpellDamageInfo::get_damage_source_id() {
	return _damage_source_id;
}

void SpellDamageInfo::set_damage_source_id(int value) {
	_damage_source_id = value;
}

SpellDamageInfo::DamageSource SpellDamageInfo::get_damage_source_type() {
	return _damage_source_type;
}

void SpellDamageInfo::set_damage_source_type(DamageSource value) {
	_damage_source_type = value;
}

void SpellDamageInfo::reset() {
	_original_damage = -1;
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
    
	ClassDB::bind_method(D_METHOD("get_damage"), &SpellDamageInfo::get_damage);
	ClassDB::bind_method(D_METHOD("set_damage", "value"), &SpellDamageInfo::set_damage);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "damage"), "set_damage", "get_damage");

	ClassDB::bind_method(D_METHOD("get_crit"), &SpellDamageInfo::get_crit);
	ClassDB::bind_method(D_METHOD("set_crit", "value"), &SpellDamageInfo::set_crit);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "crit"), "set_crit", "get_crit");
	
	ClassDB::bind_method(D_METHOD("get_amount_absorbed"), &SpellDamageInfo::get_amount_absorbed);
	ClassDB::bind_method(D_METHOD("set_amount_absorbed", "value"), &SpellDamageInfo::set_amount_absorbed);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "amount_absorbed"), "set_amount_absorbed", "get_amount_absorbed");

	ClassDB::bind_method(D_METHOD("get_spell_type"), &SpellDamageInfo::get_spell_type);
	ClassDB::bind_method(D_METHOD("set_spell_type", "value"), &SpellDamageInfo::set_spell_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "spell_type", PROPERTY_HINT_ENUM, "None, Melee, Magic"), "set_spell_type", "get_spell_type");

	ClassDB::bind_method(D_METHOD("get_dealer"), &SpellDamageInfo::get_dealer);
	ClassDB::bind_method(D_METHOD("set_dealer", "value"), &SpellDamageInfo::set_dealer_bind);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "dealer", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), "set_dealer", "get_dealer");

	ClassDB::bind_method(D_METHOD("get_receiver"), &SpellDamageInfo::get_receiver);
	ClassDB::bind_method(D_METHOD("set_receiver", "value"), &SpellDamageInfo::set_receiver_bind);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "receiver", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), "set_receiver", "get_receiver");

	ClassDB::bind_method(D_METHOD("get_damage_source"), &SpellDamageInfo::get_damage_source);
	ClassDB::bind_method(D_METHOD("set_damage_source", "value"), &SpellDamageInfo::set_damage_source);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "damage_source", PROPERTY_HINT_RESOURCE_TYPE, "Resource"), "set_damage_source", "get_damage_source");

	ClassDB::bind_method(D_METHOD("get_damage_source_id"), &SpellDamageInfo::get_damage_source_id);
	ClassDB::bind_method(D_METHOD("set_damage_source_id", "value"), &SpellDamageInfo::set_damage_source_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "damage_source_id"), "set_damage_source_id", "get_damage_source_id");

	ClassDB::bind_method(D_METHOD("get_damage_source_type"), &SpellDamageInfo::get_damage_source_type);
	ClassDB::bind_method(D_METHOD("set_damage_source_type", "value"), &SpellDamageInfo::set_damage_source_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "damage_source_type", PROPERTY_HINT_ENUM, "Unknown, Spell, Aura"), "set_damage_source_type", "get_damage_source_type");

	ClassDB::bind_method(D_METHOD("reset"), &SpellDamageInfo::reset);


	BIND_ENUM_CONSTANT(DAMAGE_SOURCE_UNKNOWN);
	BIND_ENUM_CONSTANT(DAMAGE_SOURCE_SPELL);
	BIND_ENUM_CONSTANT(DAMAGE_SOURCE_AURA);
}
