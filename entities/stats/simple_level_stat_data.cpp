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

#include "simple_level_stat_data.h"

#include "../../singletons/ess.h"

int SimpleLevelStatData::get_stat_per_level(int main_stat) {
	ERR_FAIL_INDEX_V(main_stat, ESS::get_singleton()->stat_get_main_stat_count(), 0);

	return _stat_per_level[main_stat];
}
void SimpleLevelStatData::set_stat_per_level(int main_stat, int value) {
	ERR_FAIL_INDEX(main_stat, ESS::get_singleton()->stat_get_main_stat_count());

	_stat_per_level.set(main_stat, value);
}

int SimpleLevelStatData::_get_stat_diff(int main_stat, int old_level, int new_level) {
	ERR_FAIL_INDEX_V(main_stat, ESS::get_singleton()->stat_get_main_stat_count(), 0);

	int s = _stat_per_level[main_stat];

	s *= new_level - old_level;

	return s;
}

SimpleLevelStatData::SimpleLevelStatData() {
	_stat_per_level.resize(ESS::get_singleton()->stat_get_main_stat_count());

	for (int i = 0; i < _stat_per_level.size(); ++i) {
		_stat_per_level.set(i, 0);
	}
}

SimpleLevelStatData::~SimpleLevelStatData() {
	_stat_per_level.clear();
}

bool SimpleLevelStatData::_set(const StringName &p_name, const Variant &p_value) {
	if (ESS::get_singleton()->stat_is_property(p_name)) {
		int stat_id = ESS::get_singleton()->stat_get_property_id(p_name);

		if (stat_id >= ESS::get_singleton()->stat_get_main_stat_count()) {
			return false;
		}

		_stat_per_level.set(stat_id, p_value);

		return true;
	}

	return false;
}

bool SimpleLevelStatData::_get(const StringName &p_name, Variant &r_ret) const {
	if (ESS::get_singleton()->stat_is_property(p_name)) {
		int stat_id = ESS::get_singleton()->stat_get_property_id(p_name);

		if (stat_id >= ESS::get_singleton()->stat_get_main_stat_count()) {
			return false;
		}

		r_ret = _stat_per_level[stat_id];

		return true;
	}

	return false;
}

void SimpleLevelStatData::_get_property_list(List<PropertyInfo> *p_list) const {
	//int property_usange = PROPERTY_USAGE_STORAGE | PROPERTY_USAGE_INTERNAL;
	int property_usange = PROPERTY_USAGE_DEFAULT;

	for (int i = 0; i < ESS::get_singleton()->stat_get_main_stat_count(); ++i) {
		p_list->push_back(PropertyInfo(Variant::INT, ESS::get_singleton()->stat_get_property_name(i), PROPERTY_HINT_NONE, "", property_usange));
	}
}

void SimpleLevelStatData::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_stat_per_level"), &SimpleLevelStatData::get_stat_per_level);
	ClassDB::bind_method(D_METHOD("set_stat_per_level", "value"), &SimpleLevelStatData::set_stat_per_level);

	ClassDB::bind_method(D_METHOD("_get_stat_diff", "stat", "old_level", "new_level"), &SimpleLevelStatData::_get_stat_diff);
}
