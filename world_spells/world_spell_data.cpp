#include "world_spell_data.h"

WorldSpellData::WorldSpellData() {
}

WorldSpellData::~WorldSpellData() {
}

void WorldSpellData::_bind_methods() {
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "text_name"), "set_name", "get_name");
}
