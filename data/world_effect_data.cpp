#include "world_effect_data.h"

String WorldEffectData::get_text_name() {
	return _text_name;
}
void WorldEffectData::set_text_name(String name) {
	_text_name = name;
}

WorldEffectData::WorldEffectData() {
}

WorldEffectData::~WorldEffectData() {
}

void WorldEffectData::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_text_name"), &WorldEffectData::get_text_name);
	ClassDB::bind_method(D_METHOD("set_text_name", "value"), &WorldEffectData::set_text_name);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text_name"), "set_text_name", "get_text_name");
}
