#ifndef ENTITY_CREATE_INFO_H
#define ENTITY_CREATE_INFO_H

#include "core/reference.h"
#include "core/ustring.h"
#include "../entity_enums.h"
#include "../entities/data/entity_data.h"

class EntityCreateInfo : public Reference {
	GDCLASS(EntityCreateInfo, Reference);

public:
	int get_guid() { return _guid; }
	void set_guid(int value) { _guid = value; }

	EntityEnums::EntityController get_entity_controller() { return _entity_controller; }
	void set_entity_controller(EntityEnums::EntityController value) { _entity_controller = value; }

	String get_entity_name() { return _entity_name; }
	void set_entity_name(String value) { _entity_name = value; }

	int get_level() { return _level; }
	void set_level(int value) { _level = value; }

	int get_xp() { return _xp; }
	void set_xp(int value) { _xp = value; }

	Ref<EntityData> get_entity_data() { return _entity_data; }
	void set_entity_data(Ref<EntityData> value) { _entity_data = value; }

protected:
	static void _bind_methods() {
		ClassDB::bind_method(D_METHOD("get_entity_controller"), &EntityCreateInfo::get_entity_controller);
		ClassDB::bind_method(D_METHOD("set_entity_controller", "value"), &EntityCreateInfo::set_entity_controller);
		ADD_PROPERTY(PropertyInfo(Variant::INT, "entity_controller", PROPERTY_HINT_ENUM, EntityEnums::BINDING_STRING_ENTITY_CONTOLLER), "set_entity_controller", "get_entity_controller");

		ClassDB::bind_method(D_METHOD("get_entity_name"), &EntityCreateInfo::get_entity_name);
		ClassDB::bind_method(D_METHOD("set_entity_name", "value"), &EntityCreateInfo::set_entity_name);
		ADD_PROPERTY(PropertyInfo(Variant::STRING, "player_name"), "set_entity_name", "get_entity_name");

		ClassDB::bind_method(D_METHOD("get_level"), &EntityCreateInfo::get_level);
		ClassDB::bind_method(D_METHOD("set_level", "value"), &EntityCreateInfo::set_level);
		ADD_PROPERTY(PropertyInfo(Variant::STRING, "level"), "set_level", "get_level");

		ClassDB::bind_method(D_METHOD("get_xp"), &EntityCreateInfo::get_xp);
		ClassDB::bind_method(D_METHOD("set_xp", "value"), &EntityCreateInfo::set_xp);
		ADD_PROPERTY(PropertyInfo(Variant::STRING, "xp"), "set_xp", "get_xp");
		
		ClassDB::bind_method(D_METHOD("get_entity_data"), &EntityCreateInfo::get_entity_data);
		ClassDB::bind_method(D_METHOD("set_entity_data", "value"), &EntityCreateInfo::set_entity_data);
		ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "entity_data", PROPERTY_HINT_RESOURCE_TYPE, "EntityData"), "set_entity_data", "get_entity_data");
	}

private:
	int _guid;
	EntityEnums::EntityController _entity_controller;
	String _entity_name;
	int _level;
	int _xp;

	Ref<EntityData> _entity_data;
};

#endif
