#include "world_effect_data.h"

String WorldEffectData::get_effect_name() {
	return _effect_name;
}
void WorldEffectData::set_effect_name(String name) {
	_effect_name = name;
}

WorldEffectData::WorldEffectData() {
}

WorldEffectData::~WorldEffectData() {
}

void WorldEffectData::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_effect_name"), &WorldEffectData::get_effect_name);
	ClassDB::bind_method(D_METHOD("set_effect_name", "value"), &WorldEffectData::set_effect_name);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "effect_name"), "set_effect_name", "get_effect_name");
}
