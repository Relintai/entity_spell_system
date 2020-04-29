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

#include "stat_data.h"

#include "../../singletons/ess.h"

Ref<StatDataEntry> StatData::get_stat_data(int index) {
	ERR_FAIL_INDEX_V(index, _entries.size(), Ref<StatDataEntry>(NULL));

	return _entries[index];
}

void StatData::set_stat_data(int index, Ref<StatDataEntry> entry) {
	ERR_FAIL_INDEX(index, _entries.size());

	_entries.set(index, entry);
}

Ref<LevelStatData> StatData::get_level_stat_data() {
	return _level_stat_data;
}

void StatData::set_level_stat_data(Ref<LevelStatData> value) {
	_level_stat_data = value;
}

void StatData::get_stat_for_stat(Ref<Stat> stat) {
	Ref<StatDataEntry> sd = get_stat_data(stat->get_id());

	ERR_FAIL_COND(!sd.is_valid());

	sd->get_stats_for_stat(stat);
}

StatData::StatData() {
	//TODO remove? let properties handle this?
	_entries.resize(ESS::get_instance()->stat_get_count());

	for (int i = 0; i < _entries.size(); ++i) {
		Ref<StatDataEntry> entry(memnew(StatDataEntry()));
		_entries.set(i, Ref<StatDataEntry>(entry));
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

		if (ESS::get_instance()->stat_is_property(prop)) {
			int stat_id = ESS::get_instance()->stat_get_property_id(prop);

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

		if (ESS::get_instance()->stat_is_property(prop)) {
			int stat_id = ESS::get_instance()->stat_get_property_id(prop);

			if (_entries.size() < stat_id) {
				r_ret = Ref<StatDataEntry>();

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

	for (int i = 0; i < ESS::get_instance()->stat_get_count(); ++i) {
		p_list->push_back(PropertyInfo(Variant::OBJECT, "stat/" + ESS::get_instance()->stat_get_property_name(i), PROPERTY_HINT_RESOURCE_TYPE, "StatDataEntry", property_usange));
	}
}

void StatData::_bind_methods() {

	ClassDB::bind_method(D_METHOD("get_stat_data", "index"), &StatData::get_stat_data);
	ClassDB::bind_method(D_METHOD("set_stat_data", "index", "entry"), &StatData::set_stat_data);

	ClassDB::bind_method(D_METHOD("get_level_stat_data"), &StatData::get_level_stat_data);
	ClassDB::bind_method(D_METHOD("set_level_stat_data", "value"), &StatData::set_level_stat_data);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "level_stat_data", PROPERTY_HINT_RESOURCE_TYPE, "LevelStatData"), "set_level_stat_data", "get_level_stat_data");
}
