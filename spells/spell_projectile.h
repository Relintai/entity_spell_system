#ifndef SPELL_PROJECTILE_H
#define SPELL_PROJECTILE_H

#ifdef ENTITIES_2D
#include "scene/2d/node_2d.h"
#else
#include "scene/3d/spatial.h"
#endif


#ifdef ENTITIES_2D
class SpellProjectile : public Node2D {
	GDCLASS(SpellProjectile, Node2D);
#else
class SpellProjectile : public Spatial {
	GDCLASS(SpellProjectile, Spatial);
#endif

public:
	SpellProjectile();
	~SpellProjectile();

protected:
	static void _bind_methods();
//private:
};

#endif
