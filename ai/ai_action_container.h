#ifndef AI_ACTION_CONTAINER_H
#define AI_ACTION_CONTAINER_H

#include "ai_action.h"

class AIActionContainer : public AIAction {
	GDCLASS(AIActionContainer, AIAction);

public:
	int get_num_ai_actions();
	void set_num_ai_actions(int value);

	Ref<AIAction> get_ai_action(int index);
	void set_ai_action(int index, Ref<AIAction> aura);

	Vector<Variant> get_ai_actions();
	void set_ai_actions(const Vector<Variant> &auras);

	AIActionContainer();
	~AIActionContainer();

protected:
	static void _bind_methods();

private:
	Vector<Ref<AIAction> > _ai_actions;
};

#endif
