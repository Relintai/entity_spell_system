#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"



class Bag;

class Player : public Entity {
    GDCLASS(Player, Entity);

public:
	

	////     Profiles    ////

	//Ref<InputProfile> get_input_profile();

	void _setup();

	Player();
	~Player();

protected:
	static void _bind_methods();
	
private:
	

	//Ref<InputProfile> _input_profile;
};


#endif
