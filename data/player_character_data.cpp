#include "player_character_data.h"


int PlayerCharacterData::get_id() const {
    return _id;
}
void PlayerCharacterData::set_id(const int id) {
    _id = id;
}
    
Ref<CharacterClass> PlayerCharacterData::get_character_class() const {
    return _character_class;
}
void PlayerCharacterData::set_character_class(const Ref<CharacterClass> character_class) {
    _character_class = character_class;
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
    _character_class.unref();
}

void PlayerCharacterData::_bind_methods() {
    BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::STRING, "name"), "_generate_name"));
    
    ClassDB::bind_method(D_METHOD("get_id"), &PlayerCharacterData::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "value"), &PlayerCharacterData::set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");
    
    ClassDB::bind_method(D_METHOD("get_character_class"), &PlayerCharacterData::get_character_class);
	ClassDB::bind_method(D_METHOD("set_character_class", "value"), &PlayerCharacterData::set_character_class);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "character_class", PROPERTY_HINT_RESOURCE_TYPE, "CharacterClass"), "set_character_class", "get_character_class");
    
    ClassDB::bind_method(D_METHOD("get_static_player_name"), &PlayerCharacterData::get_static_player_name);
	ClassDB::bind_method(D_METHOD("set_static_player_name", "value"), &PlayerCharacterData::set_static_player_name);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "static_player_name"), "set_static_player_name", "get_static_player_name");
}
