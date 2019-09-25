#include "ai_spell_action_container.h"

int AISpellActionContainer::get_num_ai_spell_actions() {
	return _ai_spell_actions.size();
}
void AISpellActionContainer::set_num_ai_spell_actions(int value) {
	_ai_spell_actions.resize(value);
}

Ref<AISpellAction> AISpellActionContainer::get_ai_spell_action(int index) {
	ERR_FAIL_INDEX_V(index, _ai_spell_actions.size(), Ref<AISpellAction>());

	return _ai_spell_actions[index];
}
void AISpellActionContainer::set_ai_spell_action(int index, Ref<AISpellAction> ai_spell_action) {
	ERR_FAIL_INDEX(index, _ai_spell_actions.size());

	_ai_spell_actions.set(index, ai_spell_action);
}

Vector<Variant> AISpellActionContainer::get_ai_spell_actions() {
	Vector<Variant> r;
	for (int i = 0; i < _ai_spell_actions.size(); i++) {
		r.push_back(_ai_spell_actions[i].get_ref_ptr());
	}
	return r;
}
void AISpellActionContainer::set_ai_spell_actions(const Vector<Variant> &ai_spell_actions) {
	_ai_spell_actions.clear();
	for (int i = 0; i < ai_spell_actions.size(); i++) {
		Ref<AISpellAction> ai_spell_action = Ref<AISpellAction>(ai_spell_actions[i]);

		_ai_spell_actions.push_back(ai_spell_action);
	}
}

AISpellActionContainer::AISpellActionContainer() {
}

void AISpellActionContainer::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_num_ai_spell_actions"), &AISpellActionContainer::get_num_ai_spell_actions);
	ClassDB::bind_method(D_METHOD("set_num_ai_spell_actions", "value"), &AISpellActionContainer::set_num_ai_spell_actions);

	ClassDB::bind_method(D_METHOD("get_ai_spell_action", "index"), &AISpellActionContainer::get_ai_spell_action);
	ClassDB::bind_method(D_METHOD("set_ai_spell_action", "index", "action"), &AISpellActionContainer::set_ai_spell_action);

	ClassDB::bind_method(D_METHOD("get_ai_spell_actions"), &AISpellActionContainer::get_ai_spell_actions);
	ClassDB::bind_method(D_METHOD("set_ai_spell_actions", "action"), &AISpellActionContainer::set_ai_spell_actions);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "ai_spell_actions", PROPERTY_HINT_NONE, "17/17:AISpellAction", PROPERTY_USAGE_DEFAULT, "AISpellAction"), "set_ai_spell_actions", "get_ai_spell_actions");
}
