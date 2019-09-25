#ifndef AI_SPELL_ACTION_H
#define AI_SPELL_ACTION_H

#include "core/ustring.h"

#include "ai_action.h"

class Spell;

class AISpellAction : public AIAction {
	GDCLASS(AISpellAction, AIAction);

public:
	enum AISpellActionType {
		AI_SPELL_ACTION_TYPE_NONE,
		AI_SPELL_ACTION_TYPE_ATTACK,
		AI_SPELL_ACTION_TYPE_CHARGE,
		AI_SPELL_ACTION_TYPE_CC,
		AI_SPELL_ACTION_TYPE_DPS,
		AI_SPELL_ACTION_TYPE_REGENERATION,
		AI_SPELL_ACTION_TYPE_STUNBREAK
	};

	static const String BINDING_STRING_SPELL_ACTION_TYPE;

public:
	AISpellActionType get_type() const;
	void set_type(const AISpellActionType type);

	Ref<Spell> get_spell();
	void set_spell(Ref<Spell> spell);

	int get_keep_aura_on_target() const;
	void set_keep_aura_on_target(const int value);

	int get_keep_aura_on_target_index() const;
	void set_keep_aura_on_target_index(const int value);


	int get_keep_aura_on_self() const;
	void set_keep_aura_on_self(const int value);

	int get_keep_aura_on_self_index() const;
	void set_keep_aura_on_self_index(const int value);

	AISpellAction();

protected:
	static void _bind_methods();

private:
	AISpellActionType _type;
	Ref<Spell> _spell;

	bool _keep_aura_on_target;
	int _keep_aura_on_target_index;

	bool _keep_aura_on_self;
	int _keep_aura_on_self_index;
};

VARIANT_ENUM_CAST(AISpellAction::AISpellActionType);

#endif
