#ifndef ENTITY_DATA_CONTAINER_H
#define ENTITY_DATA_CONTAINER_H

#include "core/reference.h"

class EntityDataContainer : public Reference {
	GDCLASS(EntityDataContainer, Reference);

public:
	EntityDataContainer();
	~EntityDataContainer();

protected:
	static void _bind_methods();
};

#endif
