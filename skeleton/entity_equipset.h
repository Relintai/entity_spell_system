#ifndef ENTITY_EQUIPSET_H
#define ENTITY_EQUIPSET_H

#include "core/resource.h"
#include "core/ustring.h"

class EntityEquipSet : public Resource {
	GDCLASS(EntityEquipSet, Resource);

public:
protected:
	static void _bind_methods();

	enum {
		MAX_ENTRIES = 20
	};

private:
	Ref<CharacterSkeletonVisualEntry> _entries[MAX_ENTRIES];
};

#endif
