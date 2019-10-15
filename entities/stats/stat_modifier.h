#ifndef STAT_MODIFIER_H
#define STAT_MODIFIER_H

#include "core/reference.h"

class Stat;

class StatModifier : public Reference {
	GDCLASS(StatModifier, Reference);

public:
	StatModifier();

	StatModifier(int i, float base_mod, float bonus_mod, float percent_mod, Stat *owner);

	Ref<Stat> get_owner();
	void set_owner(Ref<Stat> stat);

	int get_id();
	void set_id(int value);
	
	float get_base_mod();
	void set_base_mod(float value);
	
	float get_bonus_mod();
	void set_bonus_mod(float value);
	
	float get_percent_mod();
	void set_percent_mod(float value);

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

	Stat *_owner;
};

#endif
