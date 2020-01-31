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

#include "complex_level_stat_data.h"

int ComplexLevelStatData::get_agility_for_level(int level) {
	return _entries[level].agility;
}
void ComplexLevelStatData::set_agility_for_level(int level, int value) {
	_entries[level].agility = value;
}

int ComplexLevelStatData::get_strength_for_level(int level) {
	return _entries[level].strength;
}
void ComplexLevelStatData::set_strength_for_level(int level, int value) {
	_entries[level].strength = value;
}

int ComplexLevelStatData::get_stamina_for_level(int level) {
	return _entries[level].stamina;
}
void ComplexLevelStatData::set_stamina_for_level(int level, int value) {
	_entries[level].stamina = value;
}

int ComplexLevelStatData::get_intellect_for_level(int level) {
	return _entries[level].intellect;
}
void ComplexLevelStatData::set_intellect_for_level(int level, int value) {
	_entries[level].intellect = value;
}

int ComplexLevelStatData::get_spirit_for_level(int level) {
	return _entries[level].spirit;
}
void ComplexLevelStatData::set_spirit_for_level(int level, int value) {
	_entries[level].spirit = value;
}

int ComplexLevelStatData::_get_stat_diff(int main_stat, int old_level, int new_level) {
	int s = 0;

	for (int i = old_level; i < new_level; ++i) {
		switch (main_stat) {
			case Stat::MAIN_STAT_AGILITY:
				s += get_agility_for_level(i);
				break;
			case Stat::MAIN_STAT_STRENGTH:
				s += get_strength_for_level(i);
				break;
			case Stat::MAIN_STAT_STAMINA:
				s += get_stamina_for_level(i);
				break;
			case Stat::MAIN_STAT_INTELLECT:
				s += get_intellect_for_level(i);
				break;
			case Stat::MAIN_STAT_SPIRIT:
				s += get_spirit_for_level(i);
				break;
		}
	}

	return s;
}

void ComplexLevelStatData::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_get_stat_diff", "stat", "old_level", "new_level"), &ComplexLevelStatData::_get_stat_diff);

	ClassDB::bind_method(D_METHOD("get_agility_for_level", "level"), &ComplexLevelStatData::get_agility_for_level);
	ClassDB::bind_method(D_METHOD("set_agility_for_level", "level", "value"), &ComplexLevelStatData::set_agility_for_level);

	ClassDB::bind_method(D_METHOD("get_strength_for_level", "level"), &ComplexLevelStatData::get_strength_for_level);
	ClassDB::bind_method(D_METHOD("set_strength_for_level", "level", "value"), &ComplexLevelStatData::set_strength_for_level);

	ClassDB::bind_method(D_METHOD("get_stamina_for_level", "level"), &ComplexLevelStatData::get_stamina_for_level);
	ClassDB::bind_method(D_METHOD("set_stamina_for_level", "level", "value"), &ComplexLevelStatData::set_stamina_for_level);

	ClassDB::bind_method(D_METHOD("get_intellect_for_level", "level"), &ComplexLevelStatData::get_intellect_for_level);
	ClassDB::bind_method(D_METHOD("set_intellect_for_level", "level", "value"), &ComplexLevelStatData::set_intellect_for_level);

	ClassDB::bind_method(D_METHOD("get_spirit_for_level", "level"), &ComplexLevelStatData::get_spirit_for_level);
	ClassDB::bind_method(D_METHOD("set_spirit_for_level", "level", "value"), &ComplexLevelStatData::set_spirit_for_level);

	for (int i = 0; i < EntityEnums::MAX_LEVEL; ++i) {
		ADD_GROUP("Level " + String::num(i + 1), "level_" + String::num(i + 1));
		ADD_PROPERTYI(PropertyInfo(Variant::INT, "level_" + String::num(i + 1) + "_agility"), "set_agility_for_level", "get_agility_for_level", i);
		ADD_PROPERTYI(PropertyInfo(Variant::INT, "level_" + String::num(i + 1) + "_strength"), "set_strength_for_level", "get_strength_for_level", i);
		ADD_PROPERTYI(PropertyInfo(Variant::INT, "level_" + String::num(i + 1) + "_stamina"), "set_stamina_for_level", "get_stamina_for_level", i);
		ADD_PROPERTYI(PropertyInfo(Variant::INT, "level_" + String::num(i + 1) + "_intellect"), "set_intellect_for_level", "get_intellect_for_level", i);
		ADD_PROPERTYI(PropertyInfo(Variant::INT, "level_" + String::num(i + 1) + "_spirit"), "set_spirit_for_level", "get_spirit_for_level", i);
	}
}
