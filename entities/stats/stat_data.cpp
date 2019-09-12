#include "stat_data.h"

Ref<StatDataEntry> StatData::get_stat_data_int(int index) {
	ERR_FAIL_INDEX_V(index, Stat::STAT_ID_TOTAL_STATS, Ref<StatDataEntry>(NULL));

	return Ref<StatDataEntry>(_entries[index]);
}

void StatData::set_stat_data_int(int index, Ref<StatDataEntry> entry) {
	ERR_FAIL_INDEX(index, Stat::STAT_ID_TOTAL_STATS);

	_entries[index] = entry;
}

Ref<StatDataEntry> StatData::get_stat_data_enum(Stat::StatId stat_id) {
	ERR_FAIL_INDEX_V(stat_id, Stat::STAT_ID_TOTAL_STATS, Ref<StatDataEntry>(NULL));
	
	return Ref<StatDataEntry>(_entries[stat_id]);
}

void StatData::set_stat_data_enum(Stat::StatId stat_id, Ref<StatDataEntry> entry) {
	ERR_FAIL_INDEX(stat_id, Stat::STAT_ID_TOTAL_STATS);

	_entries[stat_id] = entry;
}

Ref<Curve> StatData::get_hp_scaling_data() {
	return _hp_scaling_data;
}

void StatData::set_hp_scaling_data(Ref<Curve> value) {
	_hp_scaling_data = value;
}

Ref<Curve> StatData::get_spell_scaling_data() {
	return _spell_scaling_data;
}

void StatData::set_spell_scaling_data(Ref<Curve> value) {
	_spell_scaling_data = value;
}

void StatData::get_stat_for_stat(Ref<Stat> stat) {
	Ref<StatDataEntry> sd = get_stat_data_enum(stat->get_id());

	ERR_FAIL_COND(sd == NULL);

	sd->get_stats_for_stat(stat);
}


StatData::StatData() {
	for (int i = 0; i < Stat::STAT_ID_TOTAL_STATS; ++i) {
		Ref<StatDataEntry> entry(memnew(StatDataEntry()));

		entry->set_stat_id(static_cast<Stat::StatId>(i));

		_entries[i] = Ref<StatDataEntry>(entry);
	}

	get_stat_data_enum(Stat::STAT_ID_HEALTH)->set_base(10000);
	get_stat_data_enum(Stat::STAT_ID_MANA)->set_base(100);
	get_stat_data_enum(Stat::STAT_ID_SPEED)->set_base(4.2);
	get_stat_data_enum(Stat::STAT_ID_GLOBAL_COOLDOWN)->set_base(1.5);
	get_stat_data_enum(Stat::STAT_ID_MELEE_CRIT)->set_base(5);
	get_stat_data_enum(Stat::STAT_ID_MELEE_CRIT_BONUS)->set_base(50);
	get_stat_data_enum(Stat::STAT_ID_SPELL_CRIT)->set_base(5);
	get_stat_data_enum(Stat::STAT_ID_SPELL_CRIT_BONUS)->set_base(50);
	get_stat_data_enum(Stat::STAT_ID_BLOCK)->set_base(10);
	get_stat_data_enum(Stat::STAT_ID_PARRY)->set_base(15);
	get_stat_data_enum(Stat::STAT_ID_MELEE_DAMAGE_REDUCTION)->set_base(15);

	get_stat_data_enum(Stat::STAT_ID_XP_RATE)->set_base(1);
}

void StatData::_bind_methods() {

	ClassDB::bind_method(D_METHOD("get_stat_data_int", "index"), &StatData::get_stat_data_int);
	ClassDB::bind_method(D_METHOD("set_stat_data_int", "index", "entry"), &StatData::set_stat_data_int);

	ClassDB::bind_method(D_METHOD("get_stat_data_enum", "index"), &StatData::get_stat_data_enum);
	ClassDB::bind_method(D_METHOD("set_stat_data_enum", "stat_id", "entry"), &StatData::set_stat_data_enum);

	for (int i = 0; i < Stat::STAT_ID_TOTAL_STATS; ++i) {
        ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "stat_" + itos(i + 1), PROPERTY_HINT_RESOURCE_TYPE, "StatDataEntry"), "set_stat_data_enum", "get_stat_data_enum", i);
    }

	ClassDB::bind_method(D_METHOD("get_hp_scaling_data"), &StatData::get_hp_scaling_data);
	ClassDB::bind_method(D_METHOD("set_hp_scaling_data", "value"), &StatData::set_hp_scaling_data);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "hp_scaling_data", PROPERTY_HINT_RESOURCE_TYPE, "Curve"), "set_hp_scaling_data", "get_hp_scaling_data");

	ClassDB::bind_method(D_METHOD("get_spell_scaling_data"), &StatData::get_spell_scaling_data);
	ClassDB::bind_method(D_METHOD("set_spell_scaling_data", "value"), &StatData::set_spell_scaling_data);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "spell_scaling_data", PROPERTY_HINT_RESOURCE_TYPE, "Curve"), "set_spell_scaling_data", "get_spell_scaling_data");

	//ClassDB::bind_method(D_METHOD("GetStatForStat", "stat"), &StatData::GetStatForStat);
}

