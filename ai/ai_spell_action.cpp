#include "ai_spell_action.h"

#include "../data/spell.h"

const String AISpellAction::BINDING_STRING_SPELL_ACTION_TYPE = "None,Attack,Charge,CC,DPS,Regeneration,Stunbreak";

AISpellAction::AISpellActionType AISpellAction::get_type() const {
	return _type;
}
void AISpellAction::set_type(const AISpellAction::AISpellActionType type) {
	_type = type;
}

Ref<Spell> AISpellAction::get_spell() {
	return _spell;
}
void AISpellAction::set_spell(Ref<Spell> spell) {
	_spell = spell;
}

int AISpellAction::get_keep_aura_on_target() const {
	return _keep_aura_on_target;
}
void AISpellAction::set_keep_aura_on_target(const int value) {
	_keep_aura_on_target = value;
}

int AISpellAction::get_keep_aura_on_target_index() const {
	return _keep_aura_on_target_index;
}
void AISpellAction::set_keep_aura_on_target_index(const int value) {
	_keep_aura_on_target_index = value;
}

int AISpellAction::get_keep_aura_on_self() const {
	return _keep_aura_on_self;
}
void AISpellAction::set_keep_aura_on_self(const int value) {
	_keep_aura_on_self = value;
}

int AISpellAction::get_keep_aura_on_self_index() const {
	return _keep_aura_on_self_index;
}
void AISpellAction::set_keep_aura_on_self_index(const int value) {
	_keep_aura_on_self_index = value;
}

AISpellAction::AISpellAction() {
	_type = AI_SPELL_ACTION_TYPE_NONE;

	_keep_aura_on_target = false;
	_keep_aura_on_target_index = 0;

	_keep_aura_on_self = false;
	_keep_aura_on_self_index = 0;
}

AISpellAction::~AISpellAction() {
	_spell.unref();
}

void AISpellAction::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_type"), &AISpellAction::get_type);
	ClassDB::bind_method(D_METHOD("set_type", "value"), &AISpellAction::set_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "type", PROPERTY_HINT_ENUM, BINDING_STRING_SPELL_ACTION_TYPE), "set_type", "get_type");

	ClassDB::bind_method(D_METHOD("get_spell"), &AISpellAction::get_spell);
	ClassDB::bind_method(D_METHOD("set_spell", "value"), &AISpellAction::set_spell);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "spell", PROPERTY_HINT_RESOURCE_TYPE, "Spell"), "set_spell", "get_spell");

	ADD_GROUP("Keep Auras", "keep_aura");
	ClassDB::bind_method(D_METHOD("get_keep_aura_on_target"), &AISpellAction::get_keep_aura_on_target);
	ClassDB::bind_method(D_METHOD("set_keep_aura_on_target", "value"), &AISpellAction::set_keep_aura_on_target);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "keep_aura_on_target"), "set_keep_aura_on_target", "get_keep_aura_on_target");

	ClassDB::bind_method(D_METHOD("get_keep_aura_on_target_index"), &AISpellAction::get_keep_aura_on_target_index);
	ClassDB::bind_method(D_METHOD("set_keep_aura_on_target_index", "value"), &AISpellAction::set_keep_aura_on_target_index);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "keep_aura_on_target_index"), "set_keep_aura_on_target_index", "get_keep_aura_on_target_index");

	ClassDB::bind_method(D_METHOD("get_keep_aura_on_self"), &AISpellAction::get_keep_aura_on_self);
	ClassDB::bind_method(D_METHOD("set_keep_aura_on_self", "value"), &AISpellAction::set_keep_aura_on_self);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "keep_aura_on_self"), "set_keep_aura_on_self", "get_keep_aura_on_self");

	ClassDB::bind_method(D_METHOD("get_keep_aura_on_self_index"), &AISpellAction::get_keep_aura_on_self_index);
	ClassDB::bind_method(D_METHOD("set_keep_aura_on_self_index", "value"), &AISpellAction::set_keep_aura_on_self_index);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "keep_aura_on_self_index"), "set_keep_aura_on_self_index", "get_keep_aura_on_self_index");


	BIND_ENUM_CONSTANT(AI_SPELL_ACTION_TYPE_NONE);
	BIND_ENUM_CONSTANT(AI_SPELL_ACTION_TYPE_ATTACK);
	BIND_ENUM_CONSTANT(AI_SPELL_ACTION_TYPE_CHARGE);
	BIND_ENUM_CONSTANT(AI_SPELL_ACTION_TYPE_CC);
	BIND_ENUM_CONSTANT(AI_SPELL_ACTION_TYPE_DPS);
	BIND_ENUM_CONSTANT(AI_SPELL_ACTION_TYPE_REGENERATION);
	BIND_ENUM_CONSTANT(AI_SPELL_ACTION_TYPE_STUNBREAK);
}
