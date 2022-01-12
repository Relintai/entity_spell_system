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

#include "complex_level_stat_data.h"

#include "../../singletons/ess.h"

int ComplexLevelStatData::get_stat_for_level(int main_stat, int level) {
	ERR_FAIL_INDEX_V(level, ESS::get_singleton()->get_max_character_level(), 0);
	ERR_FAIL_INDEX_V(main_stat, ESS::get_singleton()->stat_get_main_stat_count(), 0);

	return _stat_per_level[level][main_stat];
}
void ComplexLevelStatData::set_stat_for_level(int main_stat, int level, int value) {
	ERR_FAIL_INDEX(level, ESS::get_singleton()->get_max_character_level());
	ERR_FAIL_INDEX(main_stat, ESS::get_singleton()->stat_get_main_stat_count());

	_stat_per_level.write[level].set(main_stat, value);
}

int ComplexLevelStatData::_get_stat_diff(int main_stat, int old_level, int new_level) {
	int s = 0;

	for (int i = old_level; i < new_level; ++i) {
		s += get_stat_for_level(main_stat, i);
	}

	return s;
}

ComplexLevelStatData::ComplexLevelStatData() {
	_stat_per_level.resize(ESS::get_singleton()->get_max_character_level());

	int msc = ESS::get_singleton()->stat_get_main_stat_count();

	for (int i = 0; i < ESS::get_singleton()->get_max_character_level(); ++i) {
		_stat_per_level.write[i].resize(msc);

		for (int j = 0; j < msc; ++j) {
			_stat_per_level.write[i].set(j, 0);
		}
	}
}

ComplexLevelStatData::~ComplexLevelStatData() {
	for (int i = 0; i < ESS::get_singleton()->get_max_character_level(); ++i) {
		_stat_per_level.write[i].clear();
	}
}

bool ComplexLevelStatData::_set(const StringName &p_name, const Variant &p_value) {
	String prop_name = p_name;

	if (prop_name.begins_with("level_")) {
		String level_prop = prop_name.get_slice("/", 0);
		int level = level_prop.get_slice("_", 1).to_int();

		if (level >= ESS::get_singleton()->get_max_character_level())
			return false;

		String prop = prop_name.get_slice("/", 1);

		if (ESS::get_singleton()->stat_is_property(prop)) {
			int stat_id = ESS::get_singleton()->stat_get_property_id(prop);

			if (stat_id >= ESS::get_singleton()->stat_get_main_stat_count()) {
				return false;
			}

			_stat_per_level.write[level].set(stat_id, p_value);

			return true;
		} else {
			return false;
		}
	}

	return false;
}

bool ComplexLevelStatData::_get(const StringName &p_name, Variant &r_ret) const {
	String prop_name = p_name;

	if (prop_name.begins_with("level_")) {
		String level_prop = prop_name.get_slice("/", 0);
		int level = level_prop.get_slice("_", 1).to_int();

		if (level >= ESS::get_singleton()->get_max_character_level())
			return false;

		String prop = prop_name.get_slice("/", 1);

		if (ESS::get_singleton()->stat_is_property(prop)) {
			int stat_id = ESS::get_singleton()->stat_get_property_id(prop);

			if (stat_id >= ESS::get_singleton()->stat_get_main_stat_count()) {
				return false;
			}

			r_ret = _stat_per_level[level].get(stat_id);

			return true;
		} else {
			return false;
		}
	}

	return false;
}

void ComplexLevelStatData::_get_property_list(List<PropertyInfo> *p_list) const {
	//int property_usange = PROPERTY_USAGE_STORAGE | PROPERTY_USAGE_INTERNAL;
	int property_usange = PROPERTY_USAGE_DEFAULT;

	int msc = ESS::get_singleton()->stat_get_main_stat_count();

	for (int i = 0; i < ESS::get_singleton()->get_max_character_level(); ++i) {
		for (int j = 0; j < msc; ++j) {
			p_list->push_back(PropertyInfo(Variant::INT, "level_" + String::num(i + 1) + "/" + ESS::get_singleton()->stat_get_property_name(j), PROPERTY_HINT_NONE, "", property_usange));
		}
	}
}

void ComplexLevelStatData::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_get_stat_diff", "stat", "old_level", "new_level"), &ComplexLevelStatData::_get_stat_diff);

	ClassDB::bind_method(D_METHOD("get_stat_for_level", "main_stat", "level"), &ComplexLevelStatData::get_stat_for_level);
	ClassDB::bind_method(D_METHOD("set_stat_for_level", "main_stat", "level", "value"), &ComplexLevelStatData::set_stat_for_level);
}
