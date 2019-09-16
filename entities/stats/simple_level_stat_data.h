#ifndef SIMPLE_LEVEL_STAT_DATA_H
#define SIMPLE_LEVEL_STAT_DATA_H

#include "core/resource.h"

#include "level_stat_data.h"

class SimpleLevelStatData : public LevelStatData {
	GDCLASS(SimpleLevelStatData, LevelStatData);

public:
	int get_agility_per_level();
	void set_agility_per_level(int value);

	int get_strength_per_level();
	void set_strength_per_level(int value);

	int get_stamina_per_level();
	void set_stamina_per_level(int value);

	int get_intellect_per_level();
	void set_intellect_per_level(int value);

	int get_luck_per_level();
	void set_luck_per_level(int value);

	int _get_stat_diff(int stat, int old_level, int new_level);

	SimpleLevelStatData();

protected:
	static void _bind_methods();

private:
	int _agility_per_level;
	int _strength_per_level;
	int _stamina_per_level;
	int _intellect_per_level;
	int _luck_per_level;
};

#endif
