#ifndef WORLD_EFFECT_DATA_H
#define WORLD_EFFECT_DATA_H

#include "core/resource.h"

class WorldEffectData : public Resource {
	GDCLASS(WorldEffectData, Resource);

public:
	String get_text_name();
	void set_text_name(String name);

	WorldEffectData();
	~WorldEffectData();

protected:
	static void _bind_methods();

private:
	String _text_name;
};

#endif
