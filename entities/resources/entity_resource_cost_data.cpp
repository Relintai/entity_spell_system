#include "entity_resource_cost_data.h"

Ref<EntityResourceData> EntityResourceCostData::get_entity_resource_data() {
	return _entity_resource_data;
}
void EntityResourceCostData::set_entity_resource_data(Ref<EntityResourceData> data) {
	_entity_resource_data = data;
}

int EntityResourceCostData::get_cost() {
	return _cost;
}
void EntityResourceCostData::set_cost(int value) {
	_cost = value;
}

EntityResourceCostData::EntityResourceCostData() {
	_cost = 0;
}

void EntityResourceCostData::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_entity_resource_data"), &EntityResourceCostData::get_entity_resource_data);
	ClassDB::bind_method(D_METHOD("set_entity_resource_data", "value"), &EntityResourceCostData::set_entity_resource_data);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "entity_resource_data", PROPERTY_HINT_RESOURCE_TYPE, "EntityResourceData"), "set_entity_resource_data", "get_entity_resource_data");

	ClassDB::bind_method(D_METHOD("get_cost"), &EntityResourceCostData::get_cost);
	ClassDB::bind_method(D_METHOD("set_cost", "value"), &EntityResourceCostData::set_cost);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "cost"), "set_cost", "get_cost");
}
