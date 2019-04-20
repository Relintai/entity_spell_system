#ifndef ITEM_TEMPLATE_STAT_MODIFIER_H
#define ITEM_TEMPLATE_STAT_MODIFIER_H

#include "core/reference.h"
#include "../entities/stats/stat.h"

class ItemTemplateStatModifier : public Reference {
	GDCLASS(ItemTemplateStatModifier, Reference);

public:
	Stat::StatId get_stat_id();
	void set_stat_id(Stat::StatId value);

	float get_min_base_mod();
	void set_min_base_mod(float value);

	float get_max_base_mod();
	void set_max_base_mod(float value);

	float get_min_bonus_mod();
	void set_min_bonus_mod(float value);

	float get_max_bonus_mod();
	void set_max_bonus_mod(float value);

	float get_min_percent_mod();
	void set_min_percent_mod(float value);

	float get_max_percent_mod();
	void set_max_percent_mod(float value);

	float get_scaling_factor();
	void set_scaling_factor(float value);

	ItemTemplateStatModifier();

protected:
	static void _bind_methods();

private:
	Stat::StatId _stat_id;

	float _min_mod_max;
	float _max_mod_max;

	float _min_mod_precent;
	float _max_mod_precent;

	float _scaling_factor;
};

#endif
