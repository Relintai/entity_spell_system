#include "item_stat_modifier.h"

Stat::StatId ItemStatModifier::get_stat_id() {
	return _stat_id;
}

void ItemStatModifier::set_stat_id(Stat::StatId value) {
	_stat_id = value;
}


float ItemStatModifier::get_base_mod() {
	return _base_mod;
}

void ItemStatModifier::set_base_mod(float value) {
	_base_mod = value;
}

float ItemStatModifier::get_bonus_mod() {
	return _bonus_mod;
}

void ItemStatModifier::set_bonus_mod(float value) {
	_bonus_mod = value;
}


float ItemStatModifier::get_percent_mod() {
	return _percent_mod;
}

void ItemStatModifier::set_percent_mod(float value) {
	_percent_mod = value;
}

Dictionary ItemStatModifier::to_dict() {
	return call("_to_dict");
}
void ItemStatModifier::from_dict(const Dictionary &dict) {
	call("_from_dict", dict);
}

Dictionary ItemStatModifier::_to_dict() {
	Dictionary dict;

	dict["stat_id"] = static_cast<int>(_stat_id);

	dict["base_mod"] = _base_mod;
	dict["bonus_mod"] = _bonus_mod;
	dict["percent_mod"] = _percent_mod;

	return dict;
}
void ItemStatModifier::_from_dict(const Dictionary &dict) {
	ERR_FAIL_COND(dict.empty());


	_stat_id = static_cast<Stat::StatId>(static_cast<int>(dict.get("stat_id", 0)));
	_base_mod = dict.get("base_mod", 0);
	_bonus_mod = dict.get("bonus_mod", 0);
	_percent_mod = dict.get("percent_mod", 0);
}

ItemStatModifier::ItemStatModifier() {
	_stat_id = Stat::STAT_ID_HEALTH;
	_base_mod = 0;
	_bonus_mod = 0;
	_percent_mod = 0;
}

void ItemStatModifier::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_stat_id"), &ItemStatModifier::get_stat_id);
	ClassDB::bind_method(D_METHOD("set_stat_id", "value"), &ItemStatModifier::set_stat_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "stat_id", PROPERTY_HINT_ENUM, Stat::STAT_BINDING_STRING), "set_stat_id", "get_stat_id");

	ClassDB::bind_method(D_METHOD("get_base_mod"), &ItemStatModifier::get_base_mod);
	ClassDB::bind_method(D_METHOD("set_base_mod", "value"), &ItemStatModifier::set_base_mod);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "base_mod"), "set_base_mod", "get_base_mod");

	ClassDB::bind_method(D_METHOD("get_bonus_mod"), &ItemStatModifier::get_bonus_mod);
	ClassDB::bind_method(D_METHOD("set_bonus_mod", "value"), &ItemStatModifier::set_bonus_mod);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "bonus_mod"), "set_bonus_mod", "get_bonus_mod");

	ClassDB::bind_method(D_METHOD("get_percent_mod"), &ItemStatModifier::get_percent_mod);
	ClassDB::bind_method(D_METHOD("set_percent_mod", "value"), &ItemStatModifier::set_percent_mod);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "percent_mod"), "set_percent_mod", "get_percent_mod");
}
