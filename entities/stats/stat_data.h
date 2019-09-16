#ifndef STAT_DATA_H
#define STAT_DATA_H

#include "scene/resources/curve.h"
#include "core/resource.h"

#include "stat_data_entry.h"
#include "stat.h"
#include "level_stat_data.h"

class StatData : public Resource {
    GDCLASS(StatData, Resource);

public:
	Ref<StatDataEntry> get_stat_data_int(int index);
	void set_stat_data_int(int index, Ref<StatDataEntry> entry);

	Ref<StatDataEntry> get_stat_data_enum(Stat::StatId stat_id);
	void set_stat_data_enum(Stat::StatId stat_id, Ref<StatDataEntry> entry);

    Ref<LevelStatData> get_level_stat_data();
	void set_level_stat_data(Ref<LevelStatData> value);

    void get_stat_for_stat(Ref<Stat> stat);

    StatData();

protected:
    static void _bind_methods();

private:
	Ref<StatDataEntry> _entries[Stat::STAT_ID_TOTAL_STATS];

    Ref<LevelStatData> _level_stat_data;

};

#endif
