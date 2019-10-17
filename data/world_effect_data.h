#ifndef WORLD_EFFECT_DATA_H
#define WORLD_EFFECT_DATA_H

#include "core/resource.h"

class WorldEffectData : public Resource {
	GDCLASS(WorldEffectData, Resource);

public:
	String get_effect_name();
	void set_effect_name(String name);

	WorldEffectData();
	~WorldEffectData();

protected:
	static void _bind_methods();

private:
	String _effect_name;
};

#endif
