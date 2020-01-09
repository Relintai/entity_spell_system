#include "category_cooldown.h"

int CategoryCooldown::get_category_id() const {
	return _category_id;
}

void CategoryCooldown::set_category_id(const int value) {
	_category_id = value;
}

float CategoryCooldown::get_remaining() const {
	return _remaining;
}

void CategoryCooldown::set_remaining(const float value) {
	_remaining = value;
}

bool CategoryCooldown::update(const float delta) {
	_remaining -= delta;

	if (_remaining <= 0) {
		_remaining = 0;

		return true;
	}

	return false;
}

Dictionary CategoryCooldown::to_dict() {
	return call("_to_dict");
}
void CategoryCooldown::from_dict(const Dictionary &dict) {
	call("_from_dict", dict);
}

Dictionary CategoryCooldown::_to_dict() {
	Dictionary dict;

	dict["category_id"] = _category_id;
	dict["remaining"] = _remaining;

	return dict;
}
void CategoryCooldown::_from_dict(const Dictionary &dict) {
	ERR_FAIL_COND(dict.empty());

	_category_id = dict.get("category_id", 0);
	_remaining = dict.get("remaining", 0);
}

void CategoryCooldown::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_category_id"), &CategoryCooldown::get_category_id);
	ClassDB::bind_method(D_METHOD("set_category_id", "value"), &CategoryCooldown::set_category_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "category_id"), "set_category_id", "get_category_id");

	ClassDB::bind_method(D_METHOD("get_remaining"), &CategoryCooldown::get_remaining);
	ClassDB::bind_method(D_METHOD("set_remaining", "value"), &CategoryCooldown::set_remaining);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "remaining"), "set_remaining", "get_remaining");

	ClassDB::bind_method(D_METHOD("update", "delta"), &CategoryCooldown::update);

	//Serialization
	BIND_VMETHOD(MethodInfo("_from_dict", PropertyInfo(Variant::DICTIONARY, "dict")));
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::DICTIONARY, "dict"), "_to_dict"));

	ClassDB::bind_method(D_METHOD("from_dict", "dict"), &CategoryCooldown::from_dict);
	ClassDB::bind_method(D_METHOD("to_dict"), &CategoryCooldown::to_dict);

	ClassDB::bind_method(D_METHOD("_from_dict", "dict"), &CategoryCooldown::_from_dict);
	ClassDB::bind_method(D_METHOD("_to_dict"), &CategoryCooldown::_to_dict);
}
