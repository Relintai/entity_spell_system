#include "ai_fsm_action.h"

EntityEnums::AIStates AIFSMAction::get_state() {
	return _state;
}
void AIFSMAction::set_state(EntityEnums::AIStates state) {
	_state = state;
}

EntityEnums::AIStates AIFSMAction::get_force_state() {
	return _force_state;
}
void AIFSMAction::set_force_state(EntityEnums::AIStates state) {
	_force_state = state;
}

Ref<AIAction> AIFSMAction::get_action(const EntityEnums::AIStates index) {
	return _states[index];
}
void AIFSMAction::set_action(const EntityEnums::AIStates index, Ref<AIAction> action) {
	_states[index] = action;
}

AIFSMAction::AIFSMAction() {
	_state = EntityEnums::AI_STATE_OFF;
	_force_state = EntityEnums::AI_STATE_OFF;
}

AIFSMAction::~AIFSMAction() {
	for (int i = 0; i < EntityEnums::AI_STATE_MAX; ++i) {
		_states[i].unref();
	}
}

void AIFSMAction::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_state"), &AIFSMAction::get_state);
	ClassDB::bind_method(D_METHOD("set_state", "state"), &AIFSMAction::set_state);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "state", PROPERTY_HINT_ENUM, "SpellCastInfo"), "set_state", "get_state");

	ClassDB::bind_method(D_METHOD("get_force_state"), &AIFSMAction::get_force_state);
	ClassDB::bind_method(D_METHOD("set_force_state", "state"), &AIFSMAction::set_force_state);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "force_state", PROPERTY_HINT_ENUM, "SpellCastInfo"), "set_force_state", "get_force_state");

	ClassDB::bind_method(D_METHOD("get_action", "index"), &AIFSMAction::get_action);
	ClassDB::bind_method(D_METHOD("set_action", "index", "action"), &AIFSMAction::set_action);

	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "action_off", PROPERTY_HINT_RESOURCE_TYPE, "AIAction"), "set_action", "get_action", EntityEnums::AI_STATE_OFF);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "action_rest", PROPERTY_HINT_RESOURCE_TYPE, "AIAction"), "set_action", "get_action", EntityEnums::AI_STATE_REST);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "action_patrol", PROPERTY_HINT_RESOURCE_TYPE, "AIAction"), "set_action", "get_action", EntityEnums::AI_STATE_PATROL);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "action_follow_path", PROPERTY_HINT_RESOURCE_TYPE, "AIAction"), "set_action", "get_action", EntityEnums::AI_STATE_FOLLOW_PATH);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "action_regenerate", PROPERTY_HINT_RESOURCE_TYPE, "AIAction"), "set_action", "get_action", EntityEnums::AI_STATE_REGENERATE);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "action_attack", PROPERTY_HINT_RESOURCE_TYPE, "AIAction"), "set_action", "get_action", EntityEnums::AI_STATE_ATTACK);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "action_pet_follow", PROPERTY_HINT_RESOURCE_TYPE, "AIAction"), "set_action", "get_action", EntityEnums::AI_STATE_PET_FOLLOW);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "action_pet_stop", PROPERTY_HINT_RESOURCE_TYPE, "AIAction"), "set_action", "get_action", EntityEnums::AI_STATE_PET_STOP);
	ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "action_pet_attack", PROPERTY_HINT_RESOURCE_TYPE, "AIAction"), "set_action", "get_action", EntityEnums::AI_STATE_PET_ATTACK);
}
