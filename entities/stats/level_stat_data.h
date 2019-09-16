#ifndef LEVEL_STAT_DATA_H
#define LEVEL_STAT_DATA_H

#include "core/resource.h"

#include "stat.h"

class LevelStatData : public Resource {
	GDCLASS(LevelStatData, Resource);

public:
	int get_stat_diff(int stat, int old_level, int new_level);

protected:
	static void _bind_methods();
};

#endif
