#include "ai_formation.h"

#include "../entities/entity.h"

void AIFormation::set_owner(Entity *entity) {
	_owner = entity;

	call("_on_set_owner");
}

void AIFormation::set_owner_bind(Node *entity) {
	if (!entity) {
		return;
	}

	Entity *e = cast_to<Entity>(entity);

	if (!e) {
		return;
	}

	return set_owner(e);
}

Entity *AIFormation::get_owner() {
	return _owner;
}

void AIFormation::set_editor_description(const String &p_editor_description) {
	set_meta("_editor_description_", p_editor_description);
}
String AIFormation::get_editor_description() const {
	if (has_meta("_editor_description_")) {
		return get_meta("_editor_description_");
	} else {
		return "";
	}
}

Vector3 AIFormation::get_position(int slot_index) {
	ERR_FAIL_COND_V(!ObjectDB::instance_validate(_owner), Vector3());

	if (has_method("_get_position"))
		return call("_get_position", slot_index);

	return Vector3();
}

AIFormation::AIFormation() {
	_owner = NULL;
}

void AIFormation::_bind_methods() {
	BIND_VMETHOD(MethodInfo("_on_set_owner"));
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::VECTOR3, "pos"), "_get_position", PropertyInfo(Variant::INT, "slot_index")));

	ClassDB::bind_method(D_METHOD("get_owner"), &AIFormation::get_owner);
	ClassDB::bind_method(D_METHOD("set_owner", "entity"), &AIFormation::set_owner_bind);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "owner", PROPERTY_HINT_RESOURCE_TYPE, "Entity", 0), "set_owner", "get_owner");

	ClassDB::bind_method(D_METHOD("get_position", "slot_index"), &AIFormation::get_position);

	ClassDB::bind_method(D_METHOD("_set_editor_description", "editor_description"), &AIFormation::set_editor_description);
	ClassDB::bind_method(D_METHOD("_get_editor_description"), &AIFormation::get_editor_description);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "editor_description", PROPERTY_HINT_MULTILINE_TEXT, "", PROPERTY_USAGE_EDITOR | PROPERTY_USAGE_INTERNAL), "_set_editor_description", "_get_editor_description");
}
