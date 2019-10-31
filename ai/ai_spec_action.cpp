#include "ai_spec_action.h"

Vector<int> AISpecAction::get_spec_distribution() {
	return _spec_distribution;
}
void AISpecAction::set_spec_distribution(Vector<int> data) {
	_spec_distribution = data;
}

int AISpecAction::get_variance() {
	return _variance;
}
void AISpecAction::set_variance(int value) {
	_variance = value;
}

Ref<AIAction> AISpecAction::get_action() {
	return _action;
}
void AISpecAction::set_action(Ref<AIAction> action) {
	_action = action;
}

AISpecAction::AISpecAction() {
	_variance = 0;
}

AISpecAction::~AISpecAction() {
	_spec_distribution.clear();
	_action.unref();
}

void AISpecAction::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_spec_distribution"), &AISpecAction::get_spec_distribution);
	ClassDB::bind_method(D_METHOD("set_spec_distribution", "value"), &AISpecAction::set_spec_distribution);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "spec_distribution"), "set_spec_distribution", "get_spec_distribution");

	ClassDB::bind_method(D_METHOD("get_variance"), &AISpecAction::get_variance);
	ClassDB::bind_method(D_METHOD("set_variance", "value"), &AISpecAction::set_variance);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "variance"), "set_variance", "get_variance");

	ClassDB::bind_method(D_METHOD("get_action"), &AISpecAction::get_action);
	ClassDB::bind_method(D_METHOD("set_action", "value"), &AISpecAction::set_action);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "action", PROPERTY_HINT_RESOURCE_TYPE, "AIAction"), "set_action", "get_action");
}
