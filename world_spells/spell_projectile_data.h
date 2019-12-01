#ifndef SPELL_PROJECTILE_DATA_H
#define SPELL_PROJECTILE_DATA_H

#include "core/resource.h"

class SpellProjectileData : public Resource {
	GDCLASS(SpellProjectileData, Resource);

public:
	SpellProjectileData();
	~SpellProjectileData();

protected:
	static void _bind_methods();

//private:
};

#endif
