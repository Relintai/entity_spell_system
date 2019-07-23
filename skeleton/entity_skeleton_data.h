#ifndef ENTITY_SKELETON_DATA_H
#define ENTITY_SKELETON_DATA_H

#include "core/resource.h"
#include "core/ustring.h"

class EntitySkeletonData : public Resource {
	GDCLASS(EntitySkeletonData, Resource);

public:

protected:
	static void _bind_methods();

	enum {
		MAX_ENTRIES = 20
	};

	struct ESDataEntry {
		Ref<CharacterSkeletonVisualEntry> entry;
		Vector3 offset;
		Vector3 rotation;
		Vector3 scale;
	};

private:
	ESDataEntry _entries[MAX_ENTRIES];
};

#endif
