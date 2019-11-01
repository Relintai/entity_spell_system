#ifndef AURA_GROUP_H
#define AURA_GROUP_H

#include "core/resource.h"

class AuraGroup : public Resource {
	GDCLASS(AuraGroup, Resource);

public:
	AuraGroup();

protected:
	static void _bind_methods();
};

#endif
