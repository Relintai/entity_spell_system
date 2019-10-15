#include "stat_data_entry.h"

Stat::StatId StatDataEntry::get_stat_id() {
	return _stat_id;
}
void StatDataEntry::set_stat_id(Stat::StatId value) {
	_stat_id = value;

	if (static_cast<int>(value) < Stat::STAT_ID_GLOBAL_COOLDOWN)
		_public = true;
}

bool StatDataEntry::get_public() {
	return _public;
}
void StatDataEntry::set_public(bool value) {
	_public = value;
}

float StatDataEntry::get_base() {
	return _base;
}
void StatDataEntry::set_base(float value) {
	_base = value;
}

float StatDataEntry::get_bonus() {
	return _bonus;
}
void StatDataEntry::set_bonus(float value) {
	_bonus = value;
}

float StatDataEntry::get_percent() {
	return _percent;
}
void StatDataEntry::set_percent(float value) {
	_percent = value;
}

Stat::StatModifierApplyType StatDataEntry::get_modifier_apply_type() {
	return _modifier_apply_type;
}
void StatDataEntry::set_modifier_apply_type(Stat::StatModifierApplyType value) {
	_modifier_apply_type = value;
}

bool StatDataEntry::has_mod_stats() {
	return _mod_stat_count > 0;
}
int StatDataEntry::get_mod_stat_count() {
	return _mod_stat_count;
}

Stat::StatId StatDataEntry::get_mod_stat_id(int index) {
	ERR_FAIL_INDEX_V(index, MAX_MOD_STATS, Stat::STAT_ID_HEALTH);

	return _mod_stats[index].stat_id;
}
void StatDataEntry::set_mod_stat_id(int index, Stat::StatId value) {
	ERR_FAIL_INDEX(index, MAX_MOD_STATS);

	_mod_stats[index].stat_id = value;
}

Ref<Curve> StatDataEntry::get_mod_stat_curve(int index) {
	ERR_FAIL_INDEX_V(index, MAX_MOD_STATS, Ref<Curve>());

	return _mod_stats[index].curve;
}
void StatDataEntry::set_mod_stat_curve(int index, Ref<Curve> curve) {
	ERR_FAIL_INDEX(index, MAX_MOD_STATS);

	_mod_stats[index].curve = curve;
}

void StatDataEntry::get_stats_for_stat(Ref<Stat> stat) {
	stat->set_stat_modifier_type(get_modifier_apply_type());

	stat->clear_modifiers();

	stat->set_public(_public);
	stat->add_modifier(0, get_base(), get_bonus(), get_percent());
	stat->set_stat_data_entry(Ref<StatDataEntry>(this));

	stat->set_to_max();
}

StatDataEntry::StatDataEntry() {
	_stat_id = Stat::STAT_ID_NONE;

	_public = false;
	_base = 0;
	_bonus = 0;
	_percent = 100;
	_mod_stat_count = 0;

	_modifier_apply_type = Stat::MODIFIER_APPLY_TYPE_STANDARD;
}

StatDataEntry::~StatDataEntry() {
	for (int i = 0; i < MAX_MOD_STATS; ++i) {
		_mod_stats[i].curve.unref();
	}
}

void StatDataEntry::_bind_methods() {
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

	ClassDB::bind_method(D_METHOD("has_mod_stats"), &StatDataEntry::has_mod_stats);
	ClassDB::bind_method(D_METHOD("get_mod_stat_count"), &StatDataEntry::get_mod_stat_count);

	ClassDB::bind_method(D_METHOD("get_mod_stat_id", "index"), &StatDataEntry::get_mod_stat_id);
	ClassDB::bind_method(D_METHOD("set_mod_stat_id", "index", "value"), &StatDataEntry::set_mod_stat_id);

	ClassDB::bind_method(D_METHOD("get_mod_stat_curve", "index"), &StatDataEntry::get_mod_stat_curve);
	ClassDB::bind_method(D_METHOD("set_mod_stat_curve", "index", "value"), &StatDataEntry::set_mod_stat_curve);

	for (int i = 0; i < MAX_MOD_STATS; i++) {
		ADD_PROPERTYI(PropertyInfo(Variant::INT, "ModStat_" + itos(i) + "/stat_id", PROPERTY_HINT_ENUM, Stat::STAT_BINDING_STRING, PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_mod_stat_id", "get_mod_stat_id", i);
		ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "ModStat_" + itos(i) + "/curve", PROPERTY_HINT_RESOURCE_TYPE, "Curve", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_mod_stat_curve", "get_mod_stat_curve", i);
	}

	ClassDB::bind_method(D_METHOD("get_stats_for_stat", "stat"), &StatDataEntry::get_stats_for_stat);
}

void StatDataEntry::_validate_property(PropertyInfo &property) const {
	String prop = property.name;
	if (prop.begins_with("ModStat_")) {
		int frame = prop.get_slicec('/', 0).get_slicec('_', 1).to_int();
		if (frame >= _mod_stat_count) {
			property.usage = 0;
		}
	}
}
