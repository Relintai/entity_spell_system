#include "stat_modifier.h"

Dictionary StatModifier::to_dict() {
	return call("_to_dict");
}
void StatModifier::from_dict(const Dictionary &dict) {
	call("_from_dict", dict);
}

Dictionary StatModifier::_to_dict() {
	Dictionary dict;

	dict["id"] = _id;
	dict["base_mod"] = _base_mod;
	dict["bonus_mod"] = _bonus_mod;
	dict["percent_mod"] = _percent_mod;

	return dict;
}
void StatModifier::_from_dict(const Dictionary &dict) {
	ERR_FAIL_COND(dict.empty());
}

void StatModifier::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_id"), &StatModifier::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "value"), &StatModifier::set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");

	ClassDB::bind_method(D_METHOD("get_base_mod"), &StatModifier::get_base_mod);
	ClassDB::bind_method(D_METHOD("set_base_mod", "value"), &StatModifier::set_base_mod);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "base_mod"), "set_base_mod", "get_base_mod");

	ClassDB::bind_method(D_METHOD("get_bonus_mod"), &StatModifier::get_bonus_mod);
	ClassDB::bind_method(D_METHOD("set_bonus_mod", "value"), &StatModifier::set_bonus_mod);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "bonus_mod"), "set_bonus_mod", "get_bonus_mod");

	ClassDB::bind_method(D_METHOD("get_percent_mod"), &StatModifier::get_percent_mod);
	ClassDB::bind_method(D_METHOD("set_percent_mod", "value"), &StatModifier::set_percent_mod);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "percent_mod"), "set_percent_mod", "get_percent_mod");

	//Serialization

	BIND_VMETHOD(MethodInfo("_from_dict", PropertyInfo(Variant::DICTIONARY, "dict")));
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::DICTIONARY, "dict"), "_to_dict"));

	ClassDB::bind_method(D_METHOD("from_dict", "dict"), &StatModifier::from_dict);
	ClassDB::bind_method(D_METHOD("to_dict"), &StatModifier::to_dict);

	ClassDB::bind_method(D_METHOD("_from_dict", "dict"), &StatModifier::_from_dict);
	ClassDB::bind_method(D_METHOD("_to_dict"), &StatModifier::_to_dict);
}
