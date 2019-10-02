#include "loot_data_base.h"

float LootDataBase::get_chance() const {
	return _chance;
}
void LootDataBase::set_chance(const float value) {
	_chance = value;
}

void LootDataBase::get_loot(Array into) {
	if (has_method("_get_loot"))
		call("_get_loot", into);
}

LootDataBase::LootDataBase() {
	_chance = 100;
}

void LootDataBase::_bind_methods() {
	BIND_VMETHOD(MethodInfo("_get_loot", PropertyInfo(Variant::ARRAY, "into")));

	ClassDB::bind_method(D_METHOD("get_loot"), &LootDataBase::get_loot);

	ClassDB::bind_method(D_METHOD("get_chance"), &LootDataBase::get_chance);
	ClassDB::bind_method(D_METHOD("set_chance", "value"), &LootDataBase::set_chance);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "chance"), "set_chance", "get_chance");
}
