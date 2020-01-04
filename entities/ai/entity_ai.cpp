#include "entity_ai.h"

#include "../entity.h"

bool EntityAI::get_enabled() {
	return _enabled;
}
void EntityAI::set_enabled(bool value) {
	_enabled = value;
}

void EntityAI::set_owner(Entity *entity) {
	if (entity == _owner)
		return;

	_owner = entity;

	call("_on_set_owner");
}

void EntityAI::set_owner_bind(Node *entity) {
	if (!entity) {
		return;
	}

	Entity *e = cast_to<Entity>(entity);

	if (!e) {
		return;
	}

	return set_owner(e);
}

Entity *EntityAI::get_owner() {
	return _owner;
}

Vector<int> EntityAI::get_spec_distribution() {
	return _spec_distribution;
}
void EntityAI::set_spec_distribution(Vector<int> data) {
	_spec_distribution = data;
}

int EntityAI::get_spec_variance() {
	return _spec_variance;
}
void EntityAI::set_spec_variance(int value) {
	_spec_variance = value;
}

EntityEnums::AIStates EntityAI::get_state() {
	return _state;
}
void EntityAI::set_state(EntityEnums::AIStates state) {
	_state = state;
}

EntityEnums::AIStates EntityAI::get_force_state() {
	return _force_state;
}
void EntityAI::set_force_state(EntityEnums::AIStates state) {
	_force_state = state;
}

void EntityAI::set_editor_description(const String &p_editor_description) {
	set_meta("_editor_description_", p_editor_description);
}
String EntityAI::get_editor_description() const {
	if (has_meta("_editor_description_")) {
		return get_meta("_editor_description_");
	} else {
		return "";
	}
}

void EntityAI::update(float delta) {
	ERR_FAIL_COND(!ObjectDB::instance_validate(_owner));

	if (has_method("_update"))
		call("_update", delta);
}
void EntityAI::pet_update(float delta) {
	ERR_FAIL_COND(!ObjectDB::instance_validate(_owner));

	if (has_method("_pet_update"))
		call("_pet_update", delta);
}


void EntityAI::move(float delta) {
	ERR_FAIL_COND(!ObjectDB::instance_validate(_owner));

	if (has_method("_move"))
		call("_move", delta);
}
void EntityAI::pet_move(float delta) {
	ERR_FAIL_COND(!ObjectDB::instance_validate(_owner));

	if (has_method("_pet_move"))
		call("_pet_move", delta);
}

void EntityAI::_on_set_owner() {
}

EntityAI::EntityAI() {
	_enabled = true;
	_owner = NULL;

	_spec_variance = 0;

	_state = EntityEnums::AI_STATE_OFF;
	_force_state = EntityEnums::AI_STATE_OFF;
}

EntityAI::~EntityAI() {
	_spec_distribution.clear();
}

void EntityAI::_bind_methods() {
	BIND_VMETHOD(MethodInfo("_on_set_owner"));

	BIND_VMETHOD(MethodInfo("_update", PropertyInfo(Variant::REAL, "delta")));
	BIND_VMETHOD(MethodInfo("_pet_update", PropertyInfo(Variant::REAL, "delta")));

	BIND_VMETHOD(MethodInfo("_move", PropertyInfo(Variant::REAL, "delta")));
	BIND_VMETHOD(MethodInfo("_pet_move", PropertyInfo(Variant::REAL, "delta")));

	ClassDB::bind_method(D_METHOD("get_enabled"), &EntityAI::get_enabled);
	ClassDB::bind_method(D_METHOD("set_enabled", "value"), &EntityAI::set_enabled);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "get_enabled"), "set_enabled", "get_enabled");

	ClassDB::bind_method(D_METHOD("get_owner"), &EntityAI::get_owner);
	ClassDB::bind_method(D_METHOD("set_owner", "entity"), &EntityAI::set_owner_bind);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "owner", PROPERTY_HINT_RESOURCE_TYPE, "Entity", 0), "set_owner", "get_owner");

	ClassDB::bind_method(D_METHOD("get_spec_distribution"), &EntityAI::get_spec_distribution);
	ClassDB::bind_method(D_METHOD("set_spec_distribution", "value"), &EntityAI::set_spec_distribution);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "spec_distribution"), "set_spec_distribution", "get_spec_distribution");

	ClassDB::bind_method(D_METHOD("get_spec_variance"), &EntityAI::get_spec_variance);
	ClassDB::bind_method(D_METHOD("set_spec_variance", "value"), &EntityAI::set_spec_variance);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "spec_variance"), "set_spec_variance", "get_spec_variance");

	ClassDB::bind_method(D_METHOD("get_state"), &EntityAI::get_state);
	ClassDB::bind_method(D_METHOD("set_state", "state"), &EntityAI::set_state);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "state", PROPERTY_HINT_ENUM, EntityEnums::BINDING_STRING_AI_STATES), "set_state", "get_state");

	ClassDB::bind_method(D_METHOD("get_force_state"), &EntityAI::get_force_state);
	ClassDB::bind_method(D_METHOD("set_force_state", "state"), &EntityAI::set_force_state);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "force_state", PROPERTY_HINT_ENUM, EntityEnums::BINDING_STRING_AI_STATES), "set_force_state", "get_force_state");

	ClassDB::bind_method(D_METHOD("_set_editor_description", "editor_description"), &EntityAI::set_editor_description);
	ClassDB::bind_method(D_METHOD("_get_editor_description"), &EntityAI::get_editor_description);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "editor_description", PROPERTY_HINT_MULTILINE_TEXT, "", PROPERTY_USAGE_EDITOR | PROPERTY_USAGE_INTERNAL), "_set_editor_description", "_get_editor_description");

	ClassDB::bind_method(D_METHOD("update", "delta"), &EntityAI::update);
	ClassDB::bind_method(D_METHOD("pet_update", "delta"), &EntityAI::pet_update);

	ClassDB::bind_method(D_METHOD("move", "delta"), &EntityAI::move);
	ClassDB::bind_method(D_METHOD("pet_move", "delta"), &EntityAI::pet_move);

	ClassDB::bind_method(D_METHOD("_on_set_owner"), &EntityAI::_on_set_owner);
}
