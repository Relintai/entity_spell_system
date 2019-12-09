#ifndef WORLD_SPELL_H
#define WORLD_SPELL_H

#ifdef ENTITIES_2D
#include "scene/2d/node_2d.h"
#else
#include "scene/3d/spatial.h"
#endif

#include "world_spell_data.h"

#ifdef ENTITIES_2D
class WorldSpell : public Node2D {
	GDCLASS(WorldSpell, Node2D);
#else
class WorldSpell : public Spatial {
	GDCLASS(WorldSpell, Spatial);
#endif

public:
	WorldSpell();
	~WorldSpell();

protected:
	static void _bind_methods();

private:
};

#endif
