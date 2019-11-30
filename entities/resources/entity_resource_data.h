#ifndef ENTITY_RESOURCE_DATA_H
#define ENTITY_RESOURCE_DATA_H

#include "core/resource.h"
#include "scene/main/node.h"

#include "entity_resource.h"

class EntityResourceData : public Resource {
	GDCLASS(EntityResourceData, Resource);

public:
	Ref<EntityResource> get_entity_resource_instance();

	EntityResourceData();

protected:
	static void _bind_methods();
};

#endif
