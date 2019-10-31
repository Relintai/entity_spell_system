#ifndef AI_SPEC_ACTION_H
#define AI_SPEC_ACTION_H

#include "ai_action.h"

#include "core/vector.h"

class AISpecAction : public AIAction {
	GDCLASS(AISpecAction, AIAction);

public:
	Vector<int> get_spec_distribution();
	void set_spec_distribution(Vector<int> data);

	int get_variance();
	void set_variance(int value);

	Ref<AIAction> get_action();
	void set_action(Ref<AIAction> action);

	AISpecAction();
	~AISpecAction();

protected:
	static void _bind_methods();

private:
	Vector<int> _spec_distribution;
	int _variance;
	Ref<AIAction> _action;
};

#endif
