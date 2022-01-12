/*
Copyright (c) 2019-2022 Péter Magyar

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "entity_create_info.h"

#include "core/version.h"

#include "../data/species/species_instance.h"
#include "../entities/data/entity_data.h"
#include "../entities/entity.h"

int EntityCreateInfo::get_guid() const {
	return _guid;
}
void EntityCreateInfo::set_guid(const int value) {
	_guid = value;
}

bool EntityCreateInfo::get_networked() const {
	return _networked;
}
void EntityCreateInfo::set_networked(const bool value) {
	_networked = value;
}

int EntityCreateInfo::get_class_id() const {
	return _class_id;
}
void EntityCreateInfo::set_class_id(const int value) {
	_class_id = value;
}

int EntityCreateInfo::get_entity_player_type() {
	return _entity_player_type;
}
void EntityCreateInfo::set_entity_player_type(int value) {
	_entity_player_type = value;
}

int EntityCreateInfo::get_network_owner() const {
	return _network_owner;
}
void EntityCreateInfo::set_network_owner(const int value) {
	_network_owner = value;
}

EntityEnums::EntityController EntityCreateInfo::get_entity_controller() const {
	return _entity_controller;
}
void EntityCreateInfo::set_entity_controller(const EntityEnums::EntityController value) {
	_entity_controller = value;
}

String EntityCreateInfo::get_entity_name() const {
	return _entity_name;
}
void EntityCreateInfo::set_entity_name(const String &value) {
	_entity_name = value;
}

String EntityCreateInfo::get_node_name() const {
	return _node_name;
}
void EntityCreateInfo::set_node_name(const String &value) {
	_node_name = value;
}

int EntityCreateInfo::get_level() const {
	return _level;
}
void EntityCreateInfo::set_level(const int value) {
	_level = value;
}

int EntityCreateInfo::get_xp() const {
	return _xp;
}
void EntityCreateInfo::set_xp(const int value) {
	_xp = value;
}

Transform EntityCreateInfo::get_transform() const {
	return _transform;
}
void EntityCreateInfo::set_transform(const Transform &value) {
	_transform = value;
}

Transform2D EntityCreateInfo::get_transform2d() const {
	return _transform2d;
}
void EntityCreateInfo::set_transform2d(const Transform2D &value) {
	_transform2d = value;
}

Ref<EntityData> EntityCreateInfo::get_entity_data() const {
	return _entity_data;
}
void EntityCreateInfo::set_entity_data(const Ref<EntityData> &value) {
	_entity_data = value;
}

Ref<SpeciesInstance> EntityCreateInfo::get_species_instance() {
	return _species_instance;
}
void EntityCreateInfo::set_species_instance(const Ref<SpeciesInstance> &value) {
	_species_instance = value;
}

Dictionary EntityCreateInfo::get_serialized_data() {
	return _serialized_data;
}
void EntityCreateInfo::set_serialized_data(const Dictionary &value) {
	_serialized_data = value;
}

NodePath EntityCreateInfo::get_parent_path() const {
	return _parent_path;
}
void EntityCreateInfo::set_parent_path(const NodePath &value) {
	_parent_path = value;
}

Entity *EntityCreateInfo::get_created_entity() {
	return _created_entity;
}

void EntityCreateInfo::set_created_entity(Node *value) {
	if (!value) {
		return;
	}

	Entity *e = cast_to<Entity>(value);

	if (!e) {
		return;
	}

	_created_entity = e;
}

Dictionary EntityCreateInfo::to_dict() {
	return call("_to_dict");
}
void EntityCreateInfo::from_dict(const Dictionary &dict) {
	call("_from_dict", dict);
}

Dictionary EntityCreateInfo::_to_dict() {
	Dictionary dict;

	dict["guid"] = _guid;
	dict["networked"] = _networked;
	dict["class_id"] = _class_id;
	dict["entity_player_type"] = _entity_player_type;
	dict["network_owner"] = _network_owner;
	dict["entity_controller"] = _entity_controller;
	dict["entity_name"] = _entity_name;
	dict["level"] = _level;
	dict["xp"] = _xp;

	dict["transform"] = _transform;
	dict["transform2d"] = _transform2d;

	if (_species_instance.is_valid())
		dict["species_instance"] = _species_instance->to_dict();

	dict["serialized_data"] = _serialized_data;
	dict["parent_path"] = _parent_path;

	return dict;
}
void EntityCreateInfo::_from_dict(const Dictionary &dict) {
#if VERSION_MAJOR > 3
	ERR_FAIL_COND(dict.is_empty());
#else
	ERR_FAIL_COND(dict.empty());
#endif

	_guid = dict.get("guid", 0);
	_networked = dict.get("networked", false);
	_class_id = dict.get("class_id", 0);
	_entity_player_type = dict.get("entity_player_type", 0);
	_network_owner = dict.get("network_owner", 0);
	_entity_controller = static_cast<EntityEnums::EntityController>(static_cast<int>(dict.get("entity_controller", 0)));
	_entity_name = dict.get("entity_name", "");
	_level = dict.get("level", 0);
	_xp = dict.get("xp", 0);
	_transform = dict.get("transform", Transform());
	_transform2d = dict.get("transform2d", Transform2D());
	_species_instance = dict.get("species_instance", Ref<SpeciesInstance>());
	_serialized_data = dict.get("serialized_data", Dictionary());
	_parent_path = dict.get("parent_path", "");
}

EntityCreateInfo::EntityCreateInfo() {
	_guid = 0;
	_networked = false;
	_class_id = 0;
	_entity_player_type = 0;
	_network_owner = 0;
	_entity_controller = EntityEnums::ENITIY_CONTROLLER_NONE;
	_level = 0;
	_xp = 0;
	_created_entity = NULL;
}

EntityCreateInfo::~EntityCreateInfo() {
	_entity_data.unref();
	_species_instance.unref();
}

void EntityCreateInfo::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_guid"), &EntityCreateInfo::get_guid);
	ClassDB::bind_method(D_METHOD("set_guid", "value"), &EntityCreateInfo::set_guid);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "guid"), "set_guid", "get_guid");

	ClassDB::bind_method(D_METHOD("get_networked"), &EntityCreateInfo::get_networked);
	ClassDB::bind_method(D_METHOD("set_networked", "value"), &EntityCreateInfo::set_networked);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "networked"), "set_networked", "get_networked");

	ClassDB::bind_method(D_METHOD("get_entity_controller"), &EntityCreateInfo::get_entity_controller);
	ClassDB::bind_method(D_METHOD("set_entity_controller", "value"), &EntityCreateInfo::set_entity_controller);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "entity_controller", PROPERTY_HINT_ENUM, EntityEnums::BINDING_STRING_ENTITY_CONTOLLER), "set_entity_controller", "get_entity_controller");

	ClassDB::bind_method(D_METHOD("get_class_id"), &EntityCreateInfo::get_class_id);
	ClassDB::bind_method(D_METHOD("set_class_id", "value"), &EntityCreateInfo::set_class_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "class_id", PROPERTY_HINT_ENUM, EntityEnums::BINDING_STRING_ENTITY_CONTOLLER), "set_class_id", "get_class_id");

	ClassDB::bind_method(D_METHOD("get_entity_player_type"), &EntityCreateInfo::get_entity_player_type);
	ClassDB::bind_method(D_METHOD("set_entity_player_type", "value"), &EntityCreateInfo::set_entity_player_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "entity_player_type"), "set_entity_player_type", "get_entity_player_type");

	ClassDB::bind_method(D_METHOD("get_network_owner"), &EntityCreateInfo::get_network_owner);
	ClassDB::bind_method(D_METHOD("set_network_owner", "value"), &EntityCreateInfo::set_network_owner);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "network_owner"), "set_network_owner", "get_network_owner");

	ClassDB::bind_method(D_METHOD("get_entity_name"), &EntityCreateInfo::get_entity_name);
	ClassDB::bind_method(D_METHOD("set_entity_name", "value"), &EntityCreateInfo::set_entity_name);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "player_name"), "set_entity_name", "get_entity_name");

	ClassDB::bind_method(D_METHOD("get_node_name"), &EntityCreateInfo::get_node_name);
	ClassDB::bind_method(D_METHOD("set_node_name", "value"), &EntityCreateInfo::set_node_name);
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "node_name"), "set_node_name", "get_node_name");

	ClassDB::bind_method(D_METHOD("get_level"), &EntityCreateInfo::get_level);
	ClassDB::bind_method(D_METHOD("set_level", "value"), &EntityCreateInfo::set_level);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "level"), "set_level", "get_level");

	ClassDB::bind_method(D_METHOD("get_xp"), &EntityCreateInfo::get_xp);
	ClassDB::bind_method(D_METHOD("set_xp", "value"), &EntityCreateInfo::set_xp);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "xp"), "set_xp", "get_xp");

	ClassDB::bind_method(D_METHOD("get_transform"), &EntityCreateInfo::get_transform);
	ClassDB::bind_method(D_METHOD("set_transform", "value"), &EntityCreateInfo::set_transform);
	ADD_PROPERTY(PropertyInfo(Variant::TRANSFORM, "transform"), "set_transform", "get_transform");

	ClassDB::bind_method(D_METHOD("get_transform2d"), &EntityCreateInfo::get_transform2d);
	ClassDB::bind_method(D_METHOD("set_transform2d", "value"), &EntityCreateInfo::set_transform2d);
	ADD_PROPERTY(PropertyInfo(Variant::TRANSFORM2D, "transform2d"), "set_transform2d", "get_transform2d");

	ClassDB::bind_method(D_METHOD("get_entity_data"), &EntityCreateInfo::get_entity_data);
	ClassDB::bind_method(D_METHOD("set_entity_data", "value"), &EntityCreateInfo::set_entity_data);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "entity_data", PROPERTY_HINT_RESOURCE_TYPE, "EntityData"), "set_entity_data", "get_entity_data");

	ClassDB::bind_method(D_METHOD("get_species_instance"), &EntityCreateInfo::get_species_instance);
	ClassDB::bind_method(D_METHOD("set_species_instance", "value"), &EntityCreateInfo::set_species_instance);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "species_instance", PROPERTY_HINT_RESOURCE_TYPE, "SpeciesInstance"), "set_species_instance", "get_species_instance");

	ClassDB::bind_method(D_METHOD("get_serialized_data"), &EntityCreateInfo::get_serialized_data);
	ClassDB::bind_method(D_METHOD("set_serialized_data", "value"), &EntityCreateInfo::set_serialized_data);
	ADD_PROPERTY(PropertyInfo(Variant::DICTIONARY, "serialized_data"), "set_serialized_data", "get_serialized_data");

	ClassDB::bind_method(D_METHOD("get_parent_path"), &EntityCreateInfo::get_parent_path);
	ClassDB::bind_method(D_METHOD("set_parent_path", "value"), &EntityCreateInfo::set_parent_path);
	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "parent_path"), "set_parent_path", "get_parent_path");

	ClassDB::bind_method(D_METHOD("get_created_entity"), &EntityCreateInfo::get_created_entity);
	ClassDB::bind_method(D_METHOD("set_created_entity", "value"), &EntityCreateInfo::set_created_entity);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "created_entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), "set_created_entity", "get_created_entity");

	//Serialization
	BIND_VMETHOD(MethodInfo("_from_dict", PropertyInfo(Variant::DICTIONARY, "dict")));
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::DICTIONARY, "dict"), "_to_dict"));

	ClassDB::bind_method(D_METHOD("from_dict", "dict"), &EntityCreateInfo::from_dict);
	ClassDB::bind_method(D_METHOD("to_dict"), &EntityCreateInfo::to_dict);

	ClassDB::bind_method(D_METHOD("_from_dict", "dict"), &EntityCreateInfo::_from_dict);
	ClassDB::bind_method(D_METHOD("_to_dict"), &EntityCreateInfo::_to_dict);
}
