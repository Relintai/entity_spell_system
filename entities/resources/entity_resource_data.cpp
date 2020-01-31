#include "entity_resource_data.h"

#include "entity_resource.h"

int EntityResourceData::get_id() const {
	return _id;
}
void EntityResourceData::set_id(const int value) {
	_id = value;
}

String EntityResourceData::get_text_description() const {
	return _text_description;
}
void EntityResourceData::set_text_description(const String value) {
	_text_description = value;
}

Ref<EntityResource> EntityResourceData::get_entity_resource_instance() {
	if (has_method("_get_entity_resource_instance")) {
		return call("_get_entity_resource_instance");
	}

	return Ref<EntityResource>();
}

EntityResourceData::EntityResourceData() {
	_id = 0;
}

void EntityResourceData::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_id"), &EntityResourceData::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "value"), &EntityResourceData::set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");

	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::OBJECT, "res", PROPERTY_HINT_RESOURCE_TYPE, "EntityResource"), "_get_entity_resource_instance"));

	ClassDB::bind_method(D_METHOD("get_entity_resource_instance"), &EntityResourceData::get_entity_resource_instance);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text_name"), "set_name", "get_name");

	ClassDB::bind_method(D_METHOD("get_text_description"), &EntityResourceData::get_text_description);
	ClassDB::bind_method(D_METHOD("set_text_description", "value"), &EntityResourceData::set_text_description);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text_description", PROPERTY_HINT_MULTILINE_TEXT), "set_text_description", "get_text_description");
}
