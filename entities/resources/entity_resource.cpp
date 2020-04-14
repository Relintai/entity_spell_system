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

#include "entity_resource.h"

#include "../../database/ess_resource_db.h"
#include "../../singletons/ess.h"
#include "../entity.h"
#include "../stats/stat.h"
#include "entity_resource_data.h"

bool EntityResource::get_dirty() const {
	return _dirty;
}
void EntityResource::set_dirty(const bool value) {
	_dirty = value;
}

bool EntityResource::get_should_process() const {
	return _should_process;
}
void EntityResource::set_should_process(const bool value) {
	_should_process = value;
}

Ref<EntityResourceData> EntityResource::get_resource_data() {
	return _data;
}
void EntityResource::set_resource_data(const Ref<EntityResourceData> &value) {
	_data = value;

	_dirty = true;

	emit_signal("changed", Ref<EntityResource>(this));
}

int EntityResource::get_data_id() const {
	return _data_id;
}
void EntityResource::set_data_id(const int value) {
	_data_id = value;

	_dirty = true;

	emit_signal("changed", Ref<EntityResource>(this));
}

int EntityResource::get_current_value() const {
	return _current;
}
void EntityResource::set_current_value(const int value) {
	_current = value;

	_dirty = true;

	emit_signal("changed", Ref<EntityResource>(this));
}

int EntityResource::get_max_value() const {
	return _max;
}
void EntityResource::set_max_value(const int value) {
	_max = value;

	_dirty = true;

	emit_signal("changed", Ref<EntityResource>(this));
}

Entity *EntityResource::get_owner() {
	return _owner;
}
void EntityResource::set_owner(Entity *value) {
	_owner = value;
}
void EntityResource::set_owner_bind(Node *owner) {
	if (!owner) {
		return;
	}

	Entity *e = cast_to<Entity>(owner);

	if (!e) {
		return;
	}

	_owner = e;
}

void EntityResource::ons_added(Entity *owner) {
	_owner = owner;

	if (has_method("_ons_added"))
		call("_ons_added", owner);
}
void EntityResource::onc_added(Entity *owner) {
	_owner = owner;

	if (has_method("_onc_added"))
		call("_onc_added", owner);
}

void EntityResource::ons_stat_changed(Ref<Stat> stat) {
	if (has_method("_ons_stat_changed"))
		call("_ons_stat_changed", stat);
}
void EntityResource::onc_stat_changed(Ref<Stat> stat) {
	if (has_method("_onc_stat_changed"))
		call("_onc_stat_changed", stat);
}

void EntityResource::ons_target_changed(Entity *entity, Entity *old_target) {
	if (has_method("_ons_target_changed"))
		call("_ons_target_changed", entity, old_target);
}
void EntityResource::onc_target_changed(Entity *entity, Entity *old_target) {
	if (has_method("_ons_target_changed"))
		call("_ons_target_changed", entity, old_target);
}

void EntityResource::process_server(const float delta) {
	call("_process_server", delta);
}
void EntityResource::_process_server(const float delta) {
}

void EntityResource::process_client(const float delta) {
	call("_process_client", delta);
}
void EntityResource::_process_client(const float delta) {
}

void EntityResource::receivec_update(const int current) {
	_current = current;
}
void EntityResource::receivec_update_full(const int current, const int max) {
	_current = current;
	_max = max;
}
void EntityResource::receivec_update_string(const String str) {
	if (has_method("_receivec_update_string"))
		call("_receivec_update_string", str);
}

void EntityResource::resolve_references() {
	set_resource_data(ESS::get_instance()->get_resource_db()->get_entity_resource(_data_id));
}

Dictionary EntityResource::to_dict() {
	return call("_to_dict");
}
void EntityResource::from_dict(const Dictionary &dict) {
	call("_from_dict", dict);
}

Dictionary EntityResource::_to_dict() {
	Dictionary dict;

	dict["dirty"] = _dirty;
	dict["should_process"] = _should_process;

	dict["data_id"] = _data_id;
	dict["current"] = _current;

	dict["max"] = _max;

	return dict;
}
void EntityResource::_from_dict(const Dictionary &dict) {
	ERR_FAIL_COND(dict.empty());

	_dirty = dict.get("dirty", false);
	_should_process = dict.get("should_process", false);
	_data_id = dict.get("data_id", 0);
	_current = dict.get("current", 0);
	_max = dict.get("max", 0);
}

EntityResource::EntityResource() {
	_server_side = false;
	_dirty = false;

	_should_process = has_method("_process");

	_data_id = 0;
	_current = 0;
	_max = 0;
}

EntityResource::~EntityResource() {
	_data.unref();
}

void EntityResource::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_dirty"), &EntityResource::get_dirty);
	ClassDB::bind_method(D_METHOD("set_dirty", "value"), &EntityResource::set_dirty);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "dirty"), "set_dirty", "get_dirty");

	ClassDB::bind_method(D_METHOD("get_should_process"), &EntityResource::get_should_process);
	ClassDB::bind_method(D_METHOD("set_should_process", "value"), &EntityResource::set_should_process);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "should_process"), "set_should_process", "get_should_process");

	ClassDB::bind_method(D_METHOD("get_resource_data"), &EntityResource::get_resource_data);
	ClassDB::bind_method(D_METHOD("set_resource_data", "value"), &EntityResource::set_resource_data);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "resource_data", PROPERTY_HINT_RESOURCE_TYPE, "EntityResourceData"), "set_resource_data", "get_resource_data");

	ClassDB::bind_method(D_METHOD("get_data_id"), &EntityResource::get_data_id);
	ClassDB::bind_method(D_METHOD("set_data_id", "value"), &EntityResource::set_data_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "data_id"), "set_data_id", "get_data_id");

	ClassDB::bind_method(D_METHOD("get_current_value"), &EntityResource::get_current_value);
	ClassDB::bind_method(D_METHOD("set_current_value", "value"), &EntityResource::set_current_value);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "current_value"), "set_current_value", "get_current_value");

	ClassDB::bind_method(D_METHOD("get_max_value"), &EntityResource::get_max_value);
	ClassDB::bind_method(D_METHOD("set_max_value", "value"), &EntityResource::set_max_value);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "max_value"), "set_max_value", "get_max_value");

	ClassDB::bind_method(D_METHOD("get_owner"), &EntityResource::get_owner);
	ClassDB::bind_method(D_METHOD("set_owner", "value"), &EntityResource::set_owner_bind);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "owner", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), "set_owner", "get_owner");

	BIND_VMETHOD(MethodInfo("_ons_stat_changed", PropertyInfo(Variant::OBJECT, "stat", PROPERTY_HINT_RESOURCE_TYPE, "Stat")));
	BIND_VMETHOD(MethodInfo("_onc_stat_changed", PropertyInfo(Variant::OBJECT, "stat", PROPERTY_HINT_RESOURCE_TYPE, "Stat")));

	BIND_VMETHOD(MethodInfo("_ons_target_changed", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "old_target", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));
	BIND_VMETHOD(MethodInfo("_onc_target_changed", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), PropertyInfo(Variant::OBJECT, "old_target", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));

	BIND_VMETHOD(MethodInfo("_ons_added", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));
	BIND_VMETHOD(MethodInfo("_onc_added", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));

	BIND_VMETHOD(MethodInfo("_process_server", PropertyInfo(Variant::REAL, "delta")));
	BIND_VMETHOD(MethodInfo("_process_client", PropertyInfo(Variant::REAL, "delta")));

	ClassDB::bind_method(D_METHOD("process_server", "delta"), &EntityResource::process_server);
	ClassDB::bind_method(D_METHOD("_process_server", "delta"), &EntityResource::_process_server);

	ClassDB::bind_method(D_METHOD("process_client", "delta"), &EntityResource::process_client);
	ClassDB::bind_method(D_METHOD("_process_client", "delta"), &EntityResource::_process_client);

	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::STRING, "str"), "_gets_update_string"));
	BIND_VMETHOD(MethodInfo("_receivec_update_string", PropertyInfo(Variant::STRING, "str")));

	ADD_SIGNAL(MethodInfo("changed", PropertyInfo(Variant::OBJECT, "resource", PROPERTY_HINT_RESOURCE_TYPE, "EntityResource")));

	//Serialization
	BIND_VMETHOD(MethodInfo("_from_dict", PropertyInfo(Variant::DICTIONARY, "dict")));
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::DICTIONARY, "dict"), "_to_dict"));

	ClassDB::bind_method(D_METHOD("from_dict", "dict"), &EntityResource::from_dict);
	ClassDB::bind_method(D_METHOD("to_dict"), &EntityResource::to_dict);

	ClassDB::bind_method(D_METHOD("_from_dict", "dict"), &EntityResource::_from_dict);
	ClassDB::bind_method(D_METHOD("_to_dict"), &EntityResource::_to_dict);
}
