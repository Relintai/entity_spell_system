#ifndef ENTITY_RESOURCE_COST_DATA_H
#define ENTITY_RESOURCE_COST_DATA_H

#include "core/resource.h"

#include "entity_resource_cost_data.h"
#include "entity_resource_data.h"

class EntityResourceCostData : public Resource {
	GDCLASS(EntityResourceCostData, Resource);

public:
	Ref<EntityResourceData> get_entity_resource_data();
	void set_entity_resource_data(Ref<EntityResourceData> data);

	int get_cost();
	void set_cost(int value);

	EntityResourceCostData();

protected:
	static void _bind_methods();

private:
	Ref<EntityResourceData> _entity_resource_data;
	int _cost;
};

#endif
