#include "ai_action_container.h"

int AIActionContainer::get_num_ai_actions() {
	return _ai_actions.size();
}
void AIActionContainer::set_num_ai_actions(int value) {
	_ai_actions.resize(value);
}

Ref<AIAction> AIActionContainer::get_ai_action(int index) {
	ERR_FAIL_INDEX_V(index, _ai_actions.size(), Ref<AIAction>());

	return _ai_actions[index];
}
void AIActionContainer::set_ai_action(int index, Ref<AIAction> ai_action) {
	ERR_FAIL_INDEX(index, _ai_actions.size());

	_ai_actions.set(index, ai_action);
}

Vector<Variant> AIActionContainer::get_ai_actions() {
	Vector<Variant> r;
	for (int i = 0; i < _ai_actions.size(); i++) {
		r.push_back(_ai_actions[i].get_ref_ptr());
	}
	return r;
}
void AIActionContainer::set_ai_actions(const Vector<Variant> &ai_actions) {
	_ai_actions.clear();
	for (int i = 0; i < ai_actions.size(); i++) {
		Ref<AIAction> ai_action = Ref<AIAction>(ai_actions[i]);

		_ai_actions.push_back(ai_action);
	}
}

AIActionContainer::AIActionContainer() {
}

void AIActionContainer::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_num_ai_actions"), &AIActionContainer::get_num_ai_actions);
	ClassDB::bind_method(D_METHOD("set_num_ai_actions", "value"), &AIActionContainer::set_num_ai_actions);

	ClassDB::bind_method(D_METHOD("get_ai_action", "index"), &AIActionContainer::get_ai_action);
	ClassDB::bind_method(D_METHOD("set_ai_action", "index", "action"), &AIActionContainer::set_ai_action);

	ClassDB::bind_method(D_METHOD("get_ai_actions"), &AIActionContainer::get_ai_actions);
	ClassDB::bind_method(D_METHOD("set_ai_actions", "auras"), &AIActionContainer::set_ai_actions);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "ai_actions", PROPERTY_HINT_NONE, "17/17:AIAction", PROPERTY_USAGE_DEFAULT, "AIAction"), "set_ai_actions", "get_ai_actions");
}
