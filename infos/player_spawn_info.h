#ifndef ENTITY_SPAWN_INFO_H
#define ENTITY_SPAWN_INFO_H

#include "../entities/entity.h"
#include "core/reference.h"

class EntitySpawnInfo : public Reference {
	GDCLASS(EntitySpawnInfo, Reference);

public:

	CharacterSpawnInfo();
	~CharacterSpawnInfo();


protected:
	static void _bind_methods();

private:
	int _class_id;
	int _race;
	int _skin_color_index;
	int _item_ids[20];
	int _item_color_indexes[20];
};

#endif
