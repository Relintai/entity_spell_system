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
