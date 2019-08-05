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

protected:
	static void _bind_methods() {
		ClassDB::bind_method(D_METHOD("get_id"), &StatModifier::get_id);
		ClassDB::bind_method(D_METHOD("set_id", "value"), &StatModifier::set_id);
		ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");

		ClassDB::bind_method(D_METHOD("get_base_mod"), &StatModifier::get_base_mod);
		ClassDB::bind_method(D_METHOD("set_base_mod", "value"), &StatModifier::set_base_mod);
		ADD_PROPERTY(PropertyInfo(Variant::REAL, "base_mod"), "set_base_mod", "get_base_mod");
		
		ClassDB::bind_method(D_METHOD("get_bonus_mod"), &StatModifier::get_bonus_mod);
		ClassDB::bind_method(D_METHOD("set_bonus_mod", "value"), &StatModifier::set_bonus_mod);
		ADD_PROPERTY(PropertyInfo(Variant::REAL, "bonus_mod"), "set_bonus_mod", "get_bonus_mod");

		ClassDB::bind_method(D_METHOD("get_percent_mod"), &StatModifier::get_percent_mod);
		ClassDB::bind_method(D_METHOD("set_percent_mod", "value"), &StatModifier::set_percent_mod);
		ADD_PROPERTY(PropertyInfo(Variant::REAL, "percent_mod"), "set_percent_mod", "get_percent_mod");
	}

private:
	int _id;
	float _base_mod;
	float _bonus_mod;
	float _percent_mod;
};

#endif
