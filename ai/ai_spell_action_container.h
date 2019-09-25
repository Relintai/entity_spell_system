#ifndef AI_SPELL_ACTION_CONTAINER_H
#define AI_SPELL_ACTION_CONTAINER_H

#include "ai_action.h"
#include "ai_spell_action.h"

class AISpellActionContainer : public AIAction {
	GDCLASS(AISpellActionContainer, AIAction);

public:
	int get_num_ai_spell_actions();
	void set_num_ai_spell_actions(int value);

	Ref<AISpellAction> get_ai_spell_action(int index);
	void set_ai_spell_action(int index, Ref<AISpellAction> action);

	Vector<Variant> get_ai_spell_actions();
	void set_ai_spell_actions(const Vector<Variant> &auras);

	AISpellActionContainer();

protected:
	static void _bind_methods();

private:
	Vector<Ref<AISpellAction> > _ai_spell_actions;
};

#endif
