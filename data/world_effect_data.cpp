#include "world_effect_data.h"

WorldEffectData::WorldEffectData() {
}

WorldEffectData::~WorldEffectData() {
}

void WorldEffectData::_bind_methods() {
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text_name"), "set_name", "get_name");
}
