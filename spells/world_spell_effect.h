#ifndef WORLD_SPELL_EFFECT_H
#define WORLD_SPELL_EFFECT_H

#include "../entities/entity.h"

class WorldSpellEffect : public Entity {
	GDCLASS(WorldSpellEffect, Entity);

public:
	WorldSpellEffect();
	~WorldSpellEffect();

protected:
	static void _bind_methods();

	//private:
};

#endif
