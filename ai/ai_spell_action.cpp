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

AISpellAction::AISpellAction() {
	_type = AI_SPELL_ACTION_TYPE_NONE;
}

void AISpellAction::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_type"), &AISpellAction::get_type);
	ClassDB::bind_method(D_METHOD("set_type", "value"), &AISpellAction::set_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "type", PROPERTY_HINT_ENUM, BINDING_STRING_SPELL_ACTION_TYPE), "set_type", "get_type");

	ClassDB::bind_method(D_METHOD("get_spell"), &AISpellAction::get_spell);
	ClassDB::bind_method(D_METHOD("set_spell", "value"), &AISpellAction::set_spell);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "spell", PROPERTY_HINT_RESOURCE_TYPE, "Spell"), "set_spell", "get_spell");

	BIND_ENUM_CONSTANT(AI_SPELL_ACTION_TYPE_NONE);
	BIND_ENUM_CONSTANT(AI_SPELL_ACTION_TYPE_ATTACK);
	BIND_ENUM_CONSTANT(AI_SPELL_ACTION_TYPE_CHARGE);
	BIND_ENUM_CONSTANT(AI_SPELL_ACTION_TYPE_CC);
	BIND_ENUM_CONSTANT(AI_SPELL_ACTION_TYPE_DPS);
	BIND_ENUM_CONSTANT(AI_SPELL_ACTION_TYPE_REGENERATION);
	BIND_ENUM_CONSTANT(AI_SPELL_ACTION_TYPE_STUNBREAK);
}
