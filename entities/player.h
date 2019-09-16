#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

class Bag;

class Player : public Entity {
    GDCLASS(Player, Entity);

public:
	void _setup();

	Player();

protected:
	static void _bind_methods();
	
private:
	
};


#endif
