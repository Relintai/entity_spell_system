#include "entity_resource.h"

#include "entity.h"
#include "stats/stat.h"

bool EntityResource::get_dirty() {
	return _dirty;
}
void EntityResource::set_dirty(bool value) {
	_dirty = value;
}

bool EntityResource::get_should_process() {
	return _should_process;
}
void EntityResource::set_should_process(bool value) {
	_should_process = value;
}

int EntityResource::get_resource_type() {
	return _type;
}
void EntityResource::set_resource_type(int value) {
	_type = value;

	emit_signal("changed", Ref<EntityResource>(this));
}

int EntityResource::get_current() {
	return _current;
}
void EntityResource::set_current(int value) {
	_current = value;

	emit_signal("changed", Ref<EntityResource>(this));
}

int EntityResource::get_max() {
	return _max;
}
void EntityResource::set_max(int value) {
	_max = value;

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

void EntityResource::ons_target_changed(Entity *entity) {
	if (has_method("_ons_target_changed"))
		call("_ons_target_changed", entity);
}
void EntityResource::onc_target_changed(Entity *entity) {
	if (has_method("_ons_target_changed"))
		call("_ons_target_changed", entity);
}

void EntityResource::process(float delta) {
	call("_process", delta);
}

void EntityResource::_process(float delta) {
}

String EntityResource::gets_update_string() {
	if (has_method("_gets_update_string"))
		return call("_gets_update_string");

	return "";
}
void EntityResource::receivec_update_string(String str) {
	if (has_method("_receivec_update_string"))
		call("_receivec_update_string", str);
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

	dict["type"] = _type;
	dict["current"] = _current;

	dict["max"] = _max;

	return dict;
}
void EntityResource::_from_dict(const Dictionary &dict) {
	ERR_FAIL_COND(dict.empty());
}

EntityResource::EntityResource() {
	_dirty = false;

	_should_process = has_method("_process");

	_type = 0;
	_current = 0;
	_max = 0;
}

void EntityResource::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_dirty"), &EntityResource::get_dirty);
	ClassDB::bind_method(D_METHOD("set_dirty", "value"), &EntityResource::set_dirty);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "dirty"), "set_dirty", "get_dirty");

	ClassDB::bind_method(D_METHOD("get_should_process"), &EntityResource::get_should_process);
	ClassDB::bind_method(D_METHOD("set_should_process", "value"), &EntityResource::set_should_process);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "should_process"), "set_should_process", "get_should_process");

	ClassDB::bind_method(D_METHOD("get_resource_type"), &EntityResource::get_resource_type);
	ClassDB::bind_method(D_METHOD("set_resource_type", "value"), &EntityResource::set_resource_type);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "resource_type"), "set_resource_type", "get_resource_type");

	ClassDB::bind_method(D_METHOD("get_current"), &EntityResource::get_current);
	ClassDB::bind_method(D_METHOD("set_current", "value"), &EntityResource::set_current);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "current"), "set_current", "get_current");

	ClassDB::bind_method(D_METHOD("get_max"), &EntityResource::get_max);
	ClassDB::bind_method(D_METHOD("set_max", "value"), &EntityResource::set_max);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "max"), "set_max", "get_max");

	ClassDB::bind_method(D_METHOD("get_owner"), &EntityResource::get_owner);
	ClassDB::bind_method(D_METHOD("set_owner", "value"), &EntityResource::set_owner_bind);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "owner", PROPERTY_HINT_RESOURCE_TYPE, "Entity"), "set_owner", "get_owner");

	BIND_VMETHOD(MethodInfo("_ons_stat_changed", PropertyInfo(Variant::OBJECT, "stat", PROPERTY_HINT_RESOURCE_TYPE, "Stat")));
	BIND_VMETHOD(MethodInfo("_onc_stat_changed", PropertyInfo(Variant::OBJECT, "stat", PROPERTY_HINT_RESOURCE_TYPE, "Stat")));

	BIND_VMETHOD(MethodInfo("_ons_target_changed", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));
	BIND_VMETHOD(MethodInfo("_onc_target_changed", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));

	BIND_VMETHOD(MethodInfo("_ons_added", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));
	BIND_VMETHOD(MethodInfo("_onc_added", PropertyInfo(Variant::OBJECT, "entity", PROPERTY_HINT_RESOURCE_TYPE, "Entity")));

	BIND_VMETHOD(MethodInfo("_process", PropertyInfo(Variant::REAL, "delta")));

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
