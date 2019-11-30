#include "entity_resource_data.h"

Ref<EntityResource> EntityResourceData::get_entity_resource_instance() {
	if (has_method("_get_entity_resource_instance")) {
		return call("_get_entity_resource_instance");
	}

	return Ref<EntityResource>();
}

EntityResourceData::EntityResourceData() {
}

void EntityResourceData::_bind_methods() {
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::OBJECT, "res", PROPERTY_HINT_RESOURCE_TYPE, "EntityResource"), "_get_entity_resource_instance"));

	ClassDB::bind_method(D_METHOD("get_entity_resource_instance"), &EntityResourceData::get_entity_resource_instance);
}
