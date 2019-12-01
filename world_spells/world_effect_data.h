#ifndef WORLD_EFFECT_DATA_H
#define WORLD_EFFECT_DATA_H

#include "core/resource.h"

class WorldEffectData : public Resource {
	GDCLASS(WorldEffectData, Resource);

public:
	WorldEffectData();
	~WorldEffectData();

protected:
	static void _bind_methods();

private:
};

#endif
