#ifndef STAT_DATA_ENTRY_H
#define STAT_DATA_ENTRY_H

#include "scene/resources/curve.h"
#include "core/resource.h"

#include "stat.h"
#include "level_stat_data.h"

class StatDataEntry : public Resource {
    GDCLASS(StatDataEntry, Resource);

public:
	Stat::StatId get_stat_id() { return _stat_id; }
	void set_stat_id(Stat::StatId value) { _stat_id = value; }

	float get_base() { return _base; }
	void set_base(float value) { _base = value; }

	float get_bonus() { return _bonus; }
	void set_bonus(float value) { _bonus = value; }

	float get_percent() { return _percent; }
	void set_percent(float value) { _percent = value; }

	Stat::StatModifierApplyType get_modifier_apply_type() { return _modifier_apply_type; }
	void set_modifier_apply_type(Stat::StatModifierApplyType value) { _modifier_apply_type = value; }

	bool has_dependency() { return _depends_on != Stat::STAT_ID_NONE; }

	Stat::StatId get_depends_on() { return _depends_on; }
	void set_depends_on(Stat::StatId value) { _depends_on = value; }

	Ref<LevelStatData> get_dependdency_curve() { return _dependdency_curve; }
	void set_dependdency_curve(Ref<LevelStatData> curve) { _dependdency_curve = curve; }


	void get_stats_for_stat(Ref<Stat> stat) {
		stat->set_stat_modifier_type(get_modifier_apply_type());
		stat->set_values(get_base(), get_bonus(), get_percent());
		stat->set_stat_modifier_type(get_modifier_apply_type());

		stat->set_to_max();
	}

	StatDataEntry() {
		_stat_id = Stat::STAT_ID_NONE;

		_base = 0;
		_bonus = 0;
		_percent = 100;

		_modifier_apply_type = Stat::MODIFIER_APPLY_TYPE_STANDARD;

		_depends_on = Stat::STAT_ID_NONE;
	}

protected:
    static void _bind_methods() {
		ClassDB::bind_method(D_METHOD("get_stat_id"), &StatDataEntry::get_stat_id);
		ClassDB::bind_method(D_METHOD("set_stat_id", "value"), &StatDataEntry::set_stat_id);
		ADD_PROPERTY(PropertyInfo(Variant::INT, "stat_id", PROPERTY_HINT_ENUM, Stat::STAT_BINDING_STRING), "set_stat_id", "get_stat_id");

		ClassDB::bind_method(D_METHOD("get_base"), &StatDataEntry::get_base);
		ClassDB::bind_method(D_METHOD("set_base", "value"), &StatDataEntry::set_base);
		ADD_PROPERTY(PropertyInfo(Variant::REAL, "base"), "set_base", "get_base");

		ClassDB::bind_method(D_METHOD("get_bonus"), &StatDataEntry::get_bonus);
		ClassDB::bind_method(D_METHOD("set_bonus", "value"), &StatDataEntry::set_bonus);
		ADD_PROPERTY(PropertyInfo(Variant::REAL, "bonus"), "set_bonus", "get_bonus");

		ClassDB::bind_method(D_METHOD("get_percent"), &StatDataEntry::get_percent);
		ClassDB::bind_method(D_METHOD("set_percent", "value"), &StatDataEntry::set_percent);
		ADD_PROPERTY(PropertyInfo(Variant::REAL, "percent"), "set_percent", "get_percent");

		ClassDB::bind_method(D_METHOD("get_modifier_apply_type"), &StatDataEntry::get_modifier_apply_type);
		ClassDB::bind_method(D_METHOD("set_modifier_apply_type", "value"), &StatDataEntry::set_modifier_apply_type);
		ADD_PROPERTY(PropertyInfo(Variant::INT, "modifier_apply_type", PROPERTY_HINT_ENUM, Stat::MODIFIER_APPLY_TYPE_BINDING_STRING), "set_modifier_apply_type", "get_modifier_apply_type");

		ClassDB::bind_method(D_METHOD("has_dependency"), &StatDataEntry::has_dependency);

		ClassDB::bind_method(D_METHOD("get_depends_on"), &StatDataEntry::get_depends_on);
		ClassDB::bind_method(D_METHOD("set_depends_on", "value"), &StatDataEntry::set_depends_on);
		ADD_PROPERTY(PropertyInfo(Variant::INT, "depends_on", PROPERTY_HINT_ENUM, Stat::STAT_BINDING_STRING), "set_depends_on", "get_depends_on");

		ClassDB::bind_method(D_METHOD("get_dependdency_curve"), &StatDataEntry::get_dependdency_curve);
		ClassDB::bind_method(D_METHOD("set_dependdency_curve", "value"), &StatDataEntry::set_dependdency_curve);
		ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "dependdency_curve", PROPERTY_HINT_RESOURCE_TYPE, "Curve"), "set_dependdency_curve", "get_dependdency_curve");

		ClassDB::bind_method(D_METHOD("get_stats_for_stat", "stat"), &StatDataEntry::get_stats_for_stat);
	}

private:
	Stat::StatId _stat_id;
	float _base;
	float _bonus;
	float _percent;

	Stat::StatModifierApplyType _modifier_apply_type;

	Stat::StatId _depends_on;
	Ref<Curve> _dependdency_curve;
};

#endif
