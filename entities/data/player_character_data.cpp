#include "player_character_data.h"

Ref<EntityData> PlayerCharacterData::get_entity_data() {
	return _entity_data;
}
void PlayerCharacterData::set_entity_data(Ref<EntityData> data) {
	_entity_data = data;
}

PlayerCharacterData::PlayerCharacterData() {
}
PlayerCharacterData::~PlayerCharacterData() {
}

void PlayerCharacterData::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_entity_data"), &PlayerCharacterData::get_entity_data);
	ClassDB::bind_method(D_METHOD("set_entity_data", "value"), &PlayerCharacterData::set_entity_data);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "entity_data", PROPERTY_HINT_RESOURCE_TYPE, "EntityData"), "set_entity_data", "get_entity_data");
}
