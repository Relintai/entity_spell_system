#include "mob_data.h"

int MobData::get_id() const {
    return _id;
}
void MobData::set_id(const int id) {
    _id = id;
}
    
Ref<LootDataBase> MobData::get_loot_db() const {
    return _lootdb;
}
void MobData::set_loot_db(const Ref<LootDataBase> lootdb) {
    _lootdb = lootdb;
}
    
Ref<EntityData> MobData::get_entity_data() const {
    return _entity_data;
}
void MobData::set_entity_data(const Ref<EntityData> entity_data) {
    _entity_data = entity_data;
}

String MobData::get_player_name() {
    if (has_method("_generate_name")) {
        return call("_generate_name");
    }
    
    return _static_player_name;
}

String MobData::get_static_player_name() const {
    return _static_player_name;
}
void MobData::set_static_player_name(const String name) {
    _static_player_name = name;
}
    
MobData::MobData() {
    _id = 0;
}
MobData::~MobData() {
    _lootdb.unref();
    _entity_data.unref();
}

void MobData::_bind_methods() {
    BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::STRING, "name"), "_generate_name"));
    
    ClassDB::bind_method(D_METHOD("get_id"), &MobData::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "value"), &MobData::set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");
    
    ClassDB::bind_method(D_METHOD("get_loot_db"), &MobData::get_loot_db);
	ClassDB::bind_method(D_METHOD("set_loot_db", "value"), &MobData::set_loot_db);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "loot_db", PROPERTY_HINT_RESOURCE_TYPE, "LootDataBase"), "set_loot_db", "get_loot_db");
    
    ClassDB::bind_method(D_METHOD("get_entity_data"), &MobData::get_entity_data);
	ClassDB::bind_method(D_METHOD("set_entity_data", "value"), &MobData::set_entity_data);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "entity_data", PROPERTY_HINT_RESOURCE_TYPE, "EntityData"), "set_entity_data", "get_entity_data");
    
    ClassDB::bind_method(D_METHOD("get_static_player_name"), &MobData::get_static_player_name);
	ClassDB::bind_method(D_METHOD("set_static_player_name", "value"), &MobData::set_static_player_name);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "static_player_name"), "set_static_player_name", "get_static_player_name");
}
