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

#include "simple_level_stat_data.h"

int SimpleLevelStatData::get_agility_per_level() {
	return _agility_per_level;
}
void SimpleLevelStatData::set_agility_per_level(int value) {
	_agility_per_level = value;
}

int SimpleLevelStatData::get_strength_per_level() {
	return _strength_per_level;
}
void SimpleLevelStatData::set_strength_per_level(int value) {
	_strength_per_level = value;
}

int SimpleLevelStatData::get_stamina_per_level() {
	return _stamina_per_level;
}
void SimpleLevelStatData::set_stamina_per_level(int value) {
	_stamina_per_level = value;
}

int SimpleLevelStatData::get_intellect_per_level() {
	return _intellect_per_level;
}
void SimpleLevelStatData::set_intellect_per_level(int value) {
	_intellect_per_level = value;
}

int SimpleLevelStatData::get_spirit_per_level() {
	return _spirit_per_level;
}
void SimpleLevelStatData::set_spirit_per_level(int value) {
	_spirit_per_level = value;
}

int SimpleLevelStatData::_get_stat_diff(int main_stat, int old_level, int new_level) {
	int s = 0;

	switch (main_stat) {
		case Stat::MAIN_STAT_AGILITY:
			s = _agility_per_level;
			break;
		case Stat::MAIN_STAT_STRENGTH:
			s = _strength_per_level;
			break;
		case Stat::MAIN_STAT_STAMINA:
			s = _stamina_per_level;
			break;
		case Stat::MAIN_STAT_INTELLECT:
			s = _intellect_per_level;
			break;
		case Stat::MAIN_STAT_SPIRIT:
			s = _spirit_per_level;
			break;
	}

	s *= new_level - old_level;

	return s;
}

SimpleLevelStatData::SimpleLevelStatData() {
	_agility_per_level = 0;
	_strength_per_level = 0;
	_stamina_per_level = 0;
	_intellect_per_level = 0;
	_spirit_per_level = 0;
}

void SimpleLevelStatData::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_agility_per_level"), &SimpleLevelStatData::get_agility_per_level);
	ClassDB::bind_method(D_METHOD("set_agility_per_level", "value"), &SimpleLevelStatData::set_agility_per_level);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "agility_per_level"), "set_agility_per_level", "get_agility_per_level");

	ClassDB::bind_method(D_METHOD("get_strength_per_level"), &SimpleLevelStatData::get_strength_per_level);
	ClassDB::bind_method(D_METHOD("set_strength_per_level", "value"), &SimpleLevelStatData::set_strength_per_level);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "strength_per_level"), "set_strength_per_level", "get_strength_per_level");

	ClassDB::bind_method(D_METHOD("get_stamina_per_level"), &SimpleLevelStatData::get_stamina_per_level);
	ClassDB::bind_method(D_METHOD("set_stamina_per_level", "value"), &SimpleLevelStatData::set_stamina_per_level);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "stamina_per_level"), "set_stamina_per_level", "get_stamina_per_level");

	ClassDB::bind_method(D_METHOD("get_intellect_per_level"), &SimpleLevelStatData::get_intellect_per_level);
	ClassDB::bind_method(D_METHOD("set_intellect_per_level", "value"), &SimpleLevelStatData::set_intellect_per_level);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "intellect_per_level"), "set_intellect_per_level", "get_intellect_per_level");

	ClassDB::bind_method(D_METHOD("get_spirit_per_level"), &SimpleLevelStatData::get_spirit_per_level);
	ClassDB::bind_method(D_METHOD("set_spirit_per_level", "value"), &SimpleLevelStatData::set_spirit_per_level);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "spirit_per_level"), "set_spirit_per_level", "get_spirit_per_level");

	ClassDB::bind_method(D_METHOD("_get_stat_diff", "stat", "old_level", "new_level"), &SimpleLevelStatData::_get_stat_diff);
}
