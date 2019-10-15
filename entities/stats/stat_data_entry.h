#ifndef STAT_DATA_ENTRY_H
#define STAT_DATA_ENTRY_H

#include "core/resource.h"
#include "scene/resources/curve.h"

#include "level_stat_data.h"
#include "stat.h"

class StatDataEntry : public Resource {
	GDCLASS(StatDataEntry, Resource);

public:
	Stat::StatId get_stat_id();
	void set_stat_id(Stat::StatId value);

	bool get_public();
	void set_public(bool value);

	float get_base();
	void set_base(float value);

	float get_bonus();
	void set_bonus(float value);

	float get_percent();
	void set_percent(float value);

	Stat::StatModifierApplyType get_modifier_apply_type();
	void set_modifier_apply_type(Stat::StatModifierApplyType value);

	bool has_mod_stats();
	int get_mod_stat_count();

	Stat::StatId get_mod_stat_id(int index);
	void set_mod_stat_id(int index, Stat::StatId value);

	Ref<Curve> get_mod_stat_curve(int index);
	void set_mod_stat_curve(int index, Ref<Curve> curve);

	void get_stats_for_stat(Ref<Stat> stat);

	StatDataEntry();
	~StatDataEntry();

protected:
	static void _bind_methods();
	void _validate_property(PropertyInfo &property) const;

public:
	struct ModStat {
		Stat::StatId stat_id;
		Ref<Curve> curve;
	};

	enum {
		MAX_MOD_STATS = 3,
	};

private:
	Stat::StatId _stat_id;
	bool _public;
	float _base;
	float _bonus;
	float _percent;

	int _mod_stat_count;
	ModStat _mod_stats[MAX_MOD_STATS];

	Stat::StatModifierApplyType _modifier_apply_type;
};

#endif
