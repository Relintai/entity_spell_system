/*
Copyright (c) 2019-2020 Péter Magyar

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


int EntityCreateInfo::get_guid() const { 
    return _guid; 
}
void EntityCreateInfo::set_guid(const int value) { 
    _guid = value; 
}

int EntityCreateInfo::get_class_id() const {
    return _class_id;
}
void EntityCreateInfo::set_class_id(const int value) {
    _class_id = value;
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
    return _entity_name; 
}
void EntityCreateInfo::set_node_name(const String &value) { 
    _entity_name = value; 
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
    _transform =  value;
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

EntityCreateInfo::EntityCreateInfo() {
    _guid = 0;
    _class_id = 0;
    _network_owner = 0;
	_entity_controller = EntityEnums::ENITIY_CONTROLLER_NONE;
	_level = 0;
	_xp = 0;
}

EntityCreateInfo::~EntityCreateInfo() {
	_entity_data.unref();
}

void EntityCreateInfo::_bind_methods() {
		ClassDB::bind_method(D_METHOD("get_entity_controller"), &EntityCreateInfo::get_entity_controller);
		ClassDB::bind_method(D_METHOD("set_entity_controller", "value"), &EntityCreateInfo::set_entity_controller);
		ADD_PROPERTY(PropertyInfo(Variant::INT, "entity_controller", PROPERTY_HINT_ENUM, EntityEnums::BINDING_STRING_ENTITY_CONTOLLER), "set_entity_controller", "get_entity_controller");

        ClassDB::bind_method(D_METHOD("get_class_id"), &EntityCreateInfo::get_class_id);
		ClassDB::bind_method(D_METHOD("set_class_id", "value"), &EntityCreateInfo::set_class_id);
		ADD_PROPERTY(PropertyInfo(Variant::INT, "class_id", PROPERTY_HINT_ENUM, EntityEnums::BINDING_STRING_ENTITY_CONTOLLER), "set_class_id", "get_class_id");

        ClassDB::bind_method(D_METHOD("get_network_owner"), &EntityCreateInfo::get_network_owner);
		ClassDB::bind_method(D_METHOD("set_network_owner", "value"), &EntityCreateInfo::set_network_owner);
		ADD_PROPERTY(PropertyInfo(Variant::INT, "network_owner", PROPERTY_HINT_ENUM, EntityEnums::BINDING_STRING_ENTITY_CONTOLLER), "set_network_owner", "get_network_owner");

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
	}
