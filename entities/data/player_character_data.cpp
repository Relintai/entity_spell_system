#include "player_character_data.h"


int PlayerCharacterData::get_id() const {
    return _id;
}
void PlayerCharacterData::set_id(const int id) {
    _id = id;
}
    
Ref<EntityData> PlayerCharacterData::get_entity_data() const {
    return _entity_data;
}
void PlayerCharacterData::set_entity_data(const Ref<EntityData> entity_data) {
    _entity_data = entity_data;
}

String PlayerCharacterData::get_player_name() {
    if (has_method("_generate_name")) {
        return call("_generate_name");
    }
    
    return _static_player_name;
}

String PlayerCharacterData::get_static_player_name() const {
    return _static_player_name;
}
void PlayerCharacterData::set_static_player_name(const String name) {
    _static_player_name = name;
}
    
PlayerCharacterData::PlayerCharacterData() {
    _id = 0;
}
PlayerCharacterData::~PlayerCharacterData() {
    _entity_data.unref();
}

void PlayerCharacterData::_bind_methods() {
    BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::STRING, "name"), "_generate_name"));
    
    ClassDB::bind_method(D_METHOD("get_id"), &PlayerCharacterData::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "value"), &PlayerCharacterData::set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");
    
    ClassDB::bind_method(D_METHOD("get_entity_data"), &PlayerCharacterData::get_entity_data);
	ClassDB::bind_method(D_METHOD("set_entity_data", "value"), &PlayerCharacterData::set_entity_data);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "entity_data", PROPERTY_HINT_RESOURCE_TYPE, "EntityData"), "set_entity_data", "get_entity_data");
    
    ClassDB::bind_method(D_METHOD("get_static_player_name"), &PlayerCharacterData::get_static_player_name);
	ClassDB::bind_method(D_METHOD("set_static_player_name", "value"), &PlayerCharacterData::set_static_player_name);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "static_player_name"), "set_static_player_name", "get_static_player_name");
}
