#ifndef COMPLEX_LEVEL_STAT_DATA_H
#define COMPLEX_LEVEL_STAT_DATA_H

#include "core/resource.h"

#include "../../entity_enums.h"
#include "level_stat_data.h"

class ComplexLevelStatData : public LevelStatData {
	GDCLASS(ComplexLevelStatData, LevelStatData);

public:
	int get_agility_for_level(int level);
	void set_agility_for_level(int level, int value);

	int get_strength_for_level(int level);
	void set_strength_for_level(int level, int value);

	int get_stamina_for_level(int level);
	void set_stamina_for_level(int level, int value);

	int get_intellect_for_level(int level);
	void set_intellect_for_level(int level, int value);

	int get_spirit_for_level(int level);
	void set_spirit_for_level(int level, int value);

	int _get_stat_diff(int stat, int old_level, int new_level);

public:
	struct ComplexLevelStatsEntry {
		int agility;
		int strength;
		int stamina;
		int intellect;
		int spirit;

		ComplexLevelStatsEntry() {
			agility = 0;
			strength = 0;
			stamina = 0;
			intellect = 0;
			spirit = 0;
		}
	};

protected:
	static void _bind_methods();

private:
	ComplexLevelStatsEntry _entries[EntityEnums::MAX_LEVEL];
};

#endif
