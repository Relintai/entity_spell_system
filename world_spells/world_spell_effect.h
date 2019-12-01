#ifndef WORLD_SPELL_EFFECT_H
#define WORLD_SPELL_EFFECT_H

#ifdef ENTITIES_2D
#include "scene/2d/node_2d.h"
#else
#include "scene/3d/spatial.h"
#endif

//#include "../entities/entity.h"

#ifdef ENTITIES_2D
class WorldSpellEffect : public Node2D {
	GDCLASS(WorldSpellEffect, Node2D);
#else
class WorldSpellEffect : public Spatial {
	GDCLASS(WorldSpellEffect, Spatial);
#endif

public:
	WorldSpellEffect();
	~WorldSpellEffect();

protected:
	static void _bind_methods();

private:
};

#endif
