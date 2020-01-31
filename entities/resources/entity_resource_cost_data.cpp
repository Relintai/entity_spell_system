/*
Copyright (c) 2019-2020 Péter Magyar

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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
