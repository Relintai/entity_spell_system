#ifndef MOB_H
#define MOB_H

#include "entity.h"
#include "../entity_enums.h"

class Mob : public Entity {
	GDCLASS(Mob, Entity);

public:
	Mob();

	

protected:
	static void _bind_methods();

private:
	
};

#endif
