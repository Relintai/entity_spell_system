#include "level_stat_data.h"

int LevelStatData::get_stat_diff(int main_stat, int old_level, int new_level) {
	if (has_method("_get_stat_diff"))
		return call("_get_stat_diff");

	return 0;
}

void LevelStatData::_bind_methods() {

	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::INT, "diff"), "_get_stat_diff", PropertyInfo(Variant::INT, "main_stat"), PropertyInfo(Variant::INT, "old_level"), PropertyInfo(Variant::INT, "new_level")));

	ClassDB::bind_method(D_METHOD("get_stat_diff", "stat", "old_level", "new_level"), &LevelStatData::get_stat_diff);
}

