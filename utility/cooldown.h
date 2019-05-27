#ifndef COOLDOWN_H
#define COOLDOWN_H

#include "core/reference.h"

class Cooldown : public Reference {
	GDCLASS(Cooldown, Reference);

public:
	int get_spell_id();
	void set_spell_id(int value);

	int get_remaining();
	void set_remaining(int value);
    
    bool update(float delta);

protected:
	static void _bind_methods();

private:
	int _spell_id;
	int _remaining;
};

#endif
