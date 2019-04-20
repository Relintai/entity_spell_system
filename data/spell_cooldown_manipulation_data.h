#ifndef SPELL_COOLDOWN_MANIPULATION_DATA_H
#define SPELL_COOLDOWN_MANIPULATION_DATA_H

#include "core/reference.h"

class SpellCooldownManipulationData : public Reference {
	GDCLASS(SpellCooldownManipulationData, Reference);

public:
	void set_id() {}

	SpellCooldownManipulationData() {
		_spell_id = 0;
		_mod_value = 0;
		_remove_if_exists = false;
		_add_if_not_exists = false;
	}

protected:
	static void _bind_methods() {
	}

private:
	int _spell_id;
	int _mod_value;
	bool _remove_if_exists;
	bool _add_if_not_exists;
};

#endif
