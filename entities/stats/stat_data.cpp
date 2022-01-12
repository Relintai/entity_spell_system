/*
Copyright (c) 2019-2022 Péter Magyar

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

#include "stat_data.h"

#include "../../singletons/ess.h"

float StatData::get_base(int index) {
	ERR_FAIL_INDEX_V(index, _entries.size(), 0);

	return _entries[index];
}

void StatData::set_base(int index, float entry) {
	ERR_FAIL_INDEX(index, _entries.size());

	_entries.set(index, entry);
}

Ref<LevelStatData> StatData::get_level_stat_data() {
	return _level_stat_data;
}

void StatData::set_level_stat_data(Ref<LevelStatData> value) {
	_level_stat_data = value;
}

bool StatData::has_mod_stats() {
	return _mod_stat_count > 0;
}

int StatData::get_mod_stat_count() {
	return _mod_stat_count;
}
void StatData::set_mod_stat_count(int value) {
	_mod_stat_count = value;
}

int StatData::get_target_stat_id(int index) {
	ERR_FAIL_INDEX_V(index, MAX_MOD_STATS, 0);

	return _mod_stats[index].target_stat_id;
}
void StatData::set_target_stat_id(int index, int value) {
	ERR_FAIL_INDEX(index, MAX_MOD_STATS);

	_mod_stats[index].target_stat_id = value;
}

int StatData::get_mod_stat_id(int index) {
	ERR_FAIL_INDEX_V(index, MAX_MOD_STATS, 0);

	return _mod_stats[index].stat_id;
}
void StatData::set_mod_stat_id(int index, int value) {
	ERR_FAIL_INDEX(index, MAX_MOD_STATS);

	_mod_stats[index].stat_id = value;
}

float StatData::get_mod_stat_multiplier(int index) {
	ERR_FAIL_INDEX_V(index, MAX_MOD_STATS, 1);

	return _mod_stats[index].multiplier;
}
void StatData::set_mod_stat_multiplier(int index, float value) {
	ERR_FAIL_INDEX(index, 1);

	_mod_stats[index].multiplier = value;
}

StatData::StatData() {
	//TODO remove? let properties handle this?
	_entries.resize(ESS::get_singleton()->stat_get_count());

	for (int i = 0; i < _entries.size(); ++i) {
		_entries.set(i, 0);
	}

	_mod_stat_count = 0;

	for (int i = 0; i < MAX_MOD_STATS; ++i) {
		_mod_stats[i].stat_id = 0;
		_mod_stats[i].multiplier = 0;
	}
}

StatData::~StatData() {
	_entries.clear();

	_level_stat_data.unref();
}

bool StatData::_set(const StringName &p_name, const Variant &p_value) {
	String name = p_name;

	if (name.get_slicec('/', 0) == "stat") {
		StringName prop = name.get_slicec('/', 1);

		if (ESS::get_singleton()->stat_is_property(prop)) {
			int stat_id = ESS::get_singleton()->stat_get_property_id(prop);

			if (_entries.size() < stat_id) {
				_entries.resize(stat_id + 1);
			}

			_entries.set(stat_id, p_value);

			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}

	return true;
}

bool StatData::_get(const StringName &p_name, Variant &r_ret) const {
	String name = p_name;

	if (name.get_slicec('/', 0) == "stat") {
		StringName prop = name.get_slicec('/', 1);

		if (ESS::get_singleton()->stat_is_property(prop)) {
			int stat_id = ESS::get_singleton()->stat_get_property_id(prop);

			if (_entries.size() < stat_id) {
				r_ret = 0;

				return true;
			}

			r_ret = _entries[stat_id];

			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}

	return true;
}

void StatData::_get_property_list(List<PropertyInfo> *p_list) const {
	//int property_usange = PROPERTY_USAGE_STORAGE | PROPERTY_USAGE_INTERNAL;
	int property_usange = PROPERTY_USAGE_DEFAULT;

	for (int i = 0; i < ESS::get_singleton()->stat_get_count(); ++i) {
		p_list->push_back(PropertyInfo(Variant::REAL, "stat/" + ESS::get_singleton()->stat_get_property_name(i), PROPERTY_HINT_NONE, "", property_usange));
	}
}

void StatData::_validate_property(PropertyInfo &property) const {
	String prop = property.name;
	if (prop.begins_with("ModStat_")) {
		int frame = prop.get_slicec('/', 0).get_slicec('_', 1).to_int();
		if (frame >= _mod_stat_count) {
			property.usage = 0;
		}
	}

	if (prop.ends_with("stat_id")) {
		property.hint_string = ESS::get_singleton()->stat_get_string();
	} else if (prop.ends_with("target_stat_id")) {
		property.hint_string = ESS::get_singleton()->stat_get_string();
	}
}

void StatData::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_base", "index"), &StatData::get_base);
	ClassDB::bind_method(D_METHOD("set_base", "index", "entry"), &StatData::set_base);

	ClassDB::bind_method(D_METHOD("get_level_stat_data"), &StatData::get_level_stat_data);
	ClassDB::bind_method(D_METHOD("set_level_stat_data", "value"), &StatData::set_level_stat_data);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "level_stat_data", PROPERTY_HINT_RESOURCE_TYPE, "LevelStatData"), "set_level_stat_data", "get_level_stat_data");

	ClassDB::bind_method(D_METHOD("has_mod_stats"), &StatData::has_mod_stats);

	ClassDB::bind_method(D_METHOD("get_mod_stat_count"), &StatData::get_mod_stat_count);
	ClassDB::bind_method(D_METHOD("set_mod_stat_count", "value"), &StatData::set_mod_stat_count);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "mod_stat_count", PROPERTY_HINT_RANGE, "0," + itos(MAX_MOD_STATS), PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_UPDATE_ALL_IF_MODIFIED), "set_mod_stat_count", "get_mod_stat_count");

	ClassDB::bind_method(D_METHOD("get_target_stat_id", "index"), &StatData::get_target_stat_id);
	ClassDB::bind_method(D_METHOD("set_target_stat_id", "index", "value"), &StatData::set_target_stat_id);

	ClassDB::bind_method(D_METHOD("get_mod_stat_id", "index"), &StatData::get_mod_stat_id);
	ClassDB::bind_method(D_METHOD("set_mod_stat_id", "index", "value"), &StatData::set_mod_stat_id);

	ClassDB::bind_method(D_METHOD("get_mod_stat_multiplier", "index"), &StatData::get_mod_stat_multiplier);
	ClassDB::bind_method(D_METHOD("set_mod_stat_multiplier", "index", "value"), &StatData::set_mod_stat_multiplier);

	for (int i = 0; i < MAX_MOD_STATS; i++) {
		ADD_PROPERTYI(PropertyInfo(Variant::INT, "ModStat_" + itos(i) + "/target_stat_id", PROPERTY_HINT_ENUM, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_target_stat_id", "get_target_stat_id", i);
		ADD_PROPERTYI(PropertyInfo(Variant::INT, "ModStat_" + itos(i) + "/stat_id", PROPERTY_HINT_ENUM, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_mod_stat_id", "get_mod_stat_id", i);
		ADD_PROPERTYI(PropertyInfo(Variant::REAL, "ModStat_" + itos(i) + "/multiplier", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT | PROPERTY_USAGE_INTERNAL), "set_mod_stat_multiplier", "get_mod_stat_multiplier", i);
	}
}
