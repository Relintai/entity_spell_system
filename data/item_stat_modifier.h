#ifndef ITEM_STAT_MODIFIER_H
#define ITEM_STAT_MODIFIER_H

#include "core/reference.h"
#include "../entities/stats/stat.h"

class ItemStatModifier : public Reference {
	GDCLASS(ItemStatModifier, Reference);

public:
	Stat::StatId get_stat_id();
	void set_stat_id(Stat::StatId value);

	float get_base_mod();
	void set_base_mod(float value);

	float get_bonus_mod();
	void set_bonus_mod(float value);

	float get_percent_mod();
	void set_percent_mod(float value);

	Dictionary to_dict();
	void from_dict(const Dictionary &dict);

	virtual Dictionary _to_dict();
	virtual void _from_dict(const Dictionary &dict);

	ItemStatModifier();

protected:
	static void _bind_methods();

private:
	Stat::StatId _stat_id;
	float _base_mod;
	float _bonus_mod;
	float _percent_mod;
};

#endif
