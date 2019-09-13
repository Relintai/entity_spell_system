#ifndef STAT_MODIFIER_H
#define STAT_MODIFIER_H

#include "core/reference.h"

class StatModifier : public Reference {
	GDCLASS(StatModifier, Reference);

public:
	StatModifier() {
		_id = 0;
		_base_mod = 0;
		_bonus_mod = 0;
		_percent_mod = 0;
	}

	StatModifier(int i, float base_mod, float bonus_mod, float percent_mod) {
		_id = i;
		_base_mod = base_mod;
		_bonus_mod = bonus_mod;
		_percent_mod = percent_mod;
	}

	int get_id() { return _id; }
	void set_id(int value) { _id = value; }
	
	float get_base_mod() { return _base_mod; }
	void set_base_mod(float value) { _base_mod = value; }
	
	float get_bonus_mod() { return _bonus_mod; }
	void set_bonus_mod(float value) { _bonus_mod = value; }
	
	float get_percent_mod() { return _percent_mod; }
	void set_percent_mod(float value) { _percent_mod = value; }

	Dictionary to_dict();
	void from_dict(const Dictionary &dict);

	Dictionary _to_dict();
	void _from_dict(const Dictionary &dict);

protected:
	static void _bind_methods();

private:
	int _id;
	float _base_mod;
	float _bonus_mod;
	float _percent_mod;
};

#endif
