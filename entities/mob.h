#ifndef MOB_H
#define MOB_H

#include "entity.h"
#include "../entity_enums.h"

class Mob : public Entity {
	GDCLASS(Mob, Entity);

public:
	Mob();

	EntityEnums::AIStates gets_ai_state() const;
	void sets_ai_state(EntityEnums::AIStates state);

protected:
	static void _bind_methods();

private:
	EntityEnums::AIStates _sai_state;
};

#endif
