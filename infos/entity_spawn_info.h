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
	int _visual_set_id;
};

#endif
