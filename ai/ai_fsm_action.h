#ifndef AI_FSM_ACTION_H
#define AI_FSM_ACTION_H

#include "ai_action.h"

#include "../entity_enums.h"

class AIFSMAction : public AIAction {
	GDCLASS(AIFSMAction, AIAction);

public:
	EntityEnums::AIStates get_state();
	void set_state(EntityEnums::AIStates state);

	EntityEnums::AIStates get_force_state();
	void set_force_state(EntityEnums::AIStates state);

	Ref<AIAction> get_action(const EntityEnums::AIStates index);
	void set_action(const EntityEnums::AIStates index, Ref<AIAction> action);

	AIFSMAction();
	~AIFSMAction();

protected:
	static void _bind_methods();

private:
	EntityEnums::AIStates _state;
	EntityEnums::AIStates _force_state;

	Ref<AIAction> _states[EntityEnums::AI_STATE_MAX];
};

#endif
