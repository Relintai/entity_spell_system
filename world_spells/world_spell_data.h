#ifndef WORLD_SPELL_DATA_H
#define WORLD_SPELL_DATA_H

#include "core/resource.h"

class WorldSpellData : public Resource {
	GDCLASS(WorldSpellData, Resource);

public:
	WorldSpellData();
	~WorldSpellData();

protected:
	static void _bind_methods();

private:
};

#endif
