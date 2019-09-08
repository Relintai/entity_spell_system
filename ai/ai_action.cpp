#include "ai_action.h"

#include "../entities/entity.h"

int AIAction::get_default_priority() const {
	return _default_priority;
}
void AIAction::set_default_priority(const int value) {
	_default_priority = value;
}

int AIAction::get_priority(Entity *entity) {
	return call("_get_priority");
}

int AIAction::get_priority_bind(Node *entity) {
	if (!entity) {
		return 0;
	}

	Entity *e = cast_to<Entity>(entity);

	if (!e) {
		return 0;
	}

	return get_priority(e);
}

int AIAction::_get_priority(Node *entity) {
	return _default_priority;
}

bool AIAction::should_use(Entity *entity) {
	if (has_method("_should_use")) {
		return call("_should_use", entity);
	}

	return false;
}

bool AIAction::should_use_bind(Node *entity) {
	if (!entity) {
		return false;
	}

	Entity *e = cast_to<Entity>(entity);

	if (!e) { 
		return false;
	}

	return should_use(e);
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

AIAction::AIAction() {
	_default_priority = 0;
}

void AIAction::_bind_methods() {
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::BOOL, "ret"), "_should_use", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::INT, "ret"), "_get_priority", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));

	ClassDB::bind_method(D_METHOD("get_default_priority"), &AIAction::get_default_priority);
	ClassDB::bind_method(D_METHOD("set_default_priority", "value"), &AIAction::set_default_priority);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "default_priority"), "set_default_priority", "get_default_priority");

	ClassDB::bind_method(D_METHOD("get_priority", "entity"), &AIAction::get_priority_bind);
	ClassDB::bind_method(D_METHOD("_get_priority", "entity"), &AIAction::_get_priority);

	ClassDB::bind_method(D_METHOD("should_use", "entity"), &AIAction::should_use_bind);

	ClassDB::bind_method(D_METHOD("_set_editor_description", "editor_description"), &AIAction::set_editor_description);
	ClassDB::bind_method(D_METHOD("_get_editor_description"), &AIAction::get_editor_description);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "editor_description", PROPERTY_HINT_MULTILINE_TEXT, "", PROPERTY_USAGE_EDITOR | PROPERTY_USAGE_INTERNAL), "_set_editor_description", "_get_editor_description");

}
