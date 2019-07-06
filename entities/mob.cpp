#include "mob.h"

EntityEnums::AIStates Mob::gets_ai_state() const {
	return _sai_state;
}
void Mob::sets_ai_state(EntityEnums::AIStates state) {
	_sai_state = state;
}

Mob::Mob() : Entity() {
	_sai_state = EntityEnums::AI_STATE_OFF;
}


void Mob::_bind_methods() {
	ClassDB::bind_method(D_METHOD("gets_ai_state"), &Mob::gets_ai_state);
	ClassDB::bind_method(D_METHOD("sets_ai_state", "value"), &Mob::sets_ai_state);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "ai_state", PROPERTY_HINT_ENUM, EntityEnums::BINDING_STRING_AI_STATES), "sets_ai_state", "gets_ai_state");
}
