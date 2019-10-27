#include "ai_action.h"

#include "../entities/entity.h"

int AIAction::get_utility() const {
	return _utility;
}
void AIAction::set_utility(const int value) {
	_utility = value;
}

void AIAction::set_owner(Entity *entity) {
	_owner = entity;

	call("_on_set_owner");
}

void AIAction::set_owner_bind(Node *entity) {
	if (!entity) {
		return;
	}

	Entity *e = cast_to<Entity>(entity);

	if (!e) {
		return;
	}

	return set_owner(e);
}

Entity *AIAction::get_owner() {
	return _owner;
}

void AIAction::set_editor_description(const String &p_editor_description) {
	set_meta("_editor_description_", p_editor_description);
}
String AIAction::get_editor_description() const {
	if (has_meta("_editor_description_")) {
		return get_meta("_editor_description_");
	} else {
		return "";
	}
}

void AIAction::update(float delta) {
	ERR_FAIL_COND(!ObjectDB::instance_validate(_owner));

	if (has_method("_update"))
		call("_update", delta);
}
void AIAction::execute() {
	ERR_FAIL_COND(!ObjectDB::instance_validate(_owner));

	if (has_method("_execute"))
		call("_execute");
}

AIAction::AIAction() {
	_owner = NULL;
	_utility = 0;
}

void AIAction::_bind_methods() {
	BIND_VMETHOD(MethodInfo("_on_set_owner"));
	BIND_VMETHOD(MethodInfo("_update", PropertyInfo(Variant::REAL, "delta")));
	BIND_VMETHOD(MethodInfo( "_execute"));

	ClassDB::bind_method(D_METHOD("get_utility"), &AIAction::get_utility);
	ClassDB::bind_method(D_METHOD("set_utility", "value"), &AIAction::set_utility);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "utility", PROPERTY_HINT_NONE, "", 0), "set_utility", "get_utility");

	ClassDB::bind_method(D_METHOD("get_owner"), &AIAction::get_owner);
	ClassDB::bind_method(D_METHOD("set_owner", "entity"), &AIAction::set_owner_bind);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "owner", PROPERTY_HINT_RESOURCE_TYPE, "Entity", 0), "set_owner", "get_owner");

	ClassDB::bind_method(D_METHOD("update", "entity"), &AIAction::update);
	ClassDB::bind_method(D_METHOD("execute"), &AIAction::execute);

	ClassDB::bind_method(D_METHOD("_set_editor_description", "editor_description"), &AIAction::set_editor_description);
	ClassDB::bind_method(D_METHOD("_get_editor_description"), &AIAction::get_editor_description);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "editor_description", PROPERTY_HINT_MULTILINE_TEXT, "", PROPERTY_USAGE_EDITOR | PROPERTY_USAGE_INTERNAL), "_set_editor_description", "_get_editor_description");

}
