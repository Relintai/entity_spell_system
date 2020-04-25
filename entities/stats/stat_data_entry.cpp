/*
Copyright (c) 2019-2020 Péter Magyar

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "stat_data_entry.h"

#include "core/version.h"

#include "../../singletons/ess.h"

#if VERSION_MAJOR >= 4
#define REAL FLOAT
#endif

int StatDataEntry::get_stat_id() {
	return _stat_id;
}
void StatDataEntry::set_stat_id(int value) {
	_stat_id = value;

	//if (value < Stat::STAT_ID_GLOBAL_COOLDOWN) TODO
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
void StatDataEntry::set_mod_stat_count(int value) {
	_mod_stat_count = value;
}

int StatDataEntry::get_mod_stat_id(int index) {
	ERR_FAIL_INDEX_V(index, MAX_MOD_STATS, 0);

	return _mod_stats[index].stat_id;
}
void StatDataEntry::set_mod_stat_id(int index, int value) {
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

float StatDataEntry::get_mod_stat_max_value(int index) {
	ERR_FAIL_INDEX_V(index, MAX_MOD_STATS, 1);

	return _mod_stats[index].max_value;
}
void StatDataEntry::set_mod_stat_max_value(int index, float value) {
	ERR_FAIL_INDEX(index, 1);

	_mod_stats[index].max_value = value;
}

void StatDataEntry::get_stats_for_stat(Ref<Stat> stat) {
	stat->set_stat_modifier_type(get_modifier_apply_type());

	stat->clear_modifiers();

	stat->set_public(_public);
	stat->add_modifier(0, get_base(), get_bonus(), get_percent());
	stat->set_stat_data_entry(Ref<StatDataEntry>(this));
}

StatDataEntry::StatDataEntry() {
	_stat_id = 0;

	_public = false;
	_base = 0;
	_bonus = 0;
	_percent = 100;
	_mod_stat_count = 0;

	_modifier_apply_type = Stat::MODIFIER_APPLY_TYPE_STANDARD;

	for (int i = 0; i < MAX_MOD_STATS; ++i) {
		_mod_stats[i].stat_id = 0;
		_mod_stats[i].max_value = 1000;
	}
}

StatDataEntry::~StatDataEntry() {
	for (int i = 0; i < MAX_MOD_STATS; ++i) {
		_mod_stats[i].curve.unref();
	}
}

void StatDataEntry::_validate_property(PropertyInfo &property) const {
	String prop = property.name;
	if (prop.begins_with("ModStat_")) {
		int frame = prop.get_slicec('/', 0).get_slicec('_', 1).to_int();
		if (frame >= _mod_stat_count) {
			property.usage = 0;
		}
	}

	if (prop.ends_with("stat_id")) {
		property.hint_string = ESS::get_instance()->stat_get_string();
	}
}

void StatDataEntry::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_stat_id"), &StatDataEntry::get_stat_id);
	ClassDB::bind_method(D_METHOD("set_stat_id", "value"), &StatDataEntry::set_stat_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "stat_id", PROPERTY_HINT_ENUM, ""), "set_stat_id", "get_stat_id");

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
	ClassDB::bind_method(D_METHOD("set_mod_stat_count", "value"), &StatDataEntry::set_mod_stat_count);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "mod_stat_count", PROPERTY_HINT_RANGE, "0," + itos(MAX_MOD_STATS), PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED), "set_mod_stat_count", "get_mod_stat_count");

	ClassDB::bind_method(D_METHOD("get_mod_stat_id", "index"), &StatDataEntry::get_mod_stat_id);
	ClassDB::bind_method(D_METHOD("set_mod_stat_id", "index", "value"), &StatDataEntry::set_mod_stat_id);

	ClassDB::bind_method(D_METHOD("get_mod_stat_curve", "index"), &StatDataEntry::get_mod_stat_curve);
	ClassDB::bind_method(D_METHOD("set_mod_stat_curve", "index", "value"), &StatDataEntry::set_mod_stat_curve);

	ClassDB::bind_method(D_METHOD("get_mod_stat_max_value", "index"), &StatDataEntry::get_mod_stat_max_value);
	ClassDB::bind_method(D_METHOD("set_mod_stat_max_value", "index", "value"), &StatDataEntry::set_mod_stat_max_value);

	for (int i = 0; i < MAX_MOD_STATS; i++) {
		ADD_PROPERTYI(PropertyInfo(Variant::INT, "ModStat_" + itos(i) + "/stat_id", PROPERTY_HINT_ENUM, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_mod_stat_id", "get_mod_stat_id", i);
		ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "ModStat_" + itos(i) + "/curve", PROPERTY_HINT_RESOURCE_TYPE, "Curve", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_mod_stat_curve", "get_mod_stat_curve", i);
		ADD_PROPERTYI(PropertyInfo(Variant::REAL, "ModStat_" + itos(i) + "/max_value", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_mod_stat_max_value", "get_mod_stat_max_value", i);
	}

	ClassDB::bind_method(D_METHOD("get_stats_for_stat", "stat"), &StatDataEntry::get_stats_for_stat);
}
