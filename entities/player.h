#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

class Bag;

class Player : public Entity {
    GDCLASS(Player, Entity);

public:
	int gets_seed();
	void sets_seed(int value);

	int getc_seed();
	void setc_seed(int value);

	void _setup();

	Dictionary _to_dict();
	void _from_dict(const Dictionary &dict);

	Player();

protected:
	static void _bind_methods();
	
private:
	int _s_seed;
	int _c_seed;
};


#endif
