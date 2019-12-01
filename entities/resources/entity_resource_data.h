#ifndef ENTITY_RESOURCE_DATA_H
#define ENTITY_RESOURCE_DATA_H

#include "core/resource.h"
#include "scene/main/node.h"

class EntityResource;

class EntityResourceData : public Resource {
	GDCLASS(EntityResourceData, Resource);

public:
	int get_id();
	void set_id(int value);

	Ref<EntityResource> get_entity_resource_instance();

	EntityResourceData();

protected:
	static void _bind_methods();

private:
	int _id;
};

#endif
